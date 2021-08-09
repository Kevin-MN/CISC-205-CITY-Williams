#ifndef SEA_POLLUTION_H
#define SEA_POLLUTION_H

#include <string>
#include<iostream>

class Sea_Pollution {

	private:
		std::string name;
		float surface_area, pollution_area, salinity_level;

	public:
		//default constructor with initializer list
		Sea_Pollution() { name = "", surface_area = 0, pollution_area = 0, salinity_level = 0; }
		
		//setters
		void set_name(std::string);
		void set_surface_area(float);
		void set_pollution_area(float);
		void set_salinity_level(float);

		//getters
		std::string get_name() const { return this->name; }
		float get_surface_area() { return this->surface_area; }
		float get_pollution_area() { return this->pollution_area; }
		float get_salinity_level() { return this->salinity_level; }
		void print_data() const;

		//operators with simple implementation
		bool operator>(const Sea_Pollution right) {
			return (surface_area > right.surface_area);
		}

		bool operator<(const Sea_Pollution right) {
			return (surface_area < right.surface_area);
		}

		bool operator==(const Sea_Pollution right) {
			return (surface_area == right.surface_area);
		}

		//overloaded operators, implementation in class file
		Sea_Pollution operator+(const Sea_Pollution);
		Sea_Pollution* operator-(const Sea_Pollution);
		
};
#endif
