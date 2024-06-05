#include "IncidentList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
// This funciton opens, and reads the data into the approiate location for the struct 
IncidentList::IncidentList(const string& filename) : incidentFile(filename), arrSizeIncident(0), 
maxArrSizeIncident(50) {
	if (!incidentFile.is_open()) {
		cout << "Error opening incidents file.";
	}
	/* Create a new array of structs with 50 maximum size*/
	pIncidents = new Incidents[maxArrSizeIncident];
	string numEntries;
	/*https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
		This link helped troubleshoot how to create an array using the size of the provided file by 
		incrementing a value using getline. */
	while (getline(incidentFile, numEntries)) {
		++arrSizeIncident; // Start with array size 0 and increment by 1 per line in file
		if (arrSizeIncident == maxArrSizeIncident) {	// If lines in file are equal to max, resize.
			resizeArr();
			}
	}
	incidentFile.close();
	incidentFile.open("2023Incidents.txt");
	pIncidents = new Incidents[maxArrSizeIncident];
	
		for (size_t i = 0; i < arrSizeIncident; ++i)
		{
			incidentFile >> pIncidents[i].incidentNum;
			incidentFile >> pIncidents[i].incidentMonth;
			incidentFile >> pIncidents[i].incidentDay;
		}
		
	
}

IncidentList::~IncidentList() {
	if (incidentFile.is_open()) {
		incidentFile.close();
	}
	delete[] pIncidents;
	
}
// Iterates and displays the struct elements
void IncidentList::displayIncidentList() const  {
	int lineCounter = 0;
	for (size_t i = 0; i < arrSizeIncident; ++i)
	{
		cout << i +1 << ". " << pIncidents[i].incidentNum << " ";
		cout << pIncidents[i].incidentMonth << " ";
		cout << pIncidents[i].incidentDay << endl;
		lineCounter++;
		if (lineCounter == 20) {
			cout << "-----Please press enter to continue-----";
			cin.clear();
			cin.ignore();
			cin.get();
			lineCounter = 0;
		}
	}
}
// Call this in the default constructor to test if file opened correctly
bool IncidentList::isOpen() const {
	return incidentFile.is_open();
}

void IncidentList::addIncident(const string& newIncidentNum, const string& newIncidentMonth, 
	const int& newIncidentDay) {
	if (arrSizeIncident == maxArrSizeIncident) {
		resizeArr();
	}
	// Store new user entry in approiate data members.
	pIncidents[arrSizeIncident].incidentNum = newIncidentNum;
	pIncidents[arrSizeIncident].incidentMonth = newIncidentMonth;
	pIncidents[arrSizeIncident].incidentDay = newIncidentDay;
	arrSizeIncident++;
	// Write the changes to external file
	ofstream iOutFile(oFilename, ios::app);
	iOutFile << newIncidentNum << " ";
	iOutFile << newIncidentMonth << " ";
	iOutFile << newIncidentDay << endl;
		cout << endl;
	

}
// Checks the array and removes the entry at given position, then updates the file accordingly. 
void IncidentList::removeIncident(int incidentPos) {
	if (incidentPos < 1 || incidentPos > arrSizeIncident) {
		cout << "Error, no entry at that position." << endl << endl;
	}
	int arrIndex = incidentPos - 1;

	for (size_t i = arrIndex; i < arrSizeIncident - 1; ++i) {
		pIncidents[i] = pIncidents[i + 1];
		
	}
	--arrSizeIncident;
	
	incidentFile.close();
	ofstream iOutFile(oFilename);
	for (size_t i = 0; i < arrSizeIncident; ++i) {
		iOutFile << pIncidents[i].incidentNum << " ";
		iOutFile << pIncidents[i].incidentMonth << " ";
		iOutFile << pIncidents[i].incidentDay << endl;
	}
}
// Tried to use a different method to resize the array instead of doubling, 
// but I get an error relateing to available memory
void IncidentList::resizeArr() {
	maxArrSizeIncident *= 2;
	Incidents* pIncidentsAdd = new Incidents[maxArrSizeIncident];
	for (size_t i = 0; i < arrSizeIncident; ++i) {
	pIncidentsAdd[i] = pIncidents[i];

	}
	delete [] pIncidents;
	pIncidents = pIncidentsAdd;
}

string IncidentList::findMonth(Incidents reports[], int arrSizeIncident, string monthNames[],
	int monthCounts[], int& incidentsInMaxMonth) {
	for (size_t i = 0; i < arrSizeIncident; ++i) {
		for (size_t j = 0; j < 12; ++j) {
			//Check if struct variable matches string literal
			if (reports[i].incidentMonth == monthNames[j]) {
				// Increment the index of month that occurs in data
				monthCounts[j]++; 

			}
		}
	}
	int maxIndex = 0;
	for (size_t i = 0; i < 12; ++i) {
		// Compare the index of each month to the current max
		if (monthCounts[i] > monthCounts[maxIndex]) {	
			// Assign new maximum if a higher value is found
			maxIndex = i;	
		}

	}
	// Stores the number of incidents in most common month
	incidentsInMaxMonth = monthCounts[maxIndex];	
	// Returns string of the month with most occurences 
	return monthNames[maxIndex];	
}

bool IncidentList::isValidMonth(string months[], string userMonth) {
	for (size_t i = 0; i < NUM_MONTHS; i++) {
		if (userMonth == months[i]) {
			return true;
		}
	
	}
	return false;
}

void IncidentList::menu() {
	int choice, removalPos, newReportDay;
	string newReportNum, newReportMonth;
	bool exitMenu = false;
	bool validMonth;

	while (!exitMenu) {
		cout << "\nPlease choose from the following options: \n\n";
		cout << setw(8) << "1. View incident entries\n";
		cout << setw(8) << "2. Add entry\n";
		cout << setw(8) << "3. Delete entry\n";
		cout << setw(8) << "4. View month with most incidents\n";
		cout << setw(8) << "5. Return to main menu\n";
		cin >> choice;
		switch (choice) {
		case 1: cout << "Displaying current list...\n";
			displayIncidentList();
			break;
		case 2:
			cout << "Enter report number: \n";
			cin >> newReportNum;
			cout << "Enter month: \n";
			cin >> newReportMonth;
			validMonth = isValidMonth(monthNames, newReportMonth);
			while (!validMonth) {
				cout << "Invalid month, check capitalization. \n";
				cin >> newReportMonth;
				cin.clear();
				validMonth = isValidMonth(monthNames, newReportMonth);
			}
			cout << "Enter date: \n";
			while (!isValidDate) {
				cin >> newReportDay;

				if (newReportDay >= 1 && newReportDay <= 31) {
					isValidDate = true;
				}
				else {
					cout << "Invalid date, enter date between 1 and 31 \n";
					cin.clear();
					cin.ignore();
				}
			}
			addIncident(newReportNum, newReportMonth, newReportDay);
			break;
		case 3:
			cout << "Select entry to remove: \n";
			cin >> removalPos;
			removeIncident(removalPos);
			break;
		case 4:
			cout << endl << findMonth(pIncidents, arrSizeIncident, monthNames, monthCounts, 
				incidentsInMaxMonth) << " had " << incidentsInMaxMonth << " incidents." <<
				endl;
			break;
		case 5: cout << "Returning..." << endl;
			exitMenu = true;
			return;
		default: cout << "Invalid choice, try again.";
		}
	}
}