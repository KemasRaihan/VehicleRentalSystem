#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "ModifiedInputVehicle.h"
#include "Response.h"
#include "RentalRecord.h"
#include "MVector.h"

typedef MVector<RentalRecord> RentalHistory;

class Vehicle
{
public:
	Vehicle();
	~Vehicle();

	void display();
	void viewInfo();

	virtual inline int calculateCostPerDay() const = 0;

	virtual inline void writeDetailsToFile(std::ofstream& output) const = 0;

	void readRentalsFromFile();
	void writeRentalsToFile() const;

	inline double getAge() const;
	inline char* getMake() const;
	inline char* getModel() const;
	inline std::string getRegistrationNumber() const;
	inline RentalRecord* getRentalRecord(int index) const;
	inline int getNumberOfRentals() const;
	inline bool rentalHistoryIsEmpty() const;

	inline bool operator==(std::string registrationNumber);
	inline bool operator==(Vehicle* rhs);
	inline bool operator<(Vehicle& rhs);
	friend std::istream& operator>>(std::istream& is, Vehicle* vehicle);
	friend std::ostream& operator<<(std::ostream& os, Vehicle* vehicle);
	friend std::ifstream& operator>>(std::ifstream& input, Vehicle* vehicle);
	friend std::ofstream& operator<<(std::ofstream& output, const Vehicle* vehicle);



protected:
	static inline int capCheck(const int cost);

private:
	inline void rent();
	int inline calculateTotalRentalDays() const;
	int inline calculateTotalIncome() const;
	void viewRentalHistory();
	void viewRentalRecord(int index);

	std::string registrationNumber;
	char* make;
	char* model;
	double age;
	std::string filepath;
	RentalHistory* rentalHistory;
};

inline void Vehicle::rent()
{
	RentalRecord* record = new RentalRecord();
	std::cin >> record;
	rentalHistory->add(record);
	Response::printSuccess("Record successfully added!");
}

inline int Vehicle::calculateTotalRentalDays() const
{
	int totalNumOfDays = 0;

	// for each rental record,
	// calculate the difference in days between start and end date of rental,
	// then add to total
	for (int i = 0; i < getNumberOfRentals(); i++)
		totalNumOfDays += rentalHistory->getItem(i)->calculateDiffInDays();

	return totalNumOfDays;
}


inline int Vehicle::calculateTotalIncome() const
{
	return calculateCostPerDay() * calculateTotalRentalDays();
}


inline int Vehicle::capCheck(const int cost) { return (cost < 10) ? 10 : cost; }



inline double Vehicle::getAge() const { return age; }

inline char* Vehicle::getMake() const { return make; }

inline char* Vehicle::getModel() const { return model; }

inline std::string Vehicle::getRegistrationNumber() const { return registrationNumber; }

inline RentalRecord* Vehicle::getRentalRecord(int index) const { return rentalHistory->getItem(index); }

inline int Vehicle::getNumberOfRentals() const { return rentalHistory->getSize(); }

inline bool Vehicle::rentalHistoryIsEmpty() const { return (getNumberOfRentals() == 0); }

inline bool Vehicle::operator==(std::string registrationNumber) { return (this->registrationNumber == registrationNumber); }

inline bool Vehicle::operator==(Vehicle* rhs) { return (this->registrationNumber == rhs->registrationNumber); }
inline bool Vehicle::operator<(Vehicle& rhs) { return (registrationNumber < rhs.registrationNumber); }

