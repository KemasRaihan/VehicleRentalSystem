#include <iostream>
#include "VehicleManager.h"
#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"

const static char ADD_VEHICLE = '1';
const static char REMOVE_VEHICLE = '2';
const static char SEARCH_FOR_CAR = '3';
const static char SEARCH_FOR_BIKE = '4';
const static char SORT_VEHICLES_BY_REG = '5';
const static char SORT_COST_PER_DAY = '6';
const static char EXIT = '9';

VehicleManager* vehicleManager;

void addVehicle()
{
	std::cout << "\n=================\n";
	std::cout << "1. Add Vehicle\n";
	std::cout << "=================\n";

	const char ADD_CAR = '1';
	const char ADD_BIKE = '2';
	const char RETURN_TO_MAIN_MENU = '9';

	char option;
	bool invalid;

	do {
		// choose the type of vehicle to add
		std::cout << "\nWhich type of vehicle would you like to add?\n";
		std::cout << "1. Car\n";
		std::cout << "2. Bike\n";
		std::cout << "9. Return to main menu\n";

		std::cout << "Option: ";
		option = ModifiedInput::getCharacter();

		invalid = false;

		switch (option)
		{
		case ADD_CAR:
			vehicleManager->addToList(VehicleFactory::produce("Car")); // add a new Car object to the list
			break;
		case ADD_BIKE:
			vehicleManager->addToList(VehicleFactory::produce("Bike")); // add a new Bike object to the list
			break;
		case RETURN_TO_MAIN_MENU:Response::printReturn("Returning to main menu..."); break;
		default:
			invalid = true;
			Response::printFailure("Invalid input!");
		}
	} while (invalid);
}

void removeVehicle()
{
	if (!vehicleManager->listIsEmpty())
	{
		std::cout << "\n=================\n";
		std::cout << "2. Remove Vehicle\n";
		std::cout << "=================\n";

		std::string registrationNumber = ModifiedInput::getUpperCaseStr("Enter the registration number of the vehicle you wish to remove");

		vehicleManager->removeFromList(registrationNumber);

	}
	else
	{
		Response::printFailure("There are no vehicles in the list!");
	}
}




void searchForCar()
{
	if (!vehicleManager->listIsEmpty())
	{
		std::cout << "=================\n";
		std::cout << "3. Search For Car\n";
		std::cout << "=================\n";

		const char SEARCH_BY_REG = '1';
		const char SEARCH_BY_SEATS = '2';
		const char SEARCH_BY_DOORS = '3';
		const char RETURN_TO_MAIN_MENU = '9';
		
		char option;
		bool invalid;

		// initialiase a vector of pointers to vehicle object to find vehicles that matches with the user's chosen details
		VehicleVector matches;

		do {
			std::cout << "\nSearch for a car by:\n";
			std::cout << "-----------------------\n";
			std::cout << "1) Registration Number\n";
			std::cout << "2) Number of seats\n";
			std::cout << "3) Number of doors\n";
			std::cout << "9) Return to main menu\n";
			std::cout << "\nPlease choose an option: ";

			invalid = false;

			option = ModifiedInput::getCharacter();

			switch (option)
			{
			case SEARCH_BY_REG:
				vehicleManager->searchByReg<Car>();
				break;
			case SEARCH_BY_SEATS:
				vehicleManager->searchByNumberOfSeats(matches);
				break;
			case SEARCH_BY_DOORS:
				vehicleManager->searchByNumberOfDoors(matches);
				break;
			case RETURN_TO_MAIN_MENU:
				Response::printReturn("Returning to main menu...");
				break;
			default: // user enters an invalid input
				invalid = true;
				Response::printFailure("Invalid option. Please try again...");
			}
		} while (invalid);

	}
	else
	{
		Response::printFailure("There are no vehicles in the list!");
	}
}

void searchForBike()
{
	if (!vehicleManager->listIsEmpty())
	{
		std::cout << "=================\n";
		std::cout << "4. Search For Bike\n";
		std::cout << "=================\n";

		const char SEARCH_BY_REG = '1';
		const char SEARCH_BY_ENGINE_SIZE = '2';
		const char SEARCH_BY_WHEELS = '3';
		const char RETURN_TO_MAIN_MENU = '9';

		// initialiase a vector of pointers to vehicle object to find vehicles that matches with the user's chosen details
		VehicleVector matches;

		char option;
		bool invalid;

		do {
			std::cout << "\nSearch for a bike by:\n";
			std::cout << "-----------------------\n";
			std::cout << "1) Registration Number\n";
			std::cout << "2) Engine Size\n";
			std::cout << "3) Number of wheels\n";
			std::cout << "9) Return to main menu\n";
			std::cout << "\nPlease choose an option: ";

			invalid = false;

			option = ModifiedInput::getCharacter();

			switch (option)
			{
			case SEARCH_BY_REG:
				vehicleManager->searchByReg<Bike>();
				break;
			case SEARCH_BY_ENGINE_SIZE:
				vehicleManager->searchByEngineSize(matches);
				break;
			case SEARCH_BY_WHEELS:
				vehicleManager->searchByWheels(matches);
				break;
			case RETURN_TO_MAIN_MENU:
				Response::printReturn("Returning to main menu...");
				break;
			default:
				invalid = true;
				Response::printFailure("Invalid option. Please try again...");
			}
		} while (invalid);

	}
	else
	{
		Response::printFailure("There are no vehicles in the list!");
	}
}



void exit()
{
	std::cout << "\nGoodbye!\n\n";

	// save vehicles to disk once user exits
	vehicleManager->writeListToFile();

	// free memory of the vehicle manager object as its no longer needed
	delete vehicleManager;
}

void menu()
{
	char option;
	do
	{
		std::cout << "\n=========================\n";
		std::cout << "\nVehicle Rental System\n";
		std::cout << "=========================\n\n";

		// display vehicles added to the list
		vehicleManager->displayList();

		std::cout << "\n1) Add vehicle\n";
		std::cout << "2) Remove vehicle\n";
		std::cout << "3) Search for car\n";
		std::cout << "4) Search for bike\n";
		std::cout << "5) Sort vehicles by registration number\n";
		std::cout << "6) Sort by cost per day\n";
		std::cout << "9) Exit\n";

		std::cout << "Please enter an option: ";

		// get user to enter a character as input
		option = ModifiedInput::getCharacter();

		// menu options
		switch (option)
		{
		case ADD_VEHICLE: addVehicle(); break;
		case REMOVE_VEHICLE: removeVehicle(); break;
		case SEARCH_FOR_CAR: searchForCar(); break;
		case SEARCH_FOR_BIKE: searchForBike(); break;
		case SORT_VEHICLES_BY_REG: vehicleManager->sortListByReg(); break;
		case SORT_COST_PER_DAY: vehicleManager->sortListByCost(); break;
		case EXIT: exit(); break;
		default: Response::printFailure("Invalid input!");;
		};

	} while (option != EXIT); // while user chooses not to exit the menu


}

void start()
{
	std::cout << "Welcome to Vehicle Rental System! Press ENTER to start...";
	std::cin.ignore(); // allow user to press ENTER to start
	vehicleManager = new VehicleManager();
	menu();
}

int main()
{
#ifdef _DEBUG
//	  _CrtSetBreakAlloc(324);
	_onexit(_CrtDumpMemoryLeaks);
#endif
	start();

	return 0;
}