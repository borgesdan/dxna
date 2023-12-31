#ifndef DXNA_GRAPHICS_EFFECT_HPP
#define DXNA_GRAPHICS_EFFECT_HPP

#include "graphicsresource.hpp"
#include "constbuffer.hpp"

namespace dxna::graphics {

	//--------------------------------------------------------------------------------//
	//								EffectAnnotation								  //
	//--------------------------------------------------------------------------------//

	class EffectAnnotation {
	public:
		constexpr EffectAnnotation() = default;

		constexpr EffectAnnotation(EffectParameterClass const& class_,
			EffectParameterType const& type, std::string const& name,
			intcs rowCount, intcs columnCount, std::string const& semantic) :
			ParameterClass(class_), ParameterType(type), Name(name),
			RowCount(rowCount), ColumnCount(columnCount), Semantic(semantic) {
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
		EffectAnnotationCollection() = default;

		EffectAnnotationCollection(vectorptr<EffectAnnotationPtr> const& annotations) :
			_annotations(annotations) {
		}

		constexpr size_t Count() { return _annotations->size(); }

		EffectAnnotationPtr At(size_t index) { return _annotations->at(index); }

		EffectAnnotationPtr operator[](size_t index) { return _annotations->at(index); }

		EffectAnnotationPtr operator[](std::string const& name) {
			for (size_t i = 0; i < _annotations->size(); ++i) {
				auto a = _annotations->at(i);

				if (a->Name == name)
					return a;
			}

			return nullptr;
		}

		vectorptr<EffectAnnotationPtr> _annotations;
	};

	//--------------------------------------------------------------------------------//
	//								EffectParameter									  //
	//--------------------------------------------------------------------------------//

	class EffectParameter {
	public:
		EffectParameter() = default;

		EffectParameter(
			EffectParameterClass class_,
			EffectParameterType type,
			std::string name,
			intcs rowCount,
			intcs columnCount,
			std::string semantic,
			EffectAnnotationCollectionPtr const& annotations,
			EffectParameterCollectionPtr const& elements,
			EffectParameterCollectionPtr const& structMembers,
			anyptr const& data) :
			ParameterClass(class_), ParameterType(type), Name(name),
			RowCount(rowCount), ColumnCount(columnCount), Semantic(semantic),
			Annotations(annotations), Elements(elements), StructureMembers(structMembers),
			Data(data), StateKey(NextStateKey++) {
		}

		static ulongcs NextStateKey;

		std::string Name;
		std::string Semantic;
		EffectParameterClass ParameterClass{ EffectParameterClass::Scalar };
		EffectParameterType ParameterType{ EffectParameterType::Void };
		intcs RowCount{ 0 };
		intcs ColumnCount{ 0 };
		EffectParameterCollectionPtr Elements;
		EffectParameterCollectionPtr StructureMembers;
		EffectAnnotationCollectionPtr Annotations;
		//Representa um object
		anyptr Data;
		ulongcs StateKey{ 0 };
	};
	
	class EffectParameterCollection {
	public:
		EffectParameterCollection() = default;

		EffectParameterCollection(vectorptr<EffectParameterPtr> const& parameters) :
			_parameters(parameters) {
			_indexLookup = New<std::map<std::string, intcs>>();

			for (size_t i = 0; i < _parameters->size(); ++i) {
				const auto name = &_parameters->at(i)->Name;

				if (name->empty())
					_indexLookup->emplace(*name, static_cast<intcs>(i));
			}
		}

		constexpr size_t Count() { return _parameters->size(); }

		EffectParameterPtr At(size_t index) { return _parameters->at(index); }

		EffectParameterPtr operator[](size_t index) { return _parameters->at(index); }

		EffectParameterPtr operator[](std::string const& name) {
			const auto contains = _indexLookup->contains(name);

			if (contains) {
				const auto index = _indexLookup->at(name);
				return _parameters->at(index);
			}

			return nullptr;
		}

		mapptr<std::string, intcs> _indexLookup;
		vectorptr<EffectParameterPtr> _parameters;
	};

	//--------------------------------------------------------------------------------//
	//								EffectPass										  //
	//--------------------------------------------------------------------------------//

	class EffectPass {
	public:
		EffectPass() = default;

		EffectPass(
			EffectPtr const& effect,
			std::string const& name,
			ShaderPtr const& vertexShader,
			ShaderPtr const& pixelShader,
			BlendStatePtr const& blendState,
			DepthStencilStatePtr const& depthStencilState,
			RasterizerStatePtr const& rasterizerState,
			EffectAnnotationCollectionPtr const& annotations) :
			_effect(effect), Name(name), _vertexShader(vertexShader),
			_pixelShader(pixelShader), _blendState(blendState),
			_depthStencilState(depthStencilState), _rasterizerState(rasterizerState),
			Annotations(annotations) {
		}

		//TODO
		void Apply();

		EffectPtr _effect;
		ShaderPtr _pixelShader;
		ShaderPtr _vertexShader;
		BlendStatePtr _blendState;
		DepthStencilStatePtr _depthStencilState;
		RasterizerStatePtr _rasterizerState;
		std::string Name;
		EffectAnnotationCollectionPtr Annotations;

	private:
		//TODO
		void SetShaderSamplers(ShaderPtr const& shader, TextureCollectionPtr const& textures, SamplerStateCollection const& samplerStates);
	};

	class EffectPassCollection {
	public:
		EffectPassCollection() = default;

		EffectPassCollection(vectorptr<EffectPassPtr> const& passes) :
			_passes(passes) {
		}

		constexpr size_t Count() { return _passes->size(); }

		EffectPassPtr At(size_t index) { return _passes->at(index); }

		EffectPassPtr operator[](size_t index) { return _passes->at(index); }

		EffectPassPtr operator[](std::string const& name) {
			for (size_t i = 0; i < _passes->size(); ++i) {
				auto a = _passes->at(i);

				if (a->Name == name)
					return a;
			}

			return nullptr;
		}

		vectorptr<EffectPassPtr> _passes;
	};

	//--------------------------------------------------------------------------------//
	//								EffectTechnique									  //
	//--------------------------------------------------------------------------------//

	class EffectTechnique {
	public:
		EffectTechnique() = default;

		EffectTechnique(
			std::string const& name,
			EffectPassCollectionPtr const& passes,
			EffectAnnotationCollectionPtr const& annotations) :
		Passes(passes), Annotations(annotations), Name(name){
		}

		EffectPassCollectionPtr Passes;
		EffectAnnotationCollectionPtr Annotations;
		std::string Name;
	};

	class EffectTechniqueCollection {
	public:
		EffectTechniqueCollection() = default;

		EffectTechniqueCollection(vectorptr<EffectTechniquePtr> const& techniques) :
			_techniques(techniques) {
		}

		constexpr size_t Count() { return _techniques->size(); }

		EffectTechniquePtr At(size_t index) { return _techniques->at(index); }

		EffectTechniquePtr operator[](size_t index) { return _techniques->at(index); }

		EffectTechniquePtr operator[](std::string const& name) {
			for (size_t i = 0; i < _techniques->size(); ++i) {
				auto a = _techniques->at(i);

				if (a->Name == name)
					return a;
			}

			return nullptr;
		}

		vectorptr<EffectTechniquePtr> _techniques;
	};

	//--------------------------------------------------------------------------------//
	//								Effect											  //
	//--------------------------------------------------------------------------------//

	class Effect : public GraphicsResource, public std::enable_shared_from_this<Effect> {
	public:
		struct MGFXHeader {
			static constexpr intcs MGFXSignature() { return cs::BitConveter::IsLittleEndian() ? 0x5846474D : 0x4D474658; }
			static constexpr intcs MGFXVersion = 10;

			intcs Signature{ 0 };
			intcs Version{ 0 };
			intcs Profile{ 0 };
			intcs EffectKey{ 0 };
			intcs HeaderSize{ 0 };
		};

		Effect(GraphicsDevicePtr const& graphicsDevice,
			vectorptr<bytecs> const& effectCode,
			intcs index, intcs count);

		virtual void GraphicsDeviceResetting() override {
			for (size_t i = 0; i < ConstantBuffers->size(); i++)
				ConstantBuffers->at(i)->Clear();
		}

	protected:
		virtual void OnApply(){}

	private:
		MGFXHeader ReadHeader(vectorptr<bytecs> const& effectCode, intcs index) {
			return MGFXHeader();
		}

		void ReadEffect(cs::BinaryReader& sreader);

		static EffectAnnotationCollectionPtr ReadAnnotations(cs::BinaryReader& reader);

		static EffectPassCollectionPtr ReadPasses(cs::BinaryReader& reader, EffectPtr const& effect, vectorptr<ShaderPtr> const& shaders);

		static EffectParameterCollectionPtr ReadParameters(cs::BinaryReader& reader);

		//Campos p�blicos
	public:
		EffectParameterCollectionPtr Parameters = nullptr;
		EffectTechniqueCollectionPtr Techniques = nullptr;
		EffectTechniquePtr CurrentTechnique = nullptr;
		vectorptr<ConstantBufferPtr> ConstantBuffers = nullptr;		

	private:
		vectorptr<ShaderPtr> _shaders;
	};
}

#endif