#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include "Response.h"
class ModifiedInput
{
public:
	inline static char getCharacter();
	static int getPositiveInt(const std::string& message);
	static double getPositiveDouble(const std::string& message);
	static char* getCstr(const std::string& message);
	static std::string getUpperCaseStr(const std::string& message);

private:
	ModifiedInput();

public:
	ModifiedInput(const ModifiedInput&) = delete;
	void operator=(const ModifiedInput&) = delete;
};

inline char ModifiedInput::getCharacter()
{
	std::string input;
	getline(std::cin >> std::ws, input);
	// prompt user to enter one character
	if (input.size()==1) return input[0];
	else return '#';
}

















