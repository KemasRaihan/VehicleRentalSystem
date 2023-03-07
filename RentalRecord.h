#pragma once

#include "Customer.h"
#include "MyDate.h"


class RentalRecord {

public:
	RentalRecord();
	~RentalRecord();

	inline Customer* getCustomer() const;
	inline MyDate* getStartDate() const;
	inline MyDate* getEndDate() const;
	inline int calculateDiffInDays() const;

	friend std::istream& operator>>(std::istream& is, RentalRecord* record);
	friend std::ifstream& operator>>(std::ifstream& input, RentalRecord* record);
	friend std::ofstream& operator<<(std::ofstream& output, RentalRecord* record);

private:
	Customer* customer;
	MyDate** dates;

};

inline Customer* RentalRecord::getCustomer() const { return customer; }
inline int RentalRecord::calculateDiffInDays() const { return ((*dates[1]) - (*dates[0])); }

inline MyDate* RentalRecord::getStartDate() const { return dates[0]; }
inline MyDate* RentalRecord::getEndDate() const { return dates[1]; }
