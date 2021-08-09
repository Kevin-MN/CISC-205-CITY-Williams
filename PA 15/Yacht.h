#ifndef YACHT_H
#define YACHT_H

#include <string>
#include<iostream>

class Yacht {
	protected:
		std::string name, year_built;
		float length;

	public:
		Yacht() { name = "", year_built = "", length = 0; }

		/* potential backdoor constructor, object could be created with bad data
		Yacht(std::string nme, std::string year_blt, float len) {
			this->name = nme;
			this->year_built = year_blt;
			this->length = length;
		}
			*/

		// ~Yacht     // none of the data members are dynamic..., cant find appropriate use for destructor
		
		//setters
		void set_name(std::string);
		void set_year_built(std::string);
		void set_length(float);
		virtual void print_data() const;


		//getters 
		std::string get_name()  { return this->name; }
		std::string get_year_built() { return this->year_built; }
		float get_length() { return this->length; }
};

class Power_Boat : public Yacht{
	protected: // add additional data members specific to derived class
		int num_engines;
		float total_hp;

	public:
		Power_Boat() { name = "", year_built = "", length = 0, num_engines = 0, total_hp = 0; }

		/*		//Potential backdoor constructor
		Power_Boat(int num_engs, float ttl_hp, std::string nme, std::string year_blt, float len) :
			Yacht(nme, year_blt, len) {
			this->num_engines = num_engs;
			this->total_hp = ttl_hp;
		}
		*/
		void set_num_engines(int);
		void set_total_hp(float);

		int get_num_engines()  { return this->num_engines; }
		float get_total_hp()  { return this->total_hp; }

		void print_data() const override;

};


class Sail_Boat : public Yacht {
	protected:
		float sail_area;  // add additional data members specific to derived class

	public:
		Sail_Boat() { name = "", year_built = "", length = 0, sail_area = 0; }

		/*		// backdoor constructor
		Sail_Boat(float area, std::string nme, std::string year_blt, float len) :
			Yacht(nme, year_blt, len) {
			this->sail_area = area;
		}
		*/

		//accesor
		void set_sail_area(float);

		float get_sail_area() { return this->sail_area;  }

		void print_data() const override;
};
#endif