#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Driver.h"
using namespace std;

struct VehicleData {
	string make, model, plateNum;
};

struct DriverNode {
	string dlNum, fName, lName;
	VehicleData vehicleData;
	DriverNode* nextptr;
};

class HashTable
{
protected:
	int size;
private: 
	static const int TABLE_SIZE = 8;
	DriverNode* hTable[TABLE_SIZE]; 
	int hashDlNum(const string&);
public:
	HashTable();
	~HashTable();
	void insert(const string&, const string&, const string&, const VehicleData&);
	void search(const string&);
	bool remove(const string&);
	void loadData(const string&);
	void saveData(const string&);
	void menu();
	void displayTable() const;
};

