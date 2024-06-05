#ifndef INCIDENTLIST_H
#define INCIDENTLIST_H
#include <iostream>
#include <string>
#include <fstream>
#include "VehicleList.h"
using namespace std;
/*Project 2 -- I thought I would make this class a derived class of VehicleList as they share similar functionality, but I decided
against it as there were slight differences in almost every funciton due to this class using a struct instead of a sinlge string variable, so I 
didn't see where this class could use a funciton from a parent class in a logical way*/

class IncidentList{

private: 
	static const int NUM_MONTHS = 12;
	string monthNames[NUM_MONTHS] = { "January", "February", "March", "April", "May", "June", "July",
									 "August", "September", "October", "November", "December" };
	int monthCounts[NUM_MONTHS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ifstream incidentFile;
	int arrSizeIncident, maxArrSizeIncident, incidentsInMaxMonth;
	string oFilename = "2023Incidents.txt";
	void resizeArr();
	bool isValidDate = false;
	struct Incidents {
		string	incidentNum;
		string incidentMonth;
		short unsigned int incidentDay;
	};
	Incidents* pIncidents;
	
public:
	IncidentList(const string& filename);
	~IncidentList();
	void displayIncidentList() const;
	bool isOpen() const;
	void addIncident(const string& newincidentNum, const string& newincidentMonth, 
					 const int& newincidentDay);
	void removeIncident(int incidentPos);
	void menu();
	string findMonth(Incidents reports[], int arrSizeIncident, string monthNames[], 
					int monthCounts[], int& incidentsInMaxMonth);
	bool isValidMonth(string[], string);
};
#endif 

