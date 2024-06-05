#include "VehicleList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
/* Rick Richmond--Here the member functions are defined. The constructor reads the file 
	into a dynamic array and uses a function defined later to resize the array if needed 
	due to users adding entries, or a larger file being processed
*/
VehicleList::VehicleList(const string& filename) : vFile(filename), arrSizeVehicle(0), currArrSize(20){
	if (!vFile.is_open()) {
		cout << "Error opening cars file.";
	}
	pVehicles = new string[currArrSize];
	string vEntry;
	while (getline(vFile, vEntry)) {
		if (arrSizeVehicle == currArrSize) {
			resizeArr();
		}
		pVehicles[arrSizeVehicle++] = vEntry;
	}
}

// Destructor 
VehicleList::~VehicleList() {
	if (vFile.is_open()) {
		vFile.close();
	}
	
	delete[] pVehicles;
}
// Boolean used to see if the file is open
 bool VehicleList::isOpen() const {
	return vFile.is_open();
}
// This displays each element, one per line using the pointer
void VehicleList::displayList() const {
	int lineCounter = 0;
	for (size_t i = 0; i < arrSizeVehicle; ++i) {
		cout << i+1 << ". " << pVehicles[i] << endl;
		lineCounter++;
		if (lineCounter == 20) {
			cout << "-----Please press enter to continue-----";
			cin.ignore();
			cin.get();
			lineCounter = 0;
		}
	}
	cout << endl;
}
// This function allows users to add an entry, resizing the array if necessary
void VehicleList::addVehicle(const string& newVehicleEntry) {
	if (arrSizeVehicle == currArrSize) {
		resizeArr();
	}
	// Stores newVehicleEntry to the end of array
	pVehicles[arrSizeVehicle++] = newVehicleEntry;
	// Opens file in append mode
	ofstream vOutFile(oFileName, ios::app);
	if (vOutFile.is_open()) {
		vOutFile << newVehicleEntry << endl;
		vOutFile.close();
	}
	else {
		cout << "Error opening file" << endl;
	}
			
}
// First check if user inputs a vaild position(not index)
void VehicleList::removeVehicle(int vPosition){
	if (vPosition < 1 || vPosition > arrSizeVehicle) {
		cout << "Error, no entry at that position." << endl << endl;
	}
	// Convert index to position
	int arrIndex = vPosition - 1;
	// Loop through array and copy element[i] into element[i+1], effectively removing it
	for (size_t i = arrIndex; i < arrSizeVehicle - 1; ++i) {	
		pVehicles[i] = pVehicles[i + 1];
	}
	// Decrement the array size
	--arrSizeVehicle;	
	vFile.close();
	// Repeat what we did above by performing it on the file in addion to the array
	ofstream vOutFile(oFileName); 
	for (size_t i = 0; i < arrSizeVehicle; ++i) {	
		vOutFile << pVehicles[i] << endl;
	}
}
void VehicleList::saveToFile(const string& filename, const string* arr, int size) {
	ofstream outFile(filename); 
	if (outFile.is_open()) {
		for (size_t i = 0; i < size; ++i) {
			outFile << arr[i] << endl;
		}
		outFile.close();
		cout << "Data saved to file." << endl;
	}
	else {
		cout << "Error opening file for writing." << endl;
	}
}
void VehicleList::resizeArr() {
	// Resize array when needed, when we exceed 20
	currArrSize *= 2;
	string* pVehicleAddition = new string[currArrSize];
	for (size_t i = 0; i < arrSizeVehicle; ++i) {
		pVehicleAddition[i] = pVehicles[i];			
	}
	delete[] pVehicles;
	pVehicles = pVehicleAddition;
}
/* Check to see if the term being searched for is a partial string of an array item */
bool VehicleList::hasPartialString(const string& vehicleInArray, const string& searchTerm) {
	if (vehicleInArray.length() < searchTerm.length()) {
		return false;
	}
	/* Recieved a possible overflow warning when assigning i and j as int in the loops I used 
		this link for information and a fix: 
		https://stackoverflow.com/questions/1951519/when-to-use-stdsize-t 
	*/
	for (size_t i = 0; i <= vehicleInArray.length(); ++i) {
		bool found = true;
		for (size_t j = 0; j < searchTerm.length(); ++j) {
			if (vehicleInArray[i+j] != toupper(searchTerm[j])) {
				found = false;
				break;
			}
		}
		if (found) {
			return true;
		}
	}
	return false;
}
/* First we compare the search term to the item in the array and determing if the target is a partial string,
if it is we output that line*/
void VehicleList::partialStringSearch(const string* pVehicles, int arrSizeVehicle, 
	const string& searchTerm) {
	bool found = false;
	cout << "Searching for " << searchTerm << ": \n";
	for (size_t i = 0; i < arrSizeVehicle; ++i) {
		if (hasPartialString(pVehicles[i], searchTerm)) {
			found = true;
			cout << pVehicles[i] << endl;
		}
	}
	if (!found) {
		cout << "No matches for " << searchTerm << " were found.\n";
	}
}
void VehicleList::selectionSortAscending(string* pVehicles, int arrSizeVehile) {
	for (size_t i = 0; i < arrSizeVehicle - 1; i++) {
		int minIndex = i;
		for (size_t j = i + 1; j < arrSizeVehicle; j++) {
			if (pVehicles[j] < pVehicles[minIndex]) {
				minIndex= j;
			}
		}
		swap(pVehicles, i, minIndex);
	}
	/* This function call will save the changes of the sorting to the output file. Comment it out
	   to see the sorting without saving to the file.*/
	saveToFile(oFileName, pVehicles, arrSizeVehicle);
}
void VehicleList::selectionSortDescending(string* pVehicles, int arrSizeVehile) {
	for (size_t i = 0; i < arrSizeVehicle - 1; i++) {
		
		int maxIndex = i;
		for (size_t j = i + 1; j < arrSizeVehicle; j++) {
			if (pVehicles[j] > pVehicles[maxIndex]) {
				maxIndex= j;
			}
		}
		swap(pVehicles, i, maxIndex);
	}
	/* See comment above  */
	saveToFile(oFileName, pVehicles, arrSizeVehicle);
}
void VehicleList::swap(string* pVehicles, int i, int j) {
	string temp = pVehicles[i];
	pVehicles[i] = pVehicles[j];
	pVehicles[j] = temp;
}								
// A menu for the user to interact with the data and the file.
void VehicleList::menu() {
	int choice, vRemovalPos;
	string vAddition;
	bool exitMenu= false;

	while (!exitMenu ) {
		cout << "\nPlease choose from the following options: \n\n";
		cout << setw(8) << "1. View vehicle entries\n";
		cout << setw(8) << "2. Add entry\n";
		cout << setw(8) << "3. Delete entry\n";
		cout << setw(8) << "4. Sort vehicles in ascending order (project 3)\n";
		cout << setw(8) << "5. Sort vehicles in descending order (project 3) \n";
		cout << setw(8) << "6. Search for vehicles (project 3) \n";
		cout << setw(8) << "7. Return to main menu\n";
		cin >> choice;
		int startTime, endTime, elapsedTime;
		/* Switch statement seemed the best choice for a menu, call the relevant functions
		   when user performs add/remove/etc */
		switch (choice) {
			case 1: cout << "Displaying current list...\n";
				displayList();
				break;
			case 2: 
				cin.ignore();
				cout << "Enter make and model of vehicle: \n";
				getline(cin, vAddition);
				for (int i = 0; i < vAddition.length(); ++i) {
					if (islower(vAddition[i]) && !isspace(vAddition[i])) {
						vAddition[i] = toupper(vAddition[i]);
					}
				}
				addVehicle(vAddition);
				break;
			case 3:
				cout << "Select entry to remove: \n";
				cin >> vRemovalPos;
				removeVehicle(vRemovalPos);
				break;
			case 4: 
				//displayList();
				cout << endl << "Sorting vehicle list in alphabetical order...\n";
				startTime = GetTickCount();
				selectionSortAscending(pVehicles, arrSizeVehicle);
				Sleep(1);
				endTime = GetTickCount();
				elapsedTime = endTime - startTime;
				cout << endl << "List after sorting: \n";
				displayList();
				cout << "Selection sort took " << elapsedTime << " milliseconds.";
				break;
			case 5:
				//displayList();
				cout << endl << "Sorting vehicle list in reverse alphabetical order...\n";
				startTime = GetTickCount();
				selectionSortDescending(pVehicles, arrSizeVehicle);
				Sleep(1);
				endTime = GetTickCount();
				elapsedTime = endTime - startTime;
				cout << endl << "List after sorting: \n";
				displayList();
				cout << "Selection sort descending took " << elapsedTime << " milliseconds.";
				break;
			case 6:
				do {
					cout << "Enter search term: ";
					cin.ignore();
					getline(cin, searchTerm);
					if (searchTerm.length() < 3) {
						cout << "Please search for at least 3 characters \n";
					}
				} while (searchTerm.length() < 3);
				startTime = GetTickCount();
				partialStringSearch(pVehicles, arrSizeVehicle, searchTerm);
				Sleep(1);
				endTime = GetTickCount();
				elapsedTime = endTime - startTime;
				cout << "Search took " << elapsedTime << " milliseconds";
				break;
				case 7: cout << "Returning...\n" << endl;
				exitMenu = true;
				return;
			default: cout << "Invalid choice, try again.";
		}
	}
}

