#ifndef RESERVE_H
#define RESERVE_H
#include "Date.hpp"
#include "Period.hpp"
#include <iostream>

///Realisation of Reservation class
///
///If someone wants to reserve a room they make reservation.
///Here are stored all the needful information aboit the Reservation.


class Reservation {
	/// Period of the reservation. How many days the guests will stay.
	Period period;
	/// Note of the reservation. This can be as long as the user wants.
	char* note;
	/// Is this reservation available, e.g is any guest there or it is set unavailable for a Period (e.g in construction or smth).
	bool available;

	/// Sets the note to the Reservation
	void setNote(const char*);
	///Clears dynamic allocated memory from the heap.
	void clear(char*);
public:
	/// The period is created by default. Note note is assigned to nullptr and available is currently true.
	Reservation();
	/// Sets Reservation::note, Reservation::period and Reservation::available (=true)
	Reservation(Period& const, char const*, bool available = true);
	///Destructor clears all dynamically allocated memory @see clear(char*)
	~Reservation();
	/// @returns a copy of the current note
	char* getNote() const;
	///Assignes the value of another Reservation to this
	Reservation& operator=(Reservation const&);
	/// @returns Period::getStartDate() of Reservation::period
	Date getStartDate() const { return period.getStartDate(); }
	/// @returns Period::getEndDate() of Reservation::period
	Date getEndDate() const { return period.getEndDate(); }
	/// @returns this->available
	bool isAvailable() const { return available; }
	/// @returns if the Period of this Reservation overlaps with another Period,
	///so we can tell if the Period is free for this Reservation or not
	bool overlap(Reservation& const other) const;
	/// @returns if a Date (say, a current day) is in this reservation @see Period::isDateInPeriod(Date& const) const
	bool isDateInReservation(Date& const) const;
};

#endif
