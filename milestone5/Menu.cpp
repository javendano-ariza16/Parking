#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include "Menu.h"
#include<fstream>
/* Citation and Sources...
Final Project Milestone 1
Module: ReadWritable
Filename: Menu.cpp
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/

namespace sdds
{
	//MenItem Class
	MenuItem::MenuItem(char str[])
	{
		if (str[0] == '\0')
		{
			this->setEmpty();
		}
		else
		{
			strcpy(this->description, str);
		}
	}
	void MenuItem::setEmpty()
	{ 
		for (size_t i = 0; i < strlen(this->description); i++)
		{
			this->description[i] = '\0';
		}

	}
	bool MenuItem::isEmpty() const
	{
		return this->description[0] == '\0';
	}
	std::ostream& MenuItem::display(std::ostream& ostr=std::cout) const
	{	
		if (!(this->isEmpty()))
		{
			ostr << this->description << std::endl;
		}
		else
		{
			return ostr;
		}
		return ostr;
	};


	//Menu Class
	Menu::Menu(const char t_given[], int i_given  )
	{
		if (!(t_given [0] == '\0'))
		{
			this->indention = i_given;
			strcpy(this->tittle, t_given);
			this->no_items = 0;
		}
		else
		{
			this->clear();
		}
	}
	Menu::operator bool()const
	{
		return !(this->isEmpty());
	};
	bool Menu::isEmpty () const
	{
		return (this->tittle[0] == '\0');
	}
	std::ostream& Menu::display(std::ostream& ostr ) const
	{
		if (isEmpty())
			ostr << "Invalid Menu!" << std::endl;
		else if (this->items[0].isEmpty())
		{
			//int noSpaces = indention * 4;
			ostr << this->tittle << std::endl;
			ostr << "No Items to display!" << std::endl;
		}else
		{
			int noSpaces = indention * 4;
			int j;
			int i;
			int a;
			for (j = 0; j < noSpaces; j++)
			{
				ostr << " ";
			}
				ostr << this->tittle<<std::endl;
			for ( i = 0; (i < this->no_items) && !(this->items[i].isEmpty()); i++)
			{
				int k;
				for (k = 0; k < noSpaces; k++)
				{ostr << " ";}
				ostr << i + 1 << "- ";  this->items[i].display();
			}
			for ( a = 0; a < noSpaces; a++)
			{
				ostr << " ";
			}
			ostr << "> ";
		}
		return ostr;
	};
	Menu& Menu::operator=(const char right[])
	{
		if (!(right[0] == '\0'))
		{
			strcpy(this->tittle, right);
		}
		else
		{
			this->clear();
		}
		return *this;
	};
	//Do you have left the assigment of the newitem
	void Menu::add(const char newItem[51])
	{
		if (newItem == NULL)
		{
			this->clear();
			return;
		}
		else
		{
			if (this->no_items < MAX_NO_OF_ITEMS && !(this->isEmpty()))
			{
				strcpy(this->items[no_items].description, newItem);
				this->no_items++;
			}
		}
	}
	Menu& Menu::operator << (const char right[51])
	{
		this->add(right);
		return *this;
	};
	int Menu::run() const
	{
		int userInput=0;
		this->display();
		bool validInt = false;
		if (!(this->items[0].isEmpty()))
		{
			while (validInt == false)
			{
				std::cin >> userInput;
				if (!std::cin)
				{
					std::cout << "Invalid Integer, try again: ";
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					validInt = false;

				}
				else if (userInput <= 0 || userInput > (this->no_items))
				{
					std::cout << "Invalid selection, try again: ";
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					validInt = false;
				}
				else
				{
					std::cin.ignore(1000, '\n');
					validInt = true;
				}
			}
		}
		return userInput;
	}
	Menu::operator int() const
	{
		return this->run();
	}
	Menu& Menu::clear()
	{
		for (size_t i = 0; i < this->no_items; i++)
		{
			this->items[i].setEmpty();
		}
		this->items[0].description[0] = '\0';
		this->indention = 0; 
		this->no_items = 0;
		*this->tittle = '\0';
		return *this;
	};


	
}
