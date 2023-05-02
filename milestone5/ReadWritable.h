/* Citation and Sources...
Final Project Milestone 1
Module: ReadWritable
Filename: ReadWritable.h
Version 1.0
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_READWRITABLE_H_
#define SDDS_READWRITABLE_H_
#include <iostream>
namespace sdds
{
	class ReadWritable
	{
		bool commaSeparated;

		//Constructor
	public:
		ReadWritable();
		virtual ~ReadWritable() = 0 {};

		bool isCsv()const;
		void setCsv(bool value);

		virtual std::ostream& write(std::ostream& os = std::cout)const =0;
		virtual std::istream& read(std::istream& in = std::cin) = 0;	
	};
	std::istream& operator>>(std::istream& in, ReadWritable& right);
	std::ostream& operator<<(std::ostream& os,const ReadWritable& right);
}
#endif // !SDDS_READWRITABLE_H_
