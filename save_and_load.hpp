#pragma once
#include <fstream>
#include "graphics_and_particles.hpp"
#include <string>
#include <iostream>
#include "PARTICLE.hpp"
#include "Dependecies/json\json.hpp"
#include <vector>

static std::string FILE_NAME(bool flag=1) {
	if (flag) {
		std::cout << "What is the name of the file that you would like to save the data to?" << std::endl;
	}
	else {
		std::cout << "What is the name of the file that you would like to read the data from?" << std::endl;
	}

	std::string file_name = "";
	std::getline(std::cin >> std::ws, file_name);
	return file_name;
}
static short ERROR_CHECKING(short range_lower, short range_upper, std::string Message) {
	short user_input = 0;
	while (true) {
		std::cout << Message << std::endl;
		std::cin >> user_input;
		if (user_input >= range_lower && user_input <= range_upper && std::cin.good()) {
			return user_input;
		}
		else {
			std::cout << "Error: Please enter a number between " << range_lower << " and " << range_upper << "." << std::endl;
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
template <typename T>
static void WRITE_TO_CSV(std::ofstream& out, const particle<T>& particle_) {
	out << particle_.get_x_position() << "," << particle_.get_y_position() << "," << particle_.get_z_position() << "," <<
		particle_.get_x_velocity() << "," << particle_.get_y_velocity()<<"," << particle_.get_z_velocity() <<"," <<
		particle_.get_x_accleration()<<"," << particle_.get_y_accleration()<<"," << particle_.get_z_accleration()<<"," <<
		particle_.get_temp()<<"," << particle_.get_mass()<<"," << particle_.get_radius() << "\n";
}
template <typename T>
static void WRITE_TO_TXT(std::ofstream& out, const particle<T>& particle_) {
	out << particle_.get_x_position() << "\n";
	out << particle_.get_y_position() << "\n";
	out << particle_.get_z_position() << "\n";
	out << particle_.get_x_velocity() << "\n";
	out << particle_.get_y_velocity() << "\n";
	out << particle_.get_z_velocity() << "\n";
	out << particle_.get_x_accleration() << "\n";
	out << particle_.get_y_accleration() << "\n";
	out << particle_.get_z_accleration() << "\n";
	out << particle_.get_temp() << "\n";
	out << particle_.get_mass() << "\n";
	out << particle_.get_radius() << "\n";
}

namespace save_to_file {
	template <typename T>

	void write_to_file_particles(const graphics_and_particles<T>& particles_)
	{
		short user_choice = ERROR_CHECKING(1, 3, "Which file type would you like to write to?\nEnter 1 for .json\n Enter 2 for .csv\n Enter 3 for .txt");

		if (user_choice == 1) {
			std::string file_name = FILE_NAME();
			std::ofstream out(file_name + ".json");
			out << "{\n";
			out << "\"data type\":" << "\"" << std::string(typeid(T).name()) << "\"" << ",\n";
			out << "\"objects\": [\n";
			int counter = 0;
			for (auto& itr : particles_.main_particles.particle_container) {
				WRITE_TO_JSON(out, itr);
				if (counter < particles_.main_particles.particle_container.size() - 1) {
					out << ",";
				}
				counter++;
			}
			out << "]\n";
			out << "}";
			out.close();
		}
		if (user_choice == 2) {
			std::string file_name = FILE_NAME();
			std::ofstream out(file_name + ".csv");
			for (auto& itr : particles_.main_particles.particle_container) {
				WRITE_TO_CSV(out, itr);
			}
			out.close();
		}
		if (user_choice == 3) {
			std::string file_name = FILE_NAME();
			std::ofstream out(file_name + ".txt");
			for (auto& itr : particles_.main_particles.particle_container) {
				WRITE_TO_TXT(out, itr);
			}
			out.close();

		}
	}
}

//{
//	"data type":"double",
//		"objects" : [
//	{
//		"position" :{ "x": 3, "y" : 3, "z" : 0},
//			"velocity" : { "x": 3, "y" : 3, "z" : 0},
//			"accleration" : { "x": 3, "y" : 3, "z" : 0},
//			"temp" : 100,
//			"mass" : 100,
//			"radius" : 30
//	}
//	, {
//	"position" :{ "x": 3, "y" : 3, "z" : 0},
//	"velocity" : { "x": 3, "y" : 3, "z" : 0},
//	"accleration" : { "x": 3, "y" : 3, "z" : 0},
//	"temp" : 100,
//	"mass" : 100,
//	"radius" : 30
//	}
//		, {
//		"position" :{ "x": 3, "y" : 3, "z" : 0},
//		"velocity" : { "x": 3, "y" : 3, "z" : 0},
//		"accleration" : { "x": 3, "y" : 3, "z" : 0},
//		"temp" : 100,
//		"mass" : 100,
//		"radius" : 30
//		}
//		]
//}

template <typename T>
std::vector<particle<T>> read_from_file(std::ifstream& in) {
	std::vector<particle<T>> particles_read_from_file;
	using json = nlohmann::json;
	json data = json::parse(in);
	//found this here https://stackoverflow.com/questions/53324659/c-json-array-parsing-using-nlohmannjson
	for (auto& itr : data["objects"]) {
		vec3<T> positions;
		vec3<T> velocitys;
		vec3<T> acclerations;
		T temp;
		T mass;
		T radius;
		positions.x = itr["position"]["x"];
		positions.y = itr["position"]["y"];
		positions.z = itr["position"]["z"];

		velocitys.x = itr["velocity"]["x"];
		velocitys.y = itr["velocity"]["y"];
		velocitys.z = itr["velocity"]["z"];

		acclerations.x = itr["accleration"]["x"];
		acclerations.y = itr["accleration"]["y"];
		acclerations.z = itr["accleration"]["z"];

		temp = itr["temp"];
		mass = itr["mass"];
		radius = itr["radius"];
		particles_read_from_file.push_back(particle<T>(positions, velocitys, acclerations, temp, mass, radius));
	}
	return particles_read_from_file;
}

namespace load_from_file {
	template <typename T>
	std::vector<particle<T>> load_from_file_graphics_and_particles() {
		short user_choice = ERROR_CHECKING(1, 3, "Which file type would you like to read from?\nEnter 1 for .json\n Enter 2 for .csv\n Enter 3 for .txt");
		if (user_choice == 1) {
			std::string file_name = FILE_NAME();
		//	return read_data<T>(file_name + ".json");
			
		}
	}
}