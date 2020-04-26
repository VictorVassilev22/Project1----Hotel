#ifndef PERIOD_H
#define PERIOD_H
#include"Date.hpp"

///Realisation of Period class
///
///Contains two dates - startDate and endDate.

class Period {
	/// The periods starts here.
	Date startDate;
	///The period ends here.
	Date endDate;

public:
	///Default constructor initializes startDate and endDate with same min values. 
	///The period currently consists of 0 days.
	Period();
	///Constructor.
	Period(Date& const sd, Date& const ed);
	///Gets days in this period. @see Date::operator-()
	unsigned getDays() const;
	///Assignes one Period to another
	Period& operator=(Period const&);
	/// @returns Period::startDate
	Date getStartDate() const { return startDate; }
	///@returns Period::endDate
	Date getEndDate() const { return endDate; }
	///Checks if a Date is the current Period.
	bool isDateInPeriod(Date& const) const;
};

#endif
