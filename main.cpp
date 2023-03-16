#include "graphics_for_particles.hpp"
#include "PARTICLE.hpp"
#include <iostream>
#include "particle_collection.hpp"
#include "particle_interactions.hpp"
#include "graphics_and_particles.hpp"
#include "save_and_load.hpp"


int main()
{
    
    window_construction testing_window(0, 0, 2560, 1440, 2560, 1440);
    graphics_and_particles<double> game(testing_window);
    game.main_particles.particle_container = load_from_file::load_from_file_particles<double>();
    game.create_graphics_from_particle_vector();

    game.graphics_window.view.zoom(10.0f);
    int numberOfSteps = 0;
    while (numberOfSteps<10000000) {
        game.render_window();
        game.update_all_particle_states();
        game.sync_graphics_and_particle_positions();
        numberOfSteps++;
    }
    save_to_file::write_to_file_particles(game);

    return 0;
}