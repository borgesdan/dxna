#ifndef DXNA_GRAPHICS_CAPABILITIES_HPP
#define DXNA_GRAPHICS_CAPABILITIES_HPP

#include "forward.hpp"

namespace dxna::graphics{
	class GraphicsCapabilities {
	public:
		//TODO: Initialize
		void Initialize(GraphicsDevicePtr const& device);

		constexpr bool SupportsNonPowerOfTwo() const noexcept {
			return _supportsNonPowerOfTwo;
		}

		constexpr bool SupportsTextureFilterAnisotropic() const noexcept {
			return _supportsTextureFilterAnisotropic;
		}
		
		constexpr bool SupportsDepth24() const noexcept {
			return _supportsDepth24;
		}
		
		constexpr bool SupportsPackedDepthStencil() const noexcept {
			return _supportsPackedDepthStencil;
		}
		
		constexpr bool SupportsDepthNonLinear() const noexcept {
			return _supportsDepthNonLinear;
		}
		
		constexpr bool SupportsDxt1() const noexcept {
			return _supportsDxt1;
		}
		
		constexpr bool SupportsS3tcSupportsS3tc() const noexcept {
			return _supportsS3tcSupportsS3tc;
		}
		
		constexpr bool SupportsPvrtc() const noexcept {
			return _supportsPvrtc;
		}
		
		constexpr bool SupportsEtc1() const noexcept {
			return _supportsEtc1;
		}
		
		constexpr bool SupportsEtc2() const noexcept {
			return _supportsEtc2;
		}
		
		constexpr bool SupportsAtitc() const noexcept {
			return _supportsAtitc;
		}
		
		constexpr bool SupportsTextureMaxLevel() const noexcept {
			return _supportsTextureMaxLevel;
		}
		
		constexpr bool SupportsSRgb() const noexcept {
			return _supportsSRgb;
		}
		
		constexpr bool SupportsTextureArrays() const noexcept {
			return _supportsTextureArrays;
		}
		
		constexpr bool SupportsDepthClamp() const noexcept {
			return _supportsDepthClamp;
		}
		
		constexpr bool SupportsVertexTextures() const noexcept {
			return _supportsVertexTextures;
		}
		
		constexpr bool SupportsFloatTextures() const noexcept {
			return _supportsFloatTextures;
		}
		
		constexpr bool SupportsHalfFloatTextures() const noexcept {
			return _supportsHalfFloatTextures;
		}
		
		constexpr bool SupportsNormalized() const noexcept {
			return _supportsNormalized;
		}
		
		constexpr bool SupportsInstancing() const noexcept {
			return _supportsInstancing;
		}
		
		constexpr bool SupportsBaseIndexInstancing() const noexcept {
			return _supportsBaseIndexInstancing;
		}
		
		constexpr bool SupportsSeparateBlendStates() const noexcept {
			return _supportsSeparateBlendStates;
		}
		
		constexpr int MaxTextureAnisotropy() const noexcept {
			return _maxTextureAnisotropy;
		}
		
		constexpr int MaxMultiSampleCount() const noexcept {
			return _maxMultiSampleCount;
		}

	private:
		static constexpr int MultiSampleCountLimit = 32;

		bool _supportsNonPowerOfTwo;
		bool _supportsTextureFilterAnisotropic;
		bool _supportsDepth24;
		bool _supportsPackedDepthStencil;
		bool _supportsDepthNonLinear;
		bool _supportsDxt1;
		bool _supportsS3tcSupportsS3tc;
		bool _supportsPvrtc;
		bool _supportsEtc1;
		bool _supportsEtc2;
		bool _supportsAtitc;
		bool _supportsTextureMaxLevel;
		bool _supportsSRgb;
		bool _supportsTextureArrays;
		bool _supportsDepthClamp;
		bool _supportsVertexTextures;
		bool _supportsFloatTextures;
		bool _supportsHalfFloatTextures;
		bool _supportsNormalized;
		bool _supportsInstancing;
		bool _supportsBaseIndexInstancing;
		bool _supportsSeparateBlendStates;
		int _maxTextureAnisotropy;
		int _maxMultiSampleCount;
	};
}

#endif