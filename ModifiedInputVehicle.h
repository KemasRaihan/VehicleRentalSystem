#pragma once
#include "ModifiedInput.h"

class ModifiedInputVehicle : public ModifiedInput
{
public:
	static std::string getRegistrationNumber(const std::string& message);

private:
	ModifiedInputVehicle();

public:
	// singleton design remove copy operators
	ModifiedInputVehicle(const ModifiedInputVehicle&) = delete;
	void operator=(const ModifiedInputVehicle&) = delete;
};


class ModifiedInputBike : public ModifiedInputVehicle
{
public:
	static bool getNumberOfWheels();

private:
	ModifiedInputBike();

public:
	ModifiedInputBike(const ModifiedInputBike&) = delete;
	void operator=(const ModifiedInputBike&) = delete;
};



