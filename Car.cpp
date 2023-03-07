#include "Car.h"
Car::Car() : numberOfDoors(0), numberOfSeats(0)
{

}

Car::~Car()
{

}

std::istream& operator>>(std::istream& is, Car* car)
{
	// enter base member values from console
	std::cin >> static_cast<Vehicle*>(car);

	// enter number of doors from console 
	car->numberOfDoors = ModifiedInput::getPositiveInt("Enter number of doors");

	// enter number of seats from console 
	car->numberOfSeats = ModifiedInput::getPositiveInt("Enter number of seats");

	return is;
}

// read car details from text file
std::ifstream& operator>>(std::ifstream& input, Car* car)
{

	// retrieve values for base member variables
	input >> static_cast<Vehicle*>(car);

	// retrieve number of doors
	input >> car->numberOfDoors;

	// retrieve number of seats
	input >> car->numberOfSeats;

	return input;
}

std::ofstream& operator<<(std::ofstream& output, const Car* car)
{
	// write car details to text file
	output << "Car" << " ";
	output << static_cast<const Vehicle*>(car) << " ";
	output << car->numberOfDoors << " ";
	output << car->numberOfSeats;

	return output;
}


