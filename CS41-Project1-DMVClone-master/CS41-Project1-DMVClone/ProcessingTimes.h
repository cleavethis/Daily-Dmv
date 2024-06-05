#pragma once
#include <string>
#include "BaseHashTable.h"
using namespace std;

const string FILENAME = "appt_times.txt";
class ProcessingTimes : public BaseHashTable
{
private: 
	struct Appointment {
		string key;
		unsigned int value;
		bool filled;
		Appointment() : key(""), value(0), filled(false) {}
	};
	
	Appointment hTable[MAX_SIZE];
	int hashKey(const string&) override;
	int doubleHash(const string&);
	string createKey(const string&);
	   
	  
	   
public:
	ProcessingTimes(int, const string&);
	void insert(const string&, const int&);
	void remove(const string& key);
	int getProcessingTime(const string&);
	double getAverageTimes() const;
	double getAverageTimesByType(const string&) const;
	void displayAverageTimesByType(const string&, const string&) const;
	void displayApptTypeMenu() const;
	pair<string,int> getLongestType() const;
	void menu();
	void insertWithType(const string&, int);
	void displayTable() const;
	string getPrefix(const string&) const;
	void addAppt();
	void saveData(const string&);
};




