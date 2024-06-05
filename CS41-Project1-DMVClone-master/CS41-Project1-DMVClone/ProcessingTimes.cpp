#include "ProcessingTimes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <Windows.h> //For getTickCount()

// Constructor creates a new hash table using base class and file contents
ProcessingTimes::ProcessingTimes(int size, const string& fileName) : BaseHashTable(size) {

	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		cout << "Error opening " << fileName << " try again. \n";
		return;
	}
	
	// Read data from the file and populate the hash table
	string apptType;
	int timeMins;
	while (inFile >> apptType >> timeMins) {
		// Construct a key for the appointment type
		std::string key = createKey(apptType);

		// Insert appointment type and processing time into the hash table
		insert(key, timeMins);
	}


	inFile.close();
};

// Basic hashing calculation to store keys
int ProcessingTimes::hashKey(const string& key) {
	int hash = 0;
	for (char c : key) {
		hash = (hash * 29 + c) % size;
	}
	return hash;
}

// Takes the key, hashes it and stores it with the given time in minutes (value)
void ProcessingTimes::insert(const string& key, const int& value)  {
	int index = hashKey(key);
	int step = doubleHash(key);
	int count = 0;
	while (hTable[index].filled && hTable[index].key != key) {
		index = (index + step) % size;
		count++;

		if (count == size) {
			cout << "Table is full, unable to insert. \n";
			return;
		}
	}
	hTable[index].key = key;
	hTable[index].value = value;
	hTable[index].filled = true;

}

// This function is how the user can access the insert function
void ProcessingTimes::addAppt() {
	int choice, processingTime;

	cout << "Enter processing time in minutes: ";
	cin >> processingTime;
	// I use menus to select a type of appoointment and then create a code based on user suggestions
	do {
		cout << "\n===== Select appointment type =====\n";
		cout << "1. Driver license renewal\n";
		cout << "2. Vehicle registration renewal\n";
		cout << "3. Behind the wheel test\n";
		cout << "4. Permit written test\n";
		cout << "Enter your choice (1-4)\n";

		cin >> choice;
		// Takes the user selection, and time, then passes this to a secondary function
		switch (choice)
		{
		case 1: 
			insertWithType("Driver License Renewal", processingTime);
			break;
		case 2:
			insertWithType("Vehicle Registration Renewal", processingTime);
			break;
		case 3:
			insertWithType("Behind the Wheel Test", processingTime);
			break;
		case 4:
			insertWithType("Permit Written Test", processingTime);
			break;
		default: cout << "Invalid choice, please enter a valid option (1-4).\n";

		} 
	} while (choice < 1 || choice > 4);
	saveData("appt_times.txt");
}
// Takes the user input and generates a prefix based on appointment typt to prepare for hashing
void ProcessingTimes::insertWithType(const string& apptType, int processingTime) {
	string prefix = getPrefix(apptType);
	string key = createKey(prefix);
	insert(key, processingTime);
	cout << "Appointment added successfully.";

}
// Doubling hashing to handle collisions
int ProcessingTimes::doubleHash(const string& key)  {
	int prime = 7;
	int hashValue = hashKey(key);
	int step = prime - (hashValue % prime);
	if (step == 0) {
		step = 1;
	}
	return step;
}
// Simple remove function (not in user menu as of now)
void ProcessingTimes::remove(const string& key) {
	int index = hashKey(key);
	int step = doubleHash(key);
	int count = 0;
	while (count < size && !hTable[index].filled) {
		if (hTable[index].key == key) {
			// Clear the entry
			hTable[index].key = "";
			hTable[index].value = 0;
			hTable[index].filled = false;
			cout << "Key '" << key << "' removed from hash table.\n";
			return;
		}
		index = (index + step) % size;
		count++;
	}
	cout << "Key '" << key << "' not found in hash table.\n";
}
// This generates a key to be hashed so the user doesn't have to. The format is appointment code 
// and a 1-3 digit number
string ProcessingTimes::createKey(const string& apptType) {
	// Generate a key based on appointment type selected by user. (i.e. "VRR438")
	return apptType.substr(0, 3) + to_string(rand() % 1000);
}
// This would return the processing time for a sinlge appointment code, unused
int ProcessingTimes::getProcessingTime(const string& key) {
	int index = hashKey(key);
	if (hTable[index].filled && hTable[index].key == key) {
		return (hTable[index].value);
	}
	return -1;
}
// This returns the average processing time of all entries to the user
double ProcessingTimes::getAverageTimes() const {
	int sum = 0;
	int count = 0;

	for (size_t i = 0; i < size; ++i) {
		if (hTable[i].filled) {
			sum += hTable[i].value;
			count++;
		}
	}
	
	if (count > 0) {
		double avgTime = static_cast<double>(sum) / count;
		cout << fixed << setprecision(2);
		return avgTime;
	}
	else {
		return 0.0;
	}
}
// This function returns the average time for a selected appointment type
double ProcessingTimes::getAverageTimesByType(const string& apptTypePrefix) const {
	int sum = 0;
	int count = 0;

	for (size_t i = 0; i < size; ++i) {
		if (hTable[i].filled && hTable[i].key.substr(0, 3) == apptTypePrefix) {
			sum += hTable[i].value;
			count++;
		}
	}

	if (count > 0) {
		double avgTimeByType = static_cast<double>(sum) / count;
		cout << fixed << setprecision(2);
		return avgTimeByType;
	}
	else {
		return 0.0;
	}
}
// This is a function that displays the output of the above function
void ProcessingTimes::displayAverageTimesByType(const string& apptType, const string& prefix) const {
	cout << "Average processing time for " << apptType << ": " << getAverageTimesByType(prefix) <<
		" minutes \n";
}


// This function shows the user when appointment type took the most amount of time, and the total time in minutes
pair<string, int> ProcessingTimes::getLongestType() const {
	const int numTypes = 4;
	int typeSums[numTypes] = { 0 };

	for (size_t i= 0; i < size; ++i) {
		if (hTable[i].filled) {
			string prefix = hTable[i].key.substr(0, 3);
			int value = hTable[i].value;
			if (prefix == "DLR") {
				typeSums[0] += value;
			}
			else if (prefix == "VRR") {
				typeSums[1] += value;
			}
			else if (prefix == "BWT") {
				typeSums[2] += value;
			}
			else if (prefix == "PWT") {
				typeSums[3] += value;
			}
		}
	}

	string longestType;
	int maxSum = -1;

	for (size_t j = 0; j < numTypes; ++j) {
		if (typeSums[j] > maxSum) {
			maxSum = typeSums[j];
			switch (j) {
			case 0:
				longestType = "Driver's license renewal";
				break;
			case 1:
				longestType = "Vehicle registration renewal";
				break;
			case 2:
				longestType = "Behind the wheel test";
				break;
			case 3:
				longestType = "Permit written test";
				break;
			}
		}
	}
		
	return make_pair(longestType, maxSum);
}

// This returns a prefix for the creation of a key
string ProcessingTimes::getPrefix(const std::string& appointmentType) const {
	// Determine the prefix based on the appointment type
	if (appointmentType == "Driver License Renewal") {
		return "DLR";
	}
	else if (appointmentType == "Vehicle Registration Renewal") {
		return "VRR";
	}
	else if (appointmentType == "Behind the Wheel Test") {
		return "BWT";
	}
	else if (appointmentType == "Permit Written Test") {
		return "PWT";
	}
	else {
		return "";
	}
}

// Displays the hash table
void ProcessingTimes::displayTable() const {
	cout << "\n============ Hash table contents ============\n";
	cout << setw(15) << "Index" << setw(20) << "Key" << setw(10) << "Value" << endl;
	for (size_t i = 0; i < size; ++i) {
		if (hTable[i].filled) {
			cout << setw(15) << i << setw(20) << hTable[i].key << setw(10) << hTable[i].value << endl;
		}
	}
}

void ProcessingTimes::saveData(const string& fileName) {
	ofstream outFile(fileName);

	if (!outFile.is_open()) {
		cout << "Error opening file.\n";
		return;
	}

	for (size_t i = 0; i < size; ++i) {
		if (hTable[i].filled) {
			outFile << hTable[i].key << " " << hTable[i].value << endl;
		}
	}
	outFile.close();
	cout << "\nData saved to " << fileName << ".\n";
}


// This is the main menu for time analysis 
void ProcessingTimes::menu() {
	int choice, subChoice, startTime, endTime, elapsedTime;
	string prefix;
	pair<string, int> longestType;
	do {
		
		cout << "\n===== Processing Times Menu =====\n";
		cout << "1. Calculate average processing time for all appointments. \n";
		cout << "2. Calculate average processing time for specific appointment types. \n";
		cout << "3. Calculate appointment type with longest total processing time.\n";
		cout << "4. Display Hash table contents.\n";
		cout << "5. Add new appointment data.\n";
		cout << "6. Exit\n";
		cout << "Enter your choice (1-4): ";

		cin >> choice;

		switch (choice) {
		case 1:
			// Get and display average processing time for all appointments
			startTime = GetTickCount();
			cout << "Average processing time for all appointments: "
				<< getAverageTimes() << " minutes\n";
			Sleep(1);
			endTime = GetTickCount();
			elapsedTime = endTime - startTime;
			cout << "Algorithm actual runtime: " << elapsedTime << " milliseconds.";
			break;
		case 2:
			displayApptTypeMenu();
			break;
		case 3:
			// Get and display appointment type with longest processing time
			startTime = GetTickCount();
			 longestType = getLongestType();
			 Sleep(1);
			 cout << "Appointment with longest processing time: " << longestType.first << " (" <<
				 longestType.second << " minutes) \n";
			 endTime = GetTickCount();
			 elapsedTime = endTime - startTime;
			 cout << "Algorithm actual runtime: " << elapsedTime << " milliseconds.";
			break;
		case 4:
			displayTable();
			break;
		case 5:
			addAppt();
			break;
		case 6:
			cout << "Exiting time analysis menu.\n";
			break;
		default:
			cout << "Invalid choice. Please enter a valid option (1-4).\n";
		}
	} while (choice != 6);
}



// This is a sub menu tha that allows the user to select from among the apointment types
// This in effect validates user input by not having to validate a string
void ProcessingTimes::displayApptTypeMenu() const {
	int subChoice;
	do {
		// Display submenu options for appointment types
		cout << "\n===== Select Appointment Type =====\n";
		cout << "1. Driver License Renewal\n";
		cout << "2. Vehicle Registration Renewal\n";
		cout << "3. Behind the Wheel Test\n";
		cout << "4. Permit Written Test\n";
		cout << "5. Back to Main Menu\n";
		cout << "Enter your choice (1-5): ";

		// Read user submenu choice
		cin >> subChoice;

		if (subChoice >= 1 && subChoice <= 4) {
			// Get appointment type name and corresponding prefix
			string appointmentTypeName;
			string prefix;
			switch (subChoice) {
			case 1:
				appointmentTypeName = "Driver License Renewal";
				prefix = "DLR";
				break;
			case 2:
				appointmentTypeName = "Vehicle Registration Renewal";
				prefix = "VRR";
				break;
			case 3:
				appointmentTypeName = "Behind the Wheel Test";
				prefix = "BWT";
				break;
			case 4:
				appointmentTypeName = "Permit Written Test";
				prefix = "PWT";
				break;
			}

			// Display average processing time for the selected appointment type
			displayAverageTimesByType(appointmentTypeName, prefix);
		}
		else if (subChoice == 5) {
			std::cout << "Returning to Main Menu...\n";
		}
		else {
			std::cout << "Invalid choice. Please enter a valid option (1-5).\n";
		}
	} while (subChoice != 5);  // Continue submenu until user chooses to go back
}


