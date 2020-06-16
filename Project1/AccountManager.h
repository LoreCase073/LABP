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
	
	int accountIdCounter = 1; 
	int transactionIdCounter = 1;

	vector<Conto> accounts;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& directory;
		ar& accountIdCounter;
		ar& transactionIdCounter;
		ar& accounts;
	}

public:
	AccountManager();
	AccountManager(string dir);

	void saveOnFile(string dir);
	AccountManager readFromFile(string dir);

	void createAccount(string name, string user);

	void incrementIdAccountCounter() {
		this->accountIdCounter++;
	}

	void incrementIdTransactionCounter() {
		this->transactionIdCounter++;
	}

	void deleteAccount(int id);

	void createTransaction(Type trans, int accountId, float import, Date d, int accountId2=0);

	void modifyTransaction(int accountId, int tid, float import, Date d);

	void eraseTransaction(int aid, int tid);


	int findAccountIndex(int id);

	float getAccountBalance(int id);

	string getAccountName(int id);

	string getAccountUser(int id);

	int getNumberOfAccounts();

	void visualizeAccounts();

	void visualizeTransactions(int d);

};

