#pragma once
#include <string>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <direct.h>
#include "Transaction.h"
#include "Conto.h"

using namespace std;

class AccountManager
{
private:
	string directory;
	vector<string> files;
	int accountCounter = 1; 
	vector<Conto> accounts;


public:
	AccountManager();
	AccountManager(string dir);

	void createAccount(string name, string user);

	void incrementCounter() {
		this->accountCounter++;
	}

	void deleteAccount(int id);

};

