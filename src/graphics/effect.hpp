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
#include "../types.hpp"
#include "forward.hpp"
#include "texture.hpp"

namespace dxna::graphics {
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

	class EffectParameter {
	public:
		constexpr EffectParameter(
			EffectParameterClass const& class_,
			EffectParameterType type,
			std::string const& name,
			intcs rowCount,
			intcs columnCount,
			std::string const& semantic,
			EffectAnnotationCollectionPtr const& annotations,
			EffectParameterCollectionPtr const& elements,
			EffectParameterCollectionPtr const& structMembers,
			anyptr const& data) {
			//TODO: implementar
		}

		//TODO: implementar
		virtual std::string GetDataValueString() { return std::string(); }
		virtual bool GetValueBoolean() { return false; }
		virtual intcs GetValueInt32() { return 0; }
		virtual std::vector<intcs> GetValueInt32Array() { return std::vector<intcs>(); }
		virtual Matrix GetValueMatrix() { return Matrix(); }
		virtual std::vector<Matrix> GetValueMatrixArray() { return std::vector<Matrix>(); }
		virtual Quaternion GetValueQuaternion() { return Quaternion(); }
		virtual float GetValueSingle() { return 0; }
		virtual std::vector<float> GetValueSingleArray() { return std::vector<float>(); }
		virtual std::string GetValueString() { return std::string(); }
		virtual std::shared_ptr<Texture2D> GetValueTexture2D() { return New<Texture2D>(); }
		virtual std::shared_ptr<Texture3D> GetValueTexture3D() { return New<Texture3D>(); }
		virtual std::shared_ptr<TextureCube> GetValueTextureCube() { return New<TextureCube>(); }
		virtual Vector2 GetValueVector2() { return Vector2(); }
		virtual std::vector<Vector2> GetValueVector2Array() { return std::vector<Vector2>(); }
		virtual Vector3 GetValueVector3() { return Vector3(); }
		virtual std::vector<Vector3> GetValueVector3Array() { return std::vector<Vector3>(); }
		virtual Vector4 GetValueVector4() { return Vector4(); }
		virtual std::vector<Vector4> GetValueVector4Array() { return std::vector<Vector4>(); }

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

		std::any Data;
	};	

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

	class EffectPass {
	public:
		EffectPass(
			EffectPtr const& effect,
			std::string const& name,
			ShaderPtr const& vertexShader,
			ShaderPtr const& pixelShader,
			BlendStatePtr const& blendState,
			DepthStencilStatePtr const& depthStencilState,
			RasterizerStatePtr const& rasterizerState,
			EffectAnnotationCollectionPtr const& annotations) :
			_effect(effect), Name(name), _pixelShader(pixelShader),
			_vertexShader(vertexShader), _blendState(blendState),
			_depthStencilState(depthStencilState), _rasterizerState(rasterizerState),
			Annotations(annotations){
		}

		std::string Name;
		EffectAnnotationCollectionPtr Annotations;

		void Apply();

	private:
		std::shared_ptr<Effect> _effect;
		std::shared_ptr<Shader> _pixelShader;
		std::shared_ptr<Shader> _vertexShader;
		std::shared_ptr<BlendState> _blendState;
		std::shared_ptr<DepthStencilState> _depthStencilState;
		std::shared_ptr<RasterizerState> _rasterizerState;
	};	

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

	class EffectTechnique {
	public:
		EffectTechnique(			
			std::string const& name,
			std::shared_ptr<EffectPassCollection> const& passes,
			std::shared_ptr<EffectAnnotationCollection> const& annotations) :
			Passes(passes), Annotations(annotations), Name(name) {}

		std::shared_ptr<EffectPassCollection> Passes;
		std::shared_ptr<EffectAnnotationCollection> Annotations;
		std::string Name;
	};	

	class EffectTechniqueCollection {
	public:
		constexpr EffectTechniqueCollection() = default;

		constexpr EffectTechniqueCollection(std::vector<EffectTechniquePtr> const& techniques) :
			_techniques(techniques) {
		}

		constexpr size_t Count() const { return _techniques.size(); }

		EffectTechniquePtr At(size_t index) {
			return _techniques[index];
		}

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

	class ConstantBuffer : public GraphicsResource {
	public:
		ConstantBuffer(GraphicsDevicePtr device,
			intcs const& sizeInBytes,
			vectorptr<intcs> const& parameterIndexes,
			vectorptr<intcs> const& parameterOffsets,
			std::string const& name) {
			
			Device(device);
			_buffer = std::vector<bytecs>(sizeInBytes);
			_parameters = parameterIndexes;
			_offsets = parameterOffsets;
			_name = name;

			PlatformInitialize();
		}

		void Clear() {
			PlatformClear();
		}

		void PlatformInitialize() {
			//TODO: remover
		}
		
		void PlatformClear() {
			//TODO: remover
		}

	private:
		//void SetData(int offset, int rows, int columns, object data);

		intcs SetParameter(intcs offset, EffectParameter const& param);
		void Update(EffectParameterCollection const& parameters);

		std::vector<bytecs> _buffer;
		vectorptr<intcs> _parameters;
		vectorptr<intcs> _offsets;
		std::string _name;
		ulongcs _stateKey;
		bool _dirty;
	};	

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

	class Effect : public GraphicsResource, public std::enable_shared_from_this<Effect> {
	public:
		Effect(GraphicsDevicePtr const& graphicsDevice);
		Effect(GraphicsDevicePtr const& graphicsDevice, 
			std::vector<bytecs> const& effectCode,
			intcs index, 
			intcs count);

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

	private:
		MGFXHeader ReadHeader(std::vector<bytecs> const& effectCode, intcs index);

		void ReadEffect(cs::BinaryReader& reader);

		static EffectAnnotationCollectionPtr ReadAnnotations(cs::BinaryReader& reader);

		static EffectPassCollectionPtr ReadPasses(cs::BinaryReader& reader,
			EffectPtr const& effect, std::vector<ShaderPtr> const& shaders);

		static EffectParameterCollectionPtr ReadParameters(cs::BinaryReader& reader);

	public:
		EffectParameterCollectionPtr Parameters;
		EffectTechniqueCollectionPtr Techniques;
		EffectTechniquePtr CurrentTechnique;
		std::vector<ConstantBufferPtr> ConstantBuffers;

	private:
		std::vector<ShaderPtr> _shaders;
		bool _isClone{ true };
	};
}

#endif