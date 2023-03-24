#pragma once
#include <fstream>
#include "graphics_and_particles.hpp"
#include <string>
#include <iostream>
#include "particles/PARTICLE.hpp"
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
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	template <typename T,int size>
	void write_to_file_particles(const graphics_and_particles<T,size>& particles_)
	{
		short user_choice = ERROR_CHECKING(1, 3, "Which file type would you like to write to?\nEnter 1 for .json\n Enter 2 for .csv\n Enter 3 for .txt");

		if (user_choice == 1) {
			std::string file_name = FILE_NAME();
			std::ofstream out(file_name + ".json");
			out << "{\n";
			out << "\"data type\":" << "\"" << std::string(typeid(T).name()) << "\"" << ",\n";
			out << "\"particles\": [\n";
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
		}
		if (user_choice == 2) {
			std::string file_name = FILE_NAME();
			std::ofstream out(file_name + ".csv");
			for (auto& itr : particles_.main_particles.particle_container) {
				WRITE_TO_CSV(out, itr);
			}
		}
		if (user_choice == 3) {
			std::string file_name = FILE_NAME();
			std::ofstream out(file_name + ".txt");
			for (auto& itr : particles_.main_particles.particle_container) {
				WRITE_TO_TXT(out, itr);
			}
		}
	}
}

template <typename T>
static std::vector<particle<T>> READ_FROM_FILE_JSON(std::ifstream& in) {
	std::vector<particle<T>> particles_read_from_file;
	using json = nlohmann::json;
	json data = json::parse(in);
	//found this here https://stackoverflow.com/questions/53324659/c-json-array-parsing-using-nlohmannjson
	for (auto& itr : data["particles"]) {
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
		particle<T>* testing_ = new particle<T>(positions, velocitys, acclerations, mass, temp, radius);
		particles_read_from_file.push_back(* testing_);
	}
	return particles_read_from_file;
}

#include <sstream>
//https://www.tutorialspoint.com/cplusplus-program-to-take-out-integer-from-comma-separated-string
template <typename T>
static std::vector<T> take_double(std::string str) {
	std::stringstream ss(str);
	std::vector<T> result;
	char ch;
	T tmp;
	while (ss >> tmp) {
		result.push_back(tmp);
		ss >> ch;
	}
	return result;
}

std::string READ_IN_GETLINE(std::ifstream& in) {//will get the entire line from a file and return it as a string 
	std::string string_read_in;//local string 
	std::getline(in, string_read_in);//getting the value 
	return string_read_in;
}

template <typename T>
static std::vector<particle<T>> READ_FROM_FILE_CSV(std::ifstream& in) {
	std::vector<particle<T>> particles_read_from_file;
	while (!in.eof() && in) {
		std::vector<T> numbers_from_file= take_double<T>(READ_IN_GETLINE(in));
		if (numbers_from_file.size() == 0) {
			break;//this is because there is always a /n 
		}
		vec3<T> positions;
		vec3<T> velocitys;
		vec3<T> acclerations;
		T temp;
		T mass;
		T radius;
		positions.x = numbers_from_file.at(0);
		positions.y = numbers_from_file.at(1);
		positions.z = numbers_from_file.at(2);

		velocitys.x = numbers_from_file.at(3);
		velocitys.y = numbers_from_file.at(4);
		velocitys.z = numbers_from_file.at(5);

		acclerations.x = numbers_from_file.at(6);
		acclerations.y = numbers_from_file.at(7);
		acclerations.z = numbers_from_file.at(8);

		temp = numbers_from_file.at(9);
		mass = numbers_from_file.at(10);
		radius = numbers_from_file.at(11);
		
		particles_read_from_file.push_back(particle<T>(positions, velocitys, acclerations, temp, mass, radius));
	}
	return particles_read_from_file;
}
template <typename T> 
static std::vector<particle<T>> READ_FROM_FILE_TXT(std::ifstream& in) {
	std::vector<particle<T>> particles_read_from_file;
	T data_in_file[12];
	int index = 0;
	while (!in.eof() && in) {
		in >> data_in_file[index%12];
		if (index % 12 == 0) {
			vec3<T> positions;
			vec3<T> velocitys;
			vec3<T> acclerations;
			T temp;
			T mass;
			T radius;
			positions.x = data_in_file[0];
			positions.y = data_in_file[1];
			positions.z = data_in_file[2];

			velocitys.x = data_in_file[3];
			velocitys.y = data_in_file[4];
			velocitys.z = data_in_file[5];

			acclerations.x = data_in_file[6];
			acclerations.y = data_in_file[7];
			acclerations.z = data_in_file[8];

			temp = data_in_file[9];
			mass = data_in_file[10];
			radius = data_in_file[11];
			particles_read_from_file.push_back(particle<T>(positions, velocitys, acclerations, temp, mass, radius));
		}
		index++;
	}
	particles_read_from_file.erase(particles_read_from_file.begin());
	return particles_read_from_file;
}

namespace load_from_file {
	template <typename T>
	std::vector<particle<T>> load_from_file_particles() {
		short user_choice = ERROR_CHECKING(1, 3, "Which file type would you like to read from?\nEnter 1 for .json\n Enter 2 for .csv\n Enter 3 for .txt");
		if (user_choice == 1) {
			std::string file_name = FILE_NAME(0);
			std::ifstream in(file_name + ".json");
			return READ_FROM_FILE_JSON<T>(in);
		}
		if (user_choice == 2) {
			std::string file_name = FILE_NAME(0);
			std::ifstream in(file_name + ".csv");
			return READ_FROM_FILE_CSV<T>(in);
		}
		if (user_choice == 3) {
			std::string file_name = FILE_NAME(0);
			std::ifstream in(file_name + ".txt");
			return READ_FROM_FILE_TXT<T>(in);
		}
	}
}