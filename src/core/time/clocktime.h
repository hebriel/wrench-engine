//
// @authors {underdisk}
// License : LGPLv3
//

#pragma once

#include <chrono>

namespace wrench {

	/**
	* @brief Describes a time interval or duration
	*/
	class Time
	{
	public:

		/**
		* @brief Default constructor
		*/
		Time() = default;

		/**
		* @brief Main constructor. Takes a standard C++ chrono duration as an argument
		*/
		explicit Time(std::chrono::duration<long long, std::ratio<1,1000000000>> standardDuration);

		/**
		* @brief Seconds
		*/
		static Time seconds(long double s);

		/**
		* @brief Thousands of seconds (10^-3 second)
		*/
		static Time milliseconds(long double s);

		/**
		* @brief Thousands of milliseconds (10^-6 second)
		*/
		static Time microseconds(long double s);

		/**
		* @brief Thousands of microseconds (10^-9 second)
		*/
		static Time nanoseconds(uint64_t s);

		/**
		* @brief Time in nanoseconds
		*/
		[[nodiscard]] long long as_nanoseconds() const;

		/**
		* @brief Time in microseconds
		*/
		[[nodiscard]] long double as_microseconds() const;

		/**
		* @brief Time in milliseconds
		*/
		[[nodiscard]] long double as_milliseconds() const;

		/**
		* @brief Time in seconds
		*/
		[[nodiscard]] long double as_seconds() const;

		/**
		* @brief Is the time equal to another time ?
		*/
		bool operator==(const Time& time) const;

		/**
		* @brief Is the time smaller to another time ?
		*/
		bool operator<(const Time& time) const;

		/**
		* @brief Is the time smaller or equal to another time ?
		*/
		bool operator<=(const Time& time) const;

		/**
		* @brief Is the time bigger to another time ?
		*/
		bool operator>(const Time& time) const;

		/**
		* @brief Is the time bigger or equal to another time ?
		*/
		bool operator>=(const Time& time) const;

		/**
		* @brief Add some time to the time
		*/
		Time operator+=(const Time& time);

		/**
		* @brief Remove some time to the time
		*/
		Time operator-=(const Time& time);

		/**
		* @brief Set the time value from a standard C++ chrono duration
		*/
		void set_std_duration(std::chrono::duration<long long, std::ratio<1,1000000000>> duration);

		/**
		* @brief Time value formated as a standard C++ chrono duration
		*/
		[[nodiscard]] std::chrono::duration<long long, std::ratio<1,1000000000>> get_std_duration() const;

	private:

		std::chrono::duration<long long, std::ratio<1,1000000000>> m_duration {};
	};

	/**
	* @brief Counts the time between the moment it has been started and the present
	*/
	class Clock
	{
	public:

		/**
		* @brief Main constructor
		*/
		Clock();

		/**
		* @brief Restarts the clock
		*
		* @return Same as get_elapsed_time()
		*/
		Time restart();

		/**
		* @brief Get the time between the moment it has been started and now
		*/
		[[nodiscard]] Time get_elapsed_time() const;

	private:

		std::chrono::high_resolution_clock::time_point m_start {};
	};
}
