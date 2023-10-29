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
}

#endif