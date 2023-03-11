#pragma once
#include "PARTICLE.hpp"

namespace logic_particles {


	void update_particle_position(particle<double>& particle_1) {
		particle_1.set_x_position(particle_1.get_x_position() + particle_1.get_x_velocity());
		particle_1.set_y_position(particle_1.get_y_position() + particle_1.get_y_velocity());
		particle_1.set_z_position(particle_1.get_z_position() + particle_1.get_z_velocity());
	}
	void update_particle_velocity(particle<double>& particle_1) {
		particle_1.set_x_velocity(particle_1.get_x_velocity() + particle_1.get_x_accleration()); 	
		particle_1.set_y_velocity(particle_1.get_y_velocity() + particle_1.get_y_accleration());
		particle_1.set_z_velocity(particle_1.get_z_velocity() + particle_1.get_z_accleration());
	}
	






}