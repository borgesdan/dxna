#include "effect.hpp"

namespace dxna::graphics {
    void Effect::ReadEffect(cs::BinaryReader& reader) {

		ConstantBuffers.clear();
		
		const auto bufferSize = (intcs)reader.ReadInt32();		

		ConstantBuffers.resize(bufferSize);

		for (size_t c = 0; c < ConstantBuffers.size(); ++c) {
			const auto name = reader.ReadString();
			const auto sizeInBytes = (intcs)reader.ReadInt16();

			auto parameters = NewVectorPtr<intcs>((intcs)reader.ReadInt32());
			auto offsets = NewVectorPtr<intcs>(parameters->size());

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
			auto passes = ReadPasses(reader, this->shared_from_this(), _shaders);

			techniques[t] = New<EffectTechnique>(name, passes, annotations);
		}

		Techniques = New<EffectTechniqueCollection>(techniques);
		CurrentTechnique = Techniques->At(0);
    }

	EffectAnnotationCollectionPtr Effect::ReadAnnotations(cs::BinaryReader& reader) {
		const auto count = reader.ReadInt32();

		if (count == 0)
			return New<EffectAnnotationCollection>();

		const auto annotations = NewArray<EffectAnnotation>(count);

		return New<EffectAnnotationCollection>(annotations);
	}
	
	EffectPassCollectionPtr Effect::ReadPasses(cs::BinaryReader& reader, EffectPtr const& effect, std::vector<ShaderPtr> const& shaders) {
		const auto passCount = (intcs)reader.ReadInt32();
		auto passes = NewArray<EffectPass>(passCount);

		for (size_t i = 0; i < passes.size(); ++i) {
			const auto name = reader.ReadString();
			auto annotations = ReadAnnotations(reader);

			const auto shaderIndex = (intcs)reader.ReadInt32();
			ShaderPtr vertexShader = shaderIndex < 0 ? nullptr : shaders[shaderIndex];

			const auto pixelIndex = (intcs)reader.ReadInt32();
			ShaderPtr pixelShader = pixelIndex < 0 ? nullptr : shaders[shaderIndex];

			BlendStatePtr blend = nullptr;
			DepthStencilStatePtr depth = nullptr;
			RasterizerStatePtr raster = nullptr;

			if (reader.ReadBoolean()) {
				blend = New<BlendState>();
				blend->AlphaBlendFunction((BlendFunction)(bytecs)reader.ReadByte());
				blend->AlphaDestinationBlend((Blend)(bytecs)reader.ReadByte());
				blend->AlphaSourceBlend((Blend)(bytecs)reader.ReadByte());
				blend->BlendFactor = Color((bytecs)reader.ReadByte(), (bytecs)reader.ReadByte(), (bytecs)reader.ReadByte(), (bytecs)reader.ReadByte());
				blend->ColorBlendFunction((BlendFunction)(bytecs)reader.ReadByte());
				blend->ColorDestinationBlend((Blend)(bytecs)reader.ReadByte());
				blend->ColorSourceBlend((Blend)(bytecs)reader.ReadByte());
				blend->ColorWriteChannels((ColorWriteChannels)(bytecs)reader.ReadByte());
				blend->ColorWriteChannels1((ColorWriteChannels)(bytecs)reader.ReadByte());
				blend->ColorWriteChannels2((ColorWriteChannels)(bytecs)reader.ReadByte());
				blend->ColorWriteChannels3((ColorWriteChannels)(bytecs)reader.ReadByte());
				blend->MultiSampleMask = reader.ReadInt32();
			}

			if (reader.ReadBoolean()) {
				depth = New<DepthStencilState>();
				depth->CounterClockwiseStencilDepthBufferFail = (StencilOperation)(bytecs)reader.ReadByte();
				depth->CounterClockwiseStencilFail = (StencilOperation)(bytecs)reader.ReadByte();
				depth->CounterClockwiseStencilFunction = (CompareFunction)(bytecs)reader.ReadByte();
				depth->CounterClockwiseStencilPass = (StencilOperation)(bytecs)reader.ReadByte();
				depth->DepthBufferEnable = reader.ReadBoolean();
				depth->DepthBufferFunction = (CompareFunction)(bytecs)reader.ReadByte();
				depth->DepthBufferWriteEnable = reader.ReadBoolean();
				depth->ReferenceStencil = (intcs)reader.ReadInt32();
				depth->StencilDepthBufferFail = (StencilOperation)(bytecs)reader.ReadByte();
				depth->StencilEnable = (bool)reader.ReadBoolean();
				depth->StencilFail = (StencilOperation)(bytecs)reader.ReadByte();
				depth->StencilFunction = (CompareFunction)(bytecs)reader.ReadByte();
				depth->StencilMask = (intcs)reader.ReadInt32();
				depth->StencilPass = (StencilOperation)(bytecs)reader.ReadByte();
				depth->StencilWriteMask = (intcs)reader.ReadInt32();
				depth->TwoSidedStencilMode = (bool)reader.ReadBoolean();
			}

			if (reader.ReadBoolean()) {
				raster = New<RasterizerState>();
				raster->CullMode = (CullMode)(bytecs)reader.ReadByte();
				raster->DepthBias = (float)reader.ReadSingle();
				raster->FillMode = (FillMode)(bytecs)reader.ReadByte();
				raster->MultiSampleAntiAlias = (bool)reader.ReadBoolean();
				raster->ScissorTestEnable = (bool)reader.ReadBoolean();
				raster->SlopeScaleDepthBias = (float)reader.ReadSingle();
			}

			passes[i] = New<EffectPass>(
				effect,
				name,
				vertexShader,
				pixelShader,
				blend,
				depth,
				raster,
				annotations);
		}

		return New<EffectPassCollection>(passes);
	}
	
	EffectParameterCollectionPtr Effect::ReadParameters(cs::BinaryReader& reader) {
		const auto count = reader.ReadInt32();

		if (count == 0)
			return New<EffectParameterCollection>();

		auto parameters = NewArray<EffectParameter>(count);

		for (size_t i = 0; i < count; ++i) {
			auto class_ = (EffectParameterClass)(bytecs)reader.ReadByte();
			auto type = (EffectParameterType)(bytecs)reader.ReadByte();
			auto name = reader.ReadString();
			auto semantic = reader.ReadString();
			auto annotations = ReadAnnotations(reader);
			auto rowCount = (intcs)reader.ReadByte();
			auto columnCount = (intcs)reader.ReadByte();
			auto elements = ReadParameters(reader);
			auto structMembers = ReadParameters(reader);
			anyptr data = nullptr;

			if (elements->Count() == 0 && structMembers->Count() == 0) {

				switch (type)
				{
				case dxna::graphics::EffectParameterType::Bool:
				case dxna::graphics::EffectParameterType::Int32:
				{
					//TODO #if !OPENGL
					auto buffer = NewArray<intcs>(rowCount * columnCount);

					for (size_t j = 0; j < buffer.size(); ++j)
						buffer[j] = New<intcs>((intcs)reader.ReadInt32());

					*data.get() = buffer;
					break;
				}
				case dxna::graphics::EffectParameterType::Single:
				{
					auto buffer = NewArray<float>(rowCount * columnCount);

					for (size_t j = 0; j < buffer.size(); ++j)
						buffer[j] = New<float>((float)reader.ReadSingle());

					*data.get() = buffer;
					break;
				}
				default:
					break;
				}
			}

			parameters[i] = New<EffectParameter>(class_, type, name, rowCount,
				columnCount, semantic, annotations, elements, structMembers, data);
		}

		return New<EffectParameterCollection>(parameters);
	}
}