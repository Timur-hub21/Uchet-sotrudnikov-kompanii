#include "interaction.h"

Interaction::Interaction(const char *const pathToAccountDatabase) {
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

void Interaction::signIn(Account &account) const {
	if (!accounts.empty()) {
		std::string str;
		int foundIndex;
		while (true) {
			std::cout << "�����: ";
			std::cin >> str;
			if (isLoginFound(accounts, str, foundIndex)) {
				while (true) {
					std::cout << "������: ";
					std::cin >> str;
					if (accounts[foundIndex].getPassword() == str) {
						account.setPassword(str);
						account.setAccessLevel(accounts[foundIndex].getAccessLevel());

						std::cout << "\n�������: ���� ������� ��������!\n";
						return;
					}

					std::cout << "\n�������: �������� ������!\n\n";
				}
			}

			std::cout << "\n�������: ����� �� ������!\n\n";
		}
	}

	std::cout << "�������: ���� ������ �����!\n";
}

void Interaction::createAccount(const size_t accessLevel) {
	Account account;
	std::string str;
	while (true) {
		std::cout << "�����: ";
		std::cin >> str;
		if (!isLoginFound(accounts, str)) {
			account.setLogin(str);
			
			std::cout << "������: ";
			std::cin >> str;
			account.setPassword(str);

			account.setAccessLevel(accessLevel);
			
			accounts.push_back(account);
			std::cout << "\n�������: ������� ������� ������!\n";
			return;
		}

		std::cout << "\n�������: ����� ����� ��� ����������!\n\n";
	}
}

void Interaction::saveAccountDatabase(const char *const pathToAccountDatabase) const {
	std::ofstream ofstr(pathToAccountDatabase);
	for (size_t i = 0; i < accounts.size(); ++i) {
		ofstr << accounts[i];
		if (i + 1 < accounts.size()) {
			ofstr << std::endl;
		}
	}
	ofstr.close();
}

const std::vector<Account> &Interaction::getAccounts() const {
	return accounts;
}

bool isLoginFound(const std::vector<Account> &accounts, const std::string &login, int &foundIndex) {
	for (size_t i = 0; i < accounts.size(); ++i) {
		if (accounts[i].getLogin() == login) {
			foundIndex = i;
			return true;
		}
	}

	foundIndex = -1;
	return false;
}

bool isLoginFound(const std::vector<Account> &accounts, const std::string &login) {
	for (const Account &account : accounts) {
		if (account.getLogin() == login) {
			return true;
		}
	}

	return false;
}