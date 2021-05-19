#pragma once
#include <iostream>
#include <fstream>

class Employee {
public:
	Employee();
	friend std::ostream &operator<<(std::ostream &ostr, const Employee &employee);
	friend std::ifstream &operator>>(std::ifstream &ifstr, Employee &employee);
	friend std::ofstream &operator<<(std::ofstream &ofstr, const Employee &employee);
	void setSurname(const std::string &surname);
	void setName(const std::string &name);
	void setPatronymic(const std::string &patronymic);
	void setYear(const size_t year);
	void setMonth(const size_t month);
	void setNumberOfDaysOfTravel(const size_t numberOfDaysOfTravel);
	void setCity(const std::string &city);
	void setAmountOfTravelExpensesForOneDay(const double &amountOfTravelExpensesForOneDay);
	const std::string &getSurname() const;
	const std::string &getName() const;
	const std::string &getPatronymic() const;
	size_t getYear() const;
	size_t getMonth() const;
	size_t getNumberOfDaysOfTravel() const;
	const std::string &getCity() const;
	const double &getAmountOfTravelExpensesForOneDay() const;

private:
	std::string surname;
	std::string name;
	std::string patronymic;
	std::size_t year;
	std::size_t month;
	size_t numberOfDaysOfTravel;
	std::string city;
	double amountOfTravelExpensesForOneDay;
};