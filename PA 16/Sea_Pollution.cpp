#include "Sea_Pollution.h"
#include <iostream>
#include <iomanip>

static int temp = 1;

//class setter methods
void Sea_Pollution::set_name(std::string name) {
	if (name.length() <= 20 && name != "") {
		this->name = name;
	}
	else {
		throw (Invalid_Exception("Name was longer than 20 characters or empty\n")); // throw exception via create exception object with appropriate message and throw
	}
}

void Sea_Pollution::set_surface_area(float surf_area) {
	if (surf_area > 0 ) {
		this->surface_area = surf_area;
	}
	else {
		throw (Invalid_Exception("Float value for surface_area was less than or equal to zero which is invalid\n")); // throw exception via create exception object with appropriate message and throw
	}
}

void Sea_Pollution::set_pollution_area(float poll_area) {
	if (poll_area > 0) {
		this->pollution_area = poll_area;
	}
	else {
		throw (Invalid_Exception("Float value for pollution_area was less than or equal to zero which is invalid\n")); // throw exception via create exception object with appropriate message and throw
	}
}

void Sea_Pollution::set_salinity_level(float sal_level) {
	if (sal_level > 0) {
		this->salinity_level = sal_level;
	}
	else {
		throw (Invalid_Exception("Float value for salinity_level was less than or equal to zero which is invalid\n")); // throw exception via create exception object with appropriate message and throw
	}
}

//function that prints out all of the objects data
void Sea_Pollution::print_data() const {
	std::cout << "\nSea name: " << this->name << "\n"
		<< "Surface area: " << std::fixed << std::setprecision(2) << this->surface_area << "\n"
		<< "Pollution surface area: " << this->pollution_area << "\n"
		<< "Salinity level: " << this->salinity_level << "\n\n";
}

// operator overloads **************************

Sea_Pollution Sea_Pollution::operator+ (const Sea_Pollution right) {
	Sea_Pollution temp_obj;
	float temp_surf_area = surface_area + right.surface_area; // perform arithmetic with surface areas
	temp_obj.set_name("temp_sea_" + std::to_string(temp++)); // use mutator to set name
	temp_obj.set_surface_area(temp_surf_area); // use class mutator to set surface_area attribute of temporary object
	return temp_obj;
}

//This overloaded operator returns a pointer because unlike the addition opertor where data has a very high chance to be correct,
//the subtraction operation has a chance to create bad data, negatives or 0, so we cannot return an invalid object or null object,
//instead work with pointer and handle appropriatly in calling function
Sea_Pollution* Sea_Pollution::operator- (const Sea_Pollution right) {
	Sea_Pollution* temp_obj = new Sea_Pollution(); // create object using dynamic memory
	float temp_surf_area = surface_area - right.surface_area; // perform operation on attributes from objects
	if (temp_surf_area <= 0) { // <= 0 is bad data, we cannot create the object so return nullptr and handle in upper level
		return nullptr;
	}
	else {// subtraction was successful so object can be created with proper data
		temp_obj->set_name("temp_sea_" + std::to_string(temp++));
		temp_obj->set_surface_area(temp_surf_area); // use mutator to set data
		return temp_obj;
	}
}