#pragma once
#include "renderer.hpp"
#include <iostream>
#include <vector>
#include <list>
#include "particles/particle_collection.hpp"
#include "particles/particle_interactions.hpp"

template<typename T, int size>
class graphics_and_particles {
public:
	
	//0 argument constructor 
	graphics_and_particles();

	//1 argument constructor
	graphics_and_particles(const window_construction& window_);


	//graphics_and_particles(const graphics_and_particles& other);

	//renderer has a vector of all the objects that need to be drawn to the screen
	renderer graphics_window;

	//has a vector that is every particle instence
	particle_collection<T> main_particles;

	//will go through every particle and put it's index in the right grid cell 
	void put_particles_in_grid();

	//will loop through every particle and put the mass in the corresponding grid cell 
	void put_mass_in_grid();
	
	//sets the mass and clears the 2d array of vector indices 
	void clear_grid();

	//creates a new partice instance dynamically 
	particle<T>* create_new_particle(const vec3<T>& position_, const vec3<T>& velocity_, const vec3<T>& acceleration_, T mass_, T temp_, T radius_);

	//creates a new particle circe shape dynamically
	sf::CircleShape* create_new_circle(const vec3<T>& position_, T radius_, const renderer& graphics_for_window);

	//will calculate the color that a grid cell should be 
	void change_color_of_grid_index(short x, short y);
	
	//will create a shape to draw from all particle instinces 
	void create_graphics_from_particle_vector();
	
	//will update all grid cells gravity if the cell hasn't already been updated 
	void update_particle_gravity_grid();

	//will update the gravity for the grid using direct summation for ajacent cells and itself
	void update_particles_at_index(int i, int j);

	//will check if there is any collisons in a grid located at index i j and update all velocitys using conservation of momentum there
	void check_for_collisons(int i, int j);

	//will update the gravity  position and velocity of all particles
	void update_all_particle_states();

	//will sync the shape position with the actual particle position 
	void sync_graphics_and_particle_positions();

	//draws everything to the screen
	void render_window();


	//void create_graphics_from_particle_vector() {
	//	for (auto& itr : main_particles.particle_container) {
	//		sf::CircleShape shape(itr.get_radius());
	//		shape.setPosition(itr.get_x_position(), itr.get_y_position());
	//		shape.setFillColor(sf::Color::Blue);
	//		shape.setOrigin(itr.get_radius(), itr.get_radius());
	//		graphics_window.graphics_of_particles.push_back(shape);
	//	}
	//}

private:
	//List of indices to the particle collection at a specific grid index
	std::list<int> grid_of_particle_indices[size][size];
	//total mass of a grid cell
	double grid_of_particle_mass[size][size];

	bool already_updated[size][size];

	//size of each grid cell 
	int box_dimensions = 100;

	//will return 1-4 if top left top right bottom left bottom right corner else it will return 0
	int check_for_corner(int grid_x, int grid_y);

	//will return 1 if it is the top of the grid will return 2 if right of grid will return 3 if bottom of grid and will return 4 if left of the grid 
	//else it will return a 0 if it is not a side 
	int check_if_on_side(int grid_x, int grid_y);

	//after one run through need to set all grid cells to false 
	void already_updated_false();

	//converts cordinates to the graphics 
	sf::Vector2f cordinateConversion(T x, T y);
};

template<typename T, int size>
graphics_and_particles<T, size>::graphics_and_particles() {
	std::cout << "Window created \n";
}

template<typename T, int size>
graphics_and_particles<T, size>::graphics_and_particles(const window_construction& window_) : graphics_window(window_) {
	std::cout << "Window created \n";
}

template<typename T,int size>
void graphics_and_particles<T, size>::put_mass_in_grid() {
	for (auto& itr : main_particles.particle_container) {
		int x = itr.get_x_position() / box_dimensions + size / 2;
		int y = itr.get_y_position() / box_dimensions + size / 2;
		grid_of_particle_mass[x][y] += itr.get_mass();
	}
}

template<typename T, int size>
void graphics_and_particles<T, size>::put_particles_in_grid() {
	int index = 0;
	for (auto& itr : main_particles.particle_container) {
		int x, y;
		x = itr.get_x_position() / box_dimensions + size / 2;
		y = itr.get_y_position() / box_dimensions + size / 2;
		grid_of_particle_indices[x][y].push_back(index);
		index++;
	}
}

template<typename T, int size>
void graphics_and_particles<T, size>::clear_grid() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			grid_of_particle_mass[i][j] = 0;
			grid_of_particle_indices[i][j].clear();
		}
	}
}
template<typename T, int size>
particle<T>* graphics_and_particles<T, size>::create_new_particle(const vec3<T>& position_, const vec3<T>& velocity_, const vec3<T>& acceleration_, T mass_, T temp_, T radius_) {
	return new particle<T>(position_, velocity_, acceleration_, mass_, temp_, radius_);
}
template<typename T, int size>
sf::CircleShape* graphics_and_particles<T, size>::create_new_circle(const vec3<T>& position_, T radius_, const renderer& graphics_for_window) {
	sf::CircleShape* circle_object = new sf::CircleShape(radius_);
	circle_object->setPosition(position_.x, position_.y);
	return circle_object;
}
template<typename T, int size>
void graphics_and_particles<T, size>::change_color_of_grid_index(short x, short y) {
	for (auto& itr : grid_of_particle_indices[x][y]) {
		graphics_window.graphics_of_particles.at(itr).setFillColor(sf::Color(grid_of_particle_mass[x][y] * 10, 100, 1 / ((grid_of_particle_mass[x][y]) + 100)));
	}
}
template<typename T, int size>
void graphics_and_particles<T, size>::create_graphics_from_particle_vector() {
	for (auto& itr : main_particles.particle_container) {
		sf::RectangleShape shape(sf::Vector2f(itr.get_radius(), itr.get_radius()));
		shape.setPosition(itr.get_x_position(), itr.get_y_position());
		shape.setFillColor(sf::Color::Blue);
		shape.setOrigin(itr.get_radius(), itr.get_radius());
		graphics_window.graphics_of_particles.push_back(shape);
	}
}
template <typename T, int size>
int graphics_and_particles<T, size>::check_for_corner(int grid_x, int grid_y) {
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
template <typename T, int size>
int graphics_and_particles<T, size>::check_if_on_side(int grid_x, int grid_y) {
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
template <typename T, int size>
void graphics_and_particles<T, size>::update_particles_at_index(int i, int j) {
	if (check_for_corner(i, j) == 0) {
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
			if (grid_of_particle_mass[i - 1][j] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i - 1][j]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//right of grid update
			if (grid_of_particle_mass[i + 1][j] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i + 1][j]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//top of grid update
			if (grid_of_particle_mass[i][j - 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i][j - 1]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//bottom of grid update
			if (grid_of_particle_mass[i][j + 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i][j + 1]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//corners of grid update now

			//top left of grid
			if (grid_of_particle_mass[i - 1][j - 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i - 1][j - 1]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//top right of grid
			if (grid_of_particle_mass[i + 1][j - 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i + 1][j - 1]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//bottom left of grid
			if (grid_of_particle_mass[i - 1][j + 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i - 1][j + 1]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//bottom right of grid 
			if (grid_of_particle_mass[i + 1][j + 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i + 1][j + 1]) {
					particle_interaction::update_gravity_on_particles(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
		}
	}
}

template <typename T, int size>
void graphics_and_particles<T, size>::check_for_collisons(int i, int j) {
	if (check_for_corner(i, j) == 0) {
		//this means that it is not a corner 
		for (auto& itr_1 : grid_of_particle_indices[i][j]) {
			//same grid update
			//check if mass is 0
			if (grid_of_particle_mass[i][j] != 0) {
				for (auto& itr_2 : grid_of_particle_indices[i][j]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}

			//left grid update
			if (grid_of_particle_mass[i - 1][j] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i - 1][j]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//right of grid update
			if (grid_of_particle_mass[i + 1][j] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i + 1][j]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//top of grid update
			if (grid_of_particle_mass[i][j - 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i][j - 1]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//bottom of grid update
			if (grid_of_particle_mass[i][j + 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i][j + 1]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//corners of grid update now

			//top left of grid
			if (grid_of_particle_mass[i - 1][j - 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i - 1][j - 1]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//top right of grid
			if (grid_of_particle_mass[i + 1][j - 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i + 1][j - 1]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//bottom left of grid
			if (grid_of_particle_mass[i - 1][j + 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i - 1][j + 1]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
			//bottom right of grid 
			if (grid_of_particle_mass[i + 1][j + 1] > 0) {
				for (auto& itr_2 : grid_of_particle_indices[i + 1][j + 1]) {
					particle_interaction::check_for_and_update_collisions(main_particles.particle_container.at(itr_1), main_particles.particle_container.at(itr_2));
				}
			}
		}
	}
}

template <typename T, int size>
void graphics_and_particles<T, size>::already_updated_false() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			already_updated[i][j] = 0;
		}
	}
}
template <typename T, int size>
void graphics_and_particles<T, size>::update_particle_gravity_grid() {
	//is list index already updated 
	for (auto& itr : main_particles.particle_container) {
		short i = itr.get_x_position() / box_dimensions + size / 2;
		short j = itr.get_y_position() / box_dimensions + size / 2;
		if (!already_updated[i][j]) {
			update_particles_at_index(i, j);
			//check_for_collisons(i, j);
			already_updated[i][j] = 1;

			change_color_of_grid_index(i, j);

		}
	}
}
template <typename T, int size>
void graphics_and_particles<T, size>::update_all_particle_states() {
	put_particles_in_grid();
	put_mass_in_grid();
	already_updated_false();

	update_particle_gravity_grid();
	particle_interaction::update_particle_position_collection(main_particles);
	particle_interaction::update_particle_velocity_collection(main_particles);
	for (auto& itr : main_particles.particle_container) {
		itr.set_x_accleration(0.0f);
		itr.set_y_accleration(0.0f);
	}
	clear_grid();
}
sf::CircleShape test;
template <typename T, int size>
void graphics_and_particles<T, size>::sync_graphics_and_particle_positions() {
	for (int i = 0; i < main_particles.particle_container.size(); i++) {
		graphics_window.graphics_of_particles.at(i).setPosition(cordinateConversion(main_particles.particle_container.at(i).get_x_position(), main_particles.particle_container.at(i).get_y_position()));
	}
}

template <typename T, int size>
void graphics_and_particles<T, size>::render_window() {
	graphics_window.window.clear();
	graphics_window.render_to_screen();
}

template <typename T, int size>
sf::Vector2f graphics_and_particles<T, size>::cordinateConversion(T x, T y) {
	return sf::Vector2f(x, -y);
}
template class graphics_and_particles<float, 1>;