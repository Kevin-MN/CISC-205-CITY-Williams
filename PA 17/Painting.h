#ifndef PAINTING_H
#define PAINTING_H

#include <string>

class Painting {

private:
	std::string name, boat_name;
	float contract, paid_to_date;
public:
	Painting() { name = "", boat_name = "", contract = 0, paid_to_date = 0; } // default constructor

	std::string get_name() { return this->name; }
	std::string get_boat_name() { return this->boat_name; }
	float get_contract() { return this->contract; }
	float get_paid_to_date() { return this->paid_to_date; }

	void set_name(std::string);
	void set_boat_name(std::string);
	void set_contract(float);
	void set_paid_to_date(float);
	void print();

	bool operator>(const Painting right) {
		return (contract > right.contract);
	}

	float operator+(const Painting);







};












//Simple nested exception class 
class Invalid_Exception {
private: // hold a string member variable for error message
	std::string message;

public:
	Invalid_Exception(const std::string& msg) : message(msg) {} //Exception class created with error message as argument
	~Invalid_Exception() {}

	std::string get_message() const { return(message); }

};
#endif
