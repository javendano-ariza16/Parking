/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Parking.h
Version 1.0
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_PARKING_H
#define SDDS_PARKING_H
#include<iostream>
#include "Menu.h"
#include "Vehicle.h"
#define	MAX_NO_SPOTS 100
namespace sdds
{
	class Parking
	{
		char* filename;
		Menu subMenu1;
		Menu subMenu2;
		int noSpots;
		Vehicle* parkingSpots[MAX_NO_OF_ITEMS];
		int parkedVehicles;
		bool isEmpty();
		void parkingStatus();
		void parkVehicle();
		bool loadDataFile();
		void setEmpty();
		void saveDataFile();
		void returnVehicle();
		void listParked();
		void findVehicle();
		bool closeParking();
		bool exitParking();

	public:
		Parking(const char* filename, int noOfSpots);
		~Parking();
		void enterButton();
		Parking(Parking&) = delete;
		void operator=(Parking&) = delete;
		int run();
	};
}

#endif 
