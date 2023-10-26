#ifndef CS_EVENTARGS_HPP
#define CS_EVENTARGS_HPP

#include <vector>
#include <algorithm>

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
	class EventHandler {
	public:
		using EventHandlerCallBack = void(*)(TOBJECT const& sender, TEVENTARGS const& e);

		constexpr void operator+=(EventHandlerCallBack const& del) {
			delegates.push_back(del);
		}

		constexpr void operator-=(EventHandlerCallBack const& del) {
			std::remove(delegates.begin(), delegates.end(), del);
		}

		void Invoke(TOBJECT const& obj, TEVENTARGS const& e) const {
			if (delegates.empty())
				return;

			const auto size = delegates.size();

			for (size_t i = 0; i < size; ++i) {
				const EventHandlerCallBack del = delegates[i];

				if (del != nullptr)
					del(obj, e);
			}
		}

		constexpr bool IsEmpty() const {
			return delegates.empty();
		}

	private:
		std::vector<EventHandlerCallBack> delegates;
	};
}

#endif