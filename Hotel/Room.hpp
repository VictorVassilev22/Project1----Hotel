#ifndef ROOM_H
#define ROOM_H
#include"Reservation.hpp"

static unsigned room_count = 1;

class Room {
	unsigned number;
	unsigned beds;
	Reservation* reservations;
	size_t reservationsCount;
	bool taken;

	void setBeds();
	bool freeCheck(Reservation& const);

public:
	~Room();
	Room();
	Room(unsigned number, size_t reservationsCount = 0);
	unsigned getBeds() const { return beds; }
	unsigned getNumber() const { return number; }
	size_t getReservationsCount() const { return reservationsCount; }
	bool isTaken() const { return taken; }
	void checkOut() { taken = false; }
	bool checkDate(Date& const) const; //shows if the room is available on this date
	unsigned reportRoom(Date& const, Date& const) const; //shows how many days the room has been taken in diapason
	void makeReservation(Date& const sd, Date& const ed, char const* note);
	void makeReservation(Period p, char const* note);
	void setUnavailable(Date& const sd, Date& const ed, char const* note);
};

#endif
