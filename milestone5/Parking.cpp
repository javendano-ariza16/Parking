#define _CRT_SECURE_NO_WARNINGS
#include"Parking.h"
#include"Menu.h"
#include<iostream>
#include <fstream>
#include<cstring>
#include"Car.h"
#include"Motorcycle.h"
/* Citation and Sources...
Final Project Milestone 1
Module: ReadWritable
Filename: Parking.cpp
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

namespace sdds
{
	Parking::Parking(const char* filename, int noSpotsFile) :
		filename(nullptr),
		subMenu1("Parking Menu, select an action:", 0),
		subMenu2("Select type of the vehicle:", 1)
	{
		/// ms5
		if (noSpotsFile >= 10 && noSpotsFile <= 100)
		{
			int i = 0;
			this->noSpots = noSpotsFile;
			for (i = 0; i < noSpotsFile; i++)
			{
				this->parkingSpots[i] = nullptr;
			}
			this->parkedVehicles = 0;
		}
		/// end ms5

		if (filename != nullptr && strlen(filename) > 0)
		{
			int lenght = strlen(filename);
			this->filename = new char[lenght + 1];
			strcpy(this->filename, filename);
			if (loadDataFile())
			{
				subMenu1 << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Find Vehicle" << "Close Parking (End of day)" << "Exit Program";
				subMenu2 << "Car" << "Motorcycle" << "Cancel";
			}
			else
			{
				std::cout << "Error in data file" << std::endl;
				setEmpty();
			}
		}
		else
		{
			setEmpty();
		}
	}
	Parking::~Parking()
	{
		saveDataFile();
		delete[] this->filename;
		this->filename = nullptr;
		for (int i = 0; i <this->noSpots; i++)
		{
			delete this->parkingSpots[i];
			this->parkingSpots[i] = nullptr;
		}

	};

	bool Parking::isEmpty()
	{
		return(this->filename == nullptr);
	};
	void Parking::parkingStatus()
	{
		//ms5
		int available = this->noSpots - this->parkedVehicles;
		std::cout << "****** Valet Parking ******" << std::endl;
		std::cout << "*****  Available spots: ";
		std::cout.setf(std::ios::left);
		std::cout.width(4);
		std::cout << available;
		std::cout.unsetf(std::ios::left);
		std::cout << " *****" << std::endl;
		// ms5
	}
	void Parking::parkVehicle()
	{
		if (this->noSpots == this->parkedVehicles)
		{
			std::cout << "Parking is full" << std::endl;
			this->enterButton();
		}
		else{
		bool ok = false;
		Vehicle* newVehicle = nullptr;
			while (!ok)
			{
				switch (subMenu2.run())
				{
				case 1:
					newVehicle = new Car();
					newVehicle->setCsv(false);
					newVehicle->read();
					ok = true;
					break;
				case 2:
					newVehicle = new Motorcycle();
					newVehicle->setCsv(false);
					newVehicle->read();
					ok = true;
					break;
				case 3:
					std::cout << "Parking cancelled" << std::endl;
					ok = true;
					break;
				};
			}
			bool  done = false;
			for (int i = 0; i < this->noSpots && done==false; i++)
			{
				if (this->parkingSpots[i] == nullptr) {
					this->parkingSpots[i] = newVehicle;
					this->parkingSpots[i]->setParkingSpot(i + 1);
					std::cout << std::endl << "Parking Ticket" << std::endl;
					this->parkingSpots[i]->write();
					done = true;
					std::cout << std::endl;
					this->parkedVehicles++;
				}
			}
			this->enterButton();
	    }
	}
	void Parking::returnVehicle()
	{
		char user[50];
		char ok = false;
		int lenght = 0;
		std::cout << "Return Vehicle" << std::endl << "Enter License Plate Number: ";
		do
		{
			std::cin >> user;
			std::cout << std::endl;
			lenght = strlen(user);
			if (lenght < 1 || lenght > 8)
			{
				std::cout << "Invalid License Plate, try again: ";
				std::cin.clear();
			}
		} while (lenght < 1 || lenght > 8);
		std::cin.ignore(1000, '\n');
		for (int j = 0; (j < (lenght + 1)); j++)
		{
			user[j] = toupper(user[j]); 
		}
		int i = 0;
		while (i < this->noSpots && ok == false)
		{
			if (this->parkingSpots[i] != nullptr) {
				if (*this->parkingSpots[i] == user)
				{
					std::cout << "Returning:" << std::endl;
					this->parkingSpots[i]->setCsv(false);
					this->parkingSpots[i]->write();

					std::cout << std::endl;
					delete this->parkingSpots[i];
					this->parkingSpots[i] = nullptr;
					this->enterButton();
					ok = true;
					this->parkedVehicles--;
				}
			}
			i++;
		}
		if (ok == false)
		{
			std::cout << "License plate " << user << " Not found" << std::endl << std::endl;
			this->enterButton();
		}

	};
	void Parking::listParked()
	{
		std::cout << "*** List of parked vehicles ***" << std::endl;
		for (int i = 0; i < this->noSpots; i++)
		{
			if (this->parkingSpots[i] != nullptr)
			{
				this->parkingSpots[i]->setCsv(false);
				this->parkingSpots[i]->write();
				std::cout << "-------------------------------" << std::endl;
			}
		}
		this->enterButton();
	};
	void Parking::findVehicle()
	{
		char user[50];
		bool ok = false;
		int lenght = 0;
		std::cout << "Vehicle Search" << std::endl;
		std::cout << "Enter License Plate Number: ";
		do
		{
			std::cin >> user;
			std::cout << std::endl;
			lenght = strlen(user);
			if (lenght < 1 || lenght > 8)
			{
				std::cout << "Invalid License Plate, try again: ";
				std::cin.clear();
			}
		} while (lenght < 1 || lenght > 8);
		std::cin.ignore(1000, '\n');

		for (int k = 0; k <= lenght; k++)
		{
			user[k] = toupper(user[k]);
		}
	
		int i = 0;
		while ( i < this->noSpots && ok==false)
		{
			if (this->parkingSpots[i] != nullptr) {
				if (*this->parkingSpots[i] == user)
				{
					std::cout << "Vehicle found:" << std::endl;
					this->parkingSpots[i]->setCsv(false);
					this->parkingSpots[i]->write();
					std::cout << std::endl;
					this->enterButton();
					ok = true;

				}
			}
			i++;
		}
		if (ok==false)
		{
			std::cout << "License plate " << user << " Not found" << std::endl << std::endl;
			this->enterButton();
		}
	};
	bool Parking::closeParking()
	{
		bool done = false;
		bool close = true;
		char userInput;
		if (parkedVehicles==0)
		{
			std::cout << "Closing Parking" << std::endl;
			done = true;

		}
		else {
			std::cout << "This will Remove and tow all remaining vehicles from the parking!" << std::endl;
			std::cout << "Are you sure? (Y)es/(N)o: ";
			while (!done)
			{
				std::cin >> userInput;
				if (userInput == 'Y' || userInput == 'y')
				{
					std::cout << "Closing Parking" << std::endl;
					for (int i = 0; i < this->noSpots; i++)
					{
						if (this->parkingSpots[i] != nullptr) {
							std::cout << std::endl << "Towing request" << std::endl;
							std::cout<< "*********************" << std::endl;
							this->parkingSpots[i]->setCsv(false);
							this->parkingSpots[i]->write();
							delete this->parkingSpots[i];
							this->parkingSpots[i] = nullptr;
						}
					}
					close = true;
					done = true;
				}
				else if (userInput == 'N' || userInput == 'n')
				{
					done = true;
					close = false;
				}
				else
				{
					std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				std::cin.clear();
			}
		}
		return close;
	};
	bool Parking::exitParking()
	{
		bool done = false;
		char userInput;
		std::cout << "This will terminate the program!" << std::endl;
		std::cout << "Are you sure? (Y)es/(N)o: ";
		while (!done)
		{
			std::cin >> userInput;
			if (userInput == 'Y' || userInput == 'y')
			{
				std::cout << "Exiting program!" << std::endl;
				done = true;
				return done;
			}
			else if (userInput == 'N' || userInput == 'n')
			{
				done = true;
				return false;
			}
			else
			{
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
		}
		return false;

	};
	bool Parking::loadDataFile()
	{
		//ms5
		bool flag = true;
		if (!isEmpty())
		{
			int i = 0;
			char type;
			std::ifstream filein(this->filename);
			if (!filein || isEmpty())
			{
				flag = true;
			}
			else
			{
				Vehicle* V =nullptr;
				do
				{
					filein >> type;
					filein.ignore();
					if (!filein)
					{
						break;
					}
					else if (type == 'M')
					{
						V = new Motorcycle;
						V->setCsv(true);
						V->read(filein);
						int index = (V->getParkingSpot() - 1);
						if (filein)
						{
							this->parkingSpots[index] = V;
							this->parkedVehicles++;
						}
						else
						{
							delete V;
							flag = true;
							break;
						}

					}
					else if (type == 'C')
					{
						V = new Car;
						V->setCsv(true);
						V->read(filein);
						int index = (V->getParkingSpot() - 1);
						if (filein)
						{
							this->parkingSpots[index] = V;
							this->parkedVehicles++;
						}
					}
					else
					{
						flag = false;
						V = nullptr;
					}
					i++;
				} while (filein);
			}
		}
		else
		{
			this->setEmpty();
			flag = true;
		}
		return flag;
		//end ms5
	}
	void Parking::setEmpty()
	{
		this->filename = nullptr;
	}
	void Parking::saveDataFile()
	{
		std::ofstream file;
		if (!this->isEmpty()) file.open(filename);

		if (file)
		{
			for (int i = 0; i < this->noSpots; i++)
			{
				if (this->parkingSpots[i] != nullptr) {
					this->parkingSpots[i]->setCsv(true);
					file << *this->parkingSpots[i];
				}
				else {}
			}
		}
		file.close();
	}
	void Parking::enterButton() {
		std::string input = "";
		do {
			std::cout << "Press <ENTER> to continue....";
			std::getline(std::cin, input);
		} while (input.length() != 0);
		std::cin.clear();
	}

	int Parking::run()
	{
		if (!isEmpty())
		{
			bool done = false;
			while (!done)
			{
				this->parkingStatus();
				switch (subMenu1.run())
				{
				case 1:
					this->parkVehicle();
					break;
				case 2:
					this->returnVehicle();
					break;
				case 3:
					this->listParked();
					break;
				case 4:
					this->findVehicle();
					break;
				case 5:
					if (this->closeParking())
					{
						done = true;
					}
					break;
				case 6:
					if (this->exitParking())
					{
						done = true;
					}
					break;
				}
			}
			if (isEmpty())
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			std::cout << "Error in data file"<<std::endl;
			return 1;
		}
	}
}
