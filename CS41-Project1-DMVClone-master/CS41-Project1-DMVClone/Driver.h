#ifndef DRIVER_H
#define DRIVER_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
// Base class for drivers. May include derived class.

class DriverLL
{
private:
	/* string addressNum, addressName, addressState, zipcode, licenseExpiration, driverHeight, driverWeight,
		   firstName, lastName, driverDOB, issueDate, driverHair, driverEyes; 
	char licenseClass, driverSex; */
	ifstream driversFile;
	struct Node {
		string firstName, lastName, licenseNum;
		Node* nextPtr;
	};
	Node* listHead;
	
public:
	DriverLL(const string& filename);
	void appendNode(string, string, string);
	void deleteNode(string);
	void displayDriverList() const;
	void insertNode(string, string, string);
	DriverLL* getNext();
	bool isOpen() const;
	void menu();
	void searchDrivers(const string& licenseSearch);
	// Changed these to static to allow access by other classes without instantiating a DriverLL object
	static bool isValidDLNumber(const string&);
	static bool isValidName(const string&);
	static bool isValidPlateNum(const string&);

};
#endif