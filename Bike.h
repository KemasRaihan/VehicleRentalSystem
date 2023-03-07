#pragma once
#include "Vehicle.h"
#include "ModifiedInputVehicle.h"

class Bike : public Vehicle
{
public:
	Bike();
	~Bike();

	inline int calculateCostPerDay() const;

	inline void writeDetailsToFile(std::ofstream& output) const;

	inline double getEngineSize() const;
	inline bool hasThreeWheels() const;


	friend std::istream& operator>>(std::istream& is, Bike* bike);
	friend std::ifstream& operator>>(std::ifstream& input, Bike* bike);
	friend std::ofstream& operator<<(std::ofstream& output, const Bike* bike);

private:
	double engineSize;
	bool isThreeWheeler;
};

inline int Bike::calculateCostPerDay() const { return capCheck(1500 + (int)engineSize); }

inline void Bike::writeDetailsToFile(std::ofstream& output) const { output << this; }

inline double Bike::getEngineSize() const { return engineSize; }

inline bool Bike::hasThreeWheels() const { return isThreeWheeler; }

