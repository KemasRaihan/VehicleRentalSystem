#include "Bike.h"

Bike::Bike() : engineSize(0.0), isThreeWheeler(false)
{

}

Bike::~Bike()
{

}

std::istream& operator>>(std::istream& is, Bike* bike)
{
	// enter base member values from console
	std::cin >> static_cast<Vehicle*>(bike);

	// enter a valid double value for engine size from console
	bike->engineSize = ModifiedInput::getPositiveDouble("Enter the engine size");

	// enter valid number of wheels from console
	bike->isThreeWheeler = ModifiedInputBike::getNumberOfWheels();


	return is;
}



std::ifstream& operator>>(std::ifstream& input, Bike* bike)
{
	// retrieve details from file
	input >> static_cast<Vehicle*>(bike) >> bike->engineSize >> bike->isThreeWheeler;
	return input;


}


std::ofstream& operator<<(std::ofstream& output, const Bike* bike)
{
	// write bike details to file
	output << "Bike" << " ";
	output << static_cast<const Vehicle*>(bike);
	output << bike->engineSize << " ";
	output << bike->isThreeWheeler;
	return output;
}
