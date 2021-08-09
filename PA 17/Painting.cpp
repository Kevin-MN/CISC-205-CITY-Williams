#include "Painting.h"
#include <iostream>
#include <iomanip>

void Painting::set_name(std::string name1) {
	if (name1.length() <= 15 && name1 != "") {
		this->name = name1;
	}
	else {
		throw (Invalid_Exception("Customer name was longer than 15 characters or empty\n")); // throw exception via create exception object with appropriate message and throw
	}
}

void Painting::set_boat_name(std::string b_name) {
	if (b_name.length() <= 15 && b_name != "") {
		this->boat_name = b_name;
	}
	else {
		throw (Invalid_Exception("Boat name was longer than 15 characters or empty\n")); // throw exception via create exception object with appropriate message and throw
	}
}

void Painting::set_contract(float cont) {
	if (cont >= 0 && !std::cin.fail()) {
		this->contract = cont;
	}
	else {

		throw (Invalid_Exception("Float value for contract was less than zero which is invalid\n")); // throw exception via create exception object with appropriate message and throw
	}
}

void Painting::set_paid_to_date(float paid_to) {
	if (paid_to >= 0  && !std::cin.fail()) {
		this->paid_to_date = paid_to;
	}
	else {
		throw (Invalid_Exception("Float value for paid_to_date was less than zero which is invalid\n")); // throw exception via create exception object with appropriate message and throw
	}
}

void Painting::print() {
	std::cout << std::setw(17) << this->name << std::left << std::setw(20) << this->boat_name << "$" << std::left <<std::fixed << std::setw(20) << std::setprecision(2) << this->contract
		<< "$" << std::left << std::setw(20) << this->paid_to_date << "\n\n";
}

float Painting::operator+ (const Painting right) {
    float temp_val;
	temp_val = contract + right.contract;
	return temp_val;
}