#ifndef DXNA_GRAPHICS_EFFECT_HPP
#define DXNA_GRAPHICS_EFFECT_HPP

#include "graphicsresource.hpp"

namespace dxna::graphics {
	class EffectParameter {
	public:
		constexpr EffectParameter() = default;

		constexpr EffectParameter(EffectParameterClass const& class_,
			EffectParameterType const& type, std::string const& name,
			intcs rowCount, intcs columnCount, std::string const& semantic) :
			ParameterClass(class_),	ParameterType(type), Name(name),
			RowCount(rowCount),	ColumnCount(columnCount), Semantic(semantic){
		}

		EffectParameterClass ParameterClass{EffectParameterClass::Scalar};
		EffectParameterType ParameterType{EffectParameterType::Void};
		std::string Name;
		intcs RowCount{0};
		intcs ColumnCount{0};
		std::string Semantic;
	};

	class EffectParameterCollection {
	public:
		EffectParameterCollection() = default;

		EffectParameterCollection(vectorptr<EffectParameter> const& parameters) :
			_parameters(parameters) {
			_indexLookup = New<std::map<std::string, intcs>>();

			for (size_t i = 0; i < _parameters->size(); ++i) {
				const auto name = &_parameters->at(i).Name;

				if (name->empty())
					_indexLookup->emplace(*name, static_cast<intcs>(i));
			}
		}

		constexpr size_t Count() { return _parameters->size(); }

		EffectParameter* At(size_t index) { return &_parameters->at(index); }

		EffectParameter* operator[](size_t index) { return &_parameters->at(index); }

		EffectParameter* operator[](std::string const& name) { 
			const auto contains = _indexLookup->contains(name);	
			
			if (contains) {
				const auto index = _indexLookup->at(name);
				return &_parameters->at(index);
			}

			return nullptr;
		}

		mapptr<std::string, intcs> _indexLookup;
		vectorptr<EffectParameter> _parameters;
	};

	class Effect : public GraphicsResource {
		struct MGFXHeader {
			static constexpr intcs MGFXSignature() { return dxna::Enviroment::IsLittleEndian() ? 0x5846474D : 0x4D474658; }
			static constexpr intcs MGFXVersion = 10;

			intcs Signature{ 0 };
			intcs Version{ 0 };
			intcs Profile{ 0 };
			intcs EffectKey{ 0 };
			intcs HeaderSize{ 0 };
		};
	};
}

#endif