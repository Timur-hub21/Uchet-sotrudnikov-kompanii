#pragma once
#include <iostream>
#include <fstream>

class Account {
public:
	Account();
	friend std::ostream &operator<<(std::ostream &ostr, const Account &account);
	friend std::ifstream &operator>>(std::ifstream &ifstr, Account &account);
	friend std::ofstream &operator<<(std::ofstream &ofstr, const Account &account);
	void setLogin(const std::string &login);
	void setPassword(const std::string &password);
	void setAccessLevel(const size_t accessLevel);
	const std::string &getLogin() const;
	const std::string &getPassword() const;
	size_t getAccessLevel() const;

private:
	std::string login;
	std::string password;
	size_t accessLevel;
};