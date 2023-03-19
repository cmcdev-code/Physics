#include "graphics_and_particles.hpp"
#include "save_and_load.hpp"
#include <iostream>
#include <chrono>



window_construction testing_window(0, 0, 2560, 1440, 2560, 1440);
graphics_and_particles<float,1000> game(testing_window);
int main()
{

    

    game.main_particles.particle_container = load_from_file::load_from_file_particles<float>();
    game.create_graphics_from_particle_vector();

 
    game.graphics_window.view.zoom(1.0f);
    int numberOfSteps = 0;
    auto start= std::chrono::high_resolution_clock::now();
    while (numberOfSteps<1000) {
        game.render_window();
        game.update_all_particle_states();
        game.sync_graphics_and_particle_positions();
        numberOfSteps++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(diff);
   
    std::cout << "Time is : " << duration.count()/1000 << std::endl;
    //save_to_file::write_to_file_particles(game);

    return 0;
}