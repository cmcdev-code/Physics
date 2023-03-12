#pragma once
#include "PARTICLE.hpp"
#include <vector>

template <typename T>
class particle_collection {
	public:
		std::vector<particle<T>> particle_container;
};