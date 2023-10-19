#ifndef CS_TIMESPAN_HPP
#define CS_TIMESPAN_HPP

#include <limits>
#include <cstdint>

namespace cs {
	struct TimeSpan {
		static constexpr int64_t TicksPerMillisecond{ 10000 };
		static constexpr int64_t TicksPerSecond{ TicksPerMillisecond * 1000 };
		static constexpr int64_t TicksPerMinute{ TicksPerSecond * 60 };
		static constexpr int64_t TicksPerHour{ TicksPerMinute * 60 };
		static constexpr int64_t TicksPerDay{ TicksPerHour * 24 };

		constexpr TimeSpan() = default;
		constexpr TimeSpan(int64_t ticks) :
			_ticks(ticks) {}
		constexpr TimeSpan(int32_t hours, int32_t minutes, int32_t seconds) :
			_ticks(TimeToTicks(hours, minutes, seconds)) {}
		constexpr TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds) :
			_ticks(DayToTicks(days, hours, minutes, seconds, 0)) {}
		constexpr TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds) :
			_ticks(DayToTicks(days, hours, minutes, seconds, milliseconds)) {}

		constexpr TimeSpan operator -(TimeSpan const& t) {
			return TimeSpan(-t._ticks);
		}

		constexpr TimeSpan operator +(TimeSpan const& t) {
			return t;
		}

		constexpr friend TimeSpan operator +(TimeSpan const& t1, TimeSpan const& t2) {
			return t1.Add(t2);
		}

		constexpr friend TimeSpan operator -(TimeSpan const& t1, TimeSpan const& t2) {
			return t1.Subtract(t2);
		}

		constexpr friend bool operator ==(TimeSpan const& t1, TimeSpan const& t2) {
			return t1._ticks == t2._ticks;
		}

		constexpr friend bool operator !=(TimeSpan const& t1, TimeSpan const& t2) {
			return t1._ticks != t2._ticks;
		}

		constexpr friend bool operator <(TimeSpan const& t1, TimeSpan const& t2) {
			return t1._ticks < t2._ticks;
		}

		constexpr friend bool operator <=(TimeSpan const& t1, TimeSpan const& t2) {
			return t1._ticks <= t2._ticks;
		}

		constexpr friend bool operator >(TimeSpan const& t1, TimeSpan const& t2) {
			return t1._ticks > t2._ticks;
		}

		constexpr friend bool operator >=(TimeSpan const& t1, TimeSpan const& t2) {
			return t1._ticks >= t2._ticks;
		}

		static constexpr TimeSpan Zero() {
			return TimeSpan();
		}

		static constexpr TimeSpan MaxValue() {
			return TimeSpan(std::numeric_limits<int64_t>::max());
		}

		static constexpr TimeSpan MinValue() {
			return TimeSpan(std::numeric_limits<int64_t>::min());
		}

		static constexpr int32_t Compare(TimeSpan const& t1, TimeSpan const& t2) {
			if (t1._ticks > t2._ticks)
				return 1;

			if (t1._ticks < t2._ticks)
				return -1;

			return 0;
		}

		static constexpr TimeSpan FromDays(double value) {
			return Interval(value, MillisPerDay);
		}

		static constexpr TimeSpan FromHours(double value) {
			return Interval(value, MillisPerHour);
		}

		static constexpr TimeSpan Interval(double value, int32_t scale) {
			double tmp = value * scale;
			double millis = tmp + (value >= 0 ? 0.5 : -0.5);

			return TimeSpan(static_cast<int64_t>(millis) * TicksPerMillisecond);
		}

		static constexpr TimeSpan FromMilliseconds(double value) {
			return Interval(value, 1);
		}

		static constexpr TimeSpan FromMinutes(double value) {
			return Interval(value, MillisPerMinute);
		}

		static constexpr TimeSpan FromSeconds(double value) {
			return Interval(value, MillisPerSecond);
		}

		static constexpr TimeSpan FromTicks(int64_t value) {
			return TimeSpan(value);
		}

		constexpr int64_t Ticks() const { return _ticks; }
		constexpr int32_t Days() const { return static_cast<int32_t>(_ticks / TicksPerDay); }
		constexpr int32_t Hours() const { return static_cast<int32_t>((_ticks / TicksPerHour) % 24); }
		constexpr int32_t Milliseconds() const { return static_cast<int32_t>((_ticks / TicksPerMillisecond) % 1000); }
		constexpr int32_t Minutes() const { return static_cast<int32_t>((_ticks / TicksPerMinute) % 60); }
		constexpr int32_t Seconds() const { return static_cast<int32_t>((_ticks / TicksPerSecond) % 60); }
		constexpr double TotalDays() const { return static_cast<double>(_ticks) * DaysPerTick; }
		constexpr double TotalHours() const { return static_cast<double>(_ticks) * HoursPerTick; }

		constexpr double TotalMilliseconds() const {
			double temp = static_cast<double>(_ticks) * MillisecondsPerTick;

			if (temp > MaxMilliSeconds)
				return  static_cast<double>(MaxMilliSeconds);

			if (temp < MinMilliSeconds)
				return  static_cast<double>(MinMilliSeconds);

			return temp;
		}

		constexpr double TotalMinutes() const { return static_cast<double>(_ticks) * MinutesPerTick; }
		constexpr double TotalSeconds() const { return static_cast<double>(_ticks) * SecondsPerTick; }

		constexpr TimeSpan Add(TimeSpan const& ts) const {
			int64_t result = _ticks + ts._ticks;

			if ((_ticks >> 63 == ts._ticks >> 63) && (_ticks >> 63 != result >> 63)) {
				return TimeSpan(result, true);
			}

			return TimeSpan(result);
		}

		constexpr TimeSpan Duration() const {
			if (Ticks() == TimeSpan::MinValue().Ticks()) {
				return TimeSpan(Ticks(), true);
			}

			return TimeSpan(_ticks >= 0 ? _ticks : -_ticks);
		}

		constexpr bool Equals(TimeSpan other) const {
			return _ticks == other._ticks;
		}

		constexpr TimeSpan Negate() const {
			if (Ticks() == TimeSpan::MinValue().Ticks()) {
				return TimeSpan(Ticks(), true);
			}

			return TimeSpan(-_ticks);
		}

		constexpr TimeSpan Subtract(TimeSpan const& ts) const {
			int64_t result = _ticks - ts._ticks;

			if ((_ticks >> 63 != ts._ticks >> 63) && (_ticks >> 63 != result >> 63)) {
				return TimeSpan(result, true);
			}

			return TimeSpan(result);
		}

		constexpr bool HasOverflowException() {
			return hasOverflowException;
		}

	private:
		constexpr TimeSpan(int64_t ticks, bool overflow) :
			_ticks(ticks),
			hasOverflowException(overflow) {
		}

		static constexpr double MillisecondsPerTick = 1.0 / TicksPerMillisecond;
		static constexpr double SecondsPerTick = 1.0 / TicksPerSecond;
		static constexpr double MinutesPerTick = 1.0 / TicksPerMinute;
		static constexpr double HoursPerTick = 1.0 / TicksPerHour;
		static constexpr double DaysPerTick = 1.0 / TicksPerDay;
		static constexpr int32_t MillisPerSecond = 1000;
		static constexpr int32_t MillisPerMinute = MillisPerSecond * 60;
		static constexpr int32_t MillisPerHour = MillisPerMinute * 60;
		static constexpr int32_t MillisPerDay = MillisPerHour * 24;
		static constexpr int64_t MaxSeconds = std::numeric_limits<int64_t>::max() / TicksPerSecond;
		static constexpr int64_t MinSeconds = std::numeric_limits<int64_t>::min() / TicksPerSecond;
		static constexpr int64_t MaxMilliSeconds = std::numeric_limits<int64_t>::max() / TicksPerMillisecond;
		static constexpr int64_t MinMilliSeconds = std::numeric_limits<int64_t>::min() / TicksPerMillisecond;
		static constexpr int64_t TicksPerTenthSecond = TicksPerMillisecond * 100;

		bool hasOverflowException{ false };
		int64_t _ticks{ 0 };

		constexpr static int64_t TimeToTicks(int32_t const& hour, int32_t const& minute, int32_t const& second) {
			int64_t totalSeconds =
				static_cast<int64_t>(hour) * 3600 +
				static_cast<int64_t>(minute) * 60 +
				static_cast<int64_t>(second);

			return totalSeconds * TicksPerSecond;
		}

		constexpr static int64_t DayToTicks(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds) {
			int64_t totalMilliSeconds =
				(static_cast<int64_t>(days) * 3600 * 24 +
					static_cast<int64_t>(hours) * 3600 +
					static_cast<int64_t>(minutes) * 60 + seconds) * 1000 + milliseconds;

			return totalMilliSeconds * TicksPerMillisecond;
		}
	};
}

#endif
