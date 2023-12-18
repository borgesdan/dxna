#ifndef DXNA_CURVE_HPP
#define DXNA_CURVE_HPP

#include "enumerations.hpp"
#include "utility.hpp"
#include "types.hpp"
#include <cmath>

namespace dxna {

	// Key point on the Curve.
	struct CurveKey {
		//The position of the key on the curve.
		float Position{ 0 };
		//The tangent when approaching this point from the previous point on the curve.
		float TangentIn{ 0 };
		//The tangent when leaving this point to the next point on the curve.
		float TangentOut{ 0 };
		//value of this point.
		float Value{ 0 };
		// The indicator whether the segment between this point
		// and the next point on the curve is discrete or continuous.
		CurveContinuity Continuity{ CurveContinuity::Smooth };

		constexpr CurveKey() noexcept = default;

		constexpr CurveKey(
			float position, float value,
			float tangentIn = 0, float tangentOut = 0,
			CurveContinuity continuity = CurveContinuity::Smooth) noexcept :
			Position(position), Value(value),
			TangentIn(tangentIn), TangentOut(tangentOut),
			Continuity(continuity) {}

		constexpr size_t GetHashCode() const noexcept {
			size_t seed = 0;
			Hash::Combine(seed, Position);
			Hash::Combine(seed, TangentIn);
			Hash::Combine(seed, TangentOut);
			Hash::Combine(seed, Value);
			Hash::Combine(seed, (int)Continuity);
			return seed;
		}

		constexpr bool operator==(CurveKey const& other) const noexcept = default;
	};

	// The collection of the CurveKey elements and a part of the Curve class.
	struct CurveKeyCollection {
		CurveKeyCollection() {
			data = NewVector<CurveKey>();
		}

		constexpr CurveKey* operator[](size_t index) {
			if (data->empty() || index >= data->size())
				return nullptr;

			return &data->at(index);
		}

		constexpr CurveKey* At(size_t index) {
			if (data->empty() || index >= data->size())
				return nullptr;

			return &data->at(index);
		}

		constexpr size_t Count() const noexcept { return data->size(); }

		constexpr CurveKey* Last() const {
			return data->empty() ? nullptr : &data->at(data->size() - 1);
		}

		constexpr void Add(CurveKey const& item) const {
			if (Count() == 0) {
				data->push_back(item);
			}

			for (size_t i = 0; i < data->size(); ++i) {
				if (item.Position < data->at(i).Position) {
					data->insert(data->begin() + i, item);
					return;
				}
			}

			data->push_back(item);
		}

		constexpr void Clear() const noexcept {
			data->clear();
		}

		vectorptr<CurveKey> data;
	};

	// Contains a collection of CurveKey points in 2D space and provides
	// methods for evaluating features of the curve they define.
	struct Curve {
		Curve() = default;

		//Returns true if this curve is constant (has zero or one points).
		constexpr bool IsConstant() const noexcept {
			return Keys.Count() <= 1;
		}

		// Evaluate the value at a position of this Curve.
		constexpr float Evaluate(float position) {
			if (Keys.Count() == 0)
				return 0.0F;

			if (Keys.Count() == 1)
				return Keys[0]->Value;

			const auto first = Keys[0];
			const auto last = Keys.Last();
			auto cycle = 0;
			auto virtualPos = 0.0F;

			if (position < first->Position) {
				switch (PreLoop)
				{
				case dxna::CurveLoopType::Constant:
					return first->Value;

				case dxna::CurveLoopType::Cycle:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					return GetCurvePosition(virtualPos);

				case dxna::CurveLoopType::CycleOffset:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					return (GetCurvePosition(virtualPos) + cycle * (last->Value - first->Value));

				case dxna::CurveLoopType::Oscillate:
					cycle = GetNumberOfCycle(position);

					if (0 == std::fmod(static_cast<float>(cycle), 2.0f))
						virtualPos = position - (cycle * (last->Position - first->Position));
					else
						virtualPos = last->Position - position + first->Position + (cycle * (last->Position - first->Position));

					return GetCurvePosition(virtualPos);

				case dxna::CurveLoopType::Linear:
					return first->Value - first->TangentIn * (first->Position - position);

				default:
					break;
				}
			}
			else if (position > last->Position) {
				auto cycle = 0;
				auto virtualPos = 0.0F;

				switch (PostLoop)
				{
				case dxna::CurveLoopType::Constant:
					return last->Value;
				case dxna::CurveLoopType::Cycle:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					return GetCurvePosition(virtualPos);

				case dxna::CurveLoopType::CycleOffset:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));
					return (GetCurvePosition(virtualPos) + cycle * (last->Value - first->Value));
				case dxna::CurveLoopType::Oscillate:
					cycle = GetNumberOfCycle(position);
					virtualPos = position - (cycle * (last->Position - first->Position));

					if (0 == std::fmod(static_cast<float>(cycle), 2.0f))
						virtualPos = position - (cycle * (last->Position - first->Position));
					else
						virtualPos = last->Position - position + first->Position + (cycle * (last->Position - first->Position));

					return GetCurvePosition(virtualPos);

				case dxna::CurveLoopType::Linear:
					return last->Value + first->TangentOut * (position - last->Position);

				default:
					break;
				}
			}
		}

		// Computes tangents for all keys in the collection.
		constexpr void ComputeTangents(CurveTangent const& tangentInType, CurveTangent const& tangentOutType) {
			for (size_t i = 0; i < Keys.Count(); ++i) {
				ComputeTangent(i, tangentInType, tangentOutType);
			}
		}

		// Computes tangents for all keys in the collection.
		constexpr void ComputeTangent(size_t keyIndex, CurveTangent tangentInType, CurveTangent tangentOutType) {
			auto key = Keys[keyIndex];

			float p0, p, p1;
			p0 = p = p1 = key->Position;

			float v0, v, v1;
			v0 = v = v1 = key->Value;

			if (keyIndex > 0) {
				p0 = Keys[keyIndex - 1]->Position;
				v0 = Keys[keyIndex - 1]->Value;
			}

			if (keyIndex < Keys.Count() - 1) {
				p1 = Keys[keyIndex + 1]->Position;
				v1 = Keys[keyIndex + 1]->Value;
			}

			switch (tangentInType)
			{
			case CurveTangent::Flat:
				key->TangentIn = 0;
				break;
			case CurveTangent::Linear:
				key->TangentIn = v - v0;
				break;
			case CurveTangent::Smooth:
				const auto pn = p1 - p0;
				if (std::abs(pn) < std::numeric_limits<float>::epsilon())
					key->TangentIn = 0;
				else
					key->TangentIn = (v1 - v0) * ((p - p0) / pn);
				break;
			}

			switch (tangentOutType)
			{
			case CurveTangent::Flat:
				key->TangentOut = 0;
				break;
			case CurveTangent::Linear:
				key->TangentOut = v1 - v;
				break;
			case CurveTangent::Smooth:
				const auto pn = p1 - p0;
				if (std::abs(pn) < std::numeric_limits<float>::epsilon())
					key->TangentOut = 0;
				else
					key->TangentOut = (v1 - v0) * ((p1 - p) / pn);
				break;
			}
		}

	private:
		int GetNumberOfCycle(float position) const {
			const auto& keys = *Keys.data;
			auto cycle = (position - keys[0].Position) / (Keys.Last()->Position - keys[0].Position);

			if (cycle < 0.0f)
				cycle--;

			return static_cast<int>(cycle);
		}

		float GetCurvePosition(float position) {			
			auto& prev = *Keys[0];

			for (size_t i = 1; i < Keys.Count(); ++i) {
				const auto& next = *Keys[i];

				if (next.Position >= position) {
					if (prev.Continuity == CurveContinuity::Step) {
						if (position >= 1.0f) {
							return next.Value;
						}

						return prev.Value;
					}

					const auto t = (position - prev.Position) / (next.Position - prev.Position);
					const auto ts = t * t;
					const auto tss = ts * t;

					return (2 * tss - 3 * ts + 1.0f)
						* prev.Value + (tss - 2 * ts + t) 
						* prev.TangentOut + (3 * ts - 2 * tss) 
						* next.Value + (tss - ts) 
						* next.TangentIn;
				}

				prev = next;
			}

			return 0.0f;
		}

	public:
		// Defines how to handle weighting 
		// values that are less than the first control point in the curve.
		CurveLoopType PreLoop;
		// Defines how to handle weighting values that are greater than the
		// last control point in the curve.
		CurveLoopType PostLoop;
		// The collection of curve keys.
		CurveKeyCollection Keys;
	};
}

#endif