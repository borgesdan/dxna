#ifndef DXNA_GAMETIME_HPP
#define DXNA_GAMETIME_HPP

#include "cs/cs.hpp"
#include "includes.hpp"

namespace dxna {
	class GameTime {
	public:
		constexpr GameTime() = default;

		constexpr GameTime(cs::TimeSpan total, cs::TimeSpan elapsed, bool isSlowly) :
			TotalGameTime(total), ElapsedGameTime(elapsed), IsRunningSlowly(isSlowly) {
		}
	
		cs::TimeSpan TotalGameTime{ cs::TimeSpan::Zero() };
		cs::TimeSpan ElapsedGameTime{ cs::TimeSpan::Zero() };
		bool IsRunningSlowly{ false };
	};

	using PtrGameTime = std::shared_ptr<GameTime>;
}

#endif