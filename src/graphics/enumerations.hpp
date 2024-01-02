#ifndef DXNA_GRAPHICS_ENUMERATIONS_HPP
#define DXNA_GRAPHICS_ENUMERATIONS_HPP

namespace dxna::graphics {
    enum class ClearOptions {
        Target = 1,
        DepthBuffer = 2,
        Stencil = 4
    };

    enum class CubeMapFace {
        PositiveX,
        NegativeX,
        PositiveY,
        NegativeY,
        PositiveZ,
        NegativeZ
    };

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
    enum class EffectParameterDesc {
        Int,
        Matrix,
        Quaternion,
        Float,
        Texture,
        Vector2,
        Vector3,
        Vector4,
        Pointer
    };

    enum class SurfaceFormat {
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
        Bgr32 = 20,
        Bgra32 = 21,
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

    enum class GraphicsProfile {
        Reach,
        HiDef
    };
}

#endif