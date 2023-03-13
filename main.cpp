#include "graphics_for_particles.hpp"
#include "PARTICLE.hpp"
#include <iostream>
#include "particle_collection.hpp"
#include "particle_interactions.hpp"
#include "graphics_and_particles.hpp"


int main()
{
 

    vec3<double> testing;
    testing.x = 3;
    testing.y = 3;
    testing.z = 0;
    particle<double> new_particle_testing0(testing, testing, testing, 12, 12, 12);
    particle<double> new_particle_testing1(testing, testing, testing, 12, 12, 12);

    
    
    window_construction testing_window(0,0,1200,1200,1000,1000,"TEsting");
    graphics_and_particles<double> testing2(testing_window);
   
    testing2.graphics_window.graphics_of_particles.push_back(* testing2.create_new_circle(testing, 30, testing2.graphics_window));
    testing2.main_particles.particle_container.push_back(*testing2.create_new_particle(testing, testing, testing, 100, 100, 30));

    int a = 0;
    while (a < 1000000) {

        testing2.render_window();
        testing2.update_all_particle_states();
        testing2.sync_graphics_and_particle_positions();
    }



    return 0;
}