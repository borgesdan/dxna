#ifndef DXNA_STATIC_HPP
#define DXNA_STATIC_HPP

#include <vector>

namespace dxna {
	class StaticManager {
	public:
		using StaticCtorrCallBack = void(*)();

		static void RegisterCtors(StaticCtorrCallBack const& ctor) {
			_ctors.push_back(ctor);
		}

		static void CallCtors() {
			if (_ctors.empty())
				return;

			const auto size = _ctors.size();

			for (size_t i = 0; i < size; ++i) {
				const auto& ctr = _ctors[i];

				if (ctr != nullptr)
					ctr();
			}
		}

		inline static std::vector<StaticCtorrCallBack> _ctors;
	};
}

#endif