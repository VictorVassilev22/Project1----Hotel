#ifndef ROOM_H
#define ROOM_H
#include"Reservation.hpp"

class Room {
	unsigned number;
	unsigned beds;
	Reservation* reservations;

public:
	~Room();
};

#endif
