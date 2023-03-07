#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ModifiedInputCustomer.h"


class Customer {
public:
	Customer();
	~Customer();

	inline std::string getName() const;
	inline std::string getAddress() const;
	inline std::string getPhoneNumber() const;

	friend std::istream& operator>>(std::istream& is, Customer* customer);
	friend std::ostream& operator<<(std::ostream & os, Customer * customer);
	friend std::ifstream& operator>>(std::ifstream& input, Customer* customer);
	friend std::ofstream& operator<<(std::ofstream& output, Customer* customer);

private:
	std::string name, address, phoneNumber;

};

inline std::string Customer::getName() const { return name; }
inline std::string Customer::getAddress() const { return address; }
inline std::string Customer::getPhoneNumber() const { return phoneNumber; }