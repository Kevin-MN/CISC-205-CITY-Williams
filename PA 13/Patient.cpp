/**
*	This is the cpp file that includes the implementation for the setter methods, which all include low level validation features incase bad data passes through high level
*/
#include "Patient.h"
#include <iostream>

void Patient::set_id(int id) {
	if (id >= 0) {
		this->id = id;
	}
	else {
		std::cout << "Invalid id.\n";
		exit(EXIT_FAILURE);
	}
}

void Patient::set_name(std::string name) {
	if (name.length() < 25) {
		this->name = name;
	}
	else {
		std::cout << "Invalid name length.\n";
		exit(EXIT_FAILURE);
	}
}

void Patient::set_address(std::string address) {
	if (address.length() < 50) {
		this->address = address;
	}
	else {
		std::cout << "Invalid address length.\n";

	}
}

void Patient::set_phone(std::string phone) {
	if (phone.length() < 11) {
		this->phone = phone;
	}
	else {
		std::cout << "Invalid phone length.\n";
		exit(EXIT_FAILURE);
	}
}

void Patient::set_charge(float charge) {
	if (charge >= 0) {
		this->charges = charge;
	}
	else {
		std::cout << "Invalid charge amount.\n";
		exit(EXIT_FAILURE);
	}
}