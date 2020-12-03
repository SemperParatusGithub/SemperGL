#pragma once


namespace SemperGL
{

	class Time
	{
	public:
		Time(long long nanoseconds) : 
			m_Nanoseconds(nanoseconds)
		{}

		template<typename T>
		inline T asSeconds() const
		{
			return (T)(m_Nanoseconds / 1000000000.f);
		}
		template<typename T>
		inline T asMilliseconds() const
		{
			return (T)(m_Nanoseconds / 1000000.f);
		}	
		template<typename T>
		inline T asMicroseconds() const
		{
			return (T)(m_Nanoseconds / 1000.f);
		}
		template<typename T>
		inline T asNanoseconds() const
		{
			return (T)(m_Nanoseconds);
		}

	private:
		long long m_Nanoseconds;
	};
}