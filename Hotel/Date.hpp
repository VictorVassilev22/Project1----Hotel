#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<cmath>


const unsigned MAX_YEAR = 2100;
const unsigned MIN_YEAR = 2020;
const unsigned MAX_DAYS_YEAR= 365;
const unsigned MAX_MONTH = 12;
const unsigned MIN_MONTH = 1;
const unsigned MIN_DAY = 1;

enum DayCounts
{
	JAN = 31,
	FEB = 28,
	MAR = 31,
	APR = 30,
	MAY = 31,
	JUN = 30,
	JUL = 31,
	AUG = 31,
	SEP = 30,
	OCT = 31,
	NOV = 30,
	DEC = 31
};

class Date {
	unsigned year;
	unsigned month;
	unsigned day;
	unsigned day_count;

	unsigned getDaysBetween(Date, Date) const;
	void swap(Date&, Date&) const;

public:
	Date(unsigned year = MIN_YEAR, unsigned month = MIN_MONTH, unsigned day = MIN_DAY);
	Date(Date const& other);
	Date& operator=(Date const&);
	bool operator==(Date const&) const;
	bool operator<(Date const&) const;
	bool operator>(Date const&) const;
	bool operator<=(Date const&) const;
	bool operator>=(Date const&) const;
	unsigned operator-(Date const&) const;
	void printDate(std::ostream&) const;
};

#endif