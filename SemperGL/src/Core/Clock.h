#pragma once
#include <chrono>
#include "Time.h"


namespace SemperGL
{
	class Clock
	{
	public:
		Clock();
		~Clock() = default;

		Time Restart();

		static void Sleep(unsigned long milliseconds);

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartPoint, m_EndPoint;
	};
}