#pragma once
#include <iostream>
#include <Windows.h>
// class for responses to user requests, contains functions that allow user to see messages before they return
class Response
{
public:
	static void printSuccess(const std::string& message);
	static void printFailure(const std::string& message);
	static inline void printReturn(const std::string& message);

private:
	Response();

public:
	// singleton design; remove copy operators
	Response(const Response&) = delete;
	void operator=(const Response&) = delete;
};

inline void Response::printReturn(const std::string& message)
{ 
	std::cout << "\n" << message << "\n\n";
	Sleep(1000); // sleep for one second before returning;
}





