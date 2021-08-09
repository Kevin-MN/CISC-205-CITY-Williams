/*  Kevin Morales Nguyen
	Chapter 9 Programming assignment
	3/14/2021
*/

#include <iostream>
#include <iomanip>

//global constants used throughout program
const int SIZE = 4;
const double PI = 3.141592653589793238463;

//function prototypes
float* dynamic_double(float[], int);
float* dynamic_double_PI(float *, int);
float* sort_arr(float*, int);
void pointer_print(float*, int);


int main() {

	//create the array of size 4 with elements specified by the assignment
	float nums[SIZE] = { 9.45, 8.6, 7.3, 6.0 };
	
	//call the function that doubles all the elements in the array and stores
	// it dynamically in a new array and then return the pointer to the new array
	float* new_arr = dynamic_double(nums,SIZE);
	std::cout << "Dynamically allocated array with elements doubled: ";
	pointer_print(new_arr,SIZE); // print our the array via the pointer

	//dynamically create an array that is twice the size with its empty slots filled in 
	// with the constant PI, return pointer to array
	float* new_arr2 = dynamic_double_PI(new_arr,SIZE);
	std::cout << "Dynamically allocated array that is twice as large with PI filling blanks: ";
	pointer_print(new_arr2, SIZE * 2); // print our the array via the pointer

    // call the function that sorts the values of the second array into a third one, 
    // then return the pointer
	float* sorted_arr = sort_arr(new_arr2, SIZE * 2);
	std::cout << "Dynamically allocated array with elements sorted: ";
	pointer_print(sorted_arr, SIZE * 2);// print our the array via the pointer
	
	//delete pointers to free up memory and to prevent memory leaks
	delete [] new_arr;
	delete [] new_arr2;
	delete [] sorted_arr;
	
	return 0;
}

//function definitions

// ********************************************************
// name:      dynamic_double
// called by: main
// passed:	  float numbers[], int size
// returns:   a pointer to a float, points to first element in dynamic float array
// calls:     none
// This method accepts a raw array and then doubles it's elements and stores them 
// into a newly created dynamic array, the function then returns a pointer which 
// points to the first element in the dynamic array.       *
// ********************************************************
float* dynamic_double(float numbers[], int size) {
	float *arrptr = nullptr; // initialize pointer to nullptr
	arrptr = new float[size]; // allcoate dynamic array using new keyword

	for (int i = 0; i < size; i++) {
		*(arrptr + i) = (numbers[i] * 2); // assign values to dynamic array via dereference of pointer
		                                   // and simple pointer arithmetic to access elements
	}

	return arrptr; 
}

// ********************************************************
// name:      dynamic_double_PI
// called by: main
// passed:	  float numbers[], int size
// returns:   a pointer to a float, points to first element in float array
// calls:     none
// This method creates a dynamic array twice the size of the array passed as argument and
// then it also assigns the "empty elements" with the value of PI *
// ********************************************************
float* dynamic_double_PI(float * numbers_start, int size) {
	float* arrptr = nullptr; // initialize pointer to nullptr
	arrptr = new float[size * 2]; // allcoate dynamic array using new keyword
	 
	for (int i = 0; i < size * 2; i++) { // for loop  will run for size * 2
		if (i >= size) { // second half of the array fill up with PI
			*(arrptr + i) = PI; // 
		}
		else { // first half of the array fill up with the contents of the smaller array argument
			*(arrptr + i) = *(numbers_start + i); // assignment via dereference on both sides 
			                                       // because the function was passed a pointer as an argument not a raw array
		}
	}
	
	return arrptr;
}

// ********************************************************
// name:      sort_arr
// called by: main
// passed:	  float numbers[], int size
// returns:   a pointer to a float, points to first element in float array
// calls:     none
// This method will dynamically create a new array and then sort it elements in assending order                                  *
// ********************************************************
float* sort_arr(float* sort_arr, int size) {
	float* arrptr = nullptr; // initialize pointer to nullptr
	arrptr = new float[size]; // allcoate dynamic array using new keyword

	for (int i = 0; i < size; i++) { // copy all of elements from argument array to newly allocated array
		*(arrptr + i) = *(sort_arr + i); // assignment via dereference of pointers
	}

    // run a insertion sort, instead of subscripting with raw array just convert to pointer arithmetic
	int i, j;
	float key;
	for (i = 1; i < size; i++)
	{
		key = *(arrptr + i);
		j = i - 1;

		
		while (j >= 0 && *(arrptr + j) > key)
		{
			*(arrptr + j + 1) = *(arrptr + j);
			j = j - 1;
		}
		*(arrptr + j + 1) = key;
	}
	
	return  arrptr;
}

// ********************************************************
// name:      pointer_print
// called by: main
// passed:	  float numbers[], int size
// returns:   a pointer to a float, points to first element in float array
// calls:     none
// This method will print out the contents of a array given a pointer to the first element of the array                                     *
// ********************************************************
void pointer_print(float* arr_ptr, int size) {
	for (int i = 0; i < size; i++) { // for array of size
		std::cout << std::setprecision(5) <<  *(arr_ptr + i) << " "; // print out via dereference, traversal equation  
		                                                           // (<address to first element> + (i * <size of type>))
	}
	std::cout << "\n";
}
