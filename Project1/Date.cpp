#include "Date.h"


int Date::validNumberOfDays(int y, int m, int d)
{
	if (d < 1 || d>31)
		throw range_error("Invalid day value!");

	if ((m == 4 || m == 6 || m == 9 || m == 11) && d == 31)
		throw range_error("Invalid day value for the selected month!");

	if (m == 2) {
		if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
			if (d > 29)
				throw range_error("Invalid day value for the selected month!");
		}
		else {
			if(d>28)
				throw range_error("Invalid day value for the selected month!");
		}
	}

	return d;
}

Date::Date(int d, int m, int y)
{
	
		if (y > 1899)
			this->year = y;
		else
			throw range_error("Year not valid! Insert a year > 1899");
		if (m > 0 && m < 13)
			this->month = m;
		else
			throw range_error("Month not valid, insert a month between 1 and 12");
		this->day = validNumberOfDays(y, m, d);
	


}

int Date::getDay()
{
	return this->day;
}

int Date::getMonth()
{
	return this->month;
}

int Date::getYear()
{
	return this->year;
}
