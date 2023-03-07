#include "Customer.h"


Customer::Customer() : name(""), address(""), phoneNumber("") {}
Customer::~Customer(){}

std::istream& operator>>(std::istream& is, Customer* customer)
{
	std::cout << "Enter your name (no spaces included): ";
	getline(std::cin >> std::ws, customer->name);
	std::cout << "Enter your address (no spaces included): ";
	getline(std::cin >> std::ws, customer->address);

	// get valid phone number for custoemr
	customer->phoneNumber = ModifiedInputCustomer::getValidPhoneNumber();

	return is;

}

std::ostream& operator<<(std::ostream& os, Customer* customer)
{
	os << "\nCustomer name: " << customer->name << "\nCustomer address: " << customer->address << "\nCustomer number: " << customer->phoneNumber;
	return os;
}

std::ifstream& operator>>(std::ifstream& input, Customer* customer)
{
	// retrieve customer details from file
	input >> customer->name >> customer->address >> customer->phoneNumber;
	return input;
}

std::ofstream& operator<<(std::ofstream& output, Customer* customer)
{
	// write customer details to file
	output << customer->name << " ";
	output << customer->address << " ";
	output << customer->phoneNumber;
	return output;
}