/*
 * Transaction.h
 *
 *  Created on: 11 feb 2020
 *      Author: lorec
 */

#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Date.h"
#ifndef TRANSACTION_H_
#define TRANSACTION_H_
using namespace std;

enum class Type { Gain, Expense, Transfer }; //tipi di transazioni: guadagno(gain), spesa(expense), trasferimento(transfer)

class Transaction {
private:
	//TODO: invece che string, fare opType class enum
	
	Type opType;
	float import;
	int transactionId;
	int accountIdTo;
	//TODO: togliere receiver e modificare id conti in idfrom e idto
	int accountIdFrom;
	//TODO: inserire data non come interi, ma come classe per controllare calendario gregoriano
	Date date = Date(1,1,1900);
	//serialization with boost
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & opType;
		ar & import;
		ar& accountIdTo;
		ar& accountIdFrom;
		ar& transactionId;
		ar& date;

	}


public:
	
	Transaction(Type t, float i, int idFrom, int tid, int d, int m, int y, int aidTo = 0);
	Transaction();
	
	Type getType();

	float getImport();

	void setImport(float i);

	int getAccountIdFrom();

	int getTransactionId();

	int getAccountIdTo();

	void setDate(int y, int m, int d);

	int getDay();

	int getMonth();

	int getYear();

	virtual ~Transaction();

	//TODO metodo per modificare transazione


};

#endif /* TRANSACTION_H_ */
