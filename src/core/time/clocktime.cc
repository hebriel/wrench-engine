//
// @authors {underdisk}
// License : LGPLv3
//

#include "clocktime.h"

namespace wrench {

	Time::Time(std::chrono::duration<long long, std::ratio<1, 1000000000>> standardDuration)
	{
		m_duration = standardDuration;
	}

	Time Time::seconds(long double s)
	{
		Time time;
		time.set_std_duration(std::chrono::nanoseconds(static_cast<uint64_t>(s * 1000000000)));
		return time;
	}

	Time Time::milliseconds(long double s)
	{
		Time time;
		time.set_std_duration(std::chrono::nanoseconds(static_cast<uint64_t>(s * 1000000)));
		return time;
	}

	Time Time::microseconds(long double s)
	{
		Time time;
		time.set_std_duration(std::chrono::nanoseconds(static_cast<uint64_t>(s * 1000)));
		return time;
	}

	Time Time::nanoseconds(uint64_t s)
	{
		Time time;
		time.set_std_duration(std::chrono::nanoseconds(s));
		return time;
	}

	long long Time::as_nanoseconds() const
	{
		return m_duration.count();
	}

	long double Time::as_microseconds() const
	{
		return m_duration.count() / 1000.0;
	}

	long double Time::as_milliseconds() const
	{
		return m_duration.count() / 1000000.0;
	}

	long double Time::as_seconds() const
	{
		return m_duration.count() / 1000000000.0;
	}

	bool Time::operator==(const Time &time) const
	{
		return as_nanoseconds() == time.as_nanoseconds();
	}

	bool Time::operator<(const Time &time) const
	{
		return as_nanoseconds() < time.as_nanoseconds();
	}

	bool Time::operator<=(const Time &time) const
	{
		return as_nanoseconds() <= time.as_nanoseconds();
	}

	bool Time::operator>(const Time &time) const
	{
		return as_nanoseconds() > time.as_nanoseconds();
	}

	bool Time::operator>=(const Time &time) const
	{
		return as_nanoseconds() >= time.as_nanoseconds();
	}

	Time Time::operator+=(const Time &time)
	{
		Time t = nanoseconds(as_nanoseconds() + time.as_nanoseconds());
		return t;
	}

	Time Time::operator-=(const Time &time)
	{
		Time t = nanoseconds(as_nanoseconds() - time.as_nanoseconds());
		return t;
	}

	void Time::set_std_duration(std::chrono::duration<long long, std::ratio<1, 1000000000>> duration)
	{
		m_duration = duration;
	}

	std::chrono::duration<long long, std::ratio<1, 1000000000>> Time::get_std_duration() const
	{
		return m_duration;
	}

	Clock::Clock() : m_start(std::chrono::high_resolution_clock::now())
	{

	}

	Time Clock::restart()
	{
		auto ret = get_elapsed_time();
		m_start = std::chrono::high_resolution_clock::now();
		return ret;
	}

	Time Clock::get_elapsed_time() const
	{
		return Time(std::chrono::high_resolution_clock::now() - m_start);
	}
}