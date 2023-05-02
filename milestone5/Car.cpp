#define _CRT_SECURE_NO_WARNINGS
#include "Car.h"
/* Citation and Sources...
Final Project Milestone 1
Module: ReadWritable
Filename: Car.cpp
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
namespace sdds
{
	Car::Car()
	{
		Vehicle::setEmpty();
		this->carwash = false;
	}
	Car::Car(const char* plate, const char* model):Vehicle(plate, model)
	{
		this->carwash = false;
		if (plate != nullptr || plate[0] != '\0' || model != nullptr || model[0] != '\0')
		{
			Vehicle::setEmpty();
		}
	};
	Car::Car(Car& right)
	{
		*this = right;
	}
	Car& Car::operator=(Car& right)
	{
		Vehicle::operator=(right);
		this->carwash = right.carwash;
		return *this;
	};
	Car::~Car()
	{
		carwash = false;
	}
	std::ostream& Car::writeType(std::ostream& os) const
	{
		if (isCsv())
		{
			os << "C,";
		}
		else
		{
			os << "Vehicle type: Car" << std::endl;
		}
		return os;
	}
	std::istream& Car::read(std::istream& is)
	{
		if (!(isCsv()))
		{
			std::cout << std::endl << "Car information entry"<<std::endl;
			char temp[4]{};
			Vehicle::read(is);
			std::cout << "Carwash while parked? (Y)es/(N)o: ";
			is.get(temp, 4, '\n');
			is.ignore(1000, '\n');
			while (strnlen(temp, 3) > 2 || ((temp[0] != 'y' && temp[0] != 'n')))
			{
			std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			is.get(temp, 3, '\n');
			is.ignore(1000, '\n');
			}
			if (temp[0]=='y')
			{
				this->carwash = true;
			}
			else if (temp[0] == 'n')
			{
				this->carwash = false;
			}
		}
		else
		{
			Vehicle::read(is);
			is >> this->carwash;
			is.ignore(1000, '\n');

		}
		return is;
	}
	std::ostream& Car::write(std::ostream& os) const
	{
		if (Vehicle::isEmpty())
		{
			os << "Invalid Car Object" << std::endl;
		}
		else
		{
			Vehicle::write(os);
			if (isCsv())
			{
				os << this->carwash<<std::endl;
			}
			else
			{
				if (this->carwash == true)
				{
					os << "With Carwash"<<std::endl;
				}
				else os << "Without Carwash"<<std::endl;
			}
		}
		return os;
	};
}
