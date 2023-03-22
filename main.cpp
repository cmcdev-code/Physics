#include "graphics_for_particles.hpp"
#include "PARTICLE.hpp"
#include <iostream>
#include "particle_collection.hpp"
#include "particle_interactions.hpp"
#include "graphics_and_particles.hpp"
#include "save_and_load.hpp"
#include <chrono>

int main()
{

    window_construction testing_window(0, 0, 2560, 1440, 2560, 1440);
    graphics_and_particles<float,130> game(testing_window);
    game.main_particles.particle_container = load_from_file::load_from_file_particles<float>();
    game.create_graphics_from_particle_vector();
    
    game.graphics_window.view.zoom(5.0f);
    int numberOfSteps = 0;
    auto start= std::chrono::high_resolution_clock::now();
    while (numberOfSteps<100000) {
        game.render_window();
        game.update_all_particle_states();
        game.sync_graphics_and_particle_positions();
        numberOfSteps++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(diff);
   
    std::cout << "Time is : " << duration.count()/100 << std::endl;
    //save_to_file::write_to_file_particles(game);

    return 0;
}