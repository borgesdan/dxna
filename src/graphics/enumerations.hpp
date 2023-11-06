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
}

#endif