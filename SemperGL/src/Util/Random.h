#pragma once

#include <random>

namespace SemperGL
{

	class Random
	{
	public:
		static inline void Init()
		{
			s_RandomEngine.seed(std::random_device()());
		}

		static inline float Float()
		{
			return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
		}
		static inline float Float(float min, float max)
		{
			return min + Float() * (max - min);
		}

	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
	};

}