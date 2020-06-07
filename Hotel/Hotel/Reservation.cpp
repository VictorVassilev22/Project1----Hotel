#include "Reservation.hpp"
#include <iostream>

void Reservation::setNote(const char* other_note)
{
	if (other_note) {
		clear(note);
		note = new(std::nothrow) char[strlen(other_note) + 1];

		if (!note) {
			std::cout << "could not allocate memory" << std::endl;
			return;
		}

		strcpy(note, other_note);
	}
	else {
		clear(note);
	}
		
}

void Reservation::clear(char*& note) {
	if (note) {
		delete[] note;
		note = nullptr;
	}
}

Reservation::Reservation()
{
	note = nullptr;
	available = true;
	guests_cnt = 0;
}

Reservation::Reservation(Period& const p, char const* nt, bool av, unsigned gc)
{
	period = p;
	setNote(nt);
	available = av;
	guests_cnt = gc;
}

Reservation::Reservation(Reservation& const other)
{
	period = other.period;
	available = other.available;
	setNote(other.note);
	guests_cnt = other.guests_cnt;
}

Reservation::~Reservation()
{
	clear(note);
}

char* Reservation::getNote() const
{
	if (note == nullptr)
		return nullptr;
	else {
		char* new_note = new(std::nothrow) char[strlen(note) + 1];
		strcpy(new_note, note);
		return new_note;
	}
}

Reservation& Reservation::operator=(Reservation const& other)
{
	if (this != &other) {
		period = other.period;
		available = other.available;
		setNote(other.note);
		guests_cnt = other.guests_cnt;
	}

	return *this;
}

bool Reservation::overlap(Reservation& const other) const
{
	Date startDateA = getStartDate();
	Date startDateB = other.getStartDate();
	Date endDateA = getEndDate();
	Date endDateB = other.getEndDate();
	if ((startDateA <= endDateB && endDateA >= startDateB)
		|| (startDateB <= endDateA && endDateB >= startDateA))
		return true;
	else
		return false;
}

bool Reservation::overlap(Period const& p) const
{
	Date startDateA = getStartDate();
	Date startDateB = p.getStartDate();
	Date endDateA = getEndDate();
	Date endDateB = p.getEndDate();
	if ((startDateA <= endDateB && endDateA >= startDateB)
		|| (startDateB <= endDateA && endDateB >= startDateA))
		return true;
	else
		return false;
}

bool Reservation::isDateInReservation(Date& const d) const
{
	return period.isDateInPeriod(d);
}

std::ostream& operator<<(std::ostream& os, Reservation const& r)
{
	char* note = r.getNote();
	//return os << r.getPeriod() << ' ' << note <<' '<< r.isAvailable() <<' '<< r.getGuestsCnt();
	os << note << std::endl;
	os << r.isAvailable() << ' ' << r.getGuestsCnt() << std::endl;
	return os << r.getPeriod();
	delete[] note;
}
