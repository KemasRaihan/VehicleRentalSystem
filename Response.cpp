#include "Response.h"

void Response::printSuccess(const std::string& message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 10); // change text colour to green if request is successful

	std::cout << "\n" << message << "\n";
	Sleep(500); // sleep for 0.5 seconds before returning;

	// reset text colour back to white
	SetConsoleTextAttribute(hConsole, 15);
}


void Response::printFailure(const std::string& message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 12); // change text colour to red if request is unsuccessful

	std::cout << "\n" << message << "\n";
	Sleep(500); // sleep for 0.5 seconds before returning;

	// reset text colour back to white
	SetConsoleTextAttribute(hConsole, 15);
}
