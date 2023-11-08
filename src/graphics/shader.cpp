#include "shader.hpp"

namespace dxna::graphics {
	Shader::Shader(GraphicsDevice_* device, cs::BinaryReader* reader) {
		this->GraphicsDevice(device);

		const auto isVertexShader = (bool)reader->ReadBoolean();
		Stage = isVertexShader ? ShaderStage::Vertex : ShaderStage::Pixel;

		const auto length = (intcs)reader->ReadInt32();
		auto byteCode = reader->ReadBytes(length);
		const auto samplerCount = (intcs)reader->ReadByte();

		Samplers = std::vector<SamplerInfo>(samplerCount);

		for (size_t s = 0; s < samplerCount; ++s) {
			Samplers[s].type = (SamplerType)(bytecs)(reader->ReadByte());
			Samplers[s].state->AddressU = (TextureAddressMode)(bytecs)reader->ReadByte();
			Samplers[s].state->AddressV = (TextureAddressMode)(bytecs)reader->ReadByte();
			Samplers[s].state->AddressW = (TextureAddressMode)(bytecs)reader->ReadByte();

			if (reader->ReadBoolean()) {
				Samplers[s].state->BorderColor = Color(
					reader->ReadByte(),
					reader->ReadByte(),
					reader->ReadByte(),
					reader->ReadByte());
				Samplers[s].state->Filter = (TextureFilter)(bytecs)reader->ReadByte();
				Samplers[s].state->MaxAnisotropy = (intcs)reader->ReadInt32();
				Samplers[s].state->MaxMipLevel = (intcs)reader->ReadInt32();
				Samplers[s].state->MipMapLevelOfDetailBias = (shortcs)reader->ReadSingle();
			}

			//Samplers[s]->name = reader.ReadString();
			Samplers[s].parameter = (bytecs)reader->ReadByte();
		}

		const auto cbufferCount = (bytecs)reader->ReadByte();
		CBuffers = std::vector<intcs>(cbufferCount);

		for(size_t c = 0; c < cbufferCount; ++c)
			CBuffers[c] = (bytecs)reader->ReadByte();

		const auto attributeCount = (intcs)reader->ReadByte();
		Attributes = std::vector<VertexAttribute>(attributeCount);
		
		for (size_t a = 0; a < attributeCount; ++a) {
			//Attributes[a].name = reader->ReadString();
			Attributes[a].usage = (VertexElementUsage)(bytecs)reader->ReadByte();
			Attributes[a].index = (bytecs)reader->ReadByte();
			Attributes[a].location = (shortcs)reader->ReadInt16();
		}

		PlatformConstruct(Stage, byteCode.data());
	}
}