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
