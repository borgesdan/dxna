#ifndef DXNA_GRAPHICS_EFFECT_HPP
#define DXNA_GRAPHICS_EFFECT_HPP

#include "graphicsresource.hpp"

namespace dxna::graphics {
	class Effect : public GraphicsResource {
		struct MGFXHeader {
			static constexpr intcs MGFXSignature = dxna::Enviroment::IsLittleEndian() ? 0x5846474D : 0x4D474658;

			static constexpr intcs MGFXVersion = 10;
			intcs Signature{ 0 };
			intcs Version{ 0 };
			intcs Profile{ 0 };
			intcs EffectKey{ 0 };
			intcs HeaderSize{ 0 };
		};
	};
}

#endif