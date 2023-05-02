/* Citation and Sources...
Final Project Milestone 1
Module: ReadWritable
Filename: ReadWritable.cpp
Version 1.0
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include "ReadWritable.h"
#include<fstream>
namespace sdds
{

	ReadWritable::ReadWritable()
	{
		this->commaSeparated = false;
	}
	bool ReadWritable::isCsv()const{return this->commaSeparated;};
	void ReadWritable::setCsv(bool value)
	{
		this->commaSeparated = value;
	};
	std::ostream& operator<<(std::ostream& os, const ReadWritable& right)
	{
		return right.write(os);
	};
	std::istream& operator>>(std::istream& in, ReadWritable& right)
	{
		return right.read(in);
	};
}

