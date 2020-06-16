/*
 * Transaction.cpp
 *
 *  Created on: 11 feb 2020
 *      Author: lorec
 */

#include <string>
#include "Transaction.h"
using namespace std;


Transaction::Transaction(Type t, float i,int id, int tid, int d, int m, int y, int aid2) {
	this->opType=t;
	this->import=i;
	this->accountIdFrom=id;
	this->transactionId=tid;
	
	this->accountIdTo = aid2;

	this->date = Date(d, m, y);

}

Transaction::Transaction() {

}

Type Transaction::getType()
{
	Type t = this->opType;
	return t;
}

float Transaction::getImport()
{
	return this->import;
}

void Transaction::setImport(float i)
{
	this->import = i;
}

int Transaction::getAccountIdFrom()
{
	return this->accountIdFrom;
}

int Transaction::getTransactionId()
{
	return this->transactionId;
}

int Transaction::getAccountIdTo()
{
	return this->accountIdTo;
}

void Transaction::setDate(int y, int m, int d)
{
	this->date = Date(d, m, y);
}



int Transaction::getDay()
{
	return this->date.getDay();
}


int Transaction::getMonth()
{
	return this->date.getMonth();
}



int Transaction::getYear()
{
	return this->date.getYear();
}

Transaction::~Transaction() {
	// TODO Auto-generated destructor stub
}

