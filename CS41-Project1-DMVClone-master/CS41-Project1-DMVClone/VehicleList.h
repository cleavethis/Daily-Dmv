#ifndef VEHICLELIST_H
#define VEHICLELIST_H
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
/*
	Rick Richmond--This class is for handling all of the file processing done by the program and the user. 
	See the function defintions in the implementation file for more info
*/
class VehicleList
{
private:
	ifstream vFile;
	int arrSizeVehicle, currArrSize, startTime, endTime, elapsedTime;
	string* pVehicles;
	string  oFileName = "cars.txt", searchTerm;
	void resizeArr();
	void swap(string* pVehicles, int a, int b);
	void saveToFile(const string&, const string*, int);

public: 
	VehicleList(const string& filename);
	~VehicleList();
	bool isOpen() const;
	void displayList() const;
	void menu();
	void addVehicle(const string& newVehicleEntry);
	void removeVehicle(int vPosition);
	void exitProgram();
	bool hasPartialString(const string&, const string&);
	void partialStringSearch(const string*, int, const string&);
	void selectionSortAscending(string* pVehicles, int arrSizeVehicle); 
	void selectionSortDescending(string* pVehicles, int arrSizeVehicle);
	bool isSorted(); // Check if list is sorted before calling search
};
#endif

