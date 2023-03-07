#pragma once
#include "ModifiedInput.h"

class ModifiedInputCustomer : public ModifiedInput
{
public:
	static std::string getValidPhoneNumber();


private:
	ModifiedInputCustomer();

public:
	ModifiedInputCustomer(const ModifiedInputCustomer&) = delete;
	void operator=(const ModifiedInputCustomer&) = delete;
};