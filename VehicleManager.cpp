#include "VehicleManager.h"

VehicleManager::VehicleManager() : filepath("..\\Files\\Lists\\list.txt")
{
	readListFromFile();
}

VehicleManager::~VehicleManager()
{
	// free memory for every vehicle that is stored in STL container 'vehicles'
	std::for_each(vehicles.begin(), vehicles.end(), [=](Vehicle* vehicle) {delete vehicle; });
}

void VehicleManager::displayList()
{
	if (!listIsEmpty())
	{
		// header for list
		std::cout << "Registration Number" << "\t\t" << "Cost Per Day" << "\t\t" << "Vehicle Type" << "\n";
		std::cout << "--------------------" << "\t\t" << "------------" << "\t\t" << "------------" << "\n";

		// print vehicle details for list in menu
		for (Vehicle* vehicle : vehicles)
			std::cout << vehicle->getRegistrationNumber() << "\t\t\t" << vehicle->calculateCostPerDay() << "\t\t\t" << findType(vehicle) << "\n";
	}
}

void VehicleManager::addToList(Vehicle* vehicle)
{

	// check if vehicle, with the same registration number, already exists in the list
	// by obtaining memory address of the vehicle check; 
	// if the vehicle doest not exist then it should return a nullptr
	if (!findInList<Vehicle>(vehicle->getRegistrationNumber()))
	{
		// add to list
		vehicles.push_back(vehicle);
		Response::printSuccess("Vehicle successfully added!");
	}
	else
	{
		// free memory as it will not be added to list
		delete vehicle;
		Response::printFailure("Invalid registration number, vehicle with same registration number already exists!");
	}

}


void VehicleManager::removeFromList(const std::string& registrationNumber)
{

	// find the memory address of vehicle to be removed from the STL list
	Vehicle* vehicle = findInList<Vehicle>(registrationNumber);

	// if memory address is not a nullptr, then vehicle has been found
	if (vehicle)
	{
		// free memory of vehicle
		delete vehicle;

		// remove memory address, of the vehicle being removed, from list container
		vehicles.erase(find(vehicles.begin(), vehicles.end(), vehicle));

		Response::printSuccess("Vehicle successfully removed!");
	}
	else
	{
		Response::printFailure("Vehicle cannot be found!");
	}
}






bool VehicleManager::displayMatches(VehicleVector& matches)
{
	if (!matches.empty()) // if there are matches, then display them
	{
		// display search header, along with the type of the vehicles that the list contains
		std::cout << "\nList of " << VehicleManager::findType(matches.at(0)) << "s matching the search\n";
		std::cout << " \nRegistration Number \t\t Cost per day \t\t Make \t\t Model\n";
		std::cout << "  -------------------- \t\t ------------ \t\t ---- \t\t ------\n";
		int index = 1;
		for_each(matches.cbegin(), matches.cend(), [=](Vehicle* vehicle) mutable {
			std::cout << index++ << "\t";
			std::cout << vehicle->getRegistrationNumber() << "\t\t";
			std::cout << vehicle->calculateCostPerDay() << "\t\t";
			std::cout << vehicle->getMake() << "\t\t";
			std::cout << vehicle->getModel() << "\n"; });
		return true;
	}
	Response::printFailure("Vehicle cannot be found!");
	return false;
}

void VehicleManager::selectVehicle(VehicleVector& matches)
{
	if (displayMatches(matches))
	{// if there are vehicles available for rent

		bool invalid;
		int index;
		do {
			invalid = false;
			std::cout << "\n\nEnter number to choose vehicle or 0 to return to main menu: ";
			std::cin >> index;

			if (index > 0 && index <= matches.size())
			{// user chooses a vehicle in a valid index
				matches.at(index - 1)->viewInfo();
			}
			else if (index == 0)
			{// user chooses to return to main menu
				Response::printReturn("Returning to main menu...");
			}
			else
			{// chosen index is invalid
				invalid = true;
				Response::printFailure("Invalid option. Please try again...");
			}

		} while (invalid);
	}

	// vector no longer needed: remove all elements from matches and reduce matches's size to 0
	matches.clear();
}



inline bool compareNumberOfSeats(const Car* car, const int& numberOfSeats) { return(car->getNumberOfSeats() == numberOfSeats); }

inline bool compareNumberOfDoors(const Car* car, const int& numberOfSeats) { return(car->getNumberOfDoors() == numberOfSeats); }

inline bool compareEngineSize(const Bike* bike, const double& engineSize) { return(bike->getEngineSize() == engineSize); }

inline bool compareWheels(const Bike* bike, const bool& isThreeWheeler) { return(bike->hasThreeWheels() == isThreeWheeler); }



void VehicleManager::searchByNumberOfSeats(VehicleVector& matches)
{
	int numberOfSeats = ModifiedInput::getPositiveInt("Please enter the number of seats");

	// look for potential matches
	findMatches(compareNumberOfSeats, numberOfSeats, matches);
	selectVehicle(matches);
}
void VehicleManager::searchByNumberOfDoors(VehicleVector& matches)
{
	int numberOfDoors = ModifiedInput::getPositiveInt("Please enter the number of doors");

	// look for potential matches
	findMatches(compareNumberOfDoors, numberOfDoors, matches);
	selectVehicle(matches);
}

void VehicleManager::searchByEngineSize(VehicleVector& matches)
{
	double engineSize = ModifiedInput::getPositiveDouble("Please enter the engine size");

	// look for potential matches
	findMatches(compareEngineSize, engineSize, matches);
	selectVehicle(matches);
}
void VehicleManager::searchByWheels(VehicleVector& matches)
{
	bool isThreeWheeler = ModifiedInputBike::getNumberOfWheels();

	// look for potential matches
	findMatches(compareWheels, isThreeWheeler, matches);
	selectVehicle(matches);
}


void VehicleManager::readListFromFile()
{
	// read from file
	std::ifstream input(filepath);

	std::string line;

	// open file if it is not empty
	if (input.is_open())
	{
		// keep reading if the input is not reading an empty file or has reached the end of the text file
		while (input.peek() != std::ifstream::traits_type::eof())
		{
			// read first line, input will read the vehicle type first
			input >> line;

			// create new vehicle object on the heap to be added to the list
			Vehicle* vehicle = VehicleFactory::produce(input, line);

			// add the vehicle object to the list
			vehicles.push_back(vehicle);
		}

		input.close(); // close stream
	}
	else
		Response::printFailure("Cannot open file!");
}


void VehicleManager::writeListToFile()
{
	// open and write to filepath
	std::ofstream output(filepath);

	if (output.is_open())
	{
		// if list is not empty then write to file
		if (!vehicles.empty())
		{
			int index = 0;
			// for each vehicle, write the details to the file 
			for (Vehicle* vehicle : vehicles)
			{
				// write vehicle details to file
				vehicle->writeDetailsToFile(output);

				// if last vehicle in the list has its details written to the text file, 
				// then do not go to new line, to avoid whitespace at the bottom
				if (++index != vehicles.size())
					output << "\n"; // write new line after details have been written for each vehicle
			}
		}

		// close stream
		output.close();
	}
	else
		Response::printFailure("Cannot open file!");
}





