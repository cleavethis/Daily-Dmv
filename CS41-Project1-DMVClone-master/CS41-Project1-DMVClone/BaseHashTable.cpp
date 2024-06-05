#include "BaseHashTable.h"

BaseHashTable::BaseHashTable(int size) : size(size) {
	for (size_t i = 0; i < size; i++) {
		hTable[i] = "";
	}
}

int BaseHashTable::hashKey(const string& key) {
	int hash = 0;
	for (char c : key) {
		hash = (hash * 29 + c) % size;
	}
	return hash;
}

void BaseHashTable::insert(const string& key, const string& value) {
	int index = hashKey(key);
	hTable[index] = value;
}

string BaseHashTable::get(const string& key) {
	int index = hashKey(key);
	return hTable[index];
}