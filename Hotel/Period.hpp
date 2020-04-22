#ifndef PERIOD_H
#define PERIOD_H
#include"Date.hpp"

class Period {
	Date startDate;
	Date endDate;

public:
	Period();
	Period(Date& const sd, Date& const ed);
	unsigned getDays() const;
	Period& operator=(Period const&);
	Date getStartDate() const { return startDate; }
	Date getEndDate() const { return endDate; }
	bool isDateInPeriod(Date& const) const;
};

#endif
