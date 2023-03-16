#pragma once
#include "particle_collection.hpp"
#include "logic_for_particles.hpp"
#include <iostream>


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
	template <typename T>
	void update_gravity_on_particles(particle_collection<T>& collection) {
		//This will add the gravity for every particle to the "acceleration"
		T xAccleration(0), yAccleration(0), zAccleration(0);
		for (auto& itr : collection.particle_container) {
			for (auto& itr2 : collection.particle_container) {
				if (itr != itr2) {
					if (logic_particles::get_distance_between_particles(itr, itr2) > itr.get_radius() + itr2.get_radius()) {
						xAccleration += logic_particles::get_force_from_gravity_x(itr, itr2);
						yAccleration += logic_particles::get_force_from_gravity_y(itr, itr2);
						zAccleration += logic_particles::get_force_from_gravity_z(itr, itr2);
					}
				}
			}
		
			itr.set_x_accleration(xAccleration);
			itr.set_y_accleration(yAccleration);
			itr.set_z_accleration(zAccleration);
			//now need to set accleration to 0
			xAccleration = 0;
			yAccleration = 0;
			zAccleration = 0;
		}
	}
}