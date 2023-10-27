#ifndef DXNA_COLOR_HPP
#define DXNA_COLOR_HPP

#include "cs/cstypes.hpp"

namespace dxna {
	struct Color {
		constexpr Color(uintcs packedValue) : packedValue(packedValue) {}

		constexpr Color(intcs r, intcs g, intcs b) {
			if (((r | g | b) & -256) != 0) {
				r = ClampToByte64(r);
				g = ClampToByte64(g);
				b = ClampToByte64(b);
			}

			g <<= 8;
			b <<= 16;

			packedValue = static_cast<uintcs>(r | g | b | -16777216);
		}

		constexpr Color(intcs r, intcs g, intcs b, intcs a) {
			if (((r | g | b | a) & -256) != 0) {
				r = ClampToByte32(r);
				g = ClampToByte32(g);
				b = ClampToByte32(b);
				a = ClampToByte32(a);
			}

			g <<= 8;
			b <<= 16;
			a <<= 24;

			packedValue = static_cast<uintcs>(r | g | b | a);
		}

		constexpr uintcs PackedValue() const { return packedValue; }
		constexpr bytecs R() const { return packedValue; }		
		constexpr bytecs G() const { return packedValue >> 8; }
		constexpr bytecs B() const { return packedValue >> 16; }
		constexpr bytecs A() const { return packedValue >> 24; }
		
		constexpr void PackedValue(uintcs value) {
			packedValue = value;
		}

		constexpr void R(bytecs value) {
			packedValue = packedValue & 4294967040U | value;	
		}
		
		constexpr void G(bytecs value) {
			packedValue = static_cast<uintcs>(packedValue & -65281 | value << 8); 
		}

		constexpr void B(bytecs value) {
			packedValue = static_cast<uintcs>(packedValue & -16711681 | value << 16);
		}

		constexpr void A(bytecs value) { 
			packedValue = static_cast<uintcs>(packedValue & 16777215 | value << 24);
		}		

	private:
		static constexpr intcs ClampToByte64(longcs value) {
			if (value < 0)
				return 0;

			return value > MaxByte ? MaxByte : value;
		}

		static constexpr intcs ClampToByte32(intcs value) {
			if (value < 0)
				return 0;

			return value > MaxByte ? MaxByte : value;
		}

		uintcs packedValue{ 0 };

	public:
		static constexpr Color Transparent() { return Color(0U); }
		static constexpr Color AliceBlue() { return Color(4294965488U); }
		static constexpr Color AntiqueWhite() { return Color(4292340730U); }
		static constexpr Color Aqua() { return Color(4294967040U); }
		static constexpr Color Aquamarine() { return Color(4292149119U); }
		static constexpr Color Azure() { return Color(4294967280U); }
		static constexpr Color Beige() { return Color(4292670965U); }
		static constexpr Color Bisque() { return Color(4291093759U); }
		static constexpr Color Black() { return Color(4278190080U); }
		static constexpr Color BlanchedAlmond() { return Color(4291685375U); }
		static constexpr Color Blue() { return Color(4294901760U); }
		static constexpr Color BlueViolet() { return Color(4293012362U); }
		static constexpr Color Brown() { return Color(4280953509U); }
		static constexpr Color BurlyWood() { return Color(4287084766U); }
		static constexpr Color CadetBlue() { return Color(4288716383U); }
		static constexpr Color Chartreuse() { return Color(4278255487U); }
		static constexpr Color Chocolate() { return Color(4280183250U); }
		static constexpr Color Coral() { return Color(4283465727U); }
		static constexpr Color CornflowerBlue() { return Color(4293760356U); }
		static constexpr Color Cornsilk() { return Color(4292671743U); }
		static constexpr Color Crimson() { return Color(4282127580U); }
		static constexpr Color Cyan() { return Color(4294967040U); }
		static constexpr Color DarkBlue() { return Color(4287299584U); }
		static constexpr Color DarkCyan() { return Color(4287335168U); }
		static constexpr Color DarkGoldenrod() { return Color(4278945464U); }
		static constexpr Color DarkGray() { return Color(4289309097U); }
		static constexpr Color DarkGreen() { return Color(4278215680U); }
		static constexpr Color DarkKhaki() { return Color(4285249469U); }
		static constexpr Color DarkMagenta() { return Color(4287299723U); }
		static constexpr Color DarkOliveGreen() { return Color(4281297749U); }
		static constexpr Color DarkOrange() { return Color(4278226175U); }
		static constexpr Color DarkOrchid() { return Color(4291572377U); }
		static constexpr Color DarkRed() { return Color(4278190219U); }
		static constexpr Color DarkSalmon() { return Color(4286224105U); }
		static constexpr Color DarkSeaGreen() { return Color(4287347855U); }
		static constexpr Color DarkSlateBlue() { return Color(4287315272U); }
		static constexpr Color DarkSlateGray() { return Color(4283387695U); }
		static constexpr Color DarkTurquoise() { return Color(4291939840U); }
		static constexpr Color DarkViolet() { return Color(4292018324U); }
		static constexpr Color DeepPink() { return Color(4287829247U); }
		static constexpr Color DeepSkyBlue() { return Color(4294950656U); }
		static constexpr Color DimGray() { return Color(4285098345U); }
		static constexpr Color DodgerBlue() { return Color(4294938654U); }
		static constexpr Color Firebrick() { return Color(4280427186U); }
		static constexpr Color FloralWhite() { return Color(4293982975U); }
		static constexpr Color ForestGreen() { return Color(4280453922U); }
		static constexpr Color Fuchsia() { return Color(4294902015U); }
		static constexpr Color Gainsboro() { return Color(4292664540U); }
		static constexpr Color GhostWhite() { return Color(4294965496U); }
		static constexpr Color Gold() { return Color(4278245375U); }
		static constexpr Color Goldenrod() { return Color(4280329690U); }
		static constexpr Color Gray() { return Color(4286611584U); }
		static constexpr Color Green() { return Color(4278222848U); }
		static constexpr Color GreenYellow() { return Color(4281335725U); }
		static constexpr Color Honeydew() { return Color(4293984240U); }
		static constexpr Color HotPink() { return Color(4290013695U); }
		static constexpr Color IndianRed() { return Color(4284243149U); }
		static constexpr Color Indigo() { return Color(4286709835U); }
		static constexpr Color Ivory() { return Color(4293984255U); }
		static constexpr Color Khaki() { return Color(4287424240U); }
		static constexpr Color Lavender() { return Color(4294633190U); }
		static constexpr Color LavenderBlush() { return Color(4294308095U); }
		static constexpr Color LawnGreen() { return Color(4278254716U); }
		static constexpr Color LemonChiffon() { return Color(4291689215U); }
		static constexpr Color LightBlue() { return Color(4293318829U); }
		static constexpr Color LightCoral() { return Color(4286611696U); }
		static constexpr Color LightCyan() { return Color(4294967264U); }
		static constexpr Color LightGoldenrodYellow() { return Color(4292016890U); }
		static constexpr Color LightGreen() { return Color(4287688336U); }
		static constexpr Color LightGray() { return Color(4292072403U); }
		static constexpr Color LightPink() { return Color(4290885375U); }
		static constexpr Color LightSalmon() { return Color(4286226687U); }
		static constexpr Color LightSeaGreen() { return Color(4289376800U); }
		static constexpr Color LightSkyBlue() { return Color(4294626951U); }
		static constexpr Color LightSlateGray() { return Color(4288252023U); }
		static constexpr Color LightSteelBlue() { return Color(4292789424U); }
		static constexpr Color LightYellow() { return Color(4292935679U); }
		static constexpr Color Lime() { return Color(4278255360U); }
		static constexpr Color LimeGreen() { return Color(4281519410U); }
		static constexpr Color Linen() { return Color(4293325050U); }
		static constexpr Color Magenta() { return Color(4294902015U); }
		static constexpr Color Maroon() { return Color(4278190208U); }
		static constexpr Color MediumAquamarine() { return Color(4289383782U); }
		static constexpr Color MediumBlue() { return Color(4291624960U); }
		static constexpr Color MediumOrchid() { return Color(4292040122U); }
		static constexpr Color MediumPurple() { return Color(4292571283U); }
		static constexpr Color MediumSeaGreen() { return Color(4285641532U); }
		static constexpr Color MediumSlateBlue() { return Color(4293814395U); }
		static constexpr Color MediumSpringGreen() { return Color(4288346624U); }
		static constexpr Color MediumTurquoise() { return Color(4291613000U); }
		static constexpr Color MediumVioletRed() { return Color(4286911943U); }
		static constexpr Color MidnightBlue() { return Color(4285536537U); }
		static constexpr Color MintCream() { return Color(4294639605U); }
		static constexpr Color MistyRose() { return Color(4292994303U); }
		static constexpr Color Moccasin() { return Color(4290110719U); }
		static constexpr Color NavajoWhite() { return Color(4289584895U); }
		static constexpr Color Navy() { return Color(4286578688U); }
		static constexpr Color OldLace() { return Color(4293326333U); }
		static constexpr Color Olive() { return Color(4278222976U); }
		static constexpr Color OliveDrab() { return Color(4280520299U); }
		static constexpr Color Orange() { return Color(4278232575U); }
		static constexpr Color OrangeRed() { return Color(4278207999U); }
		static constexpr Color Orchid() { return Color(4292243674U); }
		static constexpr Color PaleGoldenrod() { return Color(4289390830U); }
		static constexpr Color PaleGreen() { return Color(4288215960U); }
		static constexpr Color PaleTurquoise() { return Color(4293848751U); }
		static constexpr Color PaleVioletRed() { return Color(4287852763U); }
		static constexpr Color PapayaWhip() { return Color(4292210687U); }
		static constexpr Color PeachPuff() { return Color(4290370303U); }
		static constexpr Color Peru() { return Color(4282353101U); }
		static constexpr Color Pink() { return Color(4291543295U); }
		static constexpr Color Plum() { return Color(4292714717U); }
		static constexpr Color PowderBlue() { return Color(4293320880U); }
		static constexpr Color Purple() { return Color(4286578816U); }
		static constexpr Color Red() { return Color(4278190335U); }
		static constexpr Color RosyBrown() { return Color(4287598524U); }
		static constexpr Color RoyalBlue() { return Color(4292962625U); }
		static constexpr Color SaddleBrown() { return Color(4279453067U); }
		static constexpr Color Salmon() { return Color(4285694202U); }
		static constexpr Color SandyBrown() { return Color(4284523764U); }
		static constexpr Color SeaGreen() { return Color(4283927342U); }
		static constexpr Color SeaShell() { return Color(4293850623U); }
		static constexpr Color Sienna() { return Color(4281160352U); }
		static constexpr Color Silver() { return Color(4290822336U); }
		static constexpr Color SkyBlue() { return Color(4293643911U); }
		static constexpr Color SlateBlue() { return Color(4291648106U); }
		static constexpr Color SlateGray() { return Color(4287660144U); }
		static constexpr Color Snow() { return Color(4294638335U); }
		static constexpr Color SpringGreen() { return Color(4286578432U); }
		static constexpr Color SteelBlue() { return Color(4290019910U); }
		static constexpr Color Tan() { return Color(4287411410U); }
		static constexpr Color Teal() { return Color(4286611456U); }
		static constexpr Color Thistle() { return Color(4292394968U); }
		static constexpr Color Tomato() { return Color(4282868735U); }
		static constexpr Color Turquoise() { return Color(4291878976U); }
		static constexpr Color Violet() { return Color(4293821166U); }
		static constexpr Color Wheat() { return Color(4289978101U); }
		static constexpr Color White() { return Color(MaxUint); }
		static constexpr Color WhiteSmoke() { return Color(4294309365U); }
		static constexpr Color Yellow() { return Color(4278255615U); }
		static constexpr Color YellowGreen() { return Color(4281519514U); }
	};
}

#endif