#pragma once
#include "account.h"
#include "employee.h"
#include <vector>

const char *const ACCOUNTS_PATH = "Accounts.txt";
const char *const EMPLOYEES_PATH = "Employees.txt";

const size_t USER = 1;
const size_t ADMIN = 2;

class User {
public:
	User(const Account &account, const char *const pathToEmployeeDatabase);
	void viewTotalAmountOfTravelExpenses() const;
	void viewFrequentlyVisitedCities();
	void sortEmployeeData();
	void viewEmployeeData() const;
	void saveEmployeeDatabase(const char *const pathToEmployeeDatabase) const;
	const Account &getAccount() const;
	const std::vector<Employee> &getEmployees() const;

protected:
	Account account;
	std::vector<Employee> employees;
};

bool isCityFound(const std::vector<std::string> &cities, const std::string &city);

class Admin : public User {
public:
	Admin(const Account &account, const char *const pathToAccountDatabase, const char *const pathToEmployeeDatabase);
	void addAccountData();
	void editAccountData();
	void removeAccountData();
	void sortAccountData();
	void viewAccountData() const;
	void saveAccountDatabase(const char *const pathToAccountDatabase) const;
	void addEmployeeData();
	void editEmployeeData();
	void removeEmployeeData();
	const std::vector<Account> &getAccounts() const;

protected:
	std::vector<Account> accounts;
};

void sortByLogin(std::vector<Account> &accounts);
void sortByPassword(std::vector<Account> &accounts);
void sortByAccessLevel(std::vector<Account> &accounts);

void sortBySurname(std::vector<Employee> &employees);
void sortByNumberOfDaysOfTravel(std::vector<Employee> &employees);
void sortByAmountOfTravelExpensesForOneDay(std::vector<Employee> &employees);

void run();
void openUserModule(User &user);
void openAdminModule(Admin &admin);
void openAccountDatabase(Admin &admin);
void openEmployeeDatabase(Admin &admin);