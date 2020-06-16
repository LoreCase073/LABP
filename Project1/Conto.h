/*
 * Conto.h
 *
 *  Created on: 11 feb 2020
 *      Author: lorec
 */
#include <string>
#include <list>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#ifndef CONTO_H_
#define CONTO_H_
#include "Transaction.h"

using namespace std;

class Conto {
private:
	string user;
	string accountName;
	int id;
	float balance;
	list <Transaction> transactions;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& user;
		ar& accountName;
		ar& id;
		ar& balance;
		ar& transactions;
	}


public:
	//nome possessore, nome conto, id
	Conto(string p, string nc, int id);
	Conto(const Conto& copy);
	Conto();
	~Conto();

	void setUser(string x);
	string getUser();
	void setAccountName(string n);
	string getAccountName();
	float getBalance();
	int getId();

	void insertTransaction(Type t,int tid, float import, Date d, Conto* account2=NULL);
	
	void modifyTrans(int tid, float import, Date d, int* ar);

	void eraseTrans(int tid, int* ar);

	

	void visualizeTransactions();


};

#endif /* CONTO_H_ */