#include "Driver.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>

 DriverLL::DriverLL(const string& filename) : driversFile(filename) {
	 listHead = nullptr;

	 if (!driversFile.is_open()) {
		 cout << "Error opening drivers file.\n";
	 }

	 string line, firstName, lastName, licenseNum;

	 while (driversFile >> firstName >> lastName >> licenseNum) {

		 Node* newNode = new Node{ firstName, lastName, licenseNum, nullptr };
		 if (!listHead) {
			 listHead = newNode; 
		 }
		 else {
			 newNode->nextPtr = listHead;
			 listHead = newNode;
		 }
	 }

	 driversFile.close();
 }

void DriverLL::appendNode(string fName, string lName, string dlNum) {
	Node* newNode; // Points to a new node
	Node* nodePtr; // Pointer to move through the list

	// Allocates a new node and stores names as the data
	newNode = new Node;			
	newNode->firstName = fName;
	newNode->lastName = lName;
	newNode->licenseNum = dlNum;
	newNode->nextPtr = nullptr;

	// If the head doesen't exist, our new node becomes the head.
	if (!listHead) {
		listHead = newNode;
	}
	// If head exists, traverse the list until nextPtr is null, then place our newNode at the end.
	else {
		nodePtr = listHead;
		while (nodePtr->nextPtr) {
			nodePtr = nodePtr->nextPtr;
		}
		nodePtr->nextPtr = newNode;
	}
}

void DriverLL::deleteNode(string dlNum) {
	Node* nodePtr;	// Pointer to move through list
	Node* prevNode; // Points at previous node

	// If the list is empty, nothing to delete
	if (!listHead)
		return;
	// Checks if head is a match to entry to be deleted
	if (listHead->licenseNum == dlNum) {
		nodePtr = listHead->nextPtr;
		delete listHead;
		listHead = nodePtr;
	}
	// If head is not a match, move through the list until we find a match for license Number
	else {
		nodePtr = listHead;
		prevNode = nodePtr;
		while (nodePtr != nullptr && nodePtr->licenseNum != dlNum) {
			prevNode = nodePtr; // Keeps track of the previous node
			nodePtr = nodePtr->nextPtr; // Points to the next node
		}
		if (nodePtr) {
			prevNode->nextPtr = nodePtr->nextPtr; // Makes the previous node point to the node after the deleted node
			delete nodePtr;
		}
	}
}

void DriverLL::displayDriverList() const {
	Node* nodePtr;
	nodePtr = listHead;

	while (nodePtr) {
		cout << nodePtr->firstName << " " << nodePtr->lastName << " " << nodePtr->licenseNum << endl;
		nodePtr = nodePtr->nextPtr;
	}
}

void DriverLL::searchDrivers(const string& licenseSearch) {
	
	Node* curNode;
	curNode = listHead;
	bool found = false;

	while (curNode != nullptr) {
		if (curNode->licenseNum == licenseSearch) {
			cout << "Driver details: \n";
			cout << curNode->firstName << " ";
			cout << curNode->lastName << " ";
			cout << curNode->licenseNum << endl;
			found = true;
			break;
		}
		curNode = curNode->nextPtr;
	}

	if (!found) {
		cout << "Driver not found";
	}

}

bool DriverLL::isValidDLNumber(const string& dlNum) {
	// AXXXXXXX A is letter and X is a digit
	// Check length
	if (dlNum.length() != 8)
		return false;
	// Check first character for a letter
	if (!isalpha(dlNum[0])) 
		return false;
	// Check the rest of string for digits
	for (size_t i = 1; i < dlNum.length(); i++) {
		if (!isdigit(dlNum[i]))
			return false;
	}
	return true;
}

bool DriverLL::isValidName(const string& name) {
	// Check if nothing is entered
	if (name.empty())
		return false;
	// Check every character is a letter and not a space (this should allow spaces)
	for (char c : name) {
		if (!isalpha(c) && c != ' ')
			return false;
	}
	return true;
}

bool DriverLL::isValidPlateNum(const string& plateNum) {
	// XAAAXXX X is a digit A is a character
	// Check length
	if (plateNum.length() != 7)
		return false;
	// Check first character is a digit
	if (!isdigit(plateNum[0]))
		return false;
	// Check 2nd, 3rd, 4th are characters
	for (size_t i = 1; i <= 3; i++) {
		if (!isalpha(plateNum[i]))
			return false;
	}
	for (size_t i = 4; i < 7; i++) {
		if (!isdigit(plateNum[i]))
			return false;
	}
	return true;
}


void DriverLL::menu() {
	int choice, driverRemovalPos;
	string newDriverFirstName, newDriverLastName, newLicenseNum, delLicenseNum, licenseSearch;
	bool exitMenu = false;
	bool validFName, validLName, validPlate, validLicense;

	while (!exitMenu) {
		cout << "\nPlease choose from the following options: \n\n";
		cout << setw(8) << "1. View driver entries\n";
		cout << setw(8) << "2. Add driver\n";
		cout << setw(8) << "3. Delete driver\n";
		cout << setw(8) << "4. Search List\n";
		cout << setw(8) << "5. Return to main menu\n";
		cin >> choice;

		switch (choice) {
		case 1: cout << "Displaying current list...\n";
			displayDriverList();
			break;

		case 2: cout << "Enter driver's first name: \n";
			cin >> newDriverFirstName;
			validFName = isValidName(newDriverFirstName);
			while (!validFName) {
				cout << "Invalid name, characters only. \n";
				cin >> newDriverFirstName;
				cin.clear();
				validFName = isValidName(newDriverFirstName);
			}
			cout << "Enter driver's last name: \n";
			cin >> newDriverLastName;
			validLName = isValidName(newDriverLastName);
			while (!validLName) {
				cout << "Invalid name, characters only. \n";
				cin >> newDriverLastName;
				cin.clear();
				validLName = isValidName(newDriverLastName);
			}
			cout << "Enter DL number (format AXXXXXXX, where A is a letter and X is a digit) \n";
			cin >> newLicenseNum;
			validLicense = isValidDLNumber(newLicenseNum);
			while (!isValidDLNumber) {
				cout << "Invalid DL number (format AXXXXXXX, where A is a letter and X is a digit) \n";
				cin >> newLicenseNum;
				cin.clear();
				validLicense = isValidDLNumber(newLicenseNum);
			}

			appendNode(newDriverFirstName, newDriverLastName, newLicenseNum);
			break;
		case 3: cout << "Select driver to delete from current list: \n";
			displayDriverList();
			cout << endl;
			cout << "Enter license number (case sensitive): \n";
			cin >> delLicenseNum;
			deleteNode(delLicenseNum);
			break;
		case 4: cout << "Enter license to search for (case sensitive): \n";
			cin >> licenseSearch;
			searchDrivers(licenseSearch);
			break;
		case 5: cout << "Returning...\n";
			exitMenu = true;
			return;
		default: cout << "Invalid choice, try again.\n";

		}
	}
}

