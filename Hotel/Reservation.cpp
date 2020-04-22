#include "Reservation.hpp"
#include <iostream>

void Reservation::setNote(const char* other_note)
{
	if (note != nullptr)
		clear(note);
	note = new(std::nothrow) char[strlen(other_note) + 1];

	if (!note) {
		std::cout << "could not allocate memory" << std::endl;
		return;
	}

	strcpy(note, other_note);
}

void Reservation::clear(char* note) {
	delete[] note;
	note = nullptr;
}

Reservation::Reservation()
{
	note = nullptr;
	available = true;
}

Reservation::Reservation(Period& const p, char const* nt, bool av)
{
	period = p;
	setNote(nt);
	available = av;
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
		strcmp(new_note, note);
		return new_note;
	}
}

Reservation& Reservation::operator=(Reservation const& other)
{
	if (this != &other) {
		period = other.period;
		available = other.available;
		setNote(other.note);
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
		return false;
	else
		return true;
}

bool Reservation::isDateInReservation(Date& const d) const
{
	return period.isDateInPeriod(d);
}
