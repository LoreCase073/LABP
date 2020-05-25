/*
 * Conto.h
 *
 *  Created on: 11 feb 2020
 *      Author: lorec
 */
#include <string>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "Transaction.h"
#ifndef CONTO_H_
#define CONTO_H_
using namespace std;

class Conto {
private:
	string user;
	string accountName;
	int id;
	int transCounter;
	float balance;
	vector<Transaction> transactions;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& user;
		ar& accountName;
		ar& id;
		ar& transCounter;
		ar& balance;
		ar& transactions;
	}


public:
	Conto(string p, string nc, int id);
	virtual ~Conto();

	void setUser(string x);
	string getUser();
	void setAccountName(string n);
	string getAccountName();
	float getBalance();
	int getId();
	int getTransCounter();
	void incrementCounter();

	//salvare su file
	void saveOnFile(string dir);

	void insertTransaction(string type, float import, int day, int month, int year, Conto* account2=NULL, bool receiver=false);
	//TODO cancellare trans e modificare

};

#endif /* CONTO_H_ */
