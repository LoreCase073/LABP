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
#ifndef CONTO_H_
#define CONTO_H_
#include "Transaction.h"

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
	//nome possessore, nome conto, id
	Conto(string p, string nc, int id);
	Conto(const Conto& copy);
	Conto();
	virtual ~Conto();

	void setUser(string x);
	string getUser();
	void setAccountName(string n);
	string getAccountName();
	float getBalance();
	int getId();
	int getTransCounter();
	void incrementCounter();

	//tipo transazione: gain, transfer or expense
	//poi importo, giorno, mese, anno, secondo conto se transfer, se ricevente oppure no
	void insertTransfer(float import, int day, int month, int year, Conto* account2=NULL);
	
	void modifyTrans(int tid, float import, int day, int month, int year, int* ar);

	void eraseTransfer(int tid, int* ar);

	void insertGain(float import, int day, int month, int year);

	void insertExpense(float import, int day, int month, int year);

	int getNumberOfTrans();

	void visualizeTransactions();


};

#endif /* CONTO_H_ */