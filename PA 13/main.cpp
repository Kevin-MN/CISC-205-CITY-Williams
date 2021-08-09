
/*
	Kevin Morales Nguyen
	Chapter 13 Programming assignment
	4/1/2021

*/

#include "Patient.h" // include the class header so we can use the class in our program
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>



const int SIZE = 5;


//function prototypes

void menu_driver(Patient[], int&);
int display_menu();

//primary functions that perform specified menu options
void create_patient(Patient[], int&);
void edit_patient(Patient[], int&);
void display_patient(Patient[], int&);


//methods that help get valid input
std::string get_string(std::string, int);
float get_float(std::string);
int get_int(std::string);
bool unique_id(Patient[], int);


int main() {

	//create the single array that holds the Customer data type
	Patient patients[SIZE];
	//create counter to keep track of boat count
	int number_of_patients = 0;

	menu_driver(patients, number_of_patients);

	return 0;
}

//function definitions


// ********************************************************
// name:      menu_driver
// called by: main
// passed:    patinet_arr[],int &pat_num
// returns:   nothing
// calls:     display_menu,create_patient,edit_patient,display_patient
// This method serves as the "driver" for selecting and calling  *
// the various functions used throughout the program to operate *
// on the array holding Patients.                                      *
// ********************************************************
void menu_driver(Patient patient_arr[], int& pat_num) {
	int choice = 0;

	while (choice != 4) {
		//get user choice
		choice = display_menu();

		//switch appropriatly and call respective function
		switch (choice) {
		case 1:
			if (pat_num < SIZE) { // check size of array 
				create_patient(patient_arr, pat_num);
			}
			else {
				std::cout << "\nContract list is full!\n\n";
			}

			break;
		case 2:
			edit_patient(patient_arr, pat_num);

			break;

		case 3:
			display_patient(patient_arr,pat_num);

			break;
			
		case 4: //exit
			
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
		std::cout << "1. Input a patient's information\n"
			<< "2. Edit a patient's information\n"
			<< "3. Display a patient's information\n"
			<< "4. Exit\n"
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
// name:      create_patient
// called by: menu_driver
// passed:    patient_arr[], pat_nam
// returns:   none
// calls:     unique_id(), get_int(), get_float(), get_string(), Patient::set_id(), 
//			  Patient::set_name(),	 Patient::set_address(),  Patient::set_phone(),  Patient::set_charge() 
// This function is used to assign values to the private data members part of the patient class, this is done 
// through the use of the class mutators. There is high level validation included into the get int,float,string helper methods.                                               
// ********************************************************
void create_patient(Patient patient_arr[], int& pat_num) {
	if (pat_num < SIZE) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// gather a unique patient id
		int id_var = get_int("Patient id"); //high level validation before passing to mutator
		bool unique = false;
		while(!unique){ // keep checking id for uniqieness 
			if (unique_id(patient_arr, id_var)) { // if the id is not a id already apart of another patient then it is unique and we end loop
				unique = true;
			}
			else { // otherwise prompt user for a unique id, loop continues
				std::cout << "\nPlease enter a unique id.\n\n";
				id_var = get_int("Patient id");
			}
		}

		patient_arr[pat_num].set_id(id_var);// use the set_id() mutator to set the id 

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer for string inputs

		std::string name_var = get_string("Patient name", 25); // high level validation before passing to mutator
		patient_arr[pat_num].set_name(name_var); //use the set_name() mutator to set the name

		std::string address_var = get_string("Patient address", 50); //high level validation before passing to mutator
		patient_arr[pat_num].set_address(address_var); //use the set_address() mutator to set the address

		std::string phone_var = get_string("Patient phone number", 11); //high level validation before passing to mutator
		patient_arr[pat_num].set_phone(phone_var); //use the set_phone() mutator to set the phone number

		float charges_var = get_float("Surgery charges"); //high level validation before passing to mutator
		patient_arr[pat_num].set_charge(charges_var); //use the set_charge() mutator to set the charge
		
		pat_num++; // increment patient count so we keep track of array index 
	}
	else { // if patient count > 5 then no more patients can added
		std::cout << "\nPatient registry is full!\n\n";
	}

	std::cout << "\n";
}


// ********************************************************
// name:      edit_patient
// called by: menu_driver
// passed:    patient_arr[], pat_nam
// returns:   none
// calls:     unique_id(), get_float(), get_string(), Patient::set_id(), 
//			  Patient::set_name(),	 Patient::set_address(),  Patient::set_phone(),  Patient::set_charge() 
// This function is used to edit the data members of a patient by using the repective mutators.*                                     
// ********************************************************
void edit_patient(Patient patient_arr[], int& pat_num) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//search by getting customers name
	std::string patient_name = get_string("Patient name",25);

	int index;
	bool found = false;
	//search names by accessing data from elements for patient by name
	for (int i = 0; i < pat_num; i++) {
		if (patient_arr[i].get_name() == patient_name) {
			found = true;
			index = i; // save index as this is where we will make the change
		}
	}
	//if not found exit
	if (!found) {
		std::cout << "\nPatient was not found.\n\n";
		return;
	}

	//initialize variables outside while and switch, use for editing patient info
	int new_id;
	std::string new_name, new_address, new_phone;
	float new_charge;
	bool unique;

	int choice = 0;
	bool selecting = true;
	//select which patient field to edit
	while (selecting) {
		std::cout << "\n1. Edit patient id\n"
			<< "2. Edit patient name\n"
			<< "3. Edit patient address \n"
			<< "4. Edit patient phone number\n"
			<< "5. Edit surgery charge\n"
			<< ">> ";
		std::cin >> choice;
		std::cout << "\n";

		if (std::cin.fail() || choice < 1 || choice > 5) {
			std::cout << "Please input a valid integer.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//switch to apprporiate choice and make the change in the repsective array and correct index
			switch (choice) {
			case 1:

				// gather a unique patient id
				new_id = get_int("New id"); //high level validation before passing to mutator
				unique = false;
				while (!unique) { // keep checking id for uniqieness 
					if (unique_id(patient_arr, new_id)) { // if the id is not a id already apart of another patient then it is unique and we end loop
						unique = true;
					}
					else { // otherwise prompt user for a unique id, loop continues
						std::cout << "\nPlease enter a unique id.\n\n";
						new_id = get_int("New id");
					}
				}

				patient_arr[index].set_id(new_id); // set new id
				std::cout << "\n\n";
				return;
				break;

			case 2:
				new_name = get_string("New name", 25);
				patient_arr[index].set_name(new_name); // set new name
				std::cout << "\n\n";
				return;
				break;

			case 3:
				new_address = get_string("New address", 50);
				patient_arr[index].set_address(new_address);// set new address
				std::cout << "\n\n";
				return;
				break;

			case 4:
				new_phone = get_string("New phone number", 11);
				patient_arr[index].set_phone(new_phone); // set new phone
				std::cout << "\n\n";
				return;
				break;

			case 5: 
				new_charge = get_float("New surgery charge");
				patient_arr[index].set_charge(new_charge); // set new charges
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
// name:      display_patient
// called by: menu_driver
// passed:    patient_arr[], pat_nam
// returns:   none
// calls:     Patient::get_id(), Patient::get_name(), Patient::get_address(),  
//			  Patient::get_phone(),  Patient::get_charge(), get_string()
// This function is used to print out all of the information of a single patient that is found by name, private
// member data is printed by the classes getter methods.
// ********************************************************
void display_patient(Patient patient_arr[], int& pat_num) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//search by getting patient's name
	std::string patient_name = get_string("Customer name", 25);

	int index;
	bool found = false;
	//search names by accessing data from elements for patient by name
	for (int i = 0; i < pat_num; i++) {
		if (patient_arr[i].get_name() == patient_name) {
			found = true;
			index = i; // save index as this is where we will make the change
		}
	}
	//if not found exit
	if (!found) {
		std::cout << "\nPatient was now found.\n\n";
		return;
	}

	std::cout << "\nPatient id: " << patient_arr[index].get_id() << "\n"
		<< "Patient name: " << patient_arr[index].get_name() << "\n"
		<< "Patient address: " << patient_arr[index].get_address() << "\n"
		<< "Patient phone number: " << patient_arr[index].get_phone() << "\n"
		<< "Patient charges: $" << patient_arr[index].get_charge() << "\n\n";

}


// ********************************************************
// name:      get_string
// called by: menu_driver
// passed:    string prompt
// returns:   none
// calls:     get_line()
// This function is used to gather valid string inputs specified by the limit paramater, 
// this function serves as high level validation for gathering input to be passed to a class mutator. *                                     
// ********************************************************
std::string get_string(std::string prompt, int limit) {
	std::string temp;
	bool collect = true;

	while (collect) {
		std::cout << prompt << ": ";

		getline(std::cin, temp);
		if (temp.length() >= limit || temp == "" || temp.length() == 0) {
			std::cout << "\nPlease enter " << prompt << " no more than " << (limit - 1) << " charaters and not empty.\n\n";
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
// passed:    string prompt
// returns:   none
// calls:     none
// This function is used to gather valid float inputs that are >= 0 *                                     
// ********************************************************
float get_float(std::string prompt) {
	float temp;
	bool collect = true;
	while (collect) {
		std::cout << prompt << ": ";
		std::cin >> temp;

		if (!std::cin.fail() && temp >= 0) {
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

// ********************************************************
// name:      get_float
// called by: menu_driver
// passed:    string prompt
// returns:   none
// calls:     none
// This function is used to gather valid float inputs that are >= 0, high level validation*                                     
// ********************************************************
int get_int(std::string prompt) {
	int temp;
	bool collect = true;
	while (collect) {
		std::cout << prompt << ": ";
		std::cin >> temp;

		if (!std::cin.fail() && temp >= 0) {
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

// ********************************************************
// name:      unique_id
// called by: create_patient, edit_patient
// passed:    Patient pat_arr[], int check
// returns:   boolean
// calls:     Patient::get_id()
// This function is used to make sure that when gathering an id to either create or edit a patient
// is unique as specified by the program requirements*                                     
// ********************************************************
bool unique_id(Patient pat_arr[], int check) {
	for (int i = 0; i < SIZE; i++) {// loop through all elements 
		if (pat_arr[i].get_id() == check) { // if id matched an id in the patient array then it is not a unique id
			return false;
		}
	}
	return true; //looped through all elements and no match, it is unique
}