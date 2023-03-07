#pragma once
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"

class VehicleFactory
{
public:
	static Vehicle* produce(const std::string& type);
	static Vehicle* produce(std::ifstream& input, const std::string& type);

private:
	VehicleFactory();

public:
	// singleton design; remove copy operators
	VehicleFactory(const VehicleFactory&) = delete; 
	void operator=(VehicleFactory const&) = delete;
};


