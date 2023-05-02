/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
Version 1.0
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include<iostream>
#define MAX_NO_OF_ITEMS 10

namespace sdds
{
	class MenuItem
	{
		//MEMBER DATA
		char description[51];
		friend class Menu;

		//Constructors
		MenuItem() = default;
		MenuItem(char []);
		MenuItem(MenuItem&) = delete;

		//Member functions
		bool isEmpty() const;
		void setEmpty();
		std::ostream& display(std::ostream&) const;

		//Member Operator
		void operator=(const MenuItem&) = delete;

	};


	class Menu
	{
	
		//MEMBER DATA
		char tittle[51];
		MenuItem items[MAX_NO_OF_ITEMS];
		int indention;
		int no_items = 0;


	public:

		//Constructors
		Menu() = default;
		Menu(const char t_given[], int i_given = 0);
		Menu(Menu&) = delete;

		//Member functions
		bool isEmpty() const;
		std::ostream& display(std::ostream& ostr = std::cout) const;
		void add(const char[51]);
		int run() const;
		Menu& clear();
		//Member Operator
		void operator=(const Menu&) = delete;
		operator bool()const;
		operator int() const;
		Menu& operator=(const char [51]);
		Menu& operator<<(const char[51]);

	};
}
#endif