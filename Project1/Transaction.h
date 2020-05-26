/*
 * Transaction.h
 *
 *  Created on: 11 feb 2020
 *      Author: lorec
 */

#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#ifndef TRANSACTION_H_
#define TRANSACTION_H_
using namespace std;

class Transaction {
private:
	string opType; //tipi di transazioni: guadagno(gain), spesa(expense), trasferimento(transfer)
	float import;
	string account;
	string account2; //entra in gioco quando si ha un trasferimento da un conto ad un altro
	int tid2;
	int aid2;
	bool receiver;
	int aid;
	int tid;
	int day;
	int month;
	int year;
	//serialization with boost
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & opType;
		ar & import;
		ar & account;
		ar & account2;
		ar& aid2;
		ar& tid2;
		ar & receiver;
		ar& aid;
		ar& tid;
		ar& day;
		ar& month;
		ar& year;

	}


public:
	Transaction(string t, float i, string a, int id, int tid, int d, int m, int y, string a2 = "", int aid2 = 0, int tid2 = 0 , bool receiver = false);
	Transaction();
	virtual ~Transaction();

	//TODO metodo per modificare transazione


};

#endif /* TRANSACTION_H_ */
