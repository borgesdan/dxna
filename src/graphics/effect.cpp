#include "effect.hpp"

namespace dxna::graphics {
    void Effect::ReadEffect(cs::BinaryReader& reader) {

		ConstantBuffers.clear();
		
		const auto bufferSize = (intcs)reader.ReadInt32();		

		ConstantBuffers.resize(bufferSize);

		for (size_t c = 0; c < ConstantBuffers.size(); ++c) {
			const auto name = reader.ReadString();
			const auto sizeInBytes = (intcs)reader.ReadInt16();

			auto parameters = NewVector<intcs>((intcs)reader.ReadInt32());
			auto offsets = NewVector<intcs>(parameters->size());

			for (size_t i = 0; i < parameters->size(); ++i) {
				auto prm = parameters.get();
				auto ofs = offsets.get();

				prm->at(i) = (intcs)reader.ReadInt32();
				ofs->at(i) = (intcs)reader.ReadUInt16();
			}

			ConstantBuffers[c] = New<ConstantBuffer>(this->Device(), sizeInBytes, parameters, offsets, name);
		}

		_shaders = NewArray<Shader>((intcs)reader.ReadInt32());

		for (size_t s = 0; s < _shaders.size(); s++)
			_shaders[s] = New<Shader>(Device(), reader);

		Parameters = ReadParameters(reader);

		auto techniques = NewArray<EffectTechnique>((intcs)reader.ReadInt32());

		for (size_t t = 0; t < techniques.size(); t++) {
			const auto name = reader.ReadString();
			auto annotations = ReadAnnotations(reader);
			auto passes = ReadPasses(reader, *this, _shaders);

			techniques[t] = New<EffectTechnique>(name, passes, annotations);
		}

		Techniques = New<EffectTechniqueCollection>(techniques);
		CurrentTechnique = Techniques->At(0);
    }
}