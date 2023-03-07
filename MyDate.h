#pragma once
#include <iostream>
#include <fstream>
#include "ModifiedInputDate.h"

class MyDate {
public:
	MyDate();

	int operator-(MyDate& rhs);
	bool operator<(const MyDate& rhs);
	friend std::istream& operator>>(std::istream& is, MyDate* date);
	friend std::ostream& operator<<(std::ostream& os, const MyDate* date);
	friend std::ifstream& operator>>(std::ifstream& input, MyDate* date);
	friend std::ofstream& operator<<(std::ofstream& output, MyDate* date);


private:
	int day, month, year;
};




