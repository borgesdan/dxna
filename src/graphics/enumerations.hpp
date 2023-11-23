#ifndef DXNA_GRAPHICS_ENUMERATIONS_HPP
#define DXNA_GRAPHICS_ENUMERATIONS_HPP

namespace dxna::graphics {
	enum class Blend {
        One,
        Zero,
        SourceColor,
        InverseSourceColor,
        SourceAlpha,
        InverseSourceAlpha,
        DestinationColor,
        InverseDestinationColor,
        DestinationAlpha,
        InverseDestinationAlpha,
        BlendFactor,
        InverseBlendFactor,
        SourceAlphaSaturation,
	};

    enum class ColorWriteChannels {
        None = 0,
        Red = 1,
        Green = 2,
        Blue = 4,
        Alpha = 8,
        All = Alpha | Blue | Green | Red,
    };

    enum class BlendFunction {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max,
    };

    enum class TextureFilter {
        Linear,
        Point,
        Anisotropic,
        LinearMipPoint,
        PointMipLinear,
        MinLinearMagPointMipLinear,
        MinLinearMagPointMipPoint,
        MinPointMagLinearMipLinear,
        MinPointMagLinearMipPoint,
    };

    enum class TextureAddressMode {
        Wrap,
        Clamp,
        Mirror,
    };

    enum class TextureFilterMode {
        Default,
        Comparison
    };

    enum class CompareFunction {
        Always,
        Never,
        Less,
        LessEqual,
        Equal,
        GreaterEqual,
        Greater,
        NotEqual
    };

    enum class DepthFormat {
        None,
        Depth16,
        Depth24,
        Depth24Stencil8
    };

    enum class CullMode {
        None,
        CullClockwiseFace,
        CullCounterClockwiseFace
    };

    enum class FillMode {
        Solid,
        WireFrame
    };

    enum class StencilOperation {
        Keep,
        Zero,
        Replace,
        Increment,
        Decrement,
        IncrementSaturation,
        DecrementSaturation,
        Invert
    };

    enum class SamplerType {
        Sampler2D = 0,
        SamplerCube = 1,
        SamplerVolume = 2,
        Sampler1D = 3,
    };

    enum class VertexElementUsage {
        Position,
        Color,
        TextureCoordinate,
        Normal,
        Binormal,
        Tangent,
        BlendIndices,
        BlendWeight,
        Depth,
        Fog,
        PointSize,
        Sample,
        TessellateFactor
    };

    enum class ShaderStage {
        Vertex,
        Pixel,
    };

    enum class EffectParameterClass {
        Scalar,
        Vector,
        Matrix,
        Object,
        Struct
    };

    enum class EffectParameterType {
        Void,
        Bool,
        Int32,
        Single,
        String,
        Texture,
        Texture1D,
        Texture2D,
        Texture3D,
        TextureCube
    };

    enum class BufferUsage {
        None,
        WriteOnly
    };

    enum class IndexElementSize {
        SixteenBits,
        ThirtyTwoBits
    };

    enum class PrimitiveType {
        TriangleList,
        TriangleStrip,
        LineList,
        LineStrip,
        PointList
    };

    enum class VertexElementFormat {
        Single,
        Vector2,
        Vector3,
        Vector4,
        Color,
        Byte4,
        Short2,
        Short4,
        NormalizedShort2,
        NormalizedShort4,
        HalfVector2,
        HalfVector4
    };
}

namespace dxna::graphics {
    inline constexpr intcs GetSize(VertexElementFormat elementFormat)
    {
        switch (elementFormat)
        {
        case VertexElementFormat::Single:
        case VertexElementFormat::Color:
        case VertexElementFormat::Byte4:
        case VertexElementFormat::Short2:
        case VertexElementFormat::HalfVector2:
        case VertexElementFormat::NormalizedShort2:
            return 4;

        case VertexElementFormat::Vector2:
        case VertexElementFormat::Short4:
        case VertexElementFormat::NormalizedShort4:
        case VertexElementFormat::HalfVector4:
            return 8;

        case VertexElementFormat::Vector3:
            return 12;

        case VertexElementFormat::Vector4:
            return 16;

        default:
            return 0;
        }
    }

}

#endif