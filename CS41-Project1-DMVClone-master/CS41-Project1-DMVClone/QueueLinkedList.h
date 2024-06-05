#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
/* I decided to implement this basic linked list for use with my queue. I may revise my 
   drivers class in the future to use this as well. I kept the funcitons definitions confined
   to this header file as they are fairly short and straightforward. */
class Node {
public:
	string apptName, apptNum;
	Node* next;
	Node(const string& name, const string& num) {
		apptName = name;
		apptNum = num;
		next = nullptr;

	}
private:
	
};

class LinkedList {
private:
	ifstream apptFile;
	Node* head;
	Node* tail;
	
public:
	LinkedList(const string&);
	Node* getHead() {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	virtual ~LinkedList();
	void append(Node*);
	void prepend(Node*);
	void removeAfter(Node*);
	void print(ostream&, const string&);
	bool isEmpty() const;
	string getHeadData();
};
#endif
