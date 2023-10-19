#ifndef CS_DELEGATE_HPP
#define CS_DELEGATE_HPP

#include <vector>
#include <algorithm>

namespace cs {
	template <typename TOBJECT, typename TEVENTARGS>
	class Delegate {
	public:
		using EventHandlerCallBack = void(*)(TOBJECT& sender, TEVENTARGS& e);

		constexpr void operator+=(EventHandlerCallBack& del) {
			delegates.push_back(del);
		}

		constexpr void operator-=(EventHandlerCallBack& del) {
			std::remove(delegates.begin(), delegates.end(), del);
		}

		void Invoke(TOBJECT& obj, TEVENTARGS& e) const {
			const auto size = delegates.size();

			for (size_t i = 0; i < size; ++i) {
				const EventHandlerCallBack del = delegates[i];

				if(del != nullptr)
					del(obj, e);
			}
		}

	private:
		std::vector<EventHandlerCallBack> delegates;
	};
}

#endif