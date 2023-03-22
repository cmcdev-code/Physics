#pragma once
#include "PARTICLE.hpp"


template <typename T>
T sqrt(T x)
{
	if (x < 2)
		return x;
	T y = x;
	T z = (y + (x / y)) / 2;

	while (abs(y - z) >= 0.1) {
		y = z;
		z = (y + (x / y)) / 2;
	}
	return z;
}



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
	
	template <typename T>
	inline T get_distance_between_particles(particle<T>& particle_1, particle<T>& particle_2) {
		return std::sqrt(
			(particle_1.get_x_position() - particle_2.get_x_position())* (particle_1.get_x_position() - particle_2.get_x_position()) +
			(particle_1.get_y_position() - particle_2.get_y_position())*(particle_1.get_y_position() - particle_2.get_y_position()) +
			0/* for z*/
		);
	}
	template <typename T> 
	inline bool particles_touching(particle<T>& particle_1, particle<T>& particle_2) {
		return get_distance_between_particles(particle_1, particle_2)*10 <= particle_1.get_radius() + particle_2.get_radius();
	}

	template <typename T>
	inline T get_force_from_gravity_x(particle<T>& particle_1, particle<T>& particle_2, T distance_between_particles_squared, double GRAVITY = 0.000000000066743) {
		//using the unit vector but just for the x
		return -(GRAVITY) *particle_1.get_mass()*particle_2.get_mass()* (particle_1.get_i_position() - particle_2.get_i_position()) / distance_between_particles_squared;
	}
	#define get_force_from_gravity_i get_force_from_gravity_x

	template <typename T>
	inline T get_force_from_gravity_y(particle<T>& particle_1, particle<T>& particle_2, T distance_between_particles_squared, double GRAVITY = 0.000000000066743) {
		//using the unit vector but just for the y
		return -(GRAVITY)*particle_1.get_mass() * particle_2.get_mass() * (particle_1.get_j_position() - particle_2.get_j_position()) / distance_between_particles_squared;
	}
	#define get_force_from_gravity_j get_force_from_gravity_y

	template <typename T>
	inline T get_force_from_gravity_z(particle<T>& particle_1, particle<T>& particle_2, T distance_between_particles_squared, double GRAVITY = 0.000000000066743) {
		//using the unit vector but just for the z
		return -(GRAVITY)*particle_1.get_mass() * particle_2.get_mass() * (particle_1.get_z_position() - particle_2.get_z_position()) / distance_between_particles_squared;
	}
	#define get_force_from_gravity_k get_force_from_gravity_z

	template <typename T>
	void change_position(particle<T>& particle_1,T x, T y, T z) {
		particle_1.set_x_position(particle_1.get_x_position() + x);
		particle_1.set_y_position(particle_1.get_y_position() + y);
		particle_1.set_z_position(particle_1.get_z_position() + z);
	}
	template <typename T>
	void change_velocity(particle<T>& particle_1, T x, T y, T z) {
		particle_1.set_x_velocity(particle_1.get_x_velocity() + x);
		particle_1.set_y_velocity(particle_1.get_y_velocity() + y);
		particle_1.set_z_velocity(particle_1.get_z_velocity() + z);
	}
	template <typename T> 
	void change_acceleration(particle<T>& particle_1, T x, T y, T z) {
		particle_1.set_x_accleration(particle_1.get_x_accleration() + x);
		particle_1.set_y_accleration(particle_1.get_y_accleration() + x);
		particle_1.set_z_accleration(particle_1.get_z_accleration() + x);
	}
	template <typename T>
	void conservation_of_momentum(particle<T>& particle_1, particle<T>& particle_2) {
		//this function is only to be called if two objects have hit eachother
		T v1x = (particle_1.get_mass() * particle_1.get_x_velocity() * (particle_1.get_mass() - particle_2.get_mass()) + (2) * particle_2.get_mass() * particle_2.get_mass() * particle_2.get_x_velocity()) / ((particle_1.get_mass() + particle_2.get_mass()) * particle_1.get_mass());
		T v2x = (particle_2.get_mass() * particle_2.get_x_velocity() * (particle_2.get_mass() - particle_1.get_mass()) + (2) * particle_1.get_mass() * particle_1.get_mass() * particle_1.get_x_velocity()) / ((particle_2.get_mass() + particle_1.get_mass()) * particle_2.get_mass());
	
		T v1y = (particle_1.get_mass() * particle_1.get_y_velocity() * (particle_1.get_mass() - particle_2.get_mass()) + (2) * particle_2.get_mass() * particle_2.get_mass() * particle_2.get_y_velocity()) / ((particle_1.get_mass() + particle_2.get_mass()) * particle_1.get_mass());
		T v2y= (particle_2.get_mass() * particle_2.get_y_velocity() * (particle_2.get_mass() - particle_1.get_mass()) + (2) * particle_1.get_mass() * particle_1.get_mass() * particle_1.get_y_velocity()) / ((particle_2.get_mass() + particle_1.get_mass()) * particle_2.get_mass());

		T v1z = (particle_1.get_mass() * particle_1.get_z_velocity() * (particle_1.get_mass() - particle_2.get_mass()) + (2) * particle_2.get_mass() * particle_2.get_mass() * particle_2.get_z_velocity()) / ((particle_1.get_mass() + particle_2.get_mass()) * particle_1.get_mass());
		T v2z = (particle_2.get_mass() * particle_2.get_z_velocity() * (particle_2.get_mass() - particle_1.get_mass()) + (2) * particle_1.get_mass() * particle_1.get_mass() * particle_1.get_z_velocity()) / ((particle_2.get_mass() + particle_1.get_mass()) * particle_2.get_mass());

		particle_1.set_x_velocity(v1x);
		particle_1.set_y_velocity(v1y);
		particle_1.set_z_velocity(v1z);

		particle_2.set_x_velocity(v2x);
		particle_2.set_y_velocity(v2y);
		particle_2.set_z_velocity(v2z);
	}
}