#ifndef SDDS_MOTORCYCLE_H_
#define SDDS_MOTORCYCLE_H_
#include "Vehicle.h"
#include "Utils.h"
#include "ReadWritable.h"

namespace sdds
{
	class Motorcycle :public Vehicle
	{
		bool sidecar = false;
	public:
		Motorcycle();
		Motorcycle(const char* plate, const char* model);
		//Rule of three
		Motorcycle(Motorcycle&);
		Motorcycle& operator=(Motorcycle&);
		~Motorcycle();
		std::ostream& writeType(std::ostream& os = std::cout) const;
		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout) const;
	};
}
#endif