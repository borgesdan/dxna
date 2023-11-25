#ifndef DXNA_GRAPHICS_VERTICES_HPP
#define DXNA_GRAPHICS_VERTICES_HPP

#include "graphicsresource.hpp"
#include <algorithm>

namespace dxna::graphics {

	//--------------------------------------------------------------------------------//
	//								IndexBuffer										  //
	//--------------------------------------------------------------------------------//

	class IndexBuffer : public GraphicsResource {
	protected:
		IndexBuffer(GraphicsDevicePtr const& graphicsDevice, IndexElementSize indexElementSize, intcs indexCount, BufferUsage bufferUsage, bool dynamic) :
			IndexElementSizeData(indexElementSize),
			IndexCount(indexCount),
			BufferUsageData(bufferUsage),
			_isDynamic(dynamic) {

			Device(graphicsDevice);
			PlatformConstruct(indexElementSize, indexCount);
		}

	public:
		virtual void GraphicsDeviceResetting() override {
			PlatformGraphicsDeviceResetting();
		}

		BufferUsage BufferUsageData;
		IndexElementSize IndexElementSizeData;
		intcs IndexCount;

	private:
		bool _isDynamic{ false };

		void PlatformConstruct(IndexElementSize indexElementSize, intcs indexCount) {
			//TODO
		}

		void PlatformGraphicsDeviceResetting() {
			//TODO
		}
	};

	class DynamicIndexBuffer : public IndexBuffer {
	public:
		intcs UserOffset{ 0 };
		bool IsContentLost{ false };

		DynamicIndexBuffer(GraphicsDevicePtr const& graphicsDevice, IndexElementSize indexElementSize, intcs indexCount, BufferUsage bufferUsage) :
			IndexBuffer(graphicsDevice, indexElementSize, indexCount, bufferUsage, true) {
		}
	};

	//--------------------------------------------------------------------------------//
	//								Vertices										  //
	//--------------------------------------------------------------------------------//

	struct VertexElement {
		intcs Offset{ 0 };
		VertexElementFormat Format{ 0 };
		VertexElementUsage Usage{ 0 };
		intcs UsageIndex{ 0 };

		constexpr VertexElement() {}

		constexpr VertexElement(intcs offset,
			const VertexElementFormat& format,
			const VertexElementUsage& usage,
			intcs usageIndex)
			: Offset(offset), Format(format), Usage(usage), UsageIndex(usageIndex) 
		{}

		constexpr intcs GetHashCode() const noexcept {
			auto hashCode = Offset;
			hashCode ^= (intcs)Format << 9;
			hashCode ^= (intcs)Usage << (9 + 4);
			hashCode ^= UsageIndex << (9 + 4 + 4);
			return hashCode;
		}

		constexpr bool operator==(const VertexElement& other) const noexcept {
			return Offset == other.Offset 
				&& Format == other.Format 
				&& Usage == other.Usage 
				&& UsageIndex == other.UsageIndex;
		}
	};

	class IVertexType {
		virtual VertexDeclarationPtr GetVertexDeclaration() const = 0;
	};

	struct VertexDeclarationData {
		VertexDeclarationData() = default;

		VertexDeclarationData(intcs vertexStride, vectorptr<VertexElement> elements) :
			VertexStride(vertexStride), Elements(elements), HashCode(getHashCode()) {
		}		

		constexpr intcs GetHashCode() const noexcept {
			return HashCode;
		}

		constexpr bool Equals(VertexDeclarationData const& other) const noexcept {
			return HashCode != other.HashCode
				|| VertexStride != other.VertexStride
				|| Elements != other.Elements
				|| Elements != nullptr && other.Elements != nullptr
				|| Elements->size() != other.Elements->size();
			
			//TODO: Será realmente necessário checar elemento por elemento?
		}

		constexpr bool operator==(const VertexDeclarationData& other) const noexcept {
			return Equals(other);
		}

	public:
		intcs VertexStride{ 0 };
		vectorptr<VertexElement> Elements = nullptr;
		intcs HashCode{ 0 };

		intcs getHashCode() const {
			auto _hashCode = Elements->at(0).GetHashCode();

			for (size_t i = 1; i < Elements->size(); ++i)
				_hashCode = (_hashCode * 397) ^ Elements->at(i).GetHashCode();

			_hashCode = (_hashCode * 397) ^ Elements->size();
			_hashCode = (_hashCode * 397) ^ VertexStride;

			return _hashCode;
		}
	};

	struct VertexDeclarationDataCompare final {
		constexpr bool operator()(VertexDeclarationData const& a, VertexDeclarationData const& b) const noexcept {
			return a == b;
		}
	};

	class VertexDeclaration : public std::enable_shared_from_this<VertexDeclaration> {
	public:		
		VertexDeclaration(vectorptr<VertexElement> const& elements) :
			VertexDeclaration(GetVertexStride(elements), elements) {
		}

		VertexDeclaration(intcs vertexStride, vectorptr<VertexElement> const& elements);

		VertexDeclaration(VertexDeclarationData const& data) : _data(data) {
		}

		void Construct(intcs vertexStride, vectorptr<VertexElement> const& elements) {
			if (elements == nullptr || elements->empty())
				return; //TODO: lançar exceção?

			auto data = VertexDeclarationData(vertexStride, elements);

			if (_vertexDeclarationCache.contains(data)) {
				auto& vertexDeclaration = _vertexDeclarationCache[data];
				_data = vertexDeclaration->_data;
			}
			else {
				//TODO: deixar o array imutável?
				data.Elements = NewVector<VertexElement>(elements->size());
				std::copy(data.Elements->begin(), data.Elements->end(), elements->begin());

				_data.Elements = elements;
				_vertexDeclarationCache[data] = this->shared_from_this();
			}
		}

		static VertexDeclarationPtr GetOrCreate(intcs vertexStride, vectorptr<VertexElement> const& elements);

		vectorptr<VertexElement> InternalVertexElements() const noexcept {
			return _data.Elements;
		}

		vectorptr<VertexElement> GetVertexElements() const {
			auto clone = NewVector<VertexElement>(_data.Elements->size());

			std::copy(_data.Elements->begin(), _data.Elements->end(), clone->begin());

			return clone;
		}

		constexpr int VertexStride() const noexcept {
			return _data.VertexStride;
		}

		template <typename T>
		static VertexDeclarationPtr FromType() {
			auto vertex = New<T>();
			return vertex->GetVertexDeclaration();
		}

	private:
		VertexDeclarationData _data;

		static intcs GetVertexStride(vectorptr<VertexElement> const& elements) noexcept {
			intcs max = 0;

			if (elements == nullptr)
				return 0;

			for (size_t i = 0; i < elements->size(); ++i) {
				const auto el = &elements->at(i);
				auto start = el->Offset + GetSize(el->Format);

				if (max < start)
					max = start;
			}

			return max;
		}

		static std::map<VertexDeclarationData, VertexDeclarationPtr, VertexDeclarationDataCompare> _vertexDeclarationCache;
	};

	struct VertexBufferBinding {
		VertexBufferPtr Buffer = nullptr;
		size_t VertexOffset{ 0 };
		size_t InstanceFrequency{ 0 };

		VertexBufferBinding(
			const VertexBufferPtr& VertexBuffer,
			const size_t& VertexOffset,
			const size_t& InstanceFrequency) noexcept
			: Buffer(VertexBuffer),
			VertexOffset(VertexOffset),
			InstanceFrequency(InstanceFrequency) {}

		constexpr VertexBufferBinding() noexcept = default;
	};

	class VertexInputLayout {
	public:
		VertexInputLayout(
			vectorptr<VertexDeclarationPtr> const& vertexDeclarations,
			vectorptr<intcs> const& instanceFrequencies,
			intcs count) 
			: _count(count),
			Declarations(vertexDeclarations),
			InstanceFrequencies(instanceFrequencies) {
		}

		constexpr intcs Count() const noexcept {
			return _count;
		}

	protected:
		vectorptr<VertexDeclarationPtr> Declarations = nullptr;
		vectorptr<intcs> InstanceFrequencies = nullptr;
		intcs _count{ 0 };
	};

	class VertexBuffer : public GraphicsResource {
	public:
		VertexBuffer(
			GraphicsDevicePtr const& graphicsDevice,
			VertexDeclarationPtr const& vertexDeclaration,
			intcs vertexCount,
			BufferUsage bufferUsage)
			: VertexBuffer(
				graphicsDevice,
				vertexDeclaration,
				vertexCount,
				bufferUsage,
				false) {}		

		constexpr intcs VertexCount() const noexcept { return _vertexCount; }

	protected:
		VertexBuffer(
			GraphicsDevicePtr const& graphicsDevice,
			VertexDeclarationPtr const& vertexDeclaration,
			intcs vertexCount,
			BufferUsage bufferUsage,
			bool dynamic)
			: Declaration(vertexDeclaration),
			_vertexCount(vertexCount),
			Buffer(bufferUsage),
			_isDynamic(dynamic) {

			if (graphicsDevice == nullptr)
				return;

			Device(graphicsDevice);

			//VertexDeclaration não é um GraphicsResource
			PlatformConstruct();
		}

		virtual void GraphicsDeviceResetting() override {
			PlatformGraphicsDeviceResetting();
		}	

	public:
		VertexDeclarationPtr Declaration = nullptr;
		BufferUsage Buffer{ 0 };

	private:
		bool _isDynamic{ false };
		intcs _vertexCount{ 0 };

		void PlatformConstruct() {
			//TODO: remover
		}

		void PlatformGraphicsDeviceResetting() {
			//TODO: remover
		}
	};

	class VertexBufferBindings : public VertexInputLayout {
	public:
		VertexBufferBindings(intcs maxVertexBufferSlots) :
			VertexInputLayout(
				NewVector<VertexDeclarationPtr>(maxVertexBufferSlots),
				NewVector<intcs>(maxVertexBufferSlots), 0),
			_vertexBuffers(NewVector<VertexBufferPtr>(maxVertexBufferSlots)),
			_vertexOffsets(NewVector<intcs>(maxVertexBufferSlots)) {
		}

		bool Clear() {
			if (_count == 0)
				return false;

			for (size_t i = 0; i < _count; ++i) {
				Declarations->at(i) = nullptr;
				InstanceFrequencies->at(i) = 0;
				_vertexBuffers->at(i) = nullptr;
				_vertexOffsets->at(i) = 0;
			}
		}

		bool Clear(size_t startIndex, size_t length) {
			if (_count == 0)
				return false;

			for (size_t i = startIndex; i < length; ++i) {
				Declarations->at(i) = nullptr;
				InstanceFrequencies->at(i) = 0;
				_vertexBuffers->at(i) = nullptr;
				_vertexOffsets->at(i) = 0;
			}
		}

		bool Set(VertexBufferPtr const& vertexBuffer, intcs vertexOffset) {
			if (_count == 1
				&& InstanceFrequencies->at(0) == 0
				&& _vertexBuffers->at(0) == vertexBuffer
				&& _vertexOffsets->at(0) == vertexOffset) {
				return false;
			}

			Declarations->at(0) = vertexBuffer->Declaration;
			InstanceFrequencies->at(0) = 0;
			_vertexBuffers->at(0) = vertexBuffer;
			_vertexOffsets->at(0) = vertexOffset;

			if (_count > 1)
			{
				const auto size = _count - 1;

				Clear(1, size);
			}

			_count = 1;
			return true;
		}

		bool Set(std::vector<VertexBufferBinding> const& vertexBufferBindings) {
			bool isDirty = false;

			for (size_t i = 0; i < vertexBufferBindings.size(); i++) {
				if (InstanceFrequencies->at(i) == vertexBufferBindings[i].InstanceFrequency
					&& _vertexBuffers->at(i) == vertexBufferBindings[i].Buffer
					&& _vertexOffsets->at(i) == vertexBufferBindings[i].VertexOffset) {
					continue;
				}

				Declarations->at(i) = vertexBufferBindings[i].Buffer->Declaration;
				InstanceFrequencies->at(i) = vertexBufferBindings[i].InstanceFrequency;
				_vertexBuffers->at(i) = vertexBufferBindings[i].Buffer;
				_vertexOffsets->at(i) = vertexBufferBindings[i].VertexOffset;
				isDirty = true;
			}

			if (_count > vertexBufferBindings.size()) {
				const auto startIndex = vertexBufferBindings.size();
				const auto length = _count - startIndex;

				Clear(startIndex, length);

				isDirty = true;
			}

			_count = vertexBufferBindings.size();
			return isDirty;
		}

		VertexBufferBinding Get(intcs slot) const {
			return VertexBufferBinding(
				_vertexBuffers->at(slot),
				_vertexOffsets->at(slot),
				InstanceFrequencies->at(slot));
		}

		vectorptr<VertexBufferBinding> Get()
		{
			auto bindings = NewVector<VertexBufferBinding>(_count);
			
			for (size_t i = 0; i < bindings->size(); i++)
				bindings->at(i) = VertexBufferBinding(
					_vertexBuffers->at(i),
					_vertexOffsets->at(i),
					InstanceFrequencies->at(i));

			return bindings;
		}

	private:
		vectorptr<VertexBufferPtr> _vertexBuffers = nullptr;
		vectorptr<intcs> _vertexOffsets = nullptr;
	};

	template <class T>
	class VertexDeclarationCache {
	public:
		VertexDeclarationPtr GetVertexDeclaration() {
			if (_cached == nullptr)
				return nullptr; //TODO

			return nullptr;
		}

	private:
		static VertexDeclarationPtr _cached;
	};

	struct VertexPosition : public IVertexType {
		constexpr VertexPosition() = default;

		constexpr VertexPosition(Vector3 const& position) noexcept :
			Position(position) {}

		VertexDeclarationPtr GetVertexDeclaration() const override {
			return Declaration;
		}		

		constexpr intcs GetHashCode() const {
			return Position.GetHashCode();
		}

		Vector3 Position{};
		static const VertexDeclarationPtr Declaration;
	};

	struct VertexPositionColor : public IVertexType {
		using Color_ = Color;

		constexpr VertexPositionColor() = default;

		constexpr VertexPositionColor(Vector3 const& position, Color_ const& color) noexcept :
			Position(position), Color(color) {}

		VertexDeclarationPtr GetVertexDeclaration() const override {
			return Declaration;
		}

		constexpr intcs GetHashCode() const {
			return Position.GetHashCode()
				^ Color.GetHashCode();
		}

		Vector3 Position{};
		Color_ Color{};
		static const VertexDeclarationPtr Declaration;
	};

	struct VertexPositionColorNormal : public IVertexType {
		using Color_ = Color;

		constexpr VertexPositionColorNormal() = default;

		constexpr VertexPositionColorNormal(
			Vector3 const& position,
			Color_ const& color,
			Vector3 const& normal) noexcept :
			Position(position), Color(color), Normal(normal) {}

		VertexDeclarationPtr GetVertexDeclaration() const override {
			return Declaration;
		}

		constexpr intcs GetHashCode() const {
			return Position.GetHashCode()
				^ Color.GetHashCode()
				^ Normal.GetHashCode();
		}

		Vector3 Position{};
		Vector3 Normal{};
		Color_ Color{};
		static const VertexDeclarationPtr Declaration;
	};

	struct VertexPositionColorNormalTexture : public IVertexType {
		using Color_ = Color;

		constexpr VertexPositionColorNormalTexture() = default;

		constexpr VertexPositionColorNormalTexture(
			Vector3 const& position,
			Color_ const& color,
			Vector3 const& normal,
			Vector2 const& textureCoordinate) noexcept :
			Position(position), Color(color), Normal(normal), TextureCoordinate(textureCoordinate){}

		VertexDeclarationPtr GetVertexDeclaration() const override {
			return Declaration;
		}

		constexpr intcs GetHashCode() const {
			return Position.GetHashCode()
				^ Color.GetHashCode()
				^ Normal.GetHashCode()
				^ TextureCoordinate.GetHashCode();
		}

		Vector3 Position{};
		Vector3 Normal{};
		Color_ Color{};
		Vector2 TextureCoordinate;
		static const VertexDeclarationPtr Declaration;
	};

	struct VertexPositionColorTexture : public IVertexType {
		using Color_ = Color;

		constexpr VertexPositionColorTexture() = default;

		constexpr VertexPositionColorTexture(
			Vector3 const& position,
			Color_ const& color,
			Vector2 const& textureCoordinate) noexcept :
			Position(position), Color(color), TextureCoordinate(textureCoordinate) {}

		VertexDeclarationPtr GetVertexDeclaration() const override {
			return Declaration;
		}

		constexpr intcs GetHashCode() const {
			return Position.GetHashCode()
				^ Color.GetHashCode()
				^ TextureCoordinate.GetHashCode();
		}

		Vector3 Position{};		
		Color_ Color{};
		Vector2 TextureCoordinate;
		static const VertexDeclarationPtr Declaration;
	};

	struct VertexPositionNormalTexture : public IVertexType {
		constexpr VertexPositionNormalTexture() = default;

		constexpr VertexPositionNormalTexture(
			Vector3 const& position,	
			Vector3 const& normal,
			Vector2 const& textureCoordinate) noexcept :
			Position(position), TextureCoordinate(textureCoordinate), Normal(normal) {}

		VertexDeclarationPtr GetVertexDeclaration() const override {
			return Declaration;
		}

		constexpr intcs GetHashCode() const {
			return Position.GetHashCode()
				^ Normal.GetHashCode()
				^ TextureCoordinate.GetHashCode();
		}

		Vector3 Position{};
		Vector3 Normal{};
		Vector2 TextureCoordinate;
		static const VertexDeclarationPtr Declaration;
	};

	struct VertexPositionTexture : public IVertexType {
		constexpr VertexPositionTexture() = default;

		constexpr VertexPositionTexture(
			Vector3 const& position,
			Vector2 const& textureCoordinate) noexcept :
			Position(position), TextureCoordinate(textureCoordinate) {}

		VertexDeclarationPtr GetVertexDeclaration() const override {
			return Declaration;
		}

		constexpr intcs GetHashCode() const {
			return Position.GetHashCode() ^ TextureCoordinate.GetHashCode();
		}

		Vector3 Position{};
		Vector2 TextureCoordinate;
		static const VertexDeclarationPtr Declaration;
	};
}

#endif