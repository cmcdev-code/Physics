#include <iostream>
#include "logic_for_particles.hpp"


int main() {

	vec3<double> positionLocal(3,4,5);
	vec3<double> velocityLocal(3, 4, 5);
	vec3<double> accelerationLocal(3, 4, 5);
	
	particle<double> test(positionLocal, velocityLocal, accelerationLocal, 100, 0, 100);


	std::cout << "Test : " << test.get_x_position()<<" "<<test.get_i_position()<<" "<<test.get_z_position()<<"\n";

	logic_particles::update_particle_position(test);
	std::cout << "Test : " << test.get_x_position() << " " << test.get_i_position() << " " << test.get_z_position() << "\n";






	return 0;
}
