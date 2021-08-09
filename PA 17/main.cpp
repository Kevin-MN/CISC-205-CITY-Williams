
/*
	Kevin Morales Nguyen
	Chapter 17 Programming assignment
	5/26/2021

*/


#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "Painting.h"
#include <vector>

using namespace std;

//function prototypes

void menu_driver(vector<Painting> &);
int display_menu();
//four main methods used throughout program
void create_customer(vector<Painting> &);
void edit_customer(vector<Painting> &);
void search_contract(vector<Painting> &);
void display_contracts(vector<Painting> &);

//methods that help get valid input
std::string get_string(std::string);
float get_float(std::string);


int main() {

	vector<Painting> paint_vector;

	menu_driver(paint_vector);

	return 0;
}

//function definitions

// ********************************************************
// name:      menu_driver
// called by: main
// passed:    string names[], string boats[], float contracts[], float paid[],int &num_boats
// returns:   nothing
// calls:     display_menu,create_customer,edit_customer,search_contract,display_contracts
// This method serves as th "driver" for selecting and calling  *
// the various functions used throughout the program to operate *
// on the parallel arrays.                                      *
// ********************************************************
void menu_driver(vector<Painting> &paint_vect) {
	int choice = 0;

	while (choice != 5) {
		//get user choice
		choice = display_menu();

		//switch appropriatly and call respective function
		switch (choice) {
		case 1:
			create_customer(paint_vect);

			break;
		case 2:
			edit_customer(paint_vect);


			break;

		case 3:
			search_contract(paint_vect);

			break;

		case 4:
			display_contracts(paint_vect);

			break;

			//exit
		case 5:


			break;
			// bad input, ask user to re-enter valid input
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
		std::cout << "1. Input a customer's information\n"
			<< "2. Edit a customer's information\n"
			<< "3. Find largest contract\n"
			<< "4. Display all contract information\n"
			<< "5. Exit\n\n"
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
// name:      create_customer
// called by: menu_driver
// passed:    string names[], string boats[], float contracts[], float paid[],int &num_boats
// returns:   none
// calls:     get_string. get_float
// This function is used to create a customer and alter the parallel arrays. *                                     
// ********************************************************
void create_customer(vector<Painting> &vect2) {
	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		Painting temp_paint; // create temporary Painting object to be added to vector

		// set customer name
		bool collect = true;
		std::string name = get_string("Customer name");

		while (collect) {
			try {
				temp_paint.set_name(name);// use the set_name() mutator to set the name
				collect = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				name = get_string("Customer name");
			}
		}

		//set boat name
		bool collect2 = true;
		std::string boat_name = get_string("Boat name");
		
		while (collect2) {
			try {
				temp_paint.set_boat_name(boat_name); //use the set_surface_area() mutator to set the surface area
				collect2 = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				boat_name = get_string("Boat name");
			}
		}

		//set contract amount
		bool collect3 = true;
		float contract = get_float("Contract");
		while (collect3) {
			try {
				temp_paint.set_contract(contract); //use the set_pollution_area() mutator to set the pollution area
				collect3 = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				contract = get_float("Contract");
			}
		}

		//set amount paid to date
		bool collect4 = true;
		float paid_date = get_float("Paid to date");
		while (collect4) {
			try {
				temp_paint.set_paid_to_date(paid_date); //use the set_salinity_level mutator to set the salinity level
				collect4 = false;
			}
			catch (Invalid_Exception& e) {
				std::cout << "\nException: " << e.get_message() << "\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				paid_date = get_float("Paid to date");
			}
		}
		
		vect2.push_back(temp_paint); // after temporary paint object is created with valid data add it to the vector
	
	std::cout << "\n";
}

// ********************************************************
// name:      edit_customer
// called by: menu_driver
// passed:    string names[], string boats[], float contracts[], float paid[],int &num_boats
// returns:   none
// calls:     get_string. get_float
// This function is used to edit the information customer and contract amounts. *                                     
// ********************************************************
void edit_customer(vector<Painting> & vect3) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//search by getting customers name
	std::string customer = get_string("Customer name");

	int index;
	bool found = false;
	//search parallel arrays for customer by name
	for (int i = 0; i < vect3.size(); i++) {
		if (vect3[i].get_name() == customer) {
			found = true;
			index = i; // save index as this is where we will make the change
		}
	}
	//if not found exit
	if (!found) {
		std::cout << "\nCustomer was now found.\n\n";
		return;
	}

	//initialize variables outside while and switch, use for editing customer info
	std::string new_name, new_boat_name;
	float new_contract, new_paid_date;
	

	int choice = 0;
	bool selecting = true;
	//select which customer field to edit
	while (selecting) {
		std::cout << "\n1. Edit customer name\n"
			<< "2. Edit customer's boat name\n"
			<< "3. Edit contract \n"
			<< "4. Edit Pait-to-date\n"
			<< ">> ";
		std::cin >> choice;
		std::cout << "\n";

		if (std::cin.fail() || choice < 1 || choice > 4) {
			std::cout << "Please input a valid integer.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			bool collect = true;
			bool collect2 = true;
			bool collect3 = true;
			bool collect4 = true;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//switch to apprporiate choice and make the change in the repsective array and correct index
			switch (choice) {
			case 1:
				new_name = get_string("New customer name");

				while (collect) {
					try {
						vect3[index].set_name(new_name);// use the set_name() mutator to set the name
						collect = false;
					}
					catch (Invalid_Exception& e) {
						std::cout << "\nException: " << e.get_message() << "\n";
						std::cin.clear();
						new_name = get_string("New customer name");
					}
				}
				std::cout << "\n\n";
				return;
				break;

			case 2:
				new_boat_name = get_string("New boat name");

				while (collect2) {
					try {
						vect3[index].set_boat_name(new_boat_name); //use the set_surface_area() mutator to set the surface area
						collect2 = false;
					}
					catch (Invalid_Exception& e) {
						std::cout << "\nException: " << e.get_message() << "\n";
						std::cin.clear();
						new_boat_name = get_string("New boat name");
					}
				}

				std::cout << "\n\n";
				return;
				break;

			case 3:
				new_contract = get_float("New contract amount");
		
				while (collect3) {
					try {
						vect3[index].set_contract(new_contract); //use the set_pollution_area() mutator to set the pollution area
						collect3 = false;
					}
					catch (Invalid_Exception& e) {
						std::cout << "\nException: " << e.get_message() << "\n";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						new_contract = get_float("New contract amount");
					}
				}
				std::cout << "\n\n";
				return;
				break;

			case 4:
				new_paid_date = get_float("New contract paid-to-date");
			
				while (collect4) {
					try {
						vect3[index].set_paid_to_date(new_paid_date); //use the set_salinity_level mutator to set the salinity level
						collect4 = false;
					}
					catch (Invalid_Exception& e) {
						std::cout << "\nException: " << e.get_message() << "\n";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						new_paid_date = get_float("New contract paid to date");
					}
				}

				std::cout << "\n\n";
				return;
				break;

			default:
				std::cout << "Invalid edit selection.\n\n";
				break;


			}
		}
	}

}

// ********************************************************
// name:      search_contract
// called by: menu_driver
// passed:    string names[], string boats[], float contracts[], float paid[],int &num_boats
// returns:   none
// calls:     get_float
// This function is used to print out contracts at or above a specified contract amount. *                                     
// ********************************************************
void search_contract(vector<Painting> &vect) {
	if (vect.size() == 0) {
		std::cout << "Vector is empty\n\n";
	}
	else {
		Painting largest = vect[0];
		std::cout << "Found largest contract:\n";

		std::cout << "\n\n" << std::left << std::setw(16) << "Name" << std::left << std::setw(18) << "Boat Name" << std::setw(22) << "Contract Value"
			<< "Paid-to-Date\n\n";
		for (int i = 0; i < vect.size(); i++) {
			if (vect[i] > largest) {
				largest = vect[i];
			}
		}
		largest.print();
	}
}

// ********************************************************
// name:      display_contract
// called by: menu_driver
// passed:    string names[], string boats[], float contracts[], float paid[],int &num_boats
// returns:   none
// calls:     none
// This function is used to print out all of the customer and contract information that has been stored so far. *                                     
// ********************************************************
void display_contracts(vector<Painting> &vect) {
    if(vect.size() == 0){
        std::cout << "vector is empty!\n";
    }
    else{
	Painting temp_obj;
	float total = 0;
	float total2 = 0;
	std::cout << std::left << std::setw(16) << "Name" << std::left << std::setw(18) << "Boat Name" << std::setw(22) << "Contract Value"
		<< "Paid-to-Date\n\n";

	for (int i = 0; i < vect.size(); i++) {
		vect[i].print();
		total = temp_obj + vect[i];
		total2 += total;
	}

	std::cout << "Total of all contracts: $" << total2 << "\n\n";
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



