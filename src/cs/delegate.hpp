#ifndef CS_DELEGATE_HPP
#define CS_DELEGATE_HPP

#include <vector>
#include <algorithm>

namespace cs {
	template <typename TOBJECT, typename TEVENTARGS>
	class Delegate {
	public:
		using EventHandlerCallBack = void(*)(TOBJECT& sender, TEVENTARGS& e);

		constexpr void operator+=(EventHandlerCallBack const& del) {
			delegates.push_back(del);
		}

		constexpr void operator-=(EventHandlerCallBack const& del) {
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

		constexpr bool IsEmpty() const {
			return delegates.empty();
		}

	private:
		std::vector<EventHandlerCallBack> delegates;
	};
}

#endif