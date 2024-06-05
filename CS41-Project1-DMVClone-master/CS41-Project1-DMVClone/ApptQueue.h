#ifndef APPTQUEUE_H
#define APPTQUEUE_H
#include "QueueLinkedList.h"
#include <iostream>
#include <fstream>

using namespace std;
/* My queue implmentation was to design a simple appointment system, using a first in
   first out priority. This makes sense for any service provider that doens't consider
   priority of customers, just serving them on a first come first served basis.*/
class ApptQueue {
private:
	LinkedList linkedList;
	string oFileName = "appointments.txt";
	
public:
	ApptQueue();
	void enQueue(const string&, int);
	string dequeue();
	void displayQueue(ostream&);
	void saveEnqueue(const string&, Node*);
	void saveDequeue(const string&, LinkedList&);

	void menu();
		
};
#endif
