#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<cmath>
#include<ctime>

/// The hotel can book rooms from MIN_YEAR.
const unsigned MIN_YEAR = 2020;
/// To MAX_YEAR.
const unsigned MAX_YEAR = 2100;
/// Indicates how many days a default year has (365, 366 for a leap year).
const unsigned MAX_DAYS_YEAR= 365;
/// Number of months per year (12).
const unsigned MAX_MONTH = 12;
/// Minimal value for month (1).
const unsigned MIN_MONTH = 1;
/// Minimal value for day (1).
const unsigned MIN_DAY = 1;
/// Maximal value for day (31).
const unsigned MAX_DAY = 31;
/// How many sybols does a year representation contain (4 + 1 for the terminating zero).
const unsigned YEAR_SYMBOLS = 5;
/// How many sybols does a month representation contain(3 + 1 for the terminating zero).
const unsigned MONTH_SYMBOLS = 3;
/// How many sybols does a day representation contain(3 + 1 for the terminating zero).
const unsigned DAY_SYMBOLS = 3;
/// The whole date object representations consists of 11 symbols by the ISO 8601 format (10 + 1 for the terminating zero).
const size_t DATE_STR_LENGTH = 11;


/// Realisation of Date class.
///
/// This class represents a date in ISO 8601 format.
/// It consists of necessary methods such as printDate() readDate()
/// There are also implemented needful comparison operators.


class Date {
	unsigned year;
	unsigned month;
	unsigned day;
	unsigned day_count;

	/// Gets days between two dates. The algorithm works quite symply.
	/// First gets how many days we need to even out the years, then the months and then the days.
	/// Tested with @ref https://www.timeanddate.com/date/duration.html 
	/// @returns unsigned type.
	unsigned getDaysBetween(Date, Date) const;
	/// Swaps values of two Date objects.
	void swap(Date&, Date&) const;

public:
	/// Default constructor assignes the min values for all parameters.
	Date(unsigned year = MIN_YEAR, unsigned month = MIN_MONTH, unsigned day = MIN_DAY);
	///Copy constructor copies all member variables from other object Date
	Date(Date const& other);
	///Does the same as copy constructor but only if the objects Date are different
	Date& operator=(Date const&);
	/// <summary>
	/// Operator == checks if the two objects ere equal
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool operator==(Date const&) const;
	///@returns true if the left hand date is before the other chronologically
	bool operator<(Date const&) const;
	///@returns true if the left hand date is after the other chronologically
	bool operator>(Date const&) const;
	///@see Date::operator<(Date const&) const
	bool operator<=(Date const&) const;
	///@see Date::operator>(Date const&) const
	bool operator>=(Date const&) const;
	/// @see Date::getDaysBetween(Date, Date) const
	unsigned operator-(Date const&) const;
	///Prints date in ISO 8601 format.
	void printDate(std::ostream&) const;
	///Reads date in ISO 8601 format.
	void readDate(std::istream&);
	///Prints date in ISO 8601 format.
	friend std::ostream& operator<<(std::ostream&, Date const&);
};

std::ostream& operator<<(std::ostream&, Date const&);
/// <summary>
/// Gets the current date using ctime and converts it to a Date object
/// </summary>
/// <param name="d"></param>
void setCurrentDate(Date& d);

#endif