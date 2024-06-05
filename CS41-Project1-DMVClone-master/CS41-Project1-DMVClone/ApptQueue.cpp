#include "ApptQueue.h"
#include "QueueLinkedList.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // ***********NOTE: Only used to access rand() function for random generation of digits
#include <ctime> //
ApptQueue::ApptQueue() : linkedList("appointments.txt") { 
	// Seeds a random number
	srand(static_cast<unsigned int>(time(nullptr)));
}

// Enqueue a new appointment, based on type provided by user
void ApptQueue::enQueue(const string& firstName, int option) {
	
	string apptType, codePrefix;

	switch (option) {
	case 1:
		apptType = "Driver's License Renewal";
		codePrefix = "DLR";
		break;
	case 2:
		apptType = "Behind the Wheel Test";
		codePrefix = "BWT";
		break;
	case 3: 
		apptType = "Vehicle Registration Renewnal";
		codePrefix = "VRR";
		break;
	case 4:
		apptType = "Permit Written Test";
		codePrefix = "PWT";
		break;
	default:
		cout << "Invalid option, Appointment not scheduled. \n";
		return;
	}
	int randomNum = rand() % 900 + 100;
	string apptNum = codePrefix + to_string(randomNum);
	Node* newNode = new Node(firstName, apptNum);
	linkedList.append(newNode);
	saveEnqueue("appointments.txt", newNode);
}

string ApptQueue::dequeue() {
	if (linkedList.isEmpty()) {
		cout << "Error: Queue is empty, unable to dequeue. \n";
		return "";
	}
	string dequeuedData = linkedList.getHeadData();
	linkedList.removeAfter(nullptr);
	return dequeuedData;
}

void ApptQueue::displayQueue(ostream& print) {
	linkedList.print(print, "\n");
}

void ApptQueue::saveEnqueue(const string& filename, Node* newNode) {
	ofstream apptOutFile(filename, ios::app);

	if (apptOutFile.is_open()) {
		apptOutFile << newNode->apptName << " " << newNode->apptNum << endl;

		apptOutFile.close();
		cout << "Data saved to file.\n";
	}

	else {
		cout << "Error saving to file.\n";
	}
}

void ApptQueue::saveDequeue(const string& filename, LinkedList& list) {

	ofstream apptOutFile(filename);

	if (!apptOutFile.is_open()) {
		cout << "Error opening file.\n";
		return;
	}

	// Iterate through the linked list and write each entry to the file
	Node* node = list.getHead();
	while (node) {
		// Write the appointment data
		apptOutFile << node->apptName << " " << node->apptNum << endl;
		node = node->next;
	}

	apptOutFile.close();

	cout << "Data saved to file after dequeue.\n";
}

void ApptQueue::menu() {
	bool exitmenu = false;
	int choice, option;
	string apptName, apptNum, apptData;
	while (!exitmenu) {
		cout << "\n1. View appointments\n";
		cout << "2. Create appointment\n";
		cout << "3. Mark appointment complete \n";
		cout << "4. Return to main menu \n";
		cin >> choice;
		switch (choice) {
		case 1: cout << "Displaying appointments: \n";
			displayQueue(cout);
			break;
		case 2: cout << "Enter First Name: ";
			cin >> apptName;
			cout << "Select appointment type:\n";
			cout << "1. Drivers License Renewal\n";
			cout << "2. Behind the Wheel Test\n";
			cout << "3. Car Registration Renewal\n";
			cout << "4. Permit Written Test\n";
			cin >> option;
			// Schedule appointment based on user's choice
			enQueue(apptName, option);
			break;
		case 3: cout << dequeue() << " completed.\n";
			saveDequeue(oFileName, linkedList);
			break;
		case 4: exitmenu = true;
			return;
		default: cout << "Invaild choice, try again\n";
		}
	}
}


