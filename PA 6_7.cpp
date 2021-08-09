
/*
	Kevin Morales Nguyen	
	Chapter 6&7 Programming assignment
	3/8/2021

*/


#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;


const int SIZE = 10;

//function prototypes

void menu_driver(std::string [], std::string [], float [], float [], int &);
int display_menu();
//four main methods used throughout program
void create_customer(std::string [], std::string [], float [], float [],int &);
void edit_customer(std::string [], std::string [], float [], float [],int &);
void search_contract(std::string [], std::string [], float [], float [],int &);
void display_contracts(std::string [], std::string [], float [], float [],int &);
//methods that help get valid input
std::string get_string(std::string);
float get_float(std::string);


int main() {
	
	//create parrallel arrays
	std::string name[SIZE];
	std::string boat_name[SIZE];
	float contract[SIZE];
	float paid_to_date[SIZE];
	//create counter to keep track of boat count
	int number_of_boats = 0;

	menu_driver(name, boat_name, contract, paid_to_date,number_of_boats);

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
void menu_driver(std::string names[], std::string boats[], float contracts[], float paid[],int &num_boats) {
	int choice = 0;

	while (choice != 5) {
		//get user choice
		choice = display_menu();

		//switch appropriatly and call respective function
		switch (choice) {
		case 1:
			create_customer(names, boats, contracts, paid, num_boats);

			break;
		case 2:
			edit_customer(names, boats, contracts, paid, num_boats);


			break;

		case 3:
			search_contract(names, boats, contracts, paid, num_boats);

			break;

		case 4:
			display_contracts(names, boats, contracts, paid, num_boats);

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
			<< "3. Search for contracts by value\n"
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
void create_customer(std::string names[], std::string boat_names[], float contracts[], float paid_to_dates[], int& numboats) {
	if (numboats < 10) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// gather customer information and store in variables
		std::string name = get_string("Name");
		std::string boat_name = get_string("Boat name");
		float contract = get_float("Contract");
		float paid_date = get_float("Paid to date");

		// assign data to respective array index
		names[numboats] = name;
		boat_names[numboats] = boat_name;
		contracts[numboats] = contract;
		paid_to_dates[numboats] = paid_date;
		numboats++; // increment boat count so we keep track
	}
	else { // if boat count > 10 then this exectes
		std::cout << "\nContract list is full!\n\n";
	}

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
void edit_customer(std::string names[], std::string boat_names[], float contracts[], float paid_to_dates[], int& numboats) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//search by getting customers name
	std::string customer = get_string("Customer name");

	int index;
	bool found = false;
	//search parallel arrays for customer by name
	for (int i = 0; i < numboats; i++) {
		if (names[i] == customer) {
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
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//switch to apprporiate choice and make the change in the repsective array and correct index
			switch (choice) {
			case 1:
				new_name = get_string("New name");
				names[index] = new_name;
				std::cout << "\n\n";
				return;
				break;

			case 2:
				new_boat_name = get_string("New boat name");
				boat_names[index] = new_boat_name;
				std::cout << "\n\n";
				return;
				break;

			case 3:
				new_contract = get_float("New contract amount");
				contracts[index] = new_contract;
				std::cout << "\n\n";
				return;
				break;

			case 4:
				new_paid_date = get_float("New contract paid-to-date");
				paid_to_dates[index] = new_paid_date;
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
void search_contract(std::string names[], std::string boat_names[], float contracts[], float paid_to_dates[], int& numboats) {
	float search = get_float("Contract amount");
	std::cout << "\n\n" << std::left << std::setw(16) << "Name" << std::left << std::setw(18) << "Boat Name" << std::setw(22) << "Contract Value"
		<< "Paid-to-Date\n\n";
	for (int i = 0; i < numboats; i++) {
		if (contracts[i] >= search) {
			std::cout << std::setw(20) << names[i] << std::left << std::setw(20) << boat_names[i] << "$" << std::left << std::setw(20) << contracts[i]
				<< "$" << std::left << std::setw(20) << paid_to_dates[i] << "\n\n";
		}
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
void display_contracts(std::string names[], std::string boat_names[], float contracts[], float paid_to_dates[], int& numboats) {
	float total = 0;
	std::cout << std::left << std::setw(16) << "Name" << std::left << std::setw(18) << "Boat Name" << std::setw(22) << "Contract Value"
				<< "Paid-to-Date\n\n";
	for (int i = 0; i < numboats; i++) {
		std::cout  << std::setw(17) << names[i]  << std::left << std::setw(20)  << boat_names[i]  << "$" << std::left << std::setw(20) << contracts[i]
			<< "$" << std::left << std::setw(20) << paid_to_dates[i] << "\n\n";
		total += contracts[i];
 	}

	std::cout << "Total of all contracts: $" << total << "\n\n";
}

// ********************************************************
// name:      get_string
// called by: menu_driver
// passed:    string names[], string boats[], float contracts[], float paid[],int &num_boats
// returns:   none
// calls:     creat_customer, edit_customer
// This function is used to gather valid string inputs specified by >= 15 chars and > 0 *                                     
// ********************************************************
std::string get_string(std::string prompt) {
	std::string temp;
	bool collect = true;

	while (collect) {
		std::cout << prompt << ": ";

		getline(std::cin, temp);
		if (temp.length() > 15 || temp == "" || temp.length() == 0) {
			std::cout << "\nPlease enter " << prompt << " no more than 15 charaters and not empty.\n\n";
		}
		else {
			return temp;
		}
	}



	return "";
}

// ********************************************************
// name:      get_float
// called by: menu_driver
// passed:    string names[], string boats[], float contracts[], float paid[],int &num_boats
// returns:   none
// calls:     creat_customer, edit_customer, search_contract
// This function is used to gather valid float inputs that are >= 0 *                                     
// ********************************************************
float get_float(std::string prompt) {
	float temp;
	bool collect = true;
	while (collect) {
		std::cout << prompt << ": ";
		std::cin >> temp;

		if (!std::cin.fail() && temp >= 0){
			return temp;
		}
		else {
			std::cout << "\nPlease enter " << prompt << " that is greater than or equal to zero.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	return 0;
}






