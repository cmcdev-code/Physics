#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>

struct window_construction {
	sf::Vector2f center;
	sf::Vector2f size_shown;

	std::string window_name;

	unsigned int modeWidth;
	unsigned int modeHeight;
};

class graphics {
	public:

	graphics(const window_construction & window_) {
		view.setCenter(window_.center);
		view.setSize(window_.size_shown);
		window.create(sf::VideoMode(window_.modeWidth, window_.modeHeight),window_.window_name);
	}
	sf::View view;
	sf::RenderWindow window;

	std::vector<sf::CircleShape> graphics_of_particles;
	
	void render_to_screen() {

		for (auto& itr : graphics_of_particles) {
			window.draw(itr);
		}
		//display to the screen
		window.display();
	}

};
