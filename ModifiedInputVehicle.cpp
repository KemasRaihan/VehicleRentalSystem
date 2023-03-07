#include "ModifiedInputVehicle.h"

std::string ModifiedInputVehicle::getRegistrationNumber(const std::string& message)
{
	// UK registration number format according to GOV.UK
	std::string input = "";

	do {
		// convert user input into upper case
		input = getUpperCaseStr(message);

		// registration number must be 8 characters long
		if (input.length() == 8)
		{
			// fourth character in registration number must be a space
			if (input[4] == ' ')
				break;
		}

		Response::printFailure("Invalid registration number");
	} while (true);

	return input;
}


bool ModifiedInputBike::getNumberOfWheels()
{
	const static char TWO_WHEELER = '1';
	const static char THREE_WHEELER = '2';

	bool isThreeWheeler = false;
	bool invalid;
	char option;
	// get user to enter a valid input for 'isThreeWheeler'
	do {
		invalid = false;
		std::cout << "\nIs the bike a two-wheeler or three-wheeler: \n";
		std::cout << "1. Two-Wheeler\n";
		std::cout << "2. Three-Wheeler\n";
		std::cout << "\nPlease select an option: ";
		option = ModifiedInput::getCharacter();
		switch (option)
		{
		case TWO_WHEELER:
			isThreeWheeler = true;
			break;
		case THREE_WHEELER:
			isThreeWheeler = false;
			break;
		default:
			invalid = true;
			Response::printFailure("Invalid input. Please try again.");
		}

	} while (invalid);

	return isThreeWheeler;

}