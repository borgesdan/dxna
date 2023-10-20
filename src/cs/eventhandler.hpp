#ifndef CS_EVENTARGS_HPP
#define CS_EVENTARGS_HPP

#include "delegate.hpp"

namespace cs {
	class EventArgs {
	public:
		constexpr EventArgs() = default;

		virtual ~EventArgs() {
		}		

		static EventArgs Empty() {
			return EventArgs();
		}
	};

	template <typename TOBJECT, typename TEVENTARGS>
	class EventHandler : public Delegate<TOBJECT, TEVENTARGS> {};
}

#endif