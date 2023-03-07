#include "ModifiedInput.h"
#include "Response.h"

std::string ModifiedInput::getUpperCaseStr(const std::string& message)
{
	// print prompt user message
	std::cout << message << ": ";
	std::string input;
	getline(std::cin, input);
	for (auto& c : input) 
		c = toupper(c); // convert each char value of string into upper case
	return input;
}

char* ModifiedInput::getCstr(const std::string& message)
{
	char* output;

	// print prompt user message
	std::cout << message << ": ";

	// get string input
	std::string input;
	getline(std::cin >> std::ws, input);

	// create block of memory for output in the size of input
	output = (char*)malloc(sizeof(char) * (input.size() + 1));

	// copy char values of input into memory address of cstr
	strcpy_s(output, input.size() + 1, input.c_str());

	return output;
}

int ModifiedInput::getPositiveInt(const std::string& message)
{
	int inputInt = -1;

	// keep asking user until they enter valid integer input
	while (true)
	{
		// print prompt user message
		std::cout << message << ": ";

		// get string input
		std::string input;
		getline(std::cin >> std::ws, input);

		// parse string to double and store in output
		if (inputInt = std::atoi(input.c_str())) // if parse is successful
			if (inputInt > 0) // if number if positive
				break; // user enters a valid input so break out of loop

		Response::printFailure("Please enter a positive integer...");
	}

	return inputInt;
}

double ModifiedInput::getPositiveDouble(const std::string& message)
{
	double inputDob = -1;

	// keep asking user until they enter valid double input
	while (true)
	{
		// print prompt user message
		std::cout << message << ": ";

		// get string input
		std::string input;
		getline(std::cin >> std::ws, input);

		// parse string to double and store in output
		if (inputDob = std::atof(input.c_str())) // if parse is successful
			if (inputDob > 0) // if number if positive
				break; // user enters a valid input so break out of loop

		Response::printFailure("Please enter a positive number...");
	}

	return inputDob;
}






