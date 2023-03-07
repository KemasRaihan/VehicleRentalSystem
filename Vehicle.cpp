#include "Vehicle.h"
Vehicle::Vehicle() : registrationNumber(""), make(nullptr), model(nullptr), age(0), filepath("..\\Files\\Rentals\\"), rentalHistory(new RentalHistory())
{
}


Vehicle::~Vehicle()
{
	free(make);
	free(model);

	delete rentalHistory;
}



void Vehicle::viewInfo()
{
	// get rental history from filepath
	readRentalsFromFile();

	const char RENT_VEHICLE = '1';
	const char VIEW_RENTALS = '2';
	const char RETURN_TO_MAIN_MENU = '9';

	char option;

	do {

		display();

		std::cout << "\n1) Rent Vehicle";
		std::cout << "\n2) View Historic Rentals";
		std::cout << "\n9) Return to main menu\n";

		std::cout << "\nPlease choose an option: ";
		option = ModifiedInput::getCharacter();

		switch (option)
		{
		case RENT_VEHICLE:
			rent();
			break;
		case VIEW_RENTALS:
			viewRentalHistory();
			break;
		case RETURN_TO_MAIN_MENU:
			Response::printReturn("Returning to main menu...");
			break;
		default:
			Response::printFailure("Invalid input. Please try again...");
			break;
		}
	} while (option != RETURN_TO_MAIN_MENU);
	// save rentals to disk once user exits information screen
	writeRentalsToFile();
}




void Vehicle::viewRentalHistory() 
{
	// check if there are rental records to view 
	if (!rentalHistoryIsEmpty())
	{
		// index of rental history array
		// start from first record
		int index = 0;

		char option;

		const char VIEW_PREVIOUS = '1';
		const char VIEW_NEXT = '2';
		const char RETURN_TO_VEHICLE_INFO = '9';


		do {
			std::cout << "\n----------------------------------------------------------";
			std::cout << "\n" << registrationNumber << " : " << model << " Rental History";
			std::cout << "\n----------------------------------------------------------";

			viewRentalRecord(index);

			std::cout << "\n\n1) View the previous record";
			std::cout << "\n2) View the next record;";
			std::cout << "\n9) Return to vehicle information screen";

			std::cout << "\n\nPlease choose an option: ";
			option = ModifiedInput::getCharacter();

			if ((option == VIEW_PREVIOUS) && (index > 0)) // if user chooses previous and is currently not at first record
				index--;
			else if ((option == VIEW_NEXT) && (index < getNumberOfRentals() - 1)) // if user chooses next and is currently not at last record
				index++;
			else if (option == RETURN_TO_VEHICLE_INFO) // user returns to vehicle information screen
				Response::printReturn("Returning to information screen...");
			else // user chooses invalid option
				Response::printFailure("Invalid option. Please try again...");

		} while (option != RETURN_TO_VEHICLE_INFO);


	}
	else // no rental records
		Response::printFailure("There are no rental records to view!");

}

void Vehicle::viewRentalRecord(int index)
{
	std::cout << "\nRental: " << (index + 1) << " of " << getNumberOfRentals();

	// display start date of rental
	std::cout << "\nDate From: " << getRentalRecord(index)->getStartDate();

	// display end date of rental
	std::cout << "\nDate To: " << getRentalRecord(index)->getEndDate();

	// calculate the difference in number of days between the two start date of rental and the end date of rental
	int difference = getRentalRecord(index)->calculateDiffInDays();
	std::cout << "\nRental days: " << difference;

	// calculate total cost where: total cost = costPerDay x numberOfRentalDays
	std::cout << "\nTotal cost: " << char(156) << (calculateCostPerDay() * difference);

	// display customer details
	std::cout << getRentalRecord(index)->getCustomer();


}




std::istream& operator>>(std::istream& is, Vehicle* vehicle)
{
	// input registration number
	vehicle->registrationNumber=ModifiedInputVehicle::getRegistrationNumber("Enter the registration number (must be in the format XXXX XXX)");

	// input make
	vehicle->make=ModifiedInput::getCstr("Enter the make");

	// input model
	vehicle->model=ModifiedInput::getCstr("Enter the model");

	// input age
	vehicle->age=ModifiedInput::getPositiveDouble("Enter the age (in years)");

	// update filepath
	vehicle->filepath += vehicle->registrationNumber + ".txt";

	return is;

}

std::ifstream& operator>>(std::ifstream& input, Vehicle* vehicle)
{
	std::string regFirstHalf, regSecondHalf, makeStr, modelStr;

	// retrieve registration number from text file, seperated by space
	input >> regFirstHalf >> regSecondHalf;
	// concatenate the two strings and store in member variable
	vehicle->registrationNumber = regFirstHalf + " " + regSecondHalf;


	//retrieve make
	input >> makeStr;

	// create new block of memory for the 'make' member variable
	vehicle->make = (char*)malloc(sizeof(char) * (makeStr.size() + 1));
	strcpy_s(vehicle->make, makeStr.size() + 1, makeStr.c_str());

	// retrieve model
	input >> modelStr;

	// create new block of memory for the 'model' member variable
	vehicle->model = (char*)malloc(sizeof(char) * (modelStr.size() + 1));
	strcpy_s(vehicle->model, modelStr.size() + 1, modelStr.c_str());

	input >> vehicle->age;

	// get file path for rental history
	vehicle->filepath += vehicle->registrationNumber + ".txt";


	return input;
}

std::ostream& operator<<(std::ostream& os, Vehicle* vehicle)
{
	os << vehicle->registrationNumber << "\t\t";
	os << vehicle->calculateCostPerDay() << "\t\t";
	os << vehicle->make << "\t\t";
	os << vehicle->model;

	return os;
}

// write details to file
std::ofstream& operator<<(std::ofstream& output, const Vehicle* vehicle)
{
	output << vehicle->registrationNumber << " ";
	output << vehicle->make << " ";
	output << vehicle->model << " ";
	output << vehicle->age;
	return output;
}


// display vehicle info
void Vehicle::display()
{
	std::cout << "\n-----------------------------------\n";
	std::cout << registrationNumber << " : " << model;
	std::cout << "\n-----------------------------------\n";
	std::cout << "\nCost per day: " << char(156) << calculateCostPerDay();
	std::cout << "\nTotal rental income: " << char(156) << calculateTotalIncome();
	std::cout << "\nTotal days rented: " << calculateTotalRentalDays() << "\n";
}


void Vehicle::readRentalsFromFile()
{
	// read from filepath
	std::ifstream input(filepath);
	// open file
	if (input.is_open())
	{
		// while the input has not reach the end of the txt file
		while (input.peek() != std::ifstream::traits_type::eof())
		{
			// create new record object on the heap
			RentalRecord* record = new RentalRecord();

			// retrieve details from file
			input >> record;

			// add to rental histroy memory array
			rentalHistory->add(record);
		}

		input.close(); // close stream
	}
}

void Vehicle::writeRentalsToFile() const
{	// write to filepath
	std::ofstream output(filepath);

	int index = 0;

	// open file
	if (output.is_open())
	{

		int index = 0;
		// for each rental record, write the details to the file 
		for (int i = 0; i < getNumberOfRentals(); i++)
		{
			// write each rental record of the vehicle to the file
			output << getRentalRecord(i);

			// if last rental record has been written to file, then break loop to avoid whitespace at the bottom
			if (++index == getNumberOfRentals())
				break;

			// go to new line
			output << "\n";
		}


		// close stream
		output.close();
	}
	else
		Response::printFailure("Cannot open file for writing!");


}

