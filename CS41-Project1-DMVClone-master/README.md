My plan for project 1 is to add four basic functions to the Vehicle class that I could then copy and implement into the
driver class later. Since we are required to read in at least 20 entries my strategy is to have a member function open the file
and then use getline to cound the number of entries into the file. For example if the file has 30 entries i will have a varaible store this value. After calculating the number of elements in the file I can then dynamically allocate an array of that size at runtime something like the following point* vehcilePointer = new vArr[computedSize]. This would change the size of the array depending on the size of the input file. The other three funcitons should allow for addition and removal of elements, and finally a funciton that will display the elements of the array.

Project 1: see comments in main.cpp for effort on Project 1.
