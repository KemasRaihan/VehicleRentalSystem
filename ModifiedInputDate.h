#pragma once
#include "ModifiedInput.h"

class ModifiedInputDate : public ModifiedInput
{
public:
	static int getValidMonth();
	static int getValidDay(const int month);

private:
	ModifiedInputDate();

public:
	ModifiedInputDate(const ModifiedInputDate&) = delete;
	void operator=(const ModifiedInputDate&) = delete;
};






