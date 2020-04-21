#include "Room.hpp"

Room::~Room()
{
	delete[] reservations;
	reservations = nullptr;
}
