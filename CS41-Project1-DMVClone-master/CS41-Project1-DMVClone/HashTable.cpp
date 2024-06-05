#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Driver.h"
/*  Used to create a load data function, instead of creating an object using a file as a parameter.
	Referenced to learn about string stream and iss:
https://stackoverflow.com/questions/20594520/what-exactly-does-stringstream-do 
https://stackoverflow.com/questions/53491404/using-istringstream-in-c
   
   Note* I ended up not using the pair return type, and opted to display the data in the search fucntion directly

   Used in search() function to return a string (Driver Name) and a Vehilce struct (driver's vehicle data)
   Reference to return 2 data types from function using pair<T1,T2>:
https://stackoverflow.com/questions/41872550/returning-two-values-of-two-different-types-in-a-c-function

*/
using namespace std;

// Creates a new Hash table and sets all buckets to null
HashTable::HashTable() {
	for (size_t i = 0; i < TABLE_SIZE; i++) {
		hTable[i] = nullptr;
	}
}

// Hashes license number to an index in array
int HashTable::hashDlNum(const string& dlNum) {
	int hash = 0;
	for (char c : dlNum) {
		hash = (hash * 31 + c) % TABLE_SIZE;
	}
	return hash;
}

// Finds index by calling hash, then inserts in correct index
void HashTable::insert(const string& dlNum, const string& firstName, const string& lastName, const VehicleData& vehicleData) {
	int index = hashDlNum(dlNum);

	// Creates a new node
	DriverNode* newNode = new DriverNode;
	newNode->dlNum = dlNum;
	newNode->fName = firstName;
	newNode->lName = lastName;
	newNode->vehicleData = vehicleData;
	newNode->nextptr = nullptr;

	// If index is null, insert node
	if (hTable[index] == nullptr) {
		hTable[index] = newNode;
	}
	// Otherwise use chaining to handle a collision
	else {
		newNode->nextptr = hTable[index];
		hTable[index] = newNode;
	}


}
// ****************** TEST ********************
bool HashTable::remove(const string& dlNum) {
	// Find index by hashing key
	int index = hashDlNum(dlNum);
	// Sets current node to data stored in hashed index
	DriverNode* currNode = hTable[index];
	DriverNode* prevNode = nullptr;
	// Strings to tell user who was removed
	string removedFName, removedLName;

	// Traverse list
	while (currNode != nullptr) {
		// Found node to delete
		if (currNode->dlNum == dlNum) {
			// Case 1: if currNode is first in table
			if (prevNode == nullptr) {
				hTable[index] = currNode->nextptr;
			}
			// Case 2: if currNode is not first
			else {
				prevNode->nextptr = currNode->nextptr;
			}
			removedFName = currNode->fName;
			removedLName = currNode->lName;
			// Remove the node, output the name, and return true
			delete currNode;
			cout << "\nRemoved " << removedFName << " " << removedLName << " (DL: " << dlNum << "). \n";
			return true;
		}
		// Continue to next node
		prevNode = currNode;
		currNode = currNode->nextptr;
	}
	// Case 3: node not found
	cout << "Driver License number " << dlNum << " nothing removed. \n";
	return false;

}

// Searches for vehicle data that is associated with driver's license number
void HashTable::search(const string& dlNum) {
	// Find index by hashing key (drivers license number)
	int index = hashDlNum(dlNum);
	// Set current node to the data stored in hashed index
	DriverNode* currNode = hTable[index];

	// Traverse list and look for a match
	while (currNode != nullptr) {
		// If found concatenate first and last name, then display name and car data
		if (currNode->dlNum == dlNum) {
			string fullName = currNode->fName + " " + currNode->lName;
			cout << "Driver found:" << endl;
			cout << "Driver Name: " << fullName << endl;
			cout << "Vehicle Make: " << currNode->vehicleData.make << endl;
			cout << "Vehicle Model: " << currNode->vehicleData.model << endl;
			cout << "Vehicle Plate Number: " << currNode->vehicleData.plateNum << endl;
			return;
		}
		currNode = currNode->nextptr;
	}
	
	cout << "Driver not found \n";
}

void HashTable::loadData(const string& filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "Error opening driver/vehilce file, try again." << endl;
		return;
	}
	// Define a string object for input
	string line;
	// While loop to proceed through file
	while (getline(inFile, line)) {
		// Use input string stream to extract data from each line of file
		istringstream iss(line);
		string dlNum, fName, lName, make, model, plateNum;
		if (iss >> dlNum >> fName >> lName >> make >> model >> plateNum) {
			// Put file data into vehicle struct
			VehicleData vehicData;
			vehicData.make = make;
			vehicData.model = model;
			vehicData.plateNum = plateNum;
			// Call HashTable::insert()
			insert(dlNum, fName, lName, vehicData);
		}
	}
	inFile.close();
}

void HashTable::saveData(const string& filename) {
	ofstream outFile(filename);
	
	if (!outFile.is_open()) {
		cout << "Error opening file.\n";
		return;
	}

	for (size_t i = 0; i < TABLE_SIZE; ++i) {
		DriverNode* currNode = hTable[i];

		// Traverse the linked list in the current bucket
		while (currNode != nullptr) {
			// Write driver and vehicle information to the file
			outFile << currNode->dlNum << " "
				<< currNode->fName << " "
				<< currNode->lName << " "
				<< currNode->vehicleData.make << " "
				<< currNode->vehicleData.model << " "
				<< currNode->vehicleData.plateNum << endl;

			currNode = currNode->nextptr; // Move to the next node in the linked list
		}
	}
	outFile.close();
}

HashTable::~HashTable() {
	for (size_t i = 0; i < TABLE_SIZE; i++) {
		DriverNode* currNode = hTable[i];
		// Delete every node in the table
		while (currNode != nullptr) {
			DriverNode* nextNode = currNode->nextptr;
			delete currNode;
			currNode = nextNode;
		}
		// Set all buckets to null
		hTable[i] = nullptr;
	}
}

void HashTable::displayTable() const {
	int lineCount = 0;

	cout << "----- Hash Table Contents -----" << endl;
	// Visit every bucket in the table
	for (size_t i = 0; i < TABLE_SIZE; i++) {
		DriverNode* currNode = hTable[i];
		// Traverse the linked list in the current bucket
		while (currNode != nullptr) {
			cout << "Driver's License Number: " << currNode->dlNum << endl;
			cout << "Driver's Name: " << currNode->fName << " " << currNode->lName << endl;
			cout << "Vehicle Make: " << currNode->vehicleData.make << endl;
			cout << "Vehicle Model: " << currNode->vehicleData.model << endl;
			cout << "Vehicle Plate Number: " << currNode->vehicleData.plateNum << endl;
			cout << "-------------------------------" << endl;
			lineCount += 6;
			// Pauses display after 20 lines *******BUG******* You may have to press enter twice
			if (lineCount >= 20) {
				cout << "Press enter to contine...";
				cin.ignore();
				cin.get();
				lineCount = 0;
				cout << endl;
				
			}

			currNode = currNode->nextptr; // Move to the next node in the linked list
		}
	}
	if (lineCount == 0) {
		cout << "No more entries. \n";
	}
}


 
void HashTable::menu() {

	int choice;
	string newDlNum, newFName, newLName, newCarMake, newCarModel, newPlateNum, 
		removeEntry, searchTarget;
	bool exitMenu = false;
	bool validFName, validLName, validDL, validPlate;
	VehicleData newCarData;

	while (!exitMenu) {
		cout << "\n1. View Drivers & their vehicles. \n";
		cout << "2. Add new driver & vehicle entry. \n";
		cout << "3. Remove entry \n";
		cout << "4. Search by driver's license number. \n";
		cout << "5. Return to main menu. \n";
		cin >> choice;
		switch (choice) {
		case 1: displayTable();
			break;
		case 2: cout << "Creating new entry. \n";
			cout << "Enter DL number (format AXXXXXXX, where A is a letter and X is a digit) \n";
			cin >> newDlNum;
			validDL = DriverLL::isValidDLNumber(newDlNum);
			while (!validDL) {
				cout << "Invald DL number (format AXXXXXXX, where A is a letter and X is a digit) \n";
				cin >> newDlNum;
				cin.clear();
				validDL = DriverLL::isValidDLNumber(newDlNum);
			}
			cout << "Enter first name: \n";
			cin >> newFName;
			validFName = DriverLL::isValidName(newFName);
			while (!validFName) {
				cout << "Invalid first name, characters only. \n";
				cin >> newFName;
				cin.clear();
				validFName = DriverLL::isValidName(newFName);
			}
			cout << "Enter last name: \n";
			cin >> newLName;
			validLName = DriverLL::isValidName(newLName);
			while (!validLName) {
				cout << "Invalid last name, characters only. \n";
				cin >> newLName;
				cin.clear();
				validLName = DriverLL::isValidName(newLName);
			}
			
			cout << "Enter vehicle make: \n";
			cin >> newCarMake;
			cout << "Enter vehicle model: \n";
			cin >> newCarModel;
			cout << "Enter plate number (format XAAAXXX, where A is a letter and X is a digit) \n";
			cin >> newPlateNum;
			validPlate = DriverLL::isValidPlateNum(newPlateNum);
			while (!validPlate) {
				cout << "Enter plate number (XAAAXXX where A is a letter and X is a digit) \n";
				cin >> newPlateNum;
				cin.clear();
				validPlate = DriverLL::isValidPlateNum(newPlateNum);
			}
			// Store new data in struct created in menu
			newCarData.make = newCarMake;
			newCarData.model = newCarModel;
			newCarData.plateNum = newPlateNum;
			// Insert the new entry
			insert(newDlNum, newFName, newLName, newCarData);
			saveData("Drivers_and_Vehics.txt");
			break;
		case 3: cout << endl;
			displayTable();
			cout << "Select DLNumber to remove from list: \n";
			cin >> removeEntry;
			remove(removeEntry);
			saveData("Drivers_and_Vehics.txt");
			break;
		case 4: cout << "Enter DLNumber: \n";
			cin.clear();
			cin >> searchTarget;
			search(searchTarget);
			break;
		case 5: cout << "Returning to main menu. \n";
			exitMenu = true;
			break;
		default: cout << "Invalid selection, try again. \n";

		}

	}

}