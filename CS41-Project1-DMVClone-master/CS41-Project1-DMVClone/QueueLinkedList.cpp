#include "QueueLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

LinkedList::LinkedList(const string& filename) : apptFile(filename) {
	head = nullptr;
	tail = nullptr;

	if (!apptFile.is_open()) {
		cout << "Error opening Drivers file.\n";
	}
	
	string apptName, apptNum;

	while (apptFile >> apptName >> apptNum) {
		Node* newNode = new Node(apptName, apptNum);
		append(newNode);
	}

	apptFile.close();
}
	


LinkedList::~LinkedList() {
	Node* curNode = head;
	while (curNode) {
		Node* next = curNode->next;
		delete curNode;
		curNode = next;
	}
	head = tail = nullptr;
}

void LinkedList::append(Node* newNode) {
	if (!newNode) {
		return;
	}

	if (!head) {
		head = newNode;
		tail = newNode;
	}

	else {
		tail->next = newNode;
		tail = newNode;
	}
}

void LinkedList::prepend(Node* newNode) {
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}

void LinkedList::removeAfter(Node* currNode) {
	if (currNode == nullptr && head) {
		// Removes head
		Node* nodeToRemove = head;
		head = head->next;
		delete nodeToRemove;

		if (head == nullptr) {
			// Last item was removed
			tail = nullptr;
		}
	}
	else if (currNode->next) {
		Node* nodeToRemove = currNode->next;
		Node* succNode = currNode->next->next;
		currNode->next = succNode;
		delete nodeToRemove;
		if (succNode == nullptr) {
			// Remove tail
			tail = currNode;
		}
	}
}

void LinkedList::print(ostream& print, const std::string& sep) {
	Node* node = head;
	while (node) {
		
	print << node->apptName << " " << node->apptNum << sep;
		node = node->next;
	}
	print << endl;
}

string LinkedList::getHeadData() {
	return head->apptName + " " + head->apptNum;
}

bool LinkedList::isEmpty() const {
	if (head)
		return false;
	else
		return true;
}
