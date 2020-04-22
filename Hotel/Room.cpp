#include "Room.hpp"

void Room::setBeds()
{
	unsigned lastDigit = number % 10;
	switch (lastDigit) {
	case 0:
		beds = 6; // VIP appartement
		break;
	case 9:
		beds = 5; // appartement
		break;
	case 8:
	case 7:
	case 6:
		beds = 4; // family
		break;
	case 5:
	case 4:
	case 3:
		beds = 3; // small family
		break;
	case 2:
		beds = 2; // couple
		break;
	case 1:
		beds = 1; // single
		break;
	default:
		std::cout << "Invalid room number! What is happening?" << std::endl;
		break;
	}
}

bool Room::freeCheck(Reservation& const r)
{
	for (size_t i = 0; i < reservationsCount; i++)
	{
		if (reservations[i].overlap(r))
			return false;
	}
	return true;
}

Room::~Room()
{
	delete[] reservations;
	reservations = nullptr;
}

Room::Room()
{
	number = room_count++;
	reservations = nullptr;
	reservationsCount = 0;
	taken = false;
	setBeds();
}

Room::Room(unsigned n, size_t res_c) : number(n), reservationsCount(res_c)
{
	setBeds();
	if (res_c == 0)
		reservations = nullptr;
	else {
		reservations = new(std::nothrow) Reservation[res_c];
		if (!reservations)
			std::cout << "could not locate memory for reservations." << std::endl;
	}
	taken = false;
}

bool Room::checkDate(Date& const d) const
{
	for (size_t i = 0; i < reservationsCount; i++)
	{
		if (reservations[i].isDateInReservation(d))
			return false;
	}
	return true;
}

unsigned Room::reportRoom(Date& const from, Date& const to) const
{
	unsigned daysCount = 0;
	Date start;
	Date end;
	for (size_t i = 0; i < reservationsCount; i++)
	{
		start = reservations[i].getStartDate();
		end = reservations[i].getEndDate();
		if (from <= start && to >= end)
			daysCount += (end - start);
		else if (from > start && to < end)
			daysCount += (to - from);
		else if (from <= start && start < to && to <= end)
			daysCount += (to - start);
		else if (start <= from && from < end && end <= to)
			daysCount += (end - from);
	}
	return daysCount;
}

void Room::makeReservation(Date& const sd, Date& const ed, char const* note)
{
	if (reservations == nullptr)
		reservations = new(std::nothrow) Reservation[100];
	//TODO: make resizable reservations

	Period p(sd, ed);
	Reservation r(p, note, true);

	if (freeCheck(r)) {
		reservations[reservationsCount] = r;
		reservationsCount++;
		std::cout << "Reservation made successfuly" << std::endl;
	}
}

void Room::makeReservation(Period p, char const* note)
{
	if (reservations == nullptr)
		reservations = new(std::nothrow) Reservation[100];
	Reservation r(p, note, true);
	if (freeCheck(r)) {
		reservations[reservationsCount] = r;
		reservationsCount++;
		std::cout << "Reservation made successfuly" << std::endl;
	}
}

void Room::setUnavailable(Date& const sd, Date& const ed, char const* note)
{
	if (reservations == nullptr)
		reservations = new(std::nothrow) Reservation[100];

	Period p(sd, ed);
	Reservation r(p, note, false);

	if (freeCheck(r)) {
		reservations[reservationsCount] = r;
		reservationsCount++;
	}
}
