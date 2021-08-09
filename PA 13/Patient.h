/**
* This is the header file that acts as a class specification for the Patient ADT.
*/
#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
	private: //private data members
		int id;
		std::string name, address, phone;
		float charges;

	public:
		Patient() { id = -1, name = "", address = "", phone = "", charges = -1; } // default constructor that has default arguments
		//setter methods, implementation in cpp file
		void set_id(int);
		void set_name(std::string);
		void set_address(std::string);
		void set_phone(std::string);
		void set_charge(float);
		// getter methods with inline implementation 
		int get_id() const { return this->id;  }
		std::string get_name() const { return this->name; }
		std::string get_address() const{ return this->address; }
		std::string get_phone() const { return this->phone; }
		float get_charge() const { return this->charges; }
};
#endif