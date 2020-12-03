#include "Clock.h"

namespace SemperGL
{
	Clock::Clock()
	{
		m_StartPoint = std::chrono::high_resolution_clock::now();
	}

	Time Clock::Restart()
	{
		m_EndPoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_StartPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_EndPoint).time_since_epoch().count();
		
		m_StartPoint = std::chrono::high_resolution_clock::now();

		return { end - start };
	}

	void Clock::Sleep(unsigned long milliseconds)
	{
		_sleep(milliseconds);
	}
}