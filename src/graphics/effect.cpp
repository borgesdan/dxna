#include "effect.hpp"
#include "states.hpp"

using namespace cs;

namespace dxna::graphics {
	ulongcs EffectParameter::NextStateKey = 0;

	EffectParameterCollectionPtr Effect::ReadParameters(cs::BinaryReader& reader) {
		const auto count = (intcs)reader.ReadInt32();

		if (count == 0)
			return New<EffectParameterCollection>();

		auto parameters = NewVector<EffectParameter>(count);

		for (size_t i = 0; i < count; ++i) {
			const auto class_ = (EffectParameterClass)reader.ReadByte().Value();
			const auto type = (EffectParameterType)reader.ReadByte().Value();
			const auto name = reader.ReadString();
			const auto semantic = reader.ReadString();
			const auto annotations = ReadAnnotations(reader);
			const auto rowCount = (intcs)reader.ReadByte();
			const auto columnCount = (intcs)reader.ReadByte();
			const auto elements = ReadParameters(reader);
			const auto structMembers = ReadParameters(reader);
			anyptr data = nullptr;

			if (elements->Count() == 0 && structMembers->Count() == 0) {
				switch (type) {
				case EffectParameterType::Bool:
				case EffectParameterType::Int32: {
					//TODO #if !OPENGL
					auto buffer = NewVector<intcs>(rowCount * columnCount);

					for (size_t j = 0; j < buffer->size(); ++j)
						buffer->at(j) = reader.ReadInt32().Value();

					*data.get() = buffer;

					break;
				}
				case EffectParameterType::Single: {
					auto buffer = NewVector<intcs>(rowCount * columnCount);
					for (size_t j = 0; j < buffer->size(); ++j)
						buffer->at(j) = reader.ReadSingle().Value();

					*data.get() = buffer;
					break;
				}
				default:
					break;
				}
			}

			parameters->at(i) = EffectParameter(
				class_, type, name, rowCount, columnCount, semantic,
				annotations, elements, structMembers, data);
		}

		return New<EffectParameterCollection>(parameters);
	}

	EffectPassCollectionPtr Effect::ReadPasses(BinaryReader& reader, EffectPtr const& effect, vectorptr<ShaderPtr> const& shaders) {
		auto passes = NewVector<EffectPassPtr>(reader.ReadInt32().Value());

		for (size_t i = 0; i < passes->size(); i++) {
			auto name = reader.ReadString();
			auto annotations = ReadAnnotations(reader);
			
			auto shaderIndex = reader.ReadInt32().Value();
			ShaderPtr vertexShader = shaderIndex < 0 ? nullptr : shaders->at(shaderIndex);
			
			shaderIndex = reader.ReadInt32().Value();
			ShaderPtr pixelShader = shaderIndex < 0 ? nullptr : shaders->at(shaderIndex);

			BlendStatePtr blend = nullptr;
			DepthStencilStatePtr depth = nullptr;
			RasterizerStatePtr raster = nullptr;

			if (reader.ReadBoolean().Value()) {
				blend = New<BlendState>();
				blend->AlphaBlendFunction((BlendFunction)reader.ReadByte().Value());
				blend->AlphaDestinationBlend((Blend)reader.ReadByte().Value());
				blend->AlphaSourceBlend((Blend)reader.ReadByte().Value());
				blend->BlendFactor = Color(reader.ReadByte(), reader.ReadByte(), reader.ReadByte(), reader.ReadByte());
				blend->ColorBlendFunction((BlendFunction)reader.ReadByte().Value());
				blend->ColorDestinationBlend((Blend)reader.ReadByte().Value());
				blend->ColorSourceBlend((Blend)reader.ReadByte().Value());
				blend->ColorWriteChannels((ColorWriteChannels)reader.ReadByte().Value());
				blend->ColorWriteChannels1((ColorWriteChannels)reader.ReadByte().Value());
				blend->ColorWriteChannels2((ColorWriteChannels)reader.ReadByte().Value());
				blend->ColorWriteChannels3((ColorWriteChannels)reader.ReadByte().Value());
				blend->MultiSampleMask = reader.ReadInt32().Value();
			}
			if (reader.ReadBoolean().Value()) {
				depth = New<DepthStencilState>();
				depth->CounterClockwiseStencilDepthBufferFail = (StencilOperation)reader.ReadByte().Value();
				depth->CounterClockwiseStencilFail = (StencilOperation)reader.ReadByte().Value();
				depth->CounterClockwiseStencilFunction = (CompareFunction)reader.ReadByte().Value();
				depth->CounterClockwiseStencilPass = (StencilOperation)reader.ReadByte().Value();
				depth->DepthBufferEnable = reader.ReadBoolean().Value();
				depth->DepthBufferFunction = (CompareFunction)reader.ReadByte().Value();
				depth->DepthBufferWriteEnable = reader.ReadBoolean().Value();
				depth->ReferenceStencil = reader.ReadInt32().Value();
				depth->StencilDepthBufferFail = (StencilOperation)reader.ReadByte().Value();
				depth->StencilEnable = reader.ReadBoolean().Value();
				depth->StencilFail = (StencilOperation)reader.ReadByte().Value();
				depth->StencilFunction = (CompareFunction)reader.ReadByte().Value();
				depth->StencilMask = reader.ReadInt32().Value();
				depth->StencilPass = (StencilOperation)reader.ReadByte().Value();
				depth->StencilWriteMask = reader.ReadInt32().Value();
				depth->TwoSidedStencilMode = reader.ReadBoolean().Value();
			}
			if (reader.ReadBoolean().Value()) {
				raster = New<RasterizerState>();
				raster->CullMode = (CullMode)reader.ReadByte().Value();
				raster->DepthBias = reader.ReadSingle().Value();
				raster->FillMode = (FillMode)reader.ReadByte().Value();
				raster->MultiSampleAntiAlias = reader.ReadBoolean().Value();
				raster->ScissorTestEnable = reader.ReadBoolean().Value();
				raster->SlopeScaleDepthBias = reader.ReadSingle().Value();
			}

			passes->at(i) = New<EffectPass>(
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
}