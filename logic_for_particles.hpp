#pragma once
#include "PARTICLE.hpp"

namespace logic_particles {

	template <typename T>
	void update_particle_position(particle<T>& particle_1) {
		particle_1.set_x_position(particle_1.get_x_position() + particle_1.get_x_velocity());
		particle_1.set_y_position(particle_1.get_y_position() + particle_1.get_y_velocity());
		particle_1.set_z_position(particle_1.get_z_position() + particle_1.get_z_velocity());
	}

	template <typename T>
	void update_particle_velocity(particle<T>& particle_1) {
		particle_1.set_x_velocity(particle_1.get_x_velocity() + particle_1.get_x_accleration());
		particle_1.set_y_velocity(particle_1.get_y_velocity() + particle_1.get_y_accleration());
		particle_1.set_z_velocity(particle_1.get_z_velocity() + particle_1.get_z_accleration());
	}

	template <typename T>
	void update_particle_acceleration(particle<T>& particle_1, T xA, T yA, T zA) {
		particle_1.set_x_accleration(xA);
		particle_1.set_y_accleration(yA);
		particle_1.set_z_accleration(zA);
	}

}