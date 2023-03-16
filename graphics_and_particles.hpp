#pragma once
#include "logic_for_particles.hpp"
#include "graphics_for_particles.hpp"
#include "particle_collection.hpp"
#include "particle_interactions.hpp"
#include <iostream>
#include <vector>




template<typename T,int size>
class graphics_and_particles {
public:

	graphics_and_particles() {
		std::cout << "Window created \n";
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				grid_of_particle_mass[i][j] = 0;
			}
		}
	}
	graphics_and_particles(const window_construction& window_) : graphics_window(window_) {
		std::cout << "Window created \n";
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				grid_of_particle_mass[i][j] = 0;
			}
		}
	}
	graphics_and_particles(const graphics_and_particles& other)
		: graphics_window(other.graphics_window), main_particles(other.main_particles)
	{
		std::cout << "Window created \n";
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				grid_of_particle_mass[i][j] = 0;
			}
		}
	}


	graphics graphics_window;
	particle_collection<T> main_particles;
	std::vector<int> grid_of_particle_indices[size][size];
	double grid_of_particle_mass[size][size];
private:
	T box_dimensions = 1000;

public:
	void put_particles_in_grid() {
		int index = 0;
		for (auto& itr : main_particles.particle_container) {
			int x, y;
			x = itr.get_x_position() / 1000+size/2;
			y = itr.get_z_position() / 1000+size/2;
			grid_of_particle_indices[x][y].push_back(index);
			grid_of_particle_mass[x][y]+=(itr.get_mass());
			index++;
		}
	}
		particle<T>* create_new_particle(const vec3<T>& position_, const vec3<T>& velocity_, const vec3<T>& acceleration_, T mass_, T temp_, T radius_) {
			return new particle<T>(position_, velocity_, acceleration_, mass_, temp_, radius_);
		}
		sf::CircleShape* create_new_circle(const vec3<T>& position_,T radius_, const graphics& graphics_for_window) {
			return new sf::CircleShape(radius_)->setPosition(position_.x,position_.y);
		}

		void create_graphics_from_particle_vector() {
			for (auto& itr : main_particles.particle_container) {
				sf::CircleShape shape(itr.get_radius());
				shape.setPosition(itr.get_x_position(), itr.get_y_position());
				shape.setFillColor(sf::Color::Blue);
				shape.setOrigin(itr.get_radius(), itr.get_radius());
				graphics_window.graphics_of_particles.push_back(shape);
			}
		}
private:
	//will return 1-4 if top left top right bottom left bottom right corner else it will return 0
	int check_for_corner(int grid_x, int grid_y) {
		if (grid_x - 1 < 0 && grid_y - 1 < 0) {
			return 1;//top left 
		}
		if (grid_x + 1 >= size && grid_y - 1 < 0) {
			return 2;//top right
		}
		if (grid_x - 1 < 0 && grid_y + 1 >= size) {
			return 3;//bottom left
		}
		if (grid_x + 1 >= size && grid_y + 1 >= size) {
			return 4;//bottom right
		}
		else {
			return 0;//not a corner
		}
	}
	//will return 1 if it is the top of the grid will return 2 if right of grid will return 3 if bottom of grid and will return 4 if left of the grid 
	//else it will return a 0 if it is not a side 
	int check_if_on_side(int grid_x, int grid_y) {
		if (grid_y - 1 < 0) {
			return 1;//top of grid
		}
		if (grid_x + 1 >= size) {
			return 2;//right of the grid
		}
		if (grid_y + 1 >= size) {
			return 3;//bottom of grid
		}
		if (grid_x - 1 < 0) {
			return 4;//left of the grid
		}
		else {
			return 0;//not a side of the grid
		}
	}

public:
		void update_particle_gravity_grid() {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (check_for_corner(i,j) == 0) {
						//this means that it is not a corner 
						for (auto& itr_1 : grid_of_particle_indices[i][j]) {
							//same grid update
							//check if mass is 0
							if (grid_of_particle_mass[i][j] != 0) {
								for (auto& itr_2 : grid_of_particle_indices[i][j]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							
							//left grid update
							if (grid_of_particle_mass[i-1][j] != 0) {
								for (auto& itr_2 : grid_of_particle_indices[i - 1][j]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							//right of grid update
							if (grid_of_particle_mass[i+1][j] != 0){
								for (auto& itr_2 : grid_of_particle_indices[i + 1][j]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							//top of grid update
							if (grid_of_particle_mass[i][j-1] != 0){
								for (auto& itr_2 : grid_of_particle_indices[i][j - 1]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							//bottom of grid update
							if (grid_of_particle_mass[i][j + 1]!= 0) {
								for (auto& itr_2 : grid_of_particle_indices[i][j + 1]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							//corners of grid update now

							//top left of grid
							if (grid_of_particle_mass[i - 1][j - 1] != 0) {
								for (auto& itr_2 : grid_of_particle_indices[i - 1][j - 1]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							//top right of grid
							if (grid_of_particle_mass[i + 1][j - 1] != 0) {
								for (auto& itr_2 : grid_of_particle_indices[i + 1][j - 1]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							//bottom left of grid
							if (grid_of_particle_mass[i - 1][j + 1] != 0) {
								for (auto& itr_2 : grid_of_particle_indices[i - 1][j + 1]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
							//bottom right of grid 
							if (grid_of_particle_mass[i + 1][j + 1] != 0) {
								for (auto& itr_2 : grid_of_particle_indices[i + 1][j + 1]) {
									particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
								}
							}
						}
					}
				}
			}
		}
		void update_all_particle_states() {
			//put_particles_in_grid();
			//particle_interaction::check_for_and_update_collisions(main_particles);
		//	update_particle_gravity_grid();
			//setting mass of all grid objects to 0
			particle_interaction::update_gravity_on_particles(main_particles);
			particle_interaction::update_particle_position_collection(main_particles);
			particle_interaction::update_particle_velocity_collection(main_particles);
		}
		void sync_graphics_and_particle_positions() {
			for (int i = 0; i < main_particles.particle_container.size(); i++) {
				graphics_window.graphics_of_particles.at(i).setPosition(cordinateConversion(main_particles.particle_container.at(i).get_x_position(), main_particles.particle_container.at(i).get_y_position()));
			}
		}
		void render_window() {
			sf::Event event;
			while (graphics_window.window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					graphics_window.window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					sf::Vector2f window_size=graphics_window.view.getSize();
					graphics_window.view.setSize(window_size.x / 1.1, window_size.y / 1.1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					sf::Vector2f window_size = graphics_window.view.getSize();
					graphics_window.view.setSize(window_size.x * 1.1, window_size.y * 1.1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					sf::Vector2f window_center = graphics_window.view.getCenter();
					graphics_window.view.setCenter(window_center.x,window_center.y-60);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					sf::Vector2f window_center = graphics_window.view.getCenter();
					graphics_window.view.setCenter(window_center.x - 60, window_center.y);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					sf::Vector2f window_center = graphics_window.view.getCenter();
					graphics_window.view.setCenter(window_center.x, window_center.y +60);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					sf::Vector2f window_center = graphics_window.view.getCenter();
					graphics_window.view.setCenter(window_center.x + 60, window_center.y);
				}

			}
			graphics_window.window.clear();
			graphics_window.render_to_screen();
		}

private:
	sf::Vector2f cordinateConversion(T x, T y) {
		return sf::Vector2f(x, -y);
	}
};