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
	window_construction(
		float center_x = 0,
		float center_y = 0,
		float size_shown_x = 180,
		float size_shown_y = 180,
		unsigned int height_ = 10,
		unsigned int width = 10,
		std::string Window_name = "Debug")
	{
		center.x = center_x;
		center.y = center_y;
		size_shown.x = size_shown_x;
		size_shown.y = size_shown_y;
		modeHeight = height_;
		modeWidth = width;
		window_name = Window_name;
	}

};
#include <iostream>
class graphics {
	public:
		graphics() {};

	graphics(const window_construction & window_) {
		view.setCenter(window_.center);
		view.setSize(window_.size_shown);
		window.create(sf::VideoMode(window_.modeHeight, window_.modeWidth),window_.window_name);
	}
	sf::View view;
	sf::RenderWindow window;

	//std::vector<sf::CircleShape> graphics_of_particles;
	std::vector<sf::RectangleShape> graphics_of_particles;
	void render_to_screen() {
		window.setView(view);
		for (auto& itr : graphics_of_particles) {
			window.draw(itr);
		}
		window.display();
	}
};