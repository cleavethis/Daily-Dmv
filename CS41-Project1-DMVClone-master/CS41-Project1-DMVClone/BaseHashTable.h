#pragma once
#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 500;
class BaseHashTable
{
protected: 
	int size;
	string hTable[MAX_SIZE];
public:
	BaseHashTable(int);
	virtual int hashKey(const string&);
	virtual void insert(const string&, const string&);
	virtual string get(const string&);

};

