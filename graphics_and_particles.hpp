#pragma once
#include "logic_for_particles.hpp"
#include "graphics_for_particles.hpp"
#include "particle_collection.hpp"
#include "particle_interactions.hpp"
#include <iostream>

template<typename T>
class graphics_and_particles {
	public:

		graphics_and_particles() {
			std::cout << "Window created \n";
		}
		graphics_and_particles(const window_construction& window_): graphics_window(window_) {
			std::cout << "Window created \n";
		}

		graphics graphics_window;
		particle_collection<T> main_particles;

		particle<T>* create_new_particle(const vec3<T>& position_, const vec3<T>& velocity_, const vec3<T>& acceleration_, T mass_, T temp_, T radius_) {
			return new particle<T>(position_, velocity_, acceleration_, mass_, temp_, radius_);
		}
		sf::CircleShape* create_new_circle(const vec3<T>& position_,T radius_, const graphics& graphics_for_window) {
			return new sf::CircleShape(radius_);
		}
		void update_all_particle_states() {
			particle_interaction::check_for_and_update_collisions(main_particles);
			particle_interaction::update_gravity_on_particles(main_particles);
			particle_interaction::update_particle_position_collection(main_particles);
			particle_interaction::update_particle_velocity_collection(main_particles);
		}
		void sync_graphics_and_particle_positions() {
			for (int i = 0; i < main_particles.particle_container.size(); i++) {
				graphics_window.graphics_of_particles.at(i).setPosition(sf::Vector2f(main_particles.particle_container.at(i).get_x_position(), main_particles.particle_container.at(i).get_y_position()));
			}
		}
		void render_window() {
			sf::Event event;
			while (graphics_window.window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					graphics_window.window.close();
			}
			graphics_window.window.clear();
			graphics_window.render_to_screen();
		}
};