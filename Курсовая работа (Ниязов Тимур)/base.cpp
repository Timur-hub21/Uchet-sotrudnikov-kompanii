#include "base.h"
#include <iomanip>
#include "interaction.h"

User::User(const Account &account, const char *const pathToEmployeeDatabase) {
	this->account.setLogin(account.getLogin());
	this->account.setPassword(account.getPassword());
	this->account.setAccessLevel(USER);

	std::ifstream ifstr(pathToEmployeeDatabase);
	if (ifstr.is_open()) {
		Employee employee;
		while (!ifstr.eof()) {
			ifstr >> employee;
			employees.push_back(employee);
		}
		ifstr.close();
	}
}

void User::viewTotalAmountOfTravelExpenses() const {
	if (!employees.empty()) {
		std::string str;
		std::cout << "�����: ";
		std::cin >> str;
		size_t month = atoi(str.substr(0, 2).c_str());

		double totalAmountOfTravelExpenses = 0.0;
		for (const Employee &employee : employees) {
			if (employee.getMonth() == month) {
				totalAmountOfTravelExpenses += employee.getAmountOfTravelExpensesForOneDay() *
					employee.getNumberOfDaysOfTravel();
			}
		}

		std::cout << "\n����� ����� ��������������� �������� �� ��������� �����: " <<
			std::fixed << std::setprecision(2) << totalAmountOfTravelExpenses << std::endl;
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

void User::viewFrequentlyVisitedCities() {
	if (!employees.empty()) {
		size_t firstMonth, lastMonth;
		std::string str;
		
		std::cout << "������ �����: ";
		std::cin >> str;
		firstMonth = atoi(str.substr(0, 2).c_str());

		std::cout << "��������� �����: ";
		std::cin >> str;
		lastMonth = atoi(str.substr(0, 2).c_str());

		sortByNumberOfDaysOfTravel(employees);

		std::vector<std::string> cities;
		for (const Employee &employee : employees) {
			if ((employee.getMonth() >= firstMonth && employee.getMonth() <= lastMonth) &&
				!isCityFound(cities, employee.getCity())) {
				cities.push_back(employee.getCity());
			}
		}

		std::cout << std::endl << std::left << std::setw(5) << '#' << std::setw(17) << "�����" <<
			"����� ���������� ���� ������������\n";
		std::cout << std::string(59, '�') << std::endl;

		size_t totalNumberOfDaysOfTravel;
		for (size_t i = 0; i < cities.size(); ++i) {
			totalNumberOfDaysOfTravel = 0;
			for (const Employee &employee : employees) {
				if ((employee.getMonth() >= firstMonth && employee.getMonth() <= lastMonth) &&
					employee.getCity() == cities[i]) {
					totalNumberOfDaysOfTravel += employee.getNumberOfDaysOfTravel();
				}
			}

			std::cout << std::left << std::setw(5) << i + 1 << std::setw(17) << cities[i] << totalNumberOfDaysOfTravel <<
				std::endl;
		}
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

void User::sortEmployeeData() {
	if (!employees.empty()) {
		std::cout << "1. �� �������\n";
		std::cout << "2. �� ���������� ���� ������������\n";
		std::cout << "3. �� ����� ��������������� �������� �� ���� �����\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '1' && ch <= '3'));

		switch (ch) {
		case '1':
			sortBySurname(employees);
			break;

		case '2':
			sortByNumberOfDaysOfTravel(employees);
			break;

		case '3':
			sortByAmountOfTravelExpensesForOneDay(employees);
		}
		
		std::cout << "\n�������: ������ ������� �������������!\n";
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

void User::viewEmployeeData() const {
	std::cout << std::left << std::setw(5) << '#' << std::setw(14) << "�������" << std::setw(10) << "���" <<
		std::setw(15) << "��������" << std::setw(5) << "���" << std::setw(9) << "�����" <<
		std::setw(5) << "���" << std::setw(17) << "�����" << "����� ��������������� �������� �� ���� �����\n";
	std::cout << std::string(127, '�') << std::endl;

	for (size_t i = 0; i < employees.size(); ++i) {
		std::cout << std::left << std::setw(5) << i + 1 << employees[i] << std::endl;
	}
}

void User::saveEmployeeDatabase(const char *const pathToEmployeeDatabase) const {
	std::ofstream ofstr(pathToEmployeeDatabase);
	for (size_t i = 0; i < employees.size(); ++i) {
		ofstr << employees[i];
		if (i + 1 < employees.size()) {
			ofstr << std::endl;
		}
	}
	ofstr.close();
}

const Account &User::getAccount() const {
	return account;
}

const std::vector<Employee> &User::getEmployees() const {
	return employees;
}

bool isCityFound(const std::vector<std::string> &cities, const std::string &city) {
	for (size_t i = 0; i < cities.size(); ++i) {
		if (cities[i] == city) {
			return true;
		}
	}

	return false;
}

Admin::Admin(const Account &account, const char *const pathToAccountDatabase, const char *const pathToEmployeeDatabase)
	: User(account, pathToEmployeeDatabase) {
	this->account.setAccessLevel(ADMIN);

	std::ifstream ifstr(pathToAccountDatabase);
	if (ifstr.is_open()) {
		Account account;
		while (!ifstr.eof()) {
			ifstr >> account;
			accounts.push_back(account);
		}
		ifstr.close();
	}
}

void Admin::addAccountData() {
	Account account;
	std::string str;

	while (true) {
		std::cout << "�����: ";
		std::cin >> str;
		if (!isLoginFound(accounts, str)) {
			account.setLogin(str);
			break;
		}

		std::cout << "\n�������: ����� ����� ��� ����������!\n\n";
	}

	std::cout << "������: ";
	std::cin >> str;
	account.setPassword(str);

	std::cout << "������� �������: ";
	std::cin >> str;
	account.setAccessLevel(atoi(str.substr(0, 1).c_str()));

	accounts.push_back(account);
	std::cout << "\n�������: ������ ������� ���������!\n";
}

void Admin::editAccountData() {
	if (!accounts.empty()) {
		viewAccountData();

		size_t recordNumber;
		std::string str;
		while (true) {
			std::cout << "\n����� ������: ";
			std::cin >> str;
			recordNumber = atoi(str.c_str());
			if (recordNumber > 0 && recordNumber <= accounts.size()) {
				break;
			}

			std::cout << "\n�������: ������ ������ ������ �� ����������!\n";
		}

		std::cout << "\n1. �����\n";
		std::cout << "2. ������\n";
		std::cout << "3. ������� �������\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '1' && ch <= '3'));

		switch (ch) {
		case '1':
			while (true) {
				std::cout << "\n�����: ";
				std::cin >> str;
				if (!isLoginFound(accounts, str)) {
					accounts[recordNumber - 1].setLogin(str);
					break;
				}

				std::cout << "\n�������: ����� ����� ��� ����������!\n";
			}
			break;

		case '2':
			std::cout << "\n������: ";
			std::cin >> str;
			accounts[recordNumber - 1].setPassword(str);
			break;

		case '3':
			std::cout << "\n������� �������: ";
			std::cin >> str;
			accounts[recordNumber - 1].setAccessLevel(atoi(str.substr(0, 1).c_str()));
		}

		std::cout << "\n�������: ������ ������� ���������������!\n";
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

void Admin::removeAccountData() {
	if (!accounts.empty()) {
		viewAccountData();

		size_t recordNumber;
		std::string str;
		while (true) {
			std::cout << "\n����� ������: ";
			std::cin >> str;
			recordNumber = atoi(str.c_str());
			if (recordNumber > 0 && recordNumber <= accounts.size()) {
				break;
			}

			std::cout << "\n�������: ������ ������ ������ �� ����������!\n";
		}

		accounts.erase(accounts.begin() + recordNumber - 1);
		std::cout << "\n�������: ������ ������� �������!\n";
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

void Admin::sortAccountData() {
	if (!accounts.empty()) {
		std::cout << "1. �� ������\n";
		std::cout << "2. �� ������\n";
		std::cout << "3. �� ������ �������\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '1' && ch <= '3'));

		switch (ch) {
		case '1':
			sortByLogin(accounts);
			break;

		case '2':
			sortByPassword(accounts);
			break;

		case '3':
			sortByAccessLevel(accounts);
		}

		std::cout << "\n�������: ������ ������� �������������!\n";
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

void Admin::viewAccountData() const {
	std::cout << std::left << std::setw(5) << '#' << std::setw(17) << "�����" << std::setw(15) << "������" <<
		"������� �������\n";
	std::cout << std::string(55, '�') << std::endl;

	for (size_t i = 0; i < accounts.size(); ++i) {
		std::cout << std::left << std::setw(5) << i + 1 << accounts[i] << std::endl;
	}
}

void Admin::saveAccountDatabase(const char *const pathToAccountDatabase) const {
	std::ofstream ofstr(pathToAccountDatabase);
	for (size_t i = 0; i < accounts.size(); ++i) {
		ofstr << accounts[i];
		if (i + 1 < accounts.size()) {
			ofstr << std::endl;
		}
	}
	ofstr.close();
}

void Admin::addEmployeeData() {
	Employee employee;
	std::string str;

	std::cout << "�������: ";
	std::cin >> str;
	employee.setSurname(str);

	std::cout << "���: ";
	std::cin >> str;
	employee.setName(str);

	std::cout << "��������: ";
	std::cin >> str;
	employee.setPatronymic(str);

	std::cout << "���: ";
	std::cin >> str;
	employee.setYear(atoi(str.substr(0, 4).c_str()));

	std::cout << "�����: ";
	std::cin >> str;
	employee.setMonth(atoi(str.substr(0, 2).c_str()));

	std::cout << "���������� ���� ������������: ";
	std::cin >> str;
	employee.setNumberOfDaysOfTravel(atoi(str.substr(0, 2).c_str()));

	std::cout << "�����: ";
	std::cin >> str;
	employee.setCity(str.substr(0, 16));

	std::cout << "����� ��������������� �������� �� ���� �����: ";
	std::cin >> str;
	employee.setAmountOfTravelExpensesForOneDay(atof(str.c_str()));

	employees.push_back(employee);
	std::cout << "\n�������: ������ ������� ���������!\n";
}

void Admin::editEmployeeData() {
	if (!employees.empty()) {
		viewEmployeeData();

		size_t recordNumber;
		std::string str;
		while (true) {
			std::cout << "\n����� ������: ";
			std::cin >> str;
			recordNumber = atoi(str.c_str());
			if (recordNumber > 0 && recordNumber <= employees.size()) {
				break;
			}

			std::cout << "\n�������: ������ ������ ������ �� ����������!\n";
		}

		std::cout << "\n1. �������\n";
		std::cout << "2. ���\n";
		std::cout << "3. ��������\n";
		std::cout << "4. ���\n";
		std::cout << "5. �����\n";
		std::cout << "6. ���������� ���� ������������\n";
		std::cout << "7. �����\n";
		std::cout << "8. ����� ��������������� �������� �� ���� �����\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '1' && ch <= '8'));

		switch (ch) {
		case '1':
			std::cout << "\n�������: ";
			std::cin >> str;
			employees[recordNumber - 1].setSurname(str);
			break;

		case '2':
			std::cout << "\n���: ";
			std::cin >> str;
			employees[recordNumber - 1].setName(str);
			break;

		case '3':
			std::cout << "\n��������: ";
			std::cin >> str;
			employees[recordNumber - 1].setPatronymic(str);
			break;

		case '4':
			std::cout << "\n���: ";
			std::cin >> str;
			employees[recordNumber - 1].setYear(atoi(str.substr(0, 4).c_str()));
			break;

		case '5':
			std::cout << "\n�����: ";
			std::cin >> str;
			employees[recordNumber - 1].setMonth(atoi(str.substr(0, 2).c_str()));
			break;

		case '6':
			std::cout << "\n���������� ���� ������������: ";
			std::cin >> str;
			employees[recordNumber - 1].setNumberOfDaysOfTravel(atoi(str.substr(0, 2).c_str()));
			break;

		case '7':
			std::cout << "\n�����: ";
			std::cin >> str;
			employees[recordNumber - 1].setCity(str.substr(0, 16));
			break;

		case '8':
			std::cout << "\n����� ��������������� �������� �� ���� �����: ";
			std::cin >> str;
			employees[recordNumber - 1].setAmountOfTravelExpensesForOneDay(atof(str.c_str()));
		}

		std::cout << "\n�������: ������ ������� ���������������!\n";
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

void Admin::removeEmployeeData() {
	if (!employees.empty()) {
		viewEmployeeData();

		size_t recordNumber;
		std::string str;
		while (true) {
			std::cout << "\n����� ������: ";
			std::cin >> str;
			recordNumber = atoi(str.c_str());
			if (recordNumber > 0 && recordNumber <= employees.size()) {
				break;
			}

			std::cout << "\n�������: ������ ������ ������ �� ����������!\n";
		}

		employees.erase(employees.begin() + recordNumber - 1);
		std::cout << "\n�������: ������ ������� �������!\n";
	}
	else {
		std::cout << "�������: ���� ������ �����!\n";
	}
}

const std::vector<Account> &Admin::getAccounts() const {
	return accounts;
}

void sortByLogin(std::vector<Account> &accounts) {
	for (size_t i = 0; i < accounts.size() - 1; ++i) {
		for (size_t j = i + 1; j < accounts.size(); ++j) {
			if (accounts[i].getLogin() > accounts[j].getLogin()) {
				std::swap(accounts[i], accounts[j]);
			}
		}
	}
}

void sortByPassword(std::vector<Account> &accounts) {
	for (size_t i = 0; i < accounts.size() - 1; ++i) {
		for (size_t j = i + 1; j < accounts.size(); ++j) {
			if (accounts[i].getPassword() > accounts[j].getPassword()) {
				std::swap(accounts[i], accounts[j]);
			}
		}
	}
}

void sortByAccessLevel(std::vector<Account> &accounts) {
	for (size_t i = 0; i < accounts.size() - 1; ++i) {
		for (size_t j = i + 1; j < accounts.size(); ++j) {
			if (accounts[i].getAccessLevel() > accounts[j].getAccessLevel()) {
				std::swap(accounts[i], accounts[j]);
			}
		}
	}
}

void sortBySurname(std::vector<Employee> &employees) {
	for (size_t i = 0; i < employees.size() - 1; ++i) {
		for (size_t j = i + 1; j < employees.size(); ++j) {
			if (employees[i].getSurname() > employees[j].getSurname()) {
				std::swap(employees[i], employees[j]);
			}
		}
	}
}

void sortByNumberOfDaysOfTravel(std::vector<Employee> &employees) {
	for (size_t i = 0; i < employees.size() - 1; ++i) {
		for (size_t j = i + 1; j < employees.size(); ++j) {
			if (employees[i].getNumberOfDaysOfTravel() < employees[j].getNumberOfDaysOfTravel()) {
				std::swap(employees[i], employees[j]);
			}
		}
	}
}

void sortByAmountOfTravelExpensesForOneDay(std::vector<Employee> &employees) {
	for (size_t i = 0; i < employees.size() - 1; ++i) {
		for (size_t j = i + 1; j < employees.size(); ++j) {
			if (employees[i].getAmountOfTravelExpensesForOneDay() < employees[j].getAmountOfTravelExpensesForOneDay()) {
				std::swap(employees[i], employees[j]);
			}
		}
	}
}

void run() {
	Interaction *interaction = new Interaction(ACCOUNTS_PATH);
	while (true) {
		std::cout << "1. �����\n";
		std::cout << "2. ������� �������\n";
		std::cout << "0. ��������� ������\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '0' && ch <= '2'));

		std::cout << std::endl;
		if (ch == '1') {
			Account account;
			interaction->signIn(account);
			if (account.getAccessLevel() == USER) {
				delete interaction;
				User user(account, EMPLOYEES_PATH);
				std::cout << std::endl;
				openUserModule(user);
				interaction = new Interaction(ACCOUNTS_PATH);
			}
			else if (account.getAccessLevel() == ADMIN) {
				delete interaction;
				Admin admin(account, ACCOUNTS_PATH, EMPLOYEES_PATH);
				std::cout << std::endl;
				openAdminModule(admin);
				interaction = new Interaction(ACCOUNTS_PATH);
			}
		}
		else if (ch == '2') {
			bool isAdminFound = false;
			for (const Account& account : interaction->getAccounts()) {
				if (account.getAccessLevel() == ADMIN) {
					isAdminFound = true;
					break;
				}
			}

			interaction->createAccount(isAdminFound ? USER : ADMIN);
			interaction->saveAccountDatabase(ACCOUNTS_PATH);
		}
		else {
			delete interaction;
			std::cout << "�������: ������ ���������!\n";
			return;
		}
		std::cout << std::endl;
	}
}

void openUserModule(User &user) {
	while (true) {
		std::cout << "1. ���������� ����� ����� ��������������� ��������\n";
		std::cout << "2. ���������� ����� ���������� ������\n";
		std::cout << "3. ������������� ������\n";
		std::cout << "4. ���������� ������\n";
		std::cout << "0. �����\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '0' && ch <= '4'));

		switch (ch) {
		case '1':
			std::cout << std::endl;
			user.viewTotalAmountOfTravelExpenses();
			break;

		case '2':
			std::cout << std::endl;
			user.viewFrequentlyVisitedCities();
			break;

		case '3':
			std::cout << std::endl;
			user.sortEmployeeData();
			break;

		case '4':
			std::cout << std::endl;
			user.viewEmployeeData();
			break;

		case '0':
			return;
		}
		std::cout << std::endl;
	}
}

void openAdminModule(Admin &admin) {
	while (true) {
		std::cout << "1. ������� ���� ������ ���������\n";
		std::cout << "2. ������� ���� ������ �����������\n";
		std::cout << "0. �����\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '0' && ch <= '2'));
		
		switch (ch) {
		case '1':
			std::cout << std::endl;
			openAccountDatabase(admin);
			break;

		case '2':
			std::cout << std::endl;
			openEmployeeDatabase(admin);
			break;

		case '0':
			return;
		}
		std::cout << std::endl;
	}
}

void openAccountDatabase(Admin &admin) {
	while (true) {
		std::cout << "1. �������� ������\n";
		std::cout << "2. ������������� ������\n";
		std::cout << "3. ������� ������\n";
		std::cout << "4. ������������� ������\n";
		std::cout << "5. ���������� ������\n";
		std::cout << "0. ��������� �����\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '0' && ch <= '5'));

		switch (ch) {
		case '1':
			std::cout << std::endl;
			admin.addAccountData();
			admin.saveAccountDatabase(ACCOUNTS_PATH);
			break;

		case '2':
			std::cout << std::endl;
			admin.editAccountData();
			admin.saveAccountDatabase(ACCOUNTS_PATH);
			break;

		case '3':
			std::cout << std::endl;
			admin.removeAccountData();
			if (!admin.getAccounts().empty()) {
				admin.saveAccountDatabase(ACCOUNTS_PATH);
			}
			else {
				remove(ACCOUNTS_PATH);
			}
			break;

		case '4':
			std::cout << std::endl;
			admin.sortAccountData();
			break;

		case '5':
			std::cout << std::endl;
			admin.viewAccountData();
			break;

		case '0':
			return;
		}
		std::cout << std::endl;
	}
}

void openEmployeeDatabase(Admin &admin) {
	while (true) {
		std::cout << "1. �������� ������\n";
		std::cout << "2. ������������� ������\n";
		std::cout << "3. ������� ������\n";
		std::cout << "4. ���������� ����� ����� ��������������� ��������\n";
		std::cout << "5. ���������� ����� ���������� ������\n";
		std::cout << "6. ������������� ������\n";
		std::cout << "7. ���������� ������\n";
		std::cout << "0. ��������� �����\n";

		char ch;
		std::cout << "\n��� �����: ";
		do {
			std::cin >> ch;
		} while (!(ch >= '0' && ch <= '7'));

		switch (ch) {
		case '1':
			std::cout << std::endl;
			admin.addEmployeeData();
			admin.saveEmployeeDatabase(EMPLOYEES_PATH);
			break;

		case '2':
			std::cout << std::endl;
			admin.editEmployeeData();
			admin.saveEmployeeDatabase(EMPLOYEES_PATH);
			break;

		case '3':
			std::cout << std::endl;
			admin.removeEmployeeData();
			if (!admin.getEmployees().empty()) {
				admin.saveEmployeeDatabase(EMPLOYEES_PATH);
			}
			else {
				remove(EMPLOYEES_PATH);
			}
			break;

		case '4':
			std::cout << std::endl;
			admin.viewTotalAmountOfTravelExpenses();
			break;

		case '5':
			std::cout << std::endl;
			admin.viewFrequentlyVisitedCities();
			break;

		case '6':
			std::cout << std::endl;
			admin.sortEmployeeData();
			break;

		case '7':
			std::cout << std::endl;
			admin.viewEmployeeData();
			break;

		case '0':
			return;
		}
		std::cout << std::endl;
	}
}