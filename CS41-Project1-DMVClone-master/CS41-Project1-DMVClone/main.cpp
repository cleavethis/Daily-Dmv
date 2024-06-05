#include "VehicleList.h"
#include "IncidentList.h"
#include "ApptQueue.h"
#include "QueueLinkedList.h"
#include "Driver.h"
#include "HashTable.h"
#include "ProcessingTimes.h"
#include <iostream>
#include <iomanip>	
#include <fstream>
/*----Rick Richmond CSCI 41 Project----
	This program is deisnged to store two sets of data; one for cars and one for drivers. The basic functionality is 
	to allow users to see how these data connect. For example, a user should be able to input a partial license plate 
	and get a list of matches. These matches will have detailed attribues about the cars, AND the drivers. Likewise if the user
	has some information about a person, they should be able to see information about their vehcile. I plan to have at least
	two classes and connect them using the data structers we learn about over the course.

	PROJECT 1: I started with the requirements for project 1 and tried to focus my effort on a simple file of 
			   vehicles with a make and a model I should be able to do something very similar with the 
			   "driver" class. I wanted to turn in what I have now, and continue building on the project as
			   the semester goes on.
			   
	PROJECT 2: Very similar to project 1, but now instead of having an array of strings, I implemented an array of
			   Structs. I created a class that stores incident reports. Holding a 2 strings and 1 integer. The array
			   of structs is dynamic just as the array from project 1. The same functionality exists, and I added the
			   option to calculate and display which month had the most incident reports.*/

/* PROJECT 3: Implemented a search and sort algorithm into the project 1 data set. I used selection 
			  sort providing ascending and descending options. My search process implements a function
			  to check if the search term is a partial string of the existing data, and then returns 
			  all resutls that conaint that partial string. I validate this data by asking user for 
			  at least 3 characters to get relevant output. My search algorithm is a linear search, 
			  checking the data against the partial string in order. This is O(n) complexity. I also 
			  report the time of each algorithm.	
   
   PROJECT 4: I thought about where a linked list makes the most sense in my project, and decided
			  that the data related to drivers would be my best bet. This allows users to continually
			  add or remove drivers as this set of data is one that should be expected to change constantly.
			  By using a linked list a DMV database/program would be dynamic and act according
			  to the needs of different counties in California. With 27 million drivers in CA 
			  (according to a quick google search) a dynamic data structure is practially a requirement.
			  
   PROJECT 5: I choose to create a queue for my DMV project. The dmv appointment system
			  uses a first in first out structure for dealing with appointments. You make
			  an appointment and are typically served in the order recieved. I implemented a queue
			  using a linked list, because the append function is perfect for enqueing nodes, and
			  the removeAfter() function is good for addressing the dequeue. Currently I have a simple
			  implementatoin that accepts a name and a number. In the future I hope to also accept a short
			  description so the data would look something like: Rick, #34, Renew registratrion.

	PROJECT 6: Project 6 is where the initial idea of my project is finally realized. I create a hash table
			   and read in driver/vehicle data. This data is then hashed and stored in the array. I decided
			   to use chaining as my solution for collisoins. This solution is a better option than linear probing
			   as I am dealing with a table of size 8 for project requirements. In a real setting this table would 
			   be larger. The class supports functionality for adding, removing, and searching. The user searches by
			   driver's license number (as this is a unique key as opposed to a name) and is returned the name of 
			   the driver and make, model, and plate number of their registered vehicle. 
			  
			  
			  
			  */



int main() {
	
	int choice;
	bool exitMenu = false;
	// Project 1 and 3 object
	VehicleList cars2("cars.txt");
	if (!cars2.isOpen())
	{
		return 1;
	}
	// Project 2 object
	IncidentList reportest("2023Incidents.txt");
	if (!reportest.isOpen())
	{
		return 2;
	}
	// Project 4 object
	DriverLL driverList("Drivers.txt");
	// Project 5 object
	ApptQueue newQueue;
	// Project 6 object
	HashTable newTable;
	newTable.loadData("Drivers_and_Vehics.txt");
	// Project 7 object
	ProcessingTimes newTimes(400, "appt_times.txt");
	
	while (!exitMenu) {
		cout << "\nMain Menu: \n";
		cout << "1. Vehicles (project 1 and 3)\n";
		cout << "2. Incidents (project 2)\n";
		cout << "3. Drivers (project 4)\n";
		cout << "4. Appointment services (project 5) \n";
		cout << "5. Drivers and registered vehicles (project 6) \n";
		cout << "6. Appointment time data analysis (project 7) \n";
		cout << "7. End program\n";
		cin >> choice;
		switch (choice) {
		case 1: cars2.menu();
			break;
		case 2: reportest.menu();
			break;
		case 3: driverList.menu();
			break;
		case 4: newQueue.menu();
			break;
		case 5: newTable.menu();
			break;
		case 6: newTimes.menu();
			break;
		case 7: cout << "Exiting main directory menu\n";
			exitMenu = true;
			break;
		default: cout << "Invalid selection, try again.\n";
		}
	}
	return 0;
}