/*
	Kevin Morales Nguyen
	Chapter 15 Programming assignment
	5/3/2021

*/

#include "Yacht.h" // include the class header so we can use the class in our program
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

const int SIZE = 10;

//function prototypes

void menu_driver(Yacht *yacht_arr[], int&);
int display_menu();

//primary functions that perform specified menu options
void enter_data(Yacht* yacht_arr[], int&, bool& , int&);
void display_all_yachts(Yacht* yacht_arr[], int&);
void delete_mem(Yacht* yacht_arr[], int&);


//methods that help get valid input
std::string get_string(std::string, int, bool&);
float get_float(std::string, bool&);
int get_int(std::string, bool&);

bool unique_name(Yacht* yacht_arr[], std::string, int&);


int main() {

	//create the single array that holds the Sea_Pollution data type
	Yacht *yachts[SIZE]; 
	//create counter to keep track of sea/pollution count
	int yacht_num = 0;
	

	menu_driver(yachts, yacht_num);

	return 0;
}

//function definitions


// ********************************************************
// name:      menu_driver
// called by: main
// passed:    poll_arr[],int &poll_num
// returns:   nothing
// calls:     display_menu,enter_data(), find_sea_pollution(), pollution_arith(), display_all_pollution()
// This method serves as the "driver" for selecting and calling  *
// the various functions used throughout the program to operate *
// on the array holding sea's/pollution.                                      
// ********************************************************
void menu_driver(Yacht* yacht_arr[], int& yacht_num) {
	int choice = 0;
	bool validate = true;

	while (choice != 6) {
		//get user choice
		choice = display_menu();

		//switch appropriatly and call respective function
		switch (choice) {
		case 1:
			if (yacht_num < SIZE) { // check size of array 
				enter_data(yacht_arr, yacht_num, validate, choice);
			}
			else {
				std::cout << "\nYacht registry is full!\n\n";
			}
			break;
		case 2:
			if (yacht_num < SIZE) { // check size of array 
				enter_data(yacht_arr, yacht_num, validate, choice);
			}
			else {
				std::cout << "\nYacht registry is full!\n\n";
			}
			break;
		case 3:
			if (yacht_num < SIZE) { // check size of array 
				enter_data(yacht_arr, yacht_num, validate, choice);
			}
			else {
				std::cout << "\nYacht registry is full!\n\n";
			}
			break;
		case 4:
			display_all_yachts(yacht_arr, yacht_num);
			break;
		case 5: // switch for turning validation on or off, simply ! the validate boolean and let user know 
			if (validate == true) {
				validate = false;
				std::cout << "Upper level validation turned off\n\n";
			}
			else {
				validate = true;
				std::cout << "Upper level validation turned on\n\n";
			}
			break;
		case 6: //exit
			delete_mem(yacht_arr, yacht_num);
			break;
		default:
			std::cout << "Please enter valid menu choice.\n\n";
			std::cout.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

// ********************************************************
// name:      display_menu
// called by: menu_driver
// passed:    none
// returns:   int
// calls:     none
// This function helps get a valid menu option.           *                                     
// ********************************************************
int  display_menu() {
	int choice = 0;
	bool selecting = true;
	//promt user for valid menu choice
	while (selecting) {
		std::cout << "1. Input a yacht's information\n"
			<< "2. Input a power boat's information\n"
			<< "3. Input a sail boat's information\n"
			<< "4. Print all yachts\n"
			<< "5. Turn off/on upper level input validation\n"
			<< "6. Exit\n"
			<< ">> ";
		std::cin >> choice;
		std::cout << "\n";

		//invalid input, handle by clearing fail bit and flushing buffer
		if (std::cin.fail()) {
			std::cout << "Please input a valid integer.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			return choice;
		}
	}

}


// ********************************************************
// name:      enter_data
// called by: menu_driver
// passed:    poll_arr[], poll_num
// returns:   none
// calls:     unique_name(), get_int(), get_float(), get_string(), Sea_Pollution::set_name(), 
//			  Sea_Pollution::set_surface_area(), Sea_Pollution::set_pollution_area(), Sea_Pollution::set_salinity_level() 
// This function is used to assign values to the private data members part of the Sea_Pollution class, this is done 
// through the use of the class mutators. There is high level validation included into the get int,float,string helper methods.                                               
// ********************************************************
void enter_data(Yacht* yacht_arr[], int& yacht_num, bool& validate , int& type) {
	if (yacht_num < SIZE) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// gather a unique sea name
		std::string name_var = get_string("Yacht name", 20, validate); //high level validation before passing to mutator
		
		bool unique = false;
		while (!unique) { // keep checking name for uniqieness 
			
			if (unique_name(yacht_arr, name_var, yacht_num)) { // if the name is not a name already apart of another sea then it is unique and we end loop
				unique = true;
			}
			else { // otherwise prompt user for a unique name, loop continues
				std::cout << "\nPlease enter a unique name.\n\n";
				name_var = get_string("Yacht name", 20, validate);
			}
		}

		//set surface area
		bool valid = false;
		bool valid2 = validate;
		std::string build_year_var = get_string("Year built", 5 , validate); //high level validation before passing to mutator
		while (!valid && valid2) {  //further high level validation on get_string to make sure string is exactly 4 chars long
			if (build_year_var.length() == 4) {
				valid = true;
				valid2 = false;
			}
			else { // otherwise prompt user for a unique name, loop continues
				std::cout << "\nPlease enter a build year that is 4 charactes long.\n\n";
				build_year_var = get_string("Year built", 5, validate);
			}
		}


		//set pollution area
		float length_var = get_float("Length of yacht", validate); //high level validation before passing to mutator
		
		if (type == 2) {
			Power_Boat *temp_pb = new Power_Boat();
			temp_pb->set_name(name_var);
			temp_pb->set_year_built(build_year_var);
			temp_pb->set_length(length_var);

			float num_engs_var = get_int("Number of engines", validate);
			float hp_var = get_float("Total horsepower", validate);

			temp_pb->set_num_engines(num_engs_var);
			temp_pb->set_total_hp(hp_var);

			yacht_arr[yacht_num] = temp_pb;

		}
		else if (type == 3) {
			Sail_Boat* temp_sb = new Sail_Boat();
			temp_sb->set_name(name_var);
			temp_sb->set_year_built(build_year_var);
			temp_sb->set_length(length_var);

			float sail_var = get_int("Area of sail", validate);

			temp_sb->set_sail_area(sail_var);
			yacht_arr[yacht_num] = temp_sb;
		}
		else {
			Yacht *temp_yacht = new Yacht();
			temp_yacht->set_name(name_var);
			temp_yacht->set_year_built(build_year_var);
			temp_yacht->set_length(length_var);

			yacht_arr[yacht_num] = temp_yacht;
		}

		yacht_num++; // increment pollution count so we keep track of array index 
	}
	else { // if pollution/sea count > 5 then no more elements can added
		std::cout << "\nYacht registry is full!\n\n";
	}

	std::cout << "\n";
}




// ********************************************************
// name:      display_all_yachts
// called by: menu_driver
// passed:    poll_arr, poll_num
// returns:   none
// calls:     Sea_Pollution::get_name(), Sea_Pollution::get_surface_area(), Sea_Pollution::get_pollution_area(),
//			  Sea_Pollution::get_salinity_level()
// This function is used to print out all of the sea/pollution object data, the class getter methods are used insted of 
// print_data() for better formatting                                      
// ********************************************************
void display_all_yachts(Yacht* yacht_arr[], int& yacht_num) {

	for (int i = 0; i < yacht_num; i++) {
		yacht_arr[i]->print_data();
	}
}


// ********************************************************
// name:      delete_mem
// called by: menu_driver
// passed:    *yachts[], yacht_num
// returns:   none
// calls:     
// This function is used to delete the dynamic memory which is allocated to create yacht objects throughout the program                                     
// ********************************************************
void delete_mem(Yacht *yachts[], int& yacht_num) {

	for (int i = 0; i < yacht_num; i++) {
		delete yachts[i];
	}

	std::cout << "\n\n Dynamic memory successfully cleared\n\n";
}


// ********************************************************
// name:      get_string
// called by: menu_driver, search_sea()
// passed:    string prompt
// returns:   none
// calls:     get_line()
// This function is used to gather valid string inputs specified by the limit paramater, 
// this function serves as high level validation for gathering input to be passed to a class mutator. *                                     
// ********************************************************
std::string get_string(std::string prompt, int limit, bool& validate) {
	std::string temp;
	bool collect = true;

	if (validate) {
		while (collect) {
			std::cout << prompt << ": ";

			getline(std::cin, temp);
			if (temp.length() > limit || temp == "" || temp.length() == 0) {
				std::cout << "\nPlease enter " << prompt << " no more than " << limit << " charaters and not empty.\n\n";
			}
			else {
				return temp;
			}
		}
	}
	else {
		std::cout << prompt << ": ";
		getline(std::cin, temp);
		return temp;
	}
	return "";
}

// ********************************************************
// name:      get_float
// called by: menu_driver, enter_data()
// passed:    string prompt, const bool& 
// returns:   none
// calls:     none
// This function is used to gather valid float inputs that are > 0,  *                                     
// ********************************************************
float get_float(std::string prompt, bool& validate) {
	float temp;
	bool collect = true;

	if (validate) {
		while (collect) {
			std::cout << prompt << ": ";
			std::cin >> temp;

			if (!std::cin.fail() && temp > 0) {
				return temp;
			}
			else {
				std::cout << "\nPlease enter " << prompt << " that is greater than or equal to zero.\n\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

	}
	else {
		std::cout << prompt << ": ";
		std::cin >> temp;
		return temp;
	}

	return 0;
}

// ********************************************************
// name:      get_int
// called by: menu_driver
// passed:    string prompt, const bool&
// returns:   none
// calls:     none
// This function is used to gather valid float inputs that are >= 0, high level validation*                                     
// ********************************************************
int get_int(std::string prompt, bool& validate) {
	int temp;
	bool collect = true;
	if (validate) {
		while (collect) {
			std::cout << prompt << ": ";
			std::cin >> temp;

			if (!std::cin.fail() && temp > 0) {
				return temp;
			}
			else {
				std::cout << "\nPlease enter " << prompt << " that is greater than or equal to zero.\n\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

	else {
		std::cout << prompt << ": ";
		std::cin >> temp;
		return temp;
	}

	return 0;
}



// ********************************************************
// name:      unique_name
// called by: enter_data()
// passed:    poll_arr[], string check
// returns:   boolean
// calls:     Sea_Pollution::get_name()
// This function is used to make sure that when gathering an name to create a Sea_Pollution object, 
// it is unique                                    
// ********************************************************
bool unique_name(Yacht* yacht_arr[], std::string check, int& yacht_num) {
	//std::cout << "inside method;";
	for (int i = 0; i < yacht_num; i++) {// loop through all elements 
		//std::cout << "before evaluation;";

		std::string temp_str = yacht_arr[i]->get_name();

		if (temp_str == check) { // if name matched an name in the sea array then it is not a unique name
			return false;
		}
	}
	//std::cout << "after loops;";
	return true; //looped through all elements and no match, it is unique
}

