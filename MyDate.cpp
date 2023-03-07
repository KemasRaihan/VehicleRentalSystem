#include "MyDate.h"

MyDate::MyDate() : day(0), month(0), year(0)
{

}

// return the difference in number of days between two dates
int MyDate::operator-(MyDate& rhs)
{
	int dyear = year - rhs.year;
	int dmonth = month - rhs.month;
	int dday = day - rhs.day;
	int res = dyear * 365 + dmonth * 31 + dday;
	return res;

}

bool MyDate::operator<(const MyDate& rhs)
{// return true if rhs is newer
	if (year > rhs.year) return false;
	else
	{// has same year as rhs or older
		if (month > rhs.month) return false;
		else
		{// has same month as rhs or older
			// rhs is older
			if (day > rhs.day) return false;
		}
	}
	// has same date or is older than rhs date
	return true;

}

std::istream& operator>>(std::istream& is, MyDate* date)
{
	date->month = ModifiedInputDate::getValidMonth();
	date->day = ModifiedInputDate::getValidDay(date->month);
	date->year = ModifiedInput::getPositiveInt("Enter the year");
	return is;
}

std::ostream& operator<<(std::ostream& os, const MyDate* date)
{
	os << date->day << "/" << date->month << "/" << date->year;
	return os;
}

std::ifstream& operator>>(std::ifstream& input, MyDate* date)
{
	// retrieve date from file
	input >> date->day >> date->month >> date->year;
	return input;
}


std::ofstream& operator<<(std::ofstream& output, MyDate* date)
{
	// write date to file
	output << date->day << " ";
	output << date->month << " ";
	output << date->year << " ";
	return output;
}



