#include "effect.hpp"
#include "states.hpp"

using namespace cs;

namespace dxna::graphics {
	ulongcs EffectParameter::NextStateKey = 0;

	Effect::Effect(GraphicsDevicePtr const& graphicsDevice,
		vectorptr<bytecs> const& effectCode, intcs index, intcs count) {
		auto header = ReadHeader(effectCode, index);
		auto effectKey = header.EffectKey;
		auto headerSize = header.HeaderSize;

		EffectPtr cloneSource = nullptr;

		//TODO
	}

	EffectParameterCollectionPtr Effect::ReadParameters(cs::BinaryReader& reader) {
		const auto count = reader.ReadInt32();

		if (count == 0)
			return New<EffectParameterCollection>();

		auto parameters = NewVector<EffectParameterPtr>(count);

		for (size_t i = 0; i < count; ++i) {
			const auto class_ = (EffectParameterClass)reader.ReadByte();
			const auto type = (EffectParameterType)reader.ReadByte();
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
						buffer->at(j) = reader.ReadInt32();

					*data = buffer;

					break;
				}
				case EffectParameterType::Single: {
					auto buffer = NewVector<intcs>(rowCount * columnCount);
					for (size_t j = 0; j < buffer->size(); ++j)
						buffer->at(j) = reader.ReadSingle();

					*data = buffer;
					break;
				}
				default:
					break;
				}
			}

			parameters->at(i) = New<EffectParameter>(
				class_, type, name, rowCount, columnCount, semantic,
				annotations, elements, structMembers, data);
		}

		return New<EffectParameterCollection>(parameters);
	}

	EffectPassCollectionPtr Effect::ReadPasses(BinaryReader& reader, EffectPtr const& effect, vectorptr<ShaderPtr> const& shaders) {
		auto passes = NewVector<EffectPassPtr>(reader.ReadInt32());

		for (size_t i = 0; i < passes->size(); i++) {
			auto name = reader.ReadString();
			auto annotations = ReadAnnotations(reader);
			
			auto shaderIndex = reader.ReadInt32();
			ShaderPtr vertexShader = shaderIndex < 0 ? nullptr : shaders->at(shaderIndex);
			
			shaderIndex = reader.ReadInt32();
			ShaderPtr pixelShader = shaderIndex < 0 ? nullptr : shaders->at(shaderIndex);

			BlendStatePtr blend = nullptr;
			DepthStencilStatePtr depth = nullptr;
			RasterizerStatePtr raster = nullptr;

			if (reader.ReadBoolean()) {
				blend = New<BlendState>();
				blend->AlphaBlendFunction((BlendFunction)reader.ReadByte());
				blend->AlphaDestinationBlend((Blend)reader.ReadByte());
				blend->AlphaSourceBlend((Blend)reader.ReadByte());
				blend->BlendFactor = Color(reader.ReadByte(), reader.ReadByte(), reader.ReadByte(), reader.ReadByte());
				blend->ColorBlendFunction((BlendFunction)reader.ReadByte());
				blend->ColorDestinationBlend((Blend)reader.ReadByte());
				blend->ColorSourceBlend((Blend)reader.ReadByte());
				blend->ColorWriteChannels((ColorWriteChannels)reader.ReadByte());
				blend->ColorWriteChannels1((ColorWriteChannels)reader.ReadByte());
				blend->ColorWriteChannels2((ColorWriteChannels)reader.ReadByte());
				blend->ColorWriteChannels3((ColorWriteChannels)reader.ReadByte());
				blend->MultiSampleMask = reader.ReadInt32();
			}
			if (reader.ReadBoolean()) {
				depth = New<DepthStencilState>();
				depth->CounterClockwiseStencilDepthBufferFail = (StencilOperation)reader.ReadByte();
				depth->CounterClockwiseStencilFail = (StencilOperation)reader.ReadByte();
				depth->CounterClockwiseStencilFunction = (CompareFunction)reader.ReadByte();
				depth->CounterClockwiseStencilPass = (StencilOperation)reader.ReadByte();
				depth->DepthBufferEnable = reader.ReadBoolean();
				depth->DepthBufferFunction = (CompareFunction)reader.ReadByte();
				depth->DepthBufferWriteEnable = reader.ReadBoolean();
				depth->ReferenceStencil = reader.ReadInt32();
				depth->StencilDepthBufferFail = (StencilOperation)reader.ReadByte();
				depth->StencilEnable = reader.ReadBoolean();
				depth->StencilFail = (StencilOperation)reader.ReadByte();
				depth->StencilFunction = (CompareFunction)reader.ReadByte();
				depth->StencilMask = reader.ReadInt32();
				depth->StencilPass = (StencilOperation)reader.ReadByte();
				depth->StencilWriteMask = reader.ReadInt32();
				depth->TwoSidedStencilMode = reader.ReadBoolean();
			}
			if (reader.ReadBoolean()) {
				raster = New<RasterizerState>();
				raster->CullMode = (CullMode)reader.ReadByte();
				raster->DepthBias = reader.ReadSingle();
				raster->FillMode = (FillMode)reader.ReadByte();
				raster->MultiSampleAntiAlias = reader.ReadBoolean();
				raster->ScissorTestEnable = reader.ReadBoolean();
				raster->SlopeScaleDepthBias = reader.ReadSingle();
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

	EffectAnnotationCollectionPtr Effect::ReadAnnotations(cs::BinaryReader& reader) {
		const auto count = reader.ReadInt32();
		
		if (count == 0)
			return New<EffectAnnotationCollection>();

		const auto annotations = NewVector<EffectAnnotationPtr>(count);

		return New<EffectAnnotationCollection>(annotations);
	}

	void Effect::ReadEffect(cs::BinaryReader& reader) {
		ConstantBuffers = NewVector<ConstantBufferPtr>(reader.ReadInt32());

		for (size_t c = 0; c < ConstantBuffers->size(); c++) {
			const auto name = reader.ReadString();
			const auto sizeInBytes = (intcs)reader.ReadInt16();
			auto parameters = NewVector<intcs>(reader.ReadInt32());
			auto offsets = NewVector<intcs>(parameters->size());

			for (size_t i = 0; i < parameters->size(); i++)	{
				parameters->at(i) = reader.ReadInt32();
				offsets->at(i) = (intcs)reader.ReadUInt16();
			}

			ConstantBuffers->at(c) = New<ConstantBuffer>(Device(),
				sizeInBytes,
				parameters,
				offsets,
				name);
		}

		_shaders = NewVector<ShaderPtr>(reader.ReadInt32());

		Parameters = ReadParameters(reader);

		auto techniques = NewVector<EffectTechniquePtr>(reader.ReadInt32());

		for (size_t t = 0; t < techniques->size(); ++t) {
			const auto name = reader.ReadString();
			const auto annotations = ReadAnnotations(reader);
			const auto passes = ReadPasses(reader, this->shared_from_this(), _shaders);

			techniques->at(t) = New<EffectTechnique>(name, passes, annotations);
		}

		Techniques = New<EffectTechniqueCollection>(techniques);

		CurrentTechnique = Techniques->At(0);
	}
}