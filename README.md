[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/QZ1A8AJz)


--PROJECT 1--

Implemented a class to handle import of vehicles, currently make and model only. User can view, add, and remove entries to list. Class imports the contents of a file into a dynamically alocated array, then resizes itself to allow entries. 

Commit comments that I made during development while pushing commites to my private repository:

loadVehicles Function is getting file contents into dynamic array.

Updated VehicleList.cpp with a better methodology. Added destructor and deallocation. Added simple member function to display list of cars.

Added a basic function for adding an item to the array. implemented a resize array function to handle resized the array when needed.

Added menu and more documentation. Project 1 should be ready to turn in

--PROJECT 2-- 

Copying Repository from Project 1 into Project 2 This is not my project 2 submission, just a place to

make changes and push commits to Project 2 code. Please see https://github.com/Reedley-College-CSCI/csci-41-spring-course-project-1-rick-r/commits/main/ for a few commits made before

copying these files. Future commits should be done in this (project-2) repository.

I created a struct called Incidents that consists of a report number with the code being MMDDYY + R + report Number. For example if the 3rd report of the year was on Jan 17 the report number would be 011724R03. 
The struct also has a data member for a month, and a day. The report number and month are both stored as strings, and the day as an integer, fufilling the requirements for the project. 
There is more functionality that this program would have in a real life scenario, for example I would have like the report number to be generated dynamically depending on the input of the user. 

After the struct I implemented a way for the data to be read in from a file and rezised the array if needed, this also allows the user to see the data by calling a display function. I spent a lot of time working on 
the add and removed entries, as I tried to use a similar apporach to what I did for project 1, but accessing struct data members proved to be more challening than adding a single string to a line. The addition/deletions
are reflected in the file during runtime as the user changes data. 

My next function was getting some meaningful calculation done, and I decided to report the month with the most incidents as well as the amount of incidents. I did this by comparing my struct month data members to a hardcoded
array of strings (the 12 months) I then incremented the apporiate position within the month array, which would result in index 1-11 having the highest number. This index would represent the month month 3 being March for example.
I then output one of the 12 months from the array using the returned index as the index in the month array. 

This is a basic implemenation of the the requirements from project 2, users can view, add, and remove incident reports, as well as get a summary of which month had the most incidents.

--PROJECT 3--

My initial plan is to add selectionSort and binarySearch functions to the VehicleList class allowing for users to searh for any term involving make or model. I then want users to be able to search for all Makes and see the relevant models. 
I want to implement a way for users to search data for related data, such as seeing who a particular vehicle is registered to, but I'm starting with simple implementaiton of the algorithms to meet the project requirements. 

See VehilceList.cpp and VehicleList.h for implmenation for asc/des sort using selection sort. You can access this new functinality through the Vehicle menu. My current plan for the search is to allow the user to search for a make 
of a vehicle and then I want to return all results for that make for example, searching "Chevy" should return all entires that start with "Chevy" such that the output is "Chevy Camaro" "Chevy Trax" "Chevy Suburban" and so forth. This is 
I will meet the requirements for this project. My goal for the final version is to allow users to search either by name of person or license plate data and return a result that shows all the details of Vehicle X and registered driver Y, 
I think the first step toward accomplising this will be in the hash table project.

See VehicleList.cpp and VehicleList.h for implementation of searching algorithim. I have succesfully implemented 2 functions in order to search using a partial string. See VehiclieList.cpp lines 105 - 174 for project requirements. Likewise you can find the function calls in the menu in VehicleList.cpp lines 218, 230, and 247. VehicleList.cpp lines function calls on lines 157 & 171 will save changes to the file. Elapsed time is reported 
after any search or sort on lines 220, 223, 224, and 227 for ascending sort, 232, 235, 236, and 239 for descending sort, and finally for searching on lines 250, 253-255.

--PROJECT 4--

I decided to implement my linked list for my data regarding drivers. I chose to keep the data related to drivers limited for the time being, as to not overwhelm myself with more work. I have functions for appending, deleting, searching, and populating the linked list with data from a file. Currenlty the linked list has data for First name, last name, and license number. When searching you can search for a Driver's License number and see the related data if it exists. This is currently case sensitive and doesn't support partial searches. I hope to implment those features later if I have the time. You can display the list to see some sample license numbers to use for testing the search function.

--Project 5--

I choose a queue for my DMV program. You can access the functions through the main menu under appointment system. This allows enqueing, dequeuing, and printing the queue.
All changes should be saved to a file that is read in at runtime. I implemented the queue using a linked list. Project 5 code resides in: ApptQueue.h/ApptQueue.cpp and QueueLinkedList.h/QueueLinkedList.cpp. I chose to break this into multiple classes for ease of readability and for supporting future projects.

