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
        intcs textureSlot;
        intcs samplerSlot;
        std::string name;
        SamplerStatePtr state;
        intcs parameter;
    };

    struct VertexAttribute {
        VertexElementUsage usage;
        intcs index;
        std::string name;
        intcs location;
    };

    class Shader : public GraphicsResource {
    public:
        Shader(GraphicsDevicePtr const& device, cs::BinaryReader* reader);

        static intcs Profile();

        intcs HashKey{0};
        std::vector<SamplerInfo> Samplers;
        std::vector<intcs> CBuffers;
        ShaderStage Stage;
        std::vector<VertexAttribute> Attributes;

        void PlatformConstruct(ShaderStage const& stage, bytecs* shaderByteCode) {
            //TODO: remover
        }
    };

    using ShaderPtr = std::shared_ptr<Shader>;
}

#endif