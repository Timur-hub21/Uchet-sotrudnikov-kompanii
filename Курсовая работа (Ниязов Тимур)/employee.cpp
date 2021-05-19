#include "employee.h"
#include <iomanip>

Employee::Employee() {
	year = 0;
	month = 0;
	numberOfDaysOfTravel = 0;
	amountOfTravelExpensesForOneDay = 0.0;
}

std::ostream &operator<<(std::ostream &ostr, const Employee &employee) {
	return ostr << std::left << std::setw(14) << employee.surname << std::setw(10) << employee.name <<
		std::setw(15) << employee.patronymic << std::setw(5) << employee.year << std::setw(9) << employee.month <<
		std::setw(5) << employee.numberOfDaysOfTravel << std::setw(17) << employee.city <<
		std::fixed << std::setprecision(2) << employee.amountOfTravelExpensesForOneDay;
}

std::ifstream& operator>>(std::ifstream& ifstr, Employee& employee) {
	ifstr >> employee.surname >> employee.name >> employee.patronymic >> employee.year >> employee.month >>
		employee.numberOfDaysOfTravel >> employee.city >> employee.amountOfTravelExpensesForOneDay;
	return ifstr;
}

std::ofstream& operator<<(std::ofstream& ofstr, const Employee& employee) {
	ofstr << std::left << std::setw(14) << employee.surname << std::setw(10) << employee.name <<
		std::setw(15) << employee.patronymic << std::setw(5) << employee.year << std::setw(9) << employee.month <<
		std::setw(5) << employee.numberOfDaysOfTravel << std::setw(17) << employee.city <<
		std::fixed << std::setprecision(2) << employee.amountOfTravelExpensesForOneDay;
	return ofstr;
}

void Employee::setSurname(const std::string& surname) {
	this->surname.assign(surname, 0, 13);
}

void Employee::setName(const std::string& name) {
	this->name.assign(name, 0, 9);
}

void Employee::setPatronymic(const std::string& patronymic) {
	this->patronymic.assign(patronymic, 0, 14);
}

void Employee::setYear(const size_t year) {
	this->year = year;
}

void Employee::setMonth(const size_t month) {
	this->month = month;
}

void Employee::setNumberOfDaysOfTravel(const size_t numberOfDaysOfTravel) {
	this->numberOfDaysOfTravel = numberOfDaysOfTravel;
}

void Employee::setCity(const std::string& ñity) {
	this->city.assign(ñity, 0, 16);
}

void Employee::setAmountOfTravelExpensesForOneDay(const double& amountOfTravelExpensesForOneDay) {
	this->amountOfTravelExpensesForOneDay = amountOfTravelExpensesForOneDay;
}

const std::string& Employee::getSurname() const {
	return surname;
}

const std::string& Employee::getName() const {
	return name;
}

const std::string& Employee::getPatronymic() const {
	return patronymic;
}

size_t Employee::getYear() const {
	return year;
}

size_t Employee::getMonth() const {
	return month;
}

size_t Employee::getNumberOfDaysOfTravel() const {
	return numberOfDaysOfTravel;
}

const std::string &Employee::getCity() const {
	return city;
}

const double &Employee::getAmountOfTravelExpensesForOneDay() const {
	return amountOfTravelExpensesForOneDay;
}