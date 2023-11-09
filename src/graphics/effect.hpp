#ifndef DXNA_GRAPHICS_EFFECT_HPP
#define DXNA_GRAPHICS_EFFECT_HPP

#include <vector>
#include <memory>
#include <any>
#include "../cs/cs.hpp"
#include "../helpers.hpp"
#include "../structs.hpp"
#include "graphicsresource.hpp"
#include "enumerations.hpp"
#include "shader.hpp"
#include "states.hpp"

namespace dxna::graphics {
	class EffectParameter;
	class EffectParameterCollection;
	class Effect;
	class Texture2D;
	class Texture3D;
	class TextureCube;

	class EffectAnnotation {
	public:
		constexpr EffectAnnotation() = default;

		constexpr EffectAnnotation(
			EffectParameterClass const& class_,
			EffectParameterType const& type,
			std::string const& name,
			intcs rowCount,
			intcs columnCount,
			std::string const& semantic)
		{
			ParameterClass = class_;
			ParameterType = type;
			Name = name;
			RowCount = rowCount;
			ColumnCount = columnCount;
			Semantic = semantic;
		}

		EffectParameterClass ParameterClass{ EffectParameterClass::Scalar };
		EffectParameterType ParameterType{ EffectParameterType::Void };
		std::string Name;
		intcs RowCount{ 0 };
		intcs ColumnCount{ 0 };
		std::string Semantic;
	};

	using EffectAnnotationPtr = std::shared_ptr<EffectAnnotation>;

	class EffectAnnotationCollection {
	public:
		constexpr EffectAnnotationCollection() = default;

		constexpr EffectAnnotationCollection(std::vector<EffectAnnotationPtr> const& annotations) :
			_annotations(annotations) {
		}

		constexpr size_t Count() const { return _annotations.size(); }

		EffectAnnotationPtr operator[](size_t index) { return _annotations[index]; }

		EffectAnnotationPtr operator[](std::string name) {
			for (size_t i = 0; i < _annotations.size(); ++i) {
				if (_annotations[i]->Name == name)
					return _annotations[i];
			}

			return nullptr;
		}

		std::vector<EffectAnnotationPtr> _annotations;
	};

	using EffectAnnotationCollectionPtr = std::shared_ptr<EffectAnnotationCollection>;

	class EffectParameter {
	public:
		constexpr EffectParameter(
			EffectParameterClass const& class_,
			EffectParameterType type,
			std::string const& name,
			intcs rowCount,
			intcs columnCount,
			std::string const& semantic,
			std::shared_ptr<EffectAnnotationCollection> const& annotations,
			std::shared_ptr<EffectParameterCollection> const& elements,
			std::shared_ptr<EffectParameterCollection> const& structMembers);

		virtual std::string GetDataValueString();
		virtual bool GetValueBoolean();
		virtual intcs GetValueInt32();
		virtual std::vector<intcs> GetValueInt32Array();
		virtual Matrix GetValueMatrix();
		virtual std::vector<Matrix> GetValueMatrixArray();
		virtual Quaternion GetValueQuaternion();
		virtual float GetValueSingle();
		virtual std::vector<float> GetValueSingleArray();
		virtual std::string GetValueString();
		virtual std::shared_ptr<Texture2D> GetValueTexture2D();
		virtual std::shared_ptr<Texture3D> GetValueTexture3D();
		virtual std::shared_ptr<TextureCube> GetValueTextureCube();
		virtual Vector2 GetValueVector2();
		virtual std::vector<Vector2> GetValueVector2Array();
		virtual Vector3 GetValueVector3();
		virtual std::vector<Vector3> GetValueVector3Array();
		virtual Vector4 GetValueVector4();
		virtual std::vector<Vector4> GetValueVector4Array();

		static ulongcs NextStateKey;

		std::string Name;
		std::string Semantic;
		EffectParameterClass ParameterClass;
		EffectParameterType ParameterType;
		intcs RowCount;
		intcs ColumnCount;

		std::shared_ptr<EffectParameterCollection> Elements;
		std::shared_ptr<EffectParameterCollection> StructMembers;
		std::shared_ptr<EffectAnnotationCollection> Annotations;

		std::any Value;
	};

	using EffectParameterPtr = std::shared_ptr<EffectParameter>;

	class EffectParameterCollection {
	public:
		constexpr EffectParameterCollection() = default;

		constexpr EffectParameterCollection(std::vector<EffectParameterPtr> const& parameters) :
			_parameters(parameters) {
		}

		constexpr size_t Count() const { return _parameters.size(); }

		EffectParameterPtr operator[](size_t index) { return _parameters[index]; }

		EffectParameterPtr operator[](std::string name) {
			for (size_t i = 0; i < _parameters.size(); ++i) {
				if (_parameters[i]->Name == name)
					return _parameters[i];
			}

			return nullptr;
		}

		std::vector<EffectParameterPtr> _parameters;
	};	

	using EffectParameterCollectionPtr = std::shared_ptr<EffectParameterCollection>;

	class EffectPass {
	public:
		EffectPass(
			std::shared_ptr<Effect> effect,
			std::string const& name,
			std::shared_ptr<Shader> pixelShader,
			std::shared_ptr<Shader> vertexShader,
			std::shared_ptr<BlendState> blendState,
			std::shared_ptr<DepthStencilState> depthStencilState,
			std::shared_ptr<RasterizerState> rasterizerState) :
			_effect(effect), Name(name), _pixelShader(pixelShader),
			_vertexShader(vertexShader), _blendState(blendState),
			_depthStencilState(depthStencilState), _rasterizerState(rasterizerState) {
		}

		std::string Name;
		std::shared_ptr<EffectAnnotationCollection> Annotations;

		void Apply();

	private:
		std::shared_ptr<Effect> _effect;
		std::shared_ptr<Shader> _pixelShader;
		std::shared_ptr<Shader> _vertexShader;
		std::shared_ptr<BlendState> _blendState;
		std::shared_ptr<DepthStencilState> _depthStencilState;
		std::shared_ptr<RasterizerState> _rasterizerState;
	};

	using EffectPassPtr = std::shared_ptr<EffectPass>;

	class EffectPassCollection {
	public:
		constexpr EffectPassCollection() = default;

		constexpr EffectPassCollection(std::vector<EffectPassPtr> const& passes) :
			_passes(passes) {
		}

		constexpr size_t Count() const { return _passes.size(); }

		EffectPassPtr operator[](size_t index) { return _passes[index]; }

		EffectPassPtr operator[](std::string name) {
			for (size_t i = 0; i < _passes.size(); ++i) {
				if (_passes[i]->Name == name)
					return _passes[i];
			}

			return nullptr;
		}

		std::vector<EffectPassPtr> _passes;
	};	

	using EffectPassCollectionPtr = std::shared_ptr<EffectPassCollection>;

	class EffectTechnique {
	public:
		EffectTechnique(std::string const& name,
			std::shared_ptr<EffectPassCollection> const& passes,
			std::shared_ptr<EffectAnnotationCollection> const& annotations) :
		Passes(passes), Annotations(annotations), Name(name){}

		std::shared_ptr<EffectPassCollection> Passes;
		std::shared_ptr<EffectAnnotationCollection> Annotations;
		std::string Name;
	};
	
	using EffectTechniquePtr = std::shared_ptr<EffectTechnique>;

	class EffectTechniqueCollection {
	public:
		constexpr EffectTechniqueCollection() = default;

		constexpr EffectTechniqueCollection(std::vector<EffectTechniquePtr> const& techniques) :
			_techniques(techniques) {
		}

		constexpr size_t Count() const { return _techniques.size(); }

		EffectTechniquePtr operator[](size_t index) { return _techniques[index]; }

		EffectTechniquePtr operator[](std::string name) {
			for (size_t i = 0; i < _techniques.size(); ++i) {
				if (_techniques[i]->Name == name)
					return _techniques[i];
			}

			return nullptr;
		}

		std::vector<EffectTechniquePtr> _techniques;
	};	

	using EffectTechniqueCollectionPtr = std::shared_ptr<EffectTechniqueCollection>;

	class ConstantBuffer : public GraphicsResource {
	public:
		ConstantBuffer(GraphicsDevice_* device, intcs const& sizeInBytes,
			std::vector<intcs> const& parameterIndexes, std::vector<intcs> const& parameterOffsets,
			std::string const& name);

		void Clear();
		void PlatformInitialize() {
			//TODO: remover
		}
		void PlatformClear();

	private:
		//void SetData(int offset, int rows, int columns, object data);

		intcs SetParameter(intcs offset, EffectParameter const& param);
		void Update(EffectParameterCollection const& parameters);

		std::vector<bytecs> _buffer;
		std::vector<intcs> _parameters;
		std::vector<intcs> _offsets;
		std::string _name;
		ulongcs _stateKey;
		bool _dirty;
	};

	using ConstantBufferPtr = std::shared_ptr<ConstantBuffer>;

	class ConstantBufferCollectionSetArgs;

	class ConstantBufferCollection {
	public:
		ConstantBufferCollection(ShaderStage const& stage, intcs maxBuffers);

		ConstantBuffer* operator[](size_t index);

		void Clear();

		void SetConstanteBuffer(ConstantBufferCollectionSetArgs& arg);

	private:
		std::vector<ConstantBuffer> _buffers;
		ShaderStage _stage;
		intcs _valid;
	};	
	
	using ConstantBufferCollectionPtr = std::shared_ptr<ConstantBufferCollection>;

	class Effect : public GraphicsResource {
	public:
		Effect(GraphicsDevicePtr const& graphicsDevice);
		Effect(GraphicsDevicePtr const& graphicsDevice, std::vector<bytecs> const& effectCode, intcs index, intcs count);

		struct MGFXHeader {
			static constexpr intcs MGFXSignature() {
				return dxna::Enviroment::IsLittleEndiannes() ? 0x5846474D : 0x4D474658;
			}

			static constexpr intcs MGFXVersion = 10;

			intcs Signature;
			intcs Version;
			intcs Profile;
			intcs EffectKey;
			intcs HeaderSize;
		};

		EffectParameterCollectionPtr Parameters;
		EffectTechniqueCollectionPtr Techniques;
		EffectTechniquePtr CurrentTechnique;
		std::vector<ConstantBufferPtr> ConstantBuffers;
	
	protected:

	private:
		MGFXHeader ReadHeader(std::vector<bytecs> const& effectCode, intcs index);
		void ReadEffect(cs::BinaryReaderPtr const& reader);
		
		static EffectAnnotationCollectionPtr ReadAnnotations(cs::BinaryReader& reader);
		static EffectPassCollection ReadPasses(cs::BinaryReader& reader,
			Effect const& effect, std::vector<Shader> const& shaders);
		static EffectParameterCollection ReadParameters(cs::BinaryReader& reader);

		std::vector<ShaderPtr> _shaders;
		bool _isClone{ true };
	};	
}

#endif