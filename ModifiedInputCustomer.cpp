#include "ModifiedInputCustomer.h"

std::string ModifiedInputCustomer::getValidPhoneNumber()
{
	std::string number = "";

	bool invalid;

	do
	{
		invalid = false;
		std::cout << "Enter your phone number: ";
		getline(std::cin >> std::ws, number);

		for (char n : number)
		{
			// check if character is a digit
			if (!isdigit(n))
			{// if one of the characters in the input is not a digit, then input is invaid
				invalid = true;
				Response::printFailure("Invalid phone number. Please try again...");
				break;
			}
		}

	} while (invalid);

	return number;

}