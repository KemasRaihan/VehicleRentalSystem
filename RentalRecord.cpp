#include "RentalRecord.h"

RentalRecord::RentalRecord() : customer(new Customer())
{
	dates = new MyDate * [2];
	dates[0] = new MyDate();
	dates[1] = new MyDate();
}
RentalRecord::~RentalRecord()
{
	delete customer;
	delete dates[0];
	delete dates[1];
	delete[] dates; // clean up dates array memory
}

std::istream& operator>>(std::istream& is, RentalRecord* record)
{
	std::cin >> record->customer; // get user to enter the customer details
	std::cout << "\nDate of rental from: ";
	std::cout << "\n----------------------\n";
	std::cin >> record->dates[0]; // get user to enter the start date of rental
	// loop until user enters a valid end date
	do {
		std::cout << "\nDate of rental to: ";
		std::cout << "\n----------------------\n";
		std::cin >> record->dates[1]; // get user to enter the end date of rental

		// end date should not be on the same day or newer than the start date
		if (*record->dates[1] < *record->dates[0])
			Response::printFailure("Invalid date please try again");
		else break;

	} while (true);
	return is;
}

std::ifstream& operator>>(std::ifstream& input, RentalRecord* record)
{
	input >> record->dates[0];
	input >> record->dates[1];
	input >> record->customer;
	return input;
}

std::ofstream& operator<<(std::ofstream& output, RentalRecord* record)
{
	output << record->dates[0];
	output << record->dates[1];
	output << record->customer;
	return output;
}