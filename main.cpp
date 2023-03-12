#include "graphics_for_particles.hpp"

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

   
   
    return 0;
}