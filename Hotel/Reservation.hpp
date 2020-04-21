#ifndef RESERVE_H
#define RESERVE_H
#include "Date.hpp"
#include "Period.hpp"
#include <iostream>

class Reservation {
	Period period;
	char* note;
	bool available;

	void setNote(const char*);
	void clear(char*);
public:
	Reservation();
	Reservation(Period& const, char const*, bool available = true);
	~Reservation();

	
	
};

#endif
