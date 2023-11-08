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
        SamplerState* state;
        intcs parameter;
    };

    struct VertexAttribute {
        VertexElementUsage usage;
        intcs index;
        std::string name;
        intcs location;
    };

    struct Shader : public GraphicsResource {
        Shader(GraphicsDevice_* device, cs::BinaryReader* reader);

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

    struct EffectParameter;
    struct EffectParameterCollection;

    class ConstantBuffer : public GraphicsResource {
    public:
        ConstantBuffer(GraphicsDevice_* device, intcs const& sizeInBytes,
            std::vector<intcs> const& parameterIndexes, std::vector<intcs> const& parameterOffsets,
            std::string const& name);

        void Clear();
        void PlatformInitialize() {
            //TODO: remover
        }
        void PlatformClear();

    private:
        //void SetData(int offset, int rows, int columns, object data);

        intcs SetParameter(intcs offset, EffectParameter const& param);
        void Update(EffectParameterCollection const& parameters);

        std::vector<bytecs> _buffer;
        std::vector<intcs> _parameters;
        std::vector<intcs> _offsets;
        std::string _name;
        ulongcs _stateKey;
        bool _dirty;
    };

    struct ConstantBufferCollectionSetArgs;

    class ConstantBufferCollection {
    public:
        ConstantBufferCollection(ShaderStage const& stage, intcs maxBuffers);

        ConstantBuffer* operator[](size_t index);

        void Clear();

        void SetConstanteBuffer(ConstantBufferCollectionSetArgs& arg);

    private:
        std::vector<ConstantBuffer> _buffers;
        ShaderStage _stage;
        intcs _valid;
    };
}

#endif