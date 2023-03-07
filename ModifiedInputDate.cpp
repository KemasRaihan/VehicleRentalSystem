#include "ModifiedInputDate.h"

int ModifiedInputDate::getValidDay(const int month)
{
	int day = 0;
	bool invalid;

	// keep asking until user enters a valid day
	do {
		invalid = false;
		day = getPositiveInt("Enter the day");

		// user chooses a month that has 31 days or less and chooses a day that is greater than 31
		bool condition1 = ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31);

		// user chooses a month that has 31 days or less and chooses a day that is greater than 30
		bool condition2 = ((month == 4 || month == 6 || month == 9 || month == 7 || month == 11) && day > 30);

		// user chooses Februrary that has 29 days or less (excluding leap years) and chooses a day that is greater than 29
		bool condition3 = ((month == 2) && day > 29);

		// if any of the conditions are true then the user has entered an invalid day
		if (condition1 || condition2 || condition3) 
		{
			invalid = true;
			Response::printFailure("Invalid input. Please enter a valid day...");
		}
	} while (invalid);

	return day;
}

int ModifiedInputDate::getValidMonth()
{
	int month = 0;
	bool invalid;
	// keep asking until user enters a valid month
	do {
		invalid = false;
		month = getPositiveInt("Enter the month");
		// invalid date
		if (month > 12)
		{
			invalid = true;
			Response::printFailure("Invalid input. Please enter a valid month...");
		}
	} while (invalid);

	return month;


}
