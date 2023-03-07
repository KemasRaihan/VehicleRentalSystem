#include "VehicleFactory.h"

// create an derived vehicle object and insert details from file stream
Vehicle* VehicleFactory::produce(std::ifstream& input, const std::string& type)
{
	// return new car object
	if (type == "Car")
	{
		Car* car = new Car(); // create new car object on the heap
		input >> car; // get details from file and input into car object
		return car;
	}
	// return new bike object
	Bike* bike = new Bike(); // create new bike object on the heap
	input >> bike; // get details from file and input into bike object
	return bike;
}

// create an derived vehicle object and insert details from console stream
Vehicle* VehicleFactory::produce(const std::string& type)
{
	// return new car object
	if (type == "Car")
	{
		Car* car = new Car(); // create new car object on the heap
		std::cin >> car; // allow user to enter details of the car from console input
		return car;
	}
	// return new bike object
	Bike* bike = new Bike(); // create new bike object on the heap
	std::cin >> bike; // allow user to enter details of the bike from console input
	return bike;
}

