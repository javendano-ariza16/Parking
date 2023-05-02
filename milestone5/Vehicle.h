#ifndef SDDS_VEHICLE_H__
#define SDDS_VEHICLE_H__

#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include "ReadWritable.h"

namespace sdds
{
    const int MAX_PLATE = 8;
    const int MAX_READ_CHAR = 60;
    class Vehicle : public ReadWritable
    {
        char licensePlate[MAX_PLATE + 1];
        char* makeAndModel;
        int parkingNumber;
    protected:

        void setEmpty();
        bool isEmpty() const;
        const char* getLicensePlate() const;
        const char* getMakeModel() const;
    public:
        Vehicle();
        Vehicle(const char*, const char*);
        ~Vehicle();
        Vehicle(const Vehicle&);
        Vehicle& operator=(const Vehicle&);
        int getParkingSpot() const;
        void setMakeModel(const char*);
        void setParkingSpot(int );
        bool operator==(const char*) const;
        bool operator==(const Vehicle&) const;
        std::istream &read(std::istream& is = std::cin);
        std::ostream &write(std::ostream& os = std::cout) const;
        virtual std::ostream &writeType(std::ostream& os = std::cout) const = 0;
    };
}

#endif