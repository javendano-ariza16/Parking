#define _CRT_SECURE_NO_WARNINGS
#include "Motorcycle.h"
/* Citation and Sources...
Final Project Milestone 1
Module: ReadWritable
Filename: Motorcycle.cpp
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
namespace sdds
{
	Motorcycle::Motorcycle()
	{
		Vehicle::setEmpty();
		this->sidecar = false;
	}
	Motorcycle::Motorcycle(const char* plate, const char* model) :Vehicle(plate, model)
	{
		this->sidecar = false;
		if (plate != nullptr || plate[0] != '\0' || model != nullptr || model[0] != '\0')
		{
			Vehicle::setEmpty();
		}
	};
	Motorcycle::Motorcycle(Motorcycle& right)
	{
		*this = right;
	}
	Motorcycle& Motorcycle::operator=(Motorcycle& right)
	{
		Vehicle::operator=(right);
		this->sidecar = right.sidecar;
		return *this;
	};
	Motorcycle::~Motorcycle()
	{
		sidecar = false;
	}
	std::ostream& Motorcycle::writeType(std::ostream& os) const
	{
		if (isCsv())
		{
			os << "M,";
		}
		else
		{
			os << "Vehicle type: Motorcycle" << std::endl;
		}
		return os;
	}
	std::istream& Motorcycle::read(std::istream& is)
	{
		if (isCsv())
		{
			Vehicle::read(is);
			is >> this->sidecar;
			is.ignore(1000, '\n');
		}
		else
		{
			char temp[4]{};
			std::cout <<std::endl<< "Motorcycle information entry"<< std::endl;
			Vehicle::read();
			std::cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			is.get(temp, 4, '\n');
			is.ignore(1000, '\n');
			while (strnlen(temp, 3) > 2 || ((temp[0] != 'y' && temp[0] != 'n')))
			{
				std::cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				is.get(temp, 3, '\n');
				is.ignore(1000, '\n');
			}
			if (temp[0] == 'y')
			{
				this->sidecar = true;
			}
			else if (temp[0] == 'n')
			{
				this->sidecar = false;
			}
		}
		return is;
	}
	std::ostream& Motorcycle::write(std::ostream& os) const
	{
		if (Vehicle::isEmpty())
		{
			os << "Invalid Motorcycle Object" << std::endl;
		}
		else
		{
			Vehicle::write(os);
			if (isCsv())
			{
				os << this->sidecar<<std::endl;
			}
			else
			{
				if (this->sidecar == true)
				{
					os << "With Sidecar" << std::endl;
				}
			}
		}
		return os;
	};
}
