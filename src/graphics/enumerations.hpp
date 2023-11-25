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

    enum class SurfaceFormat
    {
        Color,
        Bgr565,
        Bgra5551,
        Bgra4444,
        Dxt1,
        Dxt3,
        Dxt5,
        NormalizedByte2,
        NormalizedByte4,
        Rgba1010102,
        Rg32,
        Rgba64,
        Alpha8,
        Single,
        Vector2,
        Vector4,
        HalfSingle,
        HalfVector2,
        HalfVector4,
        HdrBlendable,
        Bgr32 = 20,     // B8G8R8X8       
        Bgra32 = 21,    // B8G8R8A8  
        ColorSRgb = 30,
        Bgr32SRgb = 31,
        Bgra32SRgb = 32,
        Dxt1SRgb = 33,
        Dxt3SRgb = 34,
        Dxt5SRgb = 35,
        RgbPvrtc2Bpp = 50,
        RgbPvrtc4Bpp = 51,
        RgbaPvrtc2Bpp = 52,
        RgbaPvrtc4Bpp = 53,
        RgbEtc1 = 60,
        Dxt1a = 70,
        RgbaAtcExplicitAlpha = 80,
        RgbaAtcInterpolatedAlpha = 81,
        Rgb8Etc2 = 90,
        Srgb8Etc2 = 91,
        Rgb8A1Etc2 = 92,
        Srgb8A1Etc2 = 93,
        Rgba8Etc2 = 94,
        SRgb8A8Etc2 = 95,
    };
}

namespace dxna::graphics {
    inline constexpr intcs GetSize(VertexElementFormat const& elementFormat) noexcept
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

    inline constexpr intcs GetSize(SurfaceFormat const& surfaceFormat) noexcept {
        switch (surfaceFormat)
        {
        case SurfaceFormat::Dxt1:
        case SurfaceFormat::Dxt1SRgb:
        case SurfaceFormat::Dxt1a:
        case SurfaceFormat::RgbPvrtc2Bpp:
        case SurfaceFormat::RgbaPvrtc2Bpp:
        case SurfaceFormat::RgbPvrtc4Bpp:
        case SurfaceFormat::RgbaPvrtc4Bpp:
        case SurfaceFormat::RgbEtc1:
        case SurfaceFormat::Rgb8Etc2:
        case SurfaceFormat::Srgb8Etc2:
        case SurfaceFormat::Rgb8A1Etc2:
        case SurfaceFormat::Srgb8A1Etc2:
            return 8;
        case SurfaceFormat::Dxt3:
        case SurfaceFormat::Dxt3SRgb:
        case SurfaceFormat::Dxt5:
        case SurfaceFormat::Dxt5SRgb:
        case SurfaceFormat::RgbaAtcExplicitAlpha:
        case SurfaceFormat::RgbaAtcInterpolatedAlpha:
        case SurfaceFormat::Rgba8Etc2:
        case SurfaceFormat::SRgb8A8Etc2:
            return 16;
        case SurfaceFormat::Alpha8:
            return 1;
        case SurfaceFormat::Bgr565:
        case SurfaceFormat::Bgra4444:
        case SurfaceFormat::Bgra5551:
        case SurfaceFormat::HalfSingle:
        case SurfaceFormat::NormalizedByte2:
            return 2;
        case SurfaceFormat::Color:
        case SurfaceFormat::ColorSRgb:
        case SurfaceFormat::Single:
        case SurfaceFormat::Rg32:
        case SurfaceFormat::HalfVector2:
        case SurfaceFormat::NormalizedByte4:
        case SurfaceFormat::Rgba1010102:
        case SurfaceFormat::Bgra32:
        case SurfaceFormat::Bgra32SRgb:
        case SurfaceFormat::Bgr32:
        case SurfaceFormat::Bgr32SRgb:
            return 4;
        case SurfaceFormat::HalfVector4:
        case SurfaceFormat::Rgba64:
        case SurfaceFormat::Vector2:
            return 8;
        case SurfaceFormat::Vector4:
            return 16;
        default:
            return 0;
        }
    }

    inline constexpr bool IsCompressedFormat(SurfaceFormat const& format) noexcept {
        switch (format)
        {
        case SurfaceFormat::Dxt1:
        case SurfaceFormat::Dxt1a:
        case SurfaceFormat::Dxt1SRgb:
        case SurfaceFormat::Dxt3:
        case SurfaceFormat::Dxt3SRgb:
        case SurfaceFormat::Dxt5:
        case SurfaceFormat::Dxt5SRgb:
        case SurfaceFormat::RgbaAtcExplicitAlpha:
        case SurfaceFormat::RgbaAtcInterpolatedAlpha:
        case SurfaceFormat::RgbaPvrtc2Bpp:
        case SurfaceFormat::RgbaPvrtc4Bpp:
        case SurfaceFormat::RgbEtc1:
        case SurfaceFormat::Rgb8Etc2:
        case SurfaceFormat::Srgb8Etc2:
        case SurfaceFormat::Rgb8A1Etc2:
        case SurfaceFormat::Srgb8A1Etc2:
        case SurfaceFormat::Rgba8Etc2:
        case SurfaceFormat::SRgb8A8Etc2:
        case SurfaceFormat::RgbPvrtc2Bpp:
        case SurfaceFormat::RgbPvrtc4Bpp:
            return true;
        }

        return false;
    }

    inline void GetBlockSize(SurfaceFormat const& surfaceFormat, intcs& width, intcs& height) noexcept {
        switch (surfaceFormat)
        {
        case SurfaceFormat::RgbPvrtc2Bpp:
        case SurfaceFormat::RgbaPvrtc2Bpp:
            width = 8;
            height = 4;
            break;
        case SurfaceFormat::Dxt1:
        case SurfaceFormat::Dxt1SRgb:
        case SurfaceFormat::Dxt1a:
        case SurfaceFormat::Dxt3:
        case SurfaceFormat::Dxt3SRgb:
        case SurfaceFormat::Dxt5:
        case SurfaceFormat::Dxt5SRgb:
        case SurfaceFormat::RgbPvrtc4Bpp:
        case SurfaceFormat::RgbaPvrtc4Bpp:
        case SurfaceFormat::RgbEtc1:
        case SurfaceFormat::Rgb8Etc2:
        case SurfaceFormat::Srgb8Etc2:
        case SurfaceFormat::Rgb8A1Etc2:
        case SurfaceFormat::Srgb8A1Etc2:
        case SurfaceFormat::Rgba8Etc2:
        case SurfaceFormat::SRgb8A8Etc2:
        case SurfaceFormat::RgbaAtcExplicitAlpha:
        case SurfaceFormat::RgbaAtcInterpolatedAlpha:
            width = 4;
            height = 4;
            break;
        default:
            width = 1;
            height = 1;
            break;
        }
    }
}

#endif