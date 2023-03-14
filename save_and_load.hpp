#pragma once
#include <fstream>
#include "graphics_and_particles.hpp"
#include <string>
#include <iostream>


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

#include <vector>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>

static struct Object {
	struct Position {
		double x;
		double y;
		double z;
	} position;
	struct Velocity {
		double x;
		double y;
		double z;
	} velocity;
	struct Acceleration {
		double x;
		double y;
		double z;
	} acceleration;
	double temp;
	double mass;
	double radius;
};

static std::vector<Object> read_data(const std::string& filename) {
	std::ifstream input(filename);
	std::stringstream buffer;
	buffer << input.rdbuf();
	input.close();
	std::string data = buffer.str();

	std::vector<Object> objects;
	size_t start = data.find("{");
	while (start != std::string::npos) {
		size_t end = data.find("}", start);
		std::string object_str = data.substr(start, end - start + 1);

		Object object;

		size_t pos = object_str.find("\"position\"");
		if (pos != std::string::npos) {
			size_t start_pos = object_str.find("{", pos);
			size_t end_pos = object_str.find("}", start_pos);
			std::string position_str = object_str.substr(start_pos, end_pos - start_pos + 1);

			std::stringstream position_ss(position_str);
			std::string position_token;
			position_ss >> position_token >> object.position.x >> object.position.y >> object.position.z;
		}
		pos = object_str.find("\"velocity\"");
		if (pos != std::string::npos) {
			size_t start_pos = object_str.find("{", pos);
			size_t end_pos = object_str.find("}", start_pos);
			std::string velocity_str = object_str.substr(start_pos, end_pos - start_pos + 1);

			std::stringstream velocity_ss(velocity_str);
			std::string velocity_token;
			velocity_ss >> velocity_token >> object.velocity.x >> object.velocity.y >> object.velocity.z;
		}
		pos = object_str.find("\"acceleration\"");
		if (pos != std::string::npos) {
			size_t start_pos = object_str.find("{", pos);
			size_t end_pos = object_str.find("}", start_pos);
			std::string acceleration_str = object_str.substr(start_pos, end_pos - start_pos + 1);

			std::stringstream acceleration_ss(acceleration_str);
			std::string acceleration_token;
			acceleration_ss >> acceleration_token >> object.acceleration.x >> object.acceleration.y >> object.acceleration.z;
		}
		pos = object_str.find("\"temp\"");
		if (pos != std::string::npos) {
			std::stringstream temp_ss(object_str.substr(pos));
			std::string temp_token;
			temp_ss >> temp_token >> object.temp;
		}
		pos = object_str.find("\"mass\"");
		if (pos != std::string::npos) {
			std::stringstream mass_ss(object_str.substr(pos));
			std::string mass_token;
			mass_ss >> mass_token >> object.mass;
		}
		pos = object_str.find("\"radius\"");
		if (pos != std::string::npos) {
			std::stringstream radius_ss(object_str.substr(pos));
			std::string radius_token;
			radius_ss >> radius_token >> object.radius;
		}
		objects.push_back(object);
		start = data.find("{", end);
	}
	return objects;
}



namespace load_from_file {
	template <typename T>
	graphics_and_particles<T> load_from_file_graphics_and_particles() {
		graphics_and_particles<T> graphics_and_particles_return;
		short user_choice = ERROR_CHECKING(1, 3, "Which file type would you like to read from?\nEnter 1 for .json\n Enter 2 for .csv\n Enter 3 for .txt");
		if (user_choice == 1) {
			std::string file_name = FILE_NAME();
			

		}
	}
	 


}