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
	//vector<string> files;
	int accountCounter = 1; 
	vector<Conto> accounts;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& directory;
		ar& accountCounter;
		ar& accounts;
	}

public:
	AccountManager();
	AccountManager(string dir);

	void saveOnFile(string dir);
	AccountManager readFromFile(string dir);

	void createAccount(string name, string user);

	void incrementCounter() {
		this->accountCounter++;
	}

	void deleteAccount(int id);
	//transaction type: gain, expense, transfer from-to--this case need a second id account
	void createTransaction(string trans, int accountId, float import, int day, int month, int year, int accountId2=-1);

	void modifyTransaction(int accountId, int tid, float import, int day, int month, int year);

	void eraseTransaction(int aid, int tid);
	//ritorna -1 se non ha trovato l'account
	int findAccountIndex(int id);

	float getAccountBalance(int id);

	string getAccountName(int id);

	string getAccountUser(int id);

	int getNumberOfAccounts();

	int getNumberOfTransactions(int id);

	void visualizeAccounts();

	void visualizeTransactions(int d);

};

