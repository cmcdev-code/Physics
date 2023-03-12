#pragma once
#include "particle_collection.hpp"
#include "logic_for_particles.hpp"

namespace particle_interaction{
	template <typename T>
	void update_particle_position_collection(particle_collection<T>& collection) {
		for (auto& itr : collection.particle_container) {
			logic_particles::update_particle_position(itr);
		}
	}

	template <typename T>
	void update_particle_velocity_collection(particle_collection<T>& collection) {
		for (auto& itr : collection.particle_container) {
			logic_particles::update_particle_velocity(itr);
		}
	}
	template <typename T>
	void check_for_and_update_collisions(particle_collection<T>& collection) {
		for (auto& itr : collection.particle_container) {
			for (auto& itr2 : collection.particle_container) {
				if (itr != itr2) {
					if (logic_particles::particles_touching(itr, itr2)) {
						logic_particles::conservation_of_momentum(itr, itr2);
					}
				}
			}
		}
	}
}