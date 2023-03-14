#pragma once
#include <fstream>
#include "graphics_and_particles.hpp"
#include <string>
#include <iostream>

static std::string FILE_NAME() {
	std::cout << "What is the name of the file that you would like to save the data to?" << std::endl;
	std::string file_name="";
	std::getline(std::cin>>std::ws, file_name);
	return file_name;
}
static short ERROR_CHECKING(short range_lower, short range_upper, std::string Message) {
	short user_input=0;
	while (true) {
		std::cout << Message << std::endl;
		std::cin >> user_input;
		if (user_input >= range_lower && user_input <= range_upper && std::cin.good()) {
			return user_input;
		}
		else {
			std::cout << "Error: Please enter a number between " << range_lower << " and " << range_upper <<"." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}
template <typename T>
static void WRITE_TO_JSON(std::ofstream& out, const particle<T>& particle_) {
	out << "{ \n";
		out << "\"position\" :{ \"x\": " << particle_.get_x_position() << ", \"y\": " << particle_.get_y_position() << ", \"z\": " << particle_.get_z_position() << "},\n";
		out << "\"velocity\" :{ \"x\": " << particle_.get_x_velocity() << ", \"y\": " << particle_.get_y_velocity() << ", \"z\": " << particle_.get_z_velocity() << "},\n";
		out << "\"accleration\" :{ \"x\": " << particle_.get_x_accleration() << ", \"y\": " << particle_.get_y_accleration() << ", \"z\": " << particle_.get_z_accleration() << "},\n";
		out << "\"temp\" : " << particle_.get_temp() << ",\n";
		out << "\"mass\" : " << particle_.get_mass() << ",\n";
		out << "\"radius\" : " << particle_.get_radius() << "\n";
		out << "}\n";
}

namespace save_to_file{
	template <typename T>

	void write_to_file_particles(const graphics_and_particles<T> & particles_)
	{
		short user_choice = ERROR_CHECKING(1, 3, "Which file type would you like to write to?\nEnter 1 for .json\n Enter 2 for .csv\n Enter 3 for .txt");
		switch (user_choice)
		{
		case 1:
			std::string file_name = FILE_NAME();
			std::ofstream out(file_name + ".json");
			out << "{\n";
			out << "\"data type\":" <<"\"" << std::string(typeid(T).name()) << "\"" << ",\n";
			int counter = 0;
			for (auto& itr : particles_.main_particles.particle_container) {
				WRITE_TO_JSON(out, itr);
				if (counter < particles_.main_particles.particle_container.size()-1) {
					out << ",";
				}
				counter++;
			}
			out << "}\r";
			out.close();
			

		
		}
		
	}
}