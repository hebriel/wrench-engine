//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <chrono>

namespace wrench {

	class Time
	{
	public:

		Time() = default;

		explicit Time(std::chrono::duration<long long, std::ratio<1,1000000000>> standardDuration);

		static Time seconds(long double s);
		static Time milliseconds(long double s);
		static Time microseconds(long double s);
		static Time nanoseconds(uint64_t s);

		[[nodiscard]] long long as_nanoseconds() const;
		[[nodiscard]] long double as_microseconds() const;
		[[nodiscard]] long double as_milliseconds() const;
		[[nodiscard]] long double as_seconds() const;

		bool operator==(const Time& time) const;
		bool operator<(const Time& time) const;
		bool operator<=(const Time& time) const;
		bool operator>(const Time& time) const;
		bool operator>=(const Time& time) const;
		Time operator+=(const Time& time);
		Time operator-=(const Time& time);

		void set_std_duration(std::chrono::duration<long long, std::ratio<1,1000000000>> duration);
		[[nodiscard]] std::chrono::duration<long long, std::ratio<1,1000000000>> get_std_duration() const;

	private:

		std::chrono::duration<long long, std::ratio<1,1000000000>> m_duration {};
	};

	class Clock
	{
	public:

		Clock();
		Time restart();
		[[nodiscard]] Time get_elapsed_time() const;

	private:

		std::chrono::high_resolution_clock::time_point m_start {};
	};
}
