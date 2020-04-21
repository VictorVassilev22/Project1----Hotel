#ifndef PERIOD_H
#define PERIOD_H
#include"Date.hpp"

class Period {
	Date startDate;
	Date endDate;

public:
	Period();
	Period(Date& const sd, Date& const ed);
	unsigned getDays();
	Period& operator=(Period& const);
};

#endif
