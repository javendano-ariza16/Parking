
#define _CRT_SECURE_NO_WARNINGS
#include "Vehicle.h"
#include "ReadWritable.h"
/* Citation and Sources...
Final Project Milestone 1
Module: ReadWritable
Filename: Vehicle.cpp
Version 1.0
Author	Juan David Avendao
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
using namespace std;

namespace sdds
{
    Vehicle::Vehicle()
    {
        this->makeAndModel = nullptr;
        setEmpty();
    }

    Vehicle::Vehicle(const char* plate, const char* model)
    {
        this->makeAndModel = nullptr;
        setEmpty();
        if (plate != nullptr && plate[0] != '\0' && model != nullptr && model[0] != '\0')
        {
            if (strlen(plate) <= 8 && strlen(model) >= 2 && strlen(model) <= MAX_READ_CHAR)
            {


                strcpy(this->licensePlate, plate);
                this->makeAndModel = new char[strlen(model) + 1];
                strcpy(this->makeAndModel, model);
                this->parkingNumber = 0;
            }
            else
            {
                this->makeAndModel = nullptr;
                setEmpty();
            }
        }
    }

    Vehicle::~Vehicle()
    {
        delete[] this->makeAndModel;
        this->makeAndModel = nullptr;
    }

    Vehicle::Vehicle(const Vehicle& value)
    {
        this->makeAndModel = nullptr;
        setEmpty();
        *this = value;
    }

    void Vehicle::setEmpty()
    {
        this->licensePlate[0] = '\0';
        if (this->makeAndModel != nullptr)
        {
            delete[] this->makeAndModel;
            this->makeAndModel = nullptr;
        }
        this->parkingNumber = 0;
    }

    bool Vehicle::isEmpty() const
    {
        return (this->licensePlate[0] == '\0' && this->makeAndModel == nullptr && this->parkingNumber == 0);
    }

    Vehicle& Vehicle::operator=(const Vehicle& right)
    {
        if (this != &right)
        {
            if (this->makeAndModel != nullptr)
            {
                delete[] this->makeAndModel;
                this->makeAndModel = nullptr;
            }
            strcpy(this->licensePlate, right.licensePlate);
            if (right.makeAndModel != nullptr)
            {
                this->makeAndModel = new char[strlen(right.makeAndModel) + 1];
                strcpy(this->makeAndModel, right.makeAndModel);
            }
            this->parkingNumber = right.parkingNumber;
            this->setCsv(right.isCsv());
        }
        return *this;
    }

    const char* Vehicle::getLicensePlate() const
    {
        return this->licensePlate;
    }

    const char* Vehicle::getMakeModel() const
    {
        return this->makeAndModel;
    }

    void Vehicle::setMakeModel(const char* model)
    {
        if (model != nullptr && model[0] != '\0')
        {
            if (this->makeAndModel != nullptr)
            {
                delete[] this->makeAndModel;
                this->makeAndModel = nullptr;
            }
            this->makeAndModel = new char[strlen(model) + 1];
            strcpy(this->makeAndModel, model);
        }
    }

    int Vehicle::getParkingSpot() const
    {
        return this->parkingNumber;
    }

    void Vehicle::setParkingSpot(int spot)
    {
        if (spot > 0)
        {
            this->parkingNumber = spot;
        }
        else
        {
            setEmpty();
        }
    }

    bool Vehicle::operator==(const char* licensePlate) const
    {
        if (licensePlate != nullptr && licensePlate[0] != '\0' && this->licensePlate != nullptr && this->licensePlate[0] != '\0')
        {
            char* tempUpper = new char[strlen(licensePlate) + 1];
            strcpy(tempUpper, licensePlate);
            for (int i = 0; tempUpper[i] != '\0'; i++)
            {
                tempUpper[i] = toupper(tempUpper[i]);
            }
            char* temp = new char[strlen(this->licensePlate) + 1];
            strcpy(temp, this->licensePlate);
            for (int i = 0; temp[i] != '\0'; i++)
            {
                temp[i] = toupper(temp[i]);
            }
            bool result = strcmp(tempUpper, temp) == 0;
            delete[] tempUpper;
            delete[] temp;
            return result;
        }
        return false;
    }

    bool Vehicle::operator==(const Vehicle& right) const
    {
        if (right.licensePlate != nullptr && right.licensePlate[0] != '\0' && this->licensePlate != nullptr && this->licensePlate[0] != '\0')
        {
            char* temp = new char[strlen(right.licensePlate) + 1];
            strcpy(temp, right.licensePlate);
            for (int i = 0; temp[i] != '\0'; i++)
            {
                temp[i] = toupper(temp[i]);
            }
            char *temp2 = new char[strlen(this->licensePlate) + 1];
            strcpy(temp2, this->licensePlate);
            for (int i = 0; temp2[i] != '\0'; i++)
            {
                temp2[i] = toupper(temp2[i]);
            }
            bool checkResult = strcmp(temp, temp2) == 0;
            delete[] temp;
            delete[] temp2;
            return checkResult;
            //return this->licensePlate == right.licensePlate;
        }
        return false;
    }

    istream& Vehicle::  read(istream& is)
    {
        if (isCsv())
        {
            is >> this->parkingNumber;
            is.ignore();
            is.getline(this->licensePlate, 9, ',');
            for (int i = 0; this->licensePlate[i] != '\0' && i < 9; i++)
            {
                this->licensePlate[i] = toupper(this->licensePlate[i]);
            }
            char tempMakeModel[MAX_READ_CHAR + 1];
            is.getline(tempMakeModel, MAX_READ_CHAR + 1, ',');
            setMakeModel(tempMakeModel);
        }
        else
        {

            this->parkingNumber = 0;
            cout << "Enter License Plate Number: ";
            string tempLicensePlate;
            getline(is, tempLicensePlate);
            while (tempLicensePlate.length() > 8)
            {
                cout << "Invalid License Plate, try again: ";
                getline(is, tempLicensePlate);
            }
            for (int i = 0; tempLicensePlate[i] != '\0' && i < 8; i++)
            {
                tempLicensePlate[i] = toupper(tempLicensePlate[i]);
            }
            strcpy(this->licensePlate, tempLicensePlate.c_str());
            cout << "Enter Make and Model: ";
            string tempMakeModel;
            if (getline(is, tempMakeModel))
            {
                while ((tempMakeModel.length() < 2 || tempMakeModel.length() > 60))
                {
                    cout << "Invalid Make and model, try again: ";
                    getline(is, tempMakeModel);
                }
                setMakeModel(tempMakeModel.c_str());
            }
            else if (is.fail())
            {
                setEmpty();
            }
        }
        return is;
    }

    ostream& Vehicle::write(ostream& os) const
    {
        if (isEmpty())
        {
            os << "Invalid Vehicle Object" << endl;
        }
        else
        {
            writeType(os);
            if (isCsv())
            {
                os << this->parkingNumber << "," << this->licensePlate << "," << this->makeAndModel << ",";
            }
            else
            {
                os << "Parking Spot Number: ";
                if (this->parkingNumber == 0)
                {
                    os << "N/A" << endl;
                }
                else
                {
                    os << this->parkingNumber << endl;
                }
                os << "License Plate: " << this->licensePlate << endl;
                os << "Make and Model: " << this->makeAndModel << endl;
            }
        }
        return os;
    }
}
