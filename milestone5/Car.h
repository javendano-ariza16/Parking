#ifndef SDDS_CAR_H_
#define SDDS_CAR_H_
#include "Vehicle.h"
#include "Utils.h"
#include "ReadWritable.h"

namespace sdds
{
	class Car :public Vehicle
	{
		bool carwash =false;
	public:
		Car();
		Car(const char* plate, const char* model);
		//Rule of three
		Car(Car&);	
		Car& operator=(Car&);
		~Car();
		std::ostream& writeType(std::ostream& os = std::cout) const;
		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& os = std::cout) const;
	};
}
#endif // !SDDS_CAR_H_
