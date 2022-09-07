#include"UUID.h"

#include<random>

namespace SM_UUID {
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	uint64_t GetUUID() {
		return s_UniformDistribution(s_Engine);
	}
}