#include "Account.h"
#include <iomanip>

Account::Account() {
	accessLevel = 0;
}

std::ostream &operator<<(std::ostream &ostr, const Account &account) {
	return ostr << std::left << std::setw(17) << account.login << std::setw(15) << account.password <<
		account.accessLevel;
}

std::ifstream &operator>>(std::ifstream &ifstr, Account &account) {
	ifstr >> account.login >> account.password >> account.accessLevel;
	return ifstr;
}

std::ofstream &operator<<(std::ofstream &ofstr, const Account &account) {
	ofstr << std::left << std::setw(17) << account.login << std::setw(15) << account.password <<
		account.accessLevel;
	return ofstr;
}

void Account::setLogin(const std::string &login) {
	this->login.assign(login, 0, 16);
}

void Account::setPassword(const std::string &password) {
	this->password.assign(password, 0, 14);
}

void Account::setAccessLevel(const size_t accessLevel) {
	this->accessLevel = accessLevel;
}

const std::string &Account::getLogin() const {
	return login;
}

const std::string &Account::getPassword() const {
	return password;
}

size_t Account::getAccessLevel() const {
	return accessLevel;
}