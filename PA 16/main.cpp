

/*
	Kevin Morales Nguyen
	Chapter 16 Programming assignment
	5/17/2021

*/

#include "Sea_Pollution.h" // include the class header so we can use the class in our program
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

const int SIZE = 5;


//function prototypes

void menu_driver(Sea_Pollution[], int&);
int display_menu();

//primary functions that perform specified menu options
void enter_data(Sea_Pollution[], int&);
void find_sea_pollution(Sea_Pollution[], int&);
void pollution_compare(Sea_Pollution[], int&);
void pollution_arith(Sea_Pollution[], int&);
void display_all_pollution(Sea_Pollution[], int&);


//methods that help get valid input
std::string get_string(std::string);
float get_float(std::string);
int get_int(std::string);
Sea_Pollution* search_sea(Sea_Pollution[], const int& ); 
bool unique_name(Sea_Pollution[], std::string);


int main() {

	//create the single array that holds the Sea_Pollution data type
	Sea_Pollution pollution[SIZE];
	//create counter to keep track of sea/pollution count
	int poll_num = 0;

	menu_driver(pollution, poll_num);

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
void menu_driver(Sea_Pollution poll_arr[], int& poll_num) {
	int choice = 0;
	
	while (choice != 6) {
		//get user choice
		choice = display_menu();

		//switch appropriatly and call respective function
		switch (choice) {
		case 1:
			if (poll_num < SIZE) { // check size of array 
				enter_data(poll_arr, poll_num);
			}
			else {
				std::cout << "\nSea registry is full!\n\n";
			}
			break;
		case 2:
			find_sea_pollution(poll_arr, poll_num);
			break;
		case 3:
			pollution_compare(poll_arr, poll_num);
			break;
		case 4:
			pollution_arith(poll_arr, poll_num);
			break;
		case 5: 
			display_all_pollution(poll_arr, poll_num);
			break;
		case 6: //exit
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
		std::cout << "1. Input a sea's information\n"
			<< "2. Search for a sea and print info\n"
			<< "3. Compare two seas\n"
			<< "4. Perform atirhmetic with two seas\n"
			<< "5. Print all seas and data\n"
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

	return 0;
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
void enter_data(Sea_Pollution poll_arr[], int& poll_num) {
	if (poll_num < SIZE) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// gather a unique sea name
		std::string name_var = get_string("Sea name"); //high level validation before passing to mutator
		bool unique = false;
		while (!unique) { // keep checking name for uniqieness 
			if (unique_name(poll_arr, name_var)) { // if the name is not a name already apart of another sea then it is unique and we end loop
				unique = true;
			}
			else { // otherwise prompt user for a unique name, loop continues
				std::cout << "\nPlease enter a unique name.\n\n";
				name_var = get_string("Sea name");
			}
		}

		bool collect = true;

		while (collect) {
			try {
				poll_arr[poll_num].set_name(name_var);// use the set_name() mutator to set the name
				collect = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				name_var = get_string("Sea name");
			}
		}
		//set surface area

		bool collect2 = true;
		float sea_area_var = get_float("Sea surface area");

		while(collect2){
			try {
				poll_arr[poll_num].set_surface_area(sea_area_var); //use the set_surface_area() mutator to set the surface area
				collect2 = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				sea_area_var = get_float("Sea surface area");
			}
		}
	
		//set pollution area
		bool collect3 = true;
		float poll_area_var = get_float("Pollution surface area"); 
		while (collect3) {
			try {
				poll_arr[poll_num].set_pollution_area(poll_area_var); //use the set_pollution_area() mutator to set the pollution area
				collect3 = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				poll_area_var = get_float("Pollution surface area");
			}
		}
		
		bool collect4 = true;
		float salinity_var = get_float("Salinity level");
		while (collect4) {
			try {
				poll_arr[poll_num].set_salinity_level(salinity_var); //use the set_salinity_level mutator to set the salinity level
				collect4 = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				salinity_var = get_float("Salinity level"); 
			}
		}
		
		poll_num++; // increment pollution count so we keep track of array index 
	}
	else { // if pollution/sea count > 5 then no more elements can added
		std::cout << "\nSea registry is full!\n\n";
	}

	std::cout << "\n";
}



// ********************************************************
// name:      find_sea_pollution
// called by: menu_driver
// passed:    poll_arr[], poll_nam
// returns:   none
// calls:     Sea_Pollution::print_data(), search_sea()
// This function is used to print out all of the information of a single Sea_Pollution object that is found by name, 
// using the class print_data method
// ********************************************************
void find_sea_pollution(Sea_Pollution poll_arr[], int& poll_num) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//search by getting sea's name

	Sea_Pollution *temp_sea = search_sea(poll_arr, poll_num);

	if (temp_sea == nullptr) {
		std::cout << "\nSea was not found\n\n";
	}
	else {  
		temp_sea->print_data();
	}
}

// ********************************************************
// name:      pollution_compare
// called by: menu_driver
// passed:    poll_arr[], poll_num
// returns:   none
// calls:     get_string(), search_sea(), print_data()
// This function is used to call the appropriate comparison operation on two Sea_Pollution objects,
// first we find two elements from the array and then we ask the user for the desired operation*                                     
// ********************************************************
void pollution_compare(Sea_Pollution poll_arr[], int& poll_num) {
	
	bool temp_val = true; // by default turn high level validation on 
	Sea_Pollution* sea_ptr1; // create Sea_Pollution pointers to hold return value from search_sea()
	Sea_Pollution* sea_ptr2;

	if (poll_num < 2) { // there needs to be atleast two elements to perform operation
		std::cout << "\nNeed at least two elements in order to perform an operation\n\n";
		return;
	}
	else {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		sea_ptr1 = search_sea(poll_arr, poll_num); // get elements
		sea_ptr2 = search_sea(poll_arr, poll_num);

		if (sea_ptr1 == nullptr || sea_ptr2 == nullptr) { // make sure the elements exist
			std::cout << "\nNeed two existing elements to perform operation\n\n";
			return;
		}

		std::string comp_op = get_string("Comparison operator (>, <, ==)");//prompt for operation

		 if (comp_op != ">" && comp_op != "<" && comp_op != "==") { // make sure user entered valid operation
			std::cout << "\nNeed a valid operation\n\n";
			return;
		}

		 Sea_Pollution sea_obj1 = *sea_ptr1; // dereference pointers to objects, could just use arrow operator
		 Sea_Pollution sea_obj2 = *sea_ptr2;


		 //print the data from the two elements
		sea_obj1.print_data();
		sea_obj2.print_data();


		if (comp_op == ">") {
			if (sea_obj1 > sea_obj2) { // overloaded operator > 
				std::cout << sea_obj1.get_name() << " is bigger than " << sea_obj2.get_name() << "\n\n";
			}
			else {
				std::cout << sea_obj1.get_name() << " is not bigger than " << sea_obj2.get_name() << "\n\n";
			}
		}

		if (comp_op == "<") {
			if (sea_obj1 < sea_obj2) { // overloaded operator <
				std::cout << sea_obj1.get_name() << " is smaller than " << sea_obj2.get_name() << "\n\n";
			}
			else {
				std::cout << sea_obj1.get_name() << " is not smaller than " << sea_obj2.get_name() << "\n\n";
			}
		}
		
		if (comp_op == "==") {
			if (sea_obj1 == sea_obj2) { // overloaded operator == 
				std::cout << sea_obj1.get_name() << " is the same size as " << sea_obj2.get_name() << "\n\n";
			}
			else {
				std::cout << sea_obj1.get_name() << " is not the same size as " << sea_obj2.get_name() << "\n\n";
			}
		}
	}
}


// ********************************************************
// name:      pollution_arith
// called by: menu_driver
// passed:    poll_arr[], poll_num
// returns:   none
// calls:     get_string(), search_sea(), print_data()
// This function is used to call the appropriate arithmetic operation on two Sea_Pollution objects,
// first we find two elements from the array and then we ask the user for the desired operation*                                     
// ********************************************************
void pollution_arith(Sea_Pollution poll_arr[], int& poll_num) {

	bool temp_val = true;
	Sea_Pollution* sea_ptr1; // create pointes to objects to hold return value from search_sea()
	Sea_Pollution* sea_ptr2;

	if (poll_num < 2) {
		std::cout << "\nNeed at least two elements in order to perform an operation\n\n";
	}
	else {

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		sea_ptr1 = search_sea(poll_arr, poll_num); // ask user for elements
		sea_ptr2 = search_sea(poll_arr, poll_num);

		if (sea_ptr1 == nullptr || sea_ptr2 == nullptr) { // verify elements exist
			std::cout << "\nNeed two existing elements to perform operation\n\n";
			return;
		}

		std::string comp_op = get_string("Arithmetic operator (+, -)"); // prompt for operation

		if (comp_op != "+" && comp_op != "-") { // verify operation
			std::cout << "\nNeed a valid operation\n\n";
			return;
		}

		Sea_Pollution sea_obj1 = *sea_ptr1;
		Sea_Pollution sea_obj2 = *sea_ptr2;

		sea_obj1.print_data(); // print data of both objects
		sea_obj2.print_data();

		if (comp_op == "+") { // addittion operation
			Sea_Pollution temp_sea = sea_obj1 + sea_obj2; // perform overloaded operation, returns a Sea_Pollution object stored in temporary Sea_Pollution object
			std::cout << "\nCreated temporary object, will not be added to primary array\n\n";
			temp_sea.print_data();
			return;
		}

		if (comp_op == "-") { // subtraction operation
			Sea_Pollution* temp_sea = sea_obj1 - sea_obj2; // use a pointer to handle errors before creating object, possible to
															// return nullptr to indicate invalid operation

			if (temp_sea == nullptr) { // nullptr would indicate a negative surface area, we dont create object with bad data
				std::cout << "\nCould not create object, subtraction produced surface area <= 0\n\n";
			}
			else { // subtraction operation valid
				std::cout << "\nCreated temporary object dynamically, will not be added to primary array\n\n";
				temp_sea->print_data();
				delete temp_sea;
				std::cout << "\nDynamically created temp_obj deleted\n\n";
			}
		}
	}
}

	// ********************************************************
	// name:      display_all_pollution
	// called by: menu_driver
	// passed:    poll_arr, poll_num
	// returns:   none
	// calls:     Sea_Pollution::get_name(), Sea_Pollution::get_surface_area(), Sea_Pollution::get_pollution_area(),
	//			  Sea_Pollution::get_salinity_level()
	// This function is used to print out all of the sea/pollution object data, the class getter methods are used insted of 
	// print_data() for better formatting                                      
	// ********************************************************
	void display_all_pollution(Sea_Pollution poll_arr[], int& poll_num) {

		std::cout << std::left << std::setw(16) << "Sea name" << std::left << std::setw(18) << "Surface area" << std::setw(27) << "Pollution surface area"
			<< "Salinity level\n\n";
		for (int i = 0; i < poll_num; i++) {
			std::cout << std::setw(16) << poll_arr[i].get_name() << std::fixed << std::setprecision(2) << std::left << std::setw(18) << poll_arr[i].get_surface_area() << std::left << std::setw(27) << poll_arr[i].get_pollution_area()
				<< std::left << std::setw(20) << poll_arr[i].get_salinity_level() << "\n\n";
		}
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
std::string get_string(std::string prompt) {

	std::string temp;
	std::cout << prompt << ": ";
	getline(std::cin, temp);
	return temp;
}

// ********************************************************
// name:      get_float
// called by: menu_driver, enter_data()
// passed:    string prompt, const bool& 
// returns:   none
// calls:     none
// This function is used to gather valid float inputs that are > 0,  *                                     
// ********************************************************
float get_float(std::string prompt) {

	float temp;
	std::cout << prompt << ": ";
	std::cin >> temp;
	return temp;
}

// ********************************************************
// name:      get_float
// called by: menu_driver
// passed:    string prompt, const bool&
// returns:   none
// calls:     none
// This function is used to gather valid float inputs that are >= 0, high level validation*                                     
// ********************************************************
int get_int(std::string prompt) {

	int temp;
	std::cout << prompt << ": ";
	std::cin >> temp;	
	return temp;
}

// ********************************************************
// name:      search_sea
// called by: find_sea_pollution(), pollution_compare(), pollution_arith()
// passed:    poll_arr[], int &
// returns:   Sea_Pollution*
// calls:     Sea_Pollution::get_name(), get_string()
// This function is used to find a Sea_Pollution object from an array and return a pointer to the object,
// a pointer is returned because if we cannot find a valid object the function requires a return value                            
// ********************************************************
Sea_Pollution* search_sea(Sea_Pollution poll_arr[], const int& poll_num) {
		//search by getting patient's name
	
		std::string sea_name = get_string("Sea name");

		//search names by accessing data from elements for patient by name
		for (int i = 0; i < poll_num; i++) {
			if (poll_arr[i].get_name() == sea_name) {
				return &poll_arr[i]; // return address of array element, pointer
			}
		}

		return nullptr; // if object not found return nullptr
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
bool unique_name(Sea_Pollution poll_arr[], std::string check) {
	for (int i = 0; i < SIZE; i++) {// loop through all elements 
		if (poll_arr[i].get_name() == check) { // if name matched an name in the sea array then it is not a unique name
			return false;
		}
	}
	return true; //looped through all elements and no match, it is unique
}

