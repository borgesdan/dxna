#ifndef DXNA_GRAPHICS_SHADERS_HPP
#define DXNA_GRAPHICS_SHADERS_HPP

#include "../cs/cs.hpp"
#include "./enumerations.hpp"
#include <string>
#include <vector>
#include "states.hpp"
#include "graphicsresource.hpp"

namespace dxna::graphics {
	struct SamplerInfo {
		constexpr SamplerInfo() = default;

		SamplerType type{ SamplerType::Sampler2D };
		intcs textureSlot{ 0 };
		intcs samplerSlot{ 0 };
		std::string name;
		SamplerStatePtr state = nullptr;
		intcs parameter{ 0 };
	};

	struct VertexAttribute {
		constexpr VertexAttribute() = default;

		VertexElementUsage usage{ VertexElementUsage::Position };
		intcs index{ 0 };
		std::string name;
		intcs location{ 0 };
	};

	class Shader : public GraphicsResource {
	public:
		Shader(GraphicsDevicePtr const& device, cs::BinaryReader& reader);

		static intcs Profile();

		intcs HashKey{ 0 };
		std::vector<SamplerInfo> Samplers;
		std::vector<intcs> CBuffers;
		ShaderStage Stage;
		std::vector<VertexAttribute> Attributes;

		void PlatformConstruct(ShaderStage const& stage, bytecs* shaderByteCode) {
			//TODO: remover
		}
	};	
}

#endif