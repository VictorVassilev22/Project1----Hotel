#include "Date.hpp"

Date::Date(unsigned y, unsigned m, unsigned d) {
	if (year<MIN_YEAR || year>MAX_YEAR) {
		std::cerr << "Year not in bounds (" << MIN_YEAR << " - " << MAX_YEAR << ") changing to " << MIN_YEAR << "..." << std::endl;
		year = MIN_YEAR;
	}
	else
		year = y;


	if (month<MIN_MONTH || month>MAX_MONTH) {
		std::cerr << "Month not in bounds (" << MIN_MONTH << " - " << MAX_MONTH << ") changing to " << MIN_MONTH << "..." << std::endl;
		month = MIN_MONTH;
	}
	else
		month = m;

	day_count = (unsigned)DayCounts(month - 1);
	if (day > day_count || day < MIN_DAY) {

		if (year % 4 == 0 && month == 2 && day == FEB + 1) {
			day = d;
		}else
			std::cerr << "Invalid day. This month has " << day_count << " days, (you cannot enter \"0\"). Changing to \"1\"." << std::endl;
	}
	else
		day = d;
};

Date::Date(Date const& other) : year(other.year), month(other.month), day(other.day), day_count(other.day_count) {};

Date& Date::operator=(Date const& other) {
	if (this != &other) {
		year = other.year;
		month = other.month;
		day = other.day;
	}
	return *this;
}

bool Date::operator==(Date const& other) const{
	return year == other.year && month == other.month && day == other.day;
}

bool Date::operator<(Date const& other)const {
	if (year < other.year)
		return true;
	else if (year == other.year) {
		if (month < other.month)
			return true;
		else if (month == other.month) {
			if (day < other.day)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool Date::operator>(Date const& other)const {
	if (year > other.year)
		return true;
	else if (year == other.year) {
		if (month > other.month)
			return true;
		else if (month == other.month) {
			if (day > other.day)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool Date::operator<=(Date const& other) const {

	if (*this == other || *this < other)
		return true;

}

bool Date::operator>=(Date const& other) const {

	if (*this == other || *this > other)
		return true;

}

unsigned Date::operator-(Date const& other) const
{
	return getDaysBetween(*this, other);
}

unsigned Date::getDaysBetween(Date sooner, Date later) const
{
	unsigned hasSecondSwap = 0;
	unsigned hasThirdSwap = 0;
	if (sooner > later) {
		swap(sooner, later);
	}
	unsigned daysToLaterYear = 0;
	while(sooner.year<later.year){
		if (sooner.year % 4 == 0)
			daysToLaterYear += MAX_DAYS_YEAR+1;
		else 
			daysToLaterYear += MAX_DAYS_YEAR;
		sooner.year++;
	}
	if (sooner > later) {
		swap(sooner, later);
		hasSecondSwap++;
	}
	unsigned daysToLaterMonth = 0;
	while (sooner.month < later.month) {
		if (sooner.year % 4 == 0 && sooner.month == 2)
			daysToLaterMonth += DayCounts(sooner.month - 1) + 1;
		else
			daysToLaterMonth += DayCounts(sooner.month - 1);
		sooner.month++;
	}
	if (sooner > later) {
		swap(sooner, later);
		hasThirdSwap++;
	}
	unsigned daysToLaterDay = 0;
	while (sooner.day < later.day) {
		daysToLaterDay++;
	}
	return (unsigned)(daysToLaterMonth+daysToLaterMonth*pow(-1, hasSecondSwap)
		+daysToLaterDay*pow(-1, hasThirdSwap));
}

void Date::swap(Date& d1, Date& d2) const
{
	Date temp = d1;
	d1 = d2;
	d2 = temp;
}

void Date::printDate(std::ostream& os) const {
	os << year << " - " << month << " - " << day;
}
