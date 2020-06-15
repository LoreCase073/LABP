#pragma once
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace std;
class Date
{
private:
	int day;
	int month;
	int year;

	int validNumberOfDays(int y, int m, int d);
	//serialization with boost
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& day;
		ar& month;
		ar& year;

	}

public:
	Date(int d, int m, int y);

	int getDay();
	int getMonth();
	int getYear();
};

