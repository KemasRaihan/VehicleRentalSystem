#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{
public:
	Car();
	~Car();

	inline int calculateCostPerDay() const;

	inline void writeDetailsToFile(std::ofstream& output) const;

	inline int getNumberOfDoors() const;
	inline int getNumberOfSeats() const;

	friend std::istream& operator>>(std::istream& is, Car* car);
	friend std::ifstream& operator>>(std::ifstream& input, Car* car);
	friend std::ofstream& operator<<(std::ofstream& output, const Car* car);

private:
	unsigned int numberOfDoors, numberOfSeats;
};

inline int Car::calculateCostPerDay() const { return capCheck(2500 - (int)getAge() * 150 - numberOfDoors * 200); }

//inline void Car::readDetailsFromFile(std::ifstream& input) { input >> this; }

inline void Car::writeDetailsToFile(std::ofstream& output) const { output << this; }

inline int Car::getNumberOfDoors() const { return numberOfDoors; }

inline int Car::getNumberOfSeats() const { return numberOfSeats; }




