#pragma once
#include "account.h"
#include <vector>

class Interaction {
public:
	Interaction(const char *const pathToAccountDatabase);
	void signIn(Account &account) const;
	void createAccount(const size_t accessLevel);
	void saveAccountDatabase(const char *const path) const;
	const std::vector<Account> &getAccounts() const;

private:
	std::vector<Account> accounts;
};

bool isLoginFound(const std::vector<Account> &accounts, const std::string &login, int &foundIndex);
bool isLoginFound(const std::vector<Account> &accounts, const std::string &login);