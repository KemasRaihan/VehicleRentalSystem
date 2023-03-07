#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

#include "ModifiedInput.h"
#include "ModifiedInputVehicle.h"

#include "VehicleFactory.h"
#include "Response.h"

#include "Vehicle.h"
#include "Car.h"
#include "Bike.h"


typedef std::list<Vehicle*> VehicleList;
typedef std::vector<Vehicle*> VehicleVector;
typedef std::list<Vehicle*>::iterator VehicleListItr;


class VehicleManager
{
public:
	VehicleManager();
	~VehicleManager();

	inline bool listIsEmpty();

	void displayList();

	void addToList(Vehicle* vehicle);
	void removeFromList(const std::string& registrationNumber);

	template<class T>
	void searchByReg();

	void searchByNumberOfSeats(VehicleVector& matches); 
	void searchByNumberOfDoors(VehicleVector& matches);
	void searchByEngineSize(VehicleVector& matches); 
	void searchByWheels(VehicleVector& matches);


	inline void sortListByReg();
	inline void sortListByCost();

	void writeListToFile();

private:
	template<class T>
	static inline bool isType(Vehicle* vehicle);

	static inline std::string findType(Vehicle* vehicle);

	void selectVehicle(VehicleVector& matches);

	template<class T>
	Vehicle* findInList(const std::string& reg);

	template<class T, typename U>
	void findMatches(bool(*compare)(const T*, const U&), const U& value, VehicleVector& matches);

	bool displayMatches(VehicleVector& matches);

	void readListFromFile();

	VehicleList vehicles;
	std::string filepath;
};


inline bool VehicleManager::listIsEmpty() { return vehicles.empty(); }

// template function to allow user to find a vehicle, of a derived type, by its registration number
template<class T>
void VehicleManager::searchByReg()
{
	// enter the registration number of the vehicle to find
	std::string registrationNumber = ModifiedInput::getUpperCaseStr("Enter the registration number");

	// find vehicle in the list by the derived type chosen by the user
	Vehicle* vehicle = findInList<T>(registrationNumber);
	char option;

	// vehicle exist if it is not nullptr
	if (vehicle)
	{
		std::cout << " \n Registration Number \t\t Cost per day \t\t Make \t\t Model\n";
		std::cout << "  -------------------- \t\t ------------ \t\t ---- \t\t ------\n";
		std::cout << vehicle;

		bool invalid;

		// keep asking until user enters a valid input
		do {
			std::cout << "\nEnter 1 to select vehicle or enter 0 to return to main menu: ";
			option = ModifiedInput::getCharacter();

			invalid = false;
			if (option == '1') // user chooses to view vehicle info
				vehicle->viewInfo();
			else if (option == '0') // return to main menu
				Response::printReturn("Returning to main menu...");
			else // invalid input
			{
				invalid = true;
				Response::printFailure("Invalid valid option! Please try again...");
			}
		} while (invalid);

	}
	else // vehicle does not exist in the list
		Response::printFailure("Vehicle cannot be found!");

}

template<class T>
inline bool VehicleManager::isType(Vehicle* vehicle)
{
	// dynamically cast vehicle object to retrieve derived vehicle type (car/bike)
	if (dynamic_cast<T>(vehicle)) 	// if dynamic cast is not null, then vehicle is the chosen class type
		return true;
	return false;
}

inline std::string VehicleManager::findType(Vehicle* vehicle)
{
	if (isType<Car*>(vehicle)) // checks vehicle type in function 'isType' will return true if it is a pointer to a Car object
		return "Car";
	return "Bike"; 
}

template<class T>
Vehicle* VehicleManager::findInList(const std::string& reg)
{
	for (Vehicle* vehicle : vehicles) // traverse through list
		if (isType<T*>(vehicle)) // match vehicle by type
			if (*vehicle == reg) // compare registration number 
				return vehicle;
	return nullptr; // if vehicle is not found
}





template<class T, typename U>
void VehicleManager::findMatches(bool(*compare)(const T*, const U&), const U& value, VehicleVector& matches)
{
	for (Vehicle* vehicle : vehicles) // traverse through list
		if (isType<T*>(vehicle)) // match vehicle by type
			if (compare(dynamic_cast<T*>(vehicle), value)) // match vehicle by details
				matches.push_back(vehicle); // add to end of list
}


inline void VehicleManager::sortListByReg()
{
	// sort the list alphabetically by registration number, by using the std algorithm sort
	vehicles.sort([](Vehicle* lhs, Vehicle* rhs) {return ((*lhs) < (*rhs)); });

}

inline void VehicleManager::sortListByCost()
{
	// sort the list by cost per day, ascending, by using the std algorithm sort
	vehicles.sort([](Vehicle* lhs, Vehicle* rhs) { return lhs->calculateCostPerDay() < rhs->calculateCostPerDay(); });
}



