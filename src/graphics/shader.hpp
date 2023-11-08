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
        SamplerType type;
        int textureSlot;
        int samplerSlot;
        std::string name;
        SamplerState* state;
        int parameter;
    };

    struct VertexAttribute {
        VertexElementUsage usage;
        int index;
        std::string name;
        int location;
    };

    struct Shader : public GraphicsResource {
        Shader(GraphicsDevice_* device, cs::BinaryReader* reader);

        static int Profile();

        int HashKey{0};
        std::vector<SamplerInfo> Samplers;
        std::vector<int> CBuffers;
        ShaderStage Stage;
        std::vector<VertexAttribute> Attributes;

        void PlatformConstruct(ShaderStage const& stage, bytecs* shaderByteCode) {
            //TODO: remover
        }
    };
}

#endif