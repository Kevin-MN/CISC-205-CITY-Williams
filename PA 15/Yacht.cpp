#include "Yacht.h"
#include <iostream>
#include <iomanip>

//class setter methods
void Yacht::set_name(std::string name) {
	if (name.length() <= 20 && name != "") {
		this->name = name;
	}
	else {
		std::cout << "\nName was longer than 20 characters or empty, triggering EXIT_FAILURE\n";
		exit(EXIT_FAILURE);
	}
}

void Yacht::set_year_built(std::string year) {
	if (year.length() == 4) {
		this->year_built = year;
	}
	else {
		std::cout << "\nYear built was not exactly 4 characters in length, triggering EXIT_FAILURE\n";
		exit(EXIT_FAILURE);
	}
}

void Yacht::set_length(float len) {
	if (len > 0) {
		this->length = len;
	}
	else {
		std::cout << "\nFloat value for length was less than or equal to zero which is invalid, triggeing EXIT_FAILURE\n";
		exit(EXIT_FAILURE);
	}
}


//function that prints out all of the objects data
void Yacht::print_data() const {
	std::cout << "\nYacht name: " << this->name << "\n"
		<< "Year built: " << this->year_built << "\n"
		<< "Length: " << std::fixed << std::setprecision(2) << this->length << "\n\n";
}




//POWER BOAT SETTERS AND PRINT OVERRIDE ************************


void Power_Boat::set_num_engines(int num) {
	if (num > 0) {
		this->num_engines = num;
	}
	else {
		std::cout << "\nInteger value for number of engines was less than or equal to zero which is invalid, triggeing EXIT_FAILURE\n";
		exit(EXIT_FAILURE);
	}
}

void Power_Boat::set_total_hp(float num) {
	if (num > 0) {
		this->total_hp = num;
	}
	else {
		std::cout << "\nFloat value for total horsepower was less than or equal to zero which is invalid, triggeing EXIT_FAILURE\n";
		exit(EXIT_FAILURE);
	}
}


void Power_Boat::print_data() const {
	std::cout << "\nPower boat name: " << this->name << "\n"
		<< "Year built: " << this->year_built << "\n"
		<< "Length: " << std::fixed << std::setprecision(2) << this->length << "\n"
		<< "Number of engines: "  << this->num_engines << "\n"
		<< "Total Horsepower: "   << this->total_hp << "\n\n";
}






//SAIL BOAT SETTERS AND PRINT OVERRIDE ************************

void Sail_Boat::set_sail_area(float len) {
	if (len > 0) {
		this->sail_area = len;
	}
	else {
		std::cout << "\nFloat value for sail area was less than or equal to zero which is invalid, triggeing EXIT_FAILURE\n";
		exit(EXIT_FAILURE);
	}
}


void Sail_Boat::print_data() const {
	std::cout << "\nSail boat name: " << this->name << "\n"
		<< "Year built: " << this->year_built << "\n"
		<< "Length: " << std::fixed << std::setprecision(2) << this->length << "\n"
		<< "Sail area: " << this->length << "\n\n";
}






