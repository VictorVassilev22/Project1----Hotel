#include "Period.hpp"
#pragma once

Period::Period()
{
	startDate = Date(2020, 1, 1);
	endDate = Date(2020, 1, 1);
}

Period::Period(Date& const sd, Date& const ed)
{
	startDate = sd;
	endDate = ed;

	if (startDate > endDate) {
		Date temp = startDate;
		startDate = endDate;
		endDate = temp;
	}
}

unsigned Period::getDays() const
{
	if (startDate == endDate)
		return 0;
	else
		return endDate - startDate;
}

Period& Period::operator=(Period const& other)
{
	if (this != &other) {
		startDate = other.startDate;
		endDate = other.endDate;
	}
	return *this;
}

bool Period::isDateInPeriod(Date& const d) const
{
	return d >= startDate && d <= endDate;
	
}


