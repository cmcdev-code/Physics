#include "graphics_for_particles.hpp"
#include "PARTICLE.hpp"
#include <iostream>
#include "particle_collection.hpp"
#include "particle_interactions.hpp"



int main()
{
    window_construction new_window;
    new_window.window_name = "Testing";
    new_window.modeHeight = 30;
    new_window.modeWidth = 30;
    new_window.size_shown.x = 300;
    new_window.size_shown.y = 300;
    new_window.center.x = 0;
    new_window.center.y = 0;

    graphics test(new_window);

    test.render_to_screen();


    vec3<double> testing;
    testing.x = 3;
    testing.y = 3;
    testing.z = 0;
    particle<double> new_particle_testing0(testing, testing, testing, 12, 12, 12);
    particle<double> new_particle_testing1(testing, testing, testing, 12, 12, 12);

    particle_collection<double> game;
    game.particle_container.push_back(new_particle_testing0);
    game.particle_container.push_back(new_particle_testing1);
    for (int x = 0; x < 13; x++) {
        particle_interaction::update_particle_position_collection(game);
        particle_interaction::update_particle_velocity_collection(game);
        particle_interaction::update_gravity_on_particles(game);
        std::cout << "X :" << game.particle_container.at(0).get_x_position() << " Y: " << game.particle_container.at(0).get_y_position() << std::endl;
    }
    return 0;
}