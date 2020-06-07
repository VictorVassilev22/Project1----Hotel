#include "Room.hpp"

void Room::setBeds()
{
	unsigned lastDigit = number % 10;

	if(lastDigit==0)
		beds = 6; // VIP appartement
	else if(lastDigit == 9)
		beds = 5; // appartement
	else if(lastDigit<=8 && lastDigit>=6)
		beds = 4; // family
	else if(lastDigit <= 5 && lastDigit >= 3)
		beds = 3; // small family
	else if(lastDigit == 2)
		beds = 2; // couple
	else if(lastDigit==1)
		beds = 1; // single
	else
		std::cout << "Invalid room number! What is happening?" << std::endl;
}

bool Room::freeCheck(Reservation& const r) const
{
	for (size_t i = 0; i < reservationsCount; i++)
	{
		if (reservations[i].overlap(r))
			return false;
	}
	return true;
}

bool Room::checkBorder(bool c) const
{
	if (c) {
		if (reservationsCount>(size_t)(MAX_RES_BORDER*capacity)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (reservationsCount < (size_t)(MIN_RES_BORDER * capacity)) {
			return true;
		}
		else {
			return false;
		}
	}
}

void Room::resizeReservations(size_t new_cap)
{
	Reservation* new_reservations = new(std::nothrow) Reservation[new_cap];
	if (!new_reservations)
		std::cout << "Reservations allocation failed" << std::endl;

	copyReservations(new_reservations, reservations, reservationsCount);
	delete[] reservations;
	reservations = nullptr;
	reservations = new_reservations;
	capacity = new_cap;
}

void Room::removeReservation(size_t index)
{
	if (index >= reservationsCount) {
		std::cout << "invalid index of reservation passed" << std::endl;
		return;
	}


	if (reservationsCount == 1) {
		reservations[0] = Reservation();
		reservationsCount--;
		return;
	}

	for (size_t i = index; i < reservationsCount-1; i++)
	{
		reservations[i] = reservations[i + 1];
	}
	reservations[reservationsCount - 1] = Reservation();
	reservationsCount--;
}

void Room::sortReservations() 
{
	bool isSorted = false;
	bool hasSwapped = false;
	while (!isSorted) {
		hasSwapped = false;
		for (size_t i = 0; i < reservationsCount-1; i++)
		{
			if (reservations[i].getStartDate() < reservations[i + 1].getStartDate()) {
				swapReservations(reservations[i], reservations[i + 1]);
				hasSwapped = true;
			}
		}
		if (!hasSwapped)
			isSorted = true;
	}
}

void Room::freeReservation()
{
	if (!reservations) {
		std::cout << "No reservations" << std::endl;
		return;
	}
	Reservation r = reservations[0];
	Date today;
	setCurrentDate(today);
	if (!r.isDateInReservation(today)) {
		std::cout << "Guests have not settled yet. Cannot free reservation!" << std::endl;
		return;
	}

	removeReservation(0);
	taken = false;

	if (checkBorder(true))
		resizeReservations(true);

	std::cout << "Reservation freed successfuly!" << std::endl;
}

int Room::getReservationWithLessGuests(unsigned& guests, Period const& p)
{
	if (reservationsCount == 0)
		return 0;

	Reservation r;
	unsigned less_guests = UINT_MAX;
	unsigned curr_guests = 0;
	int index = -1;
	for (size_t i = 0; i < reservationsCount; i++)
	{
		r = reservations[i];
		curr_guests = r.getGuestsCnt();
		if (curr_guests < beds) {
			if (curr_guests < less_guests && p.getStartDate()>=r.getStartDate() &&p.getEndDate()<= r.getEndDate()) {
				less_guests = curr_guests;
				index = i;
			}
		}
	}
	guests = less_guests;
	return index;
}

void Room::copyReservations(Reservation*& dest, Reservation* origin, size_t size)
{
	
	for (size_t i = 0; i < size; i++)
	{
		dest[i] = origin[i];
	}

}

void Room::swapReservations(Reservation& r1, Reservation& r2)
{
	Reservation temp = r1;
	r1 = r2;
	r2 = temp;
}

Room::~Room()
{
	delete[] reservations;
	reservations = nullptr;
}

Room::Room()
{
	//TODO: read from file, pop all past reservations, update taken to date
	capacity = MIN_CAP;
	number = room_count++;
	reservations = nullptr;
	reservationsCount = 0;
	taken = false;
	setBeds();
}

Room& Room::operator=(Room const& other)
{
	if (this != &other) {
		if(!reservations)
		reservations = new(std::nothrow) Reservation[capacity];
		if (!reservations)
			std::cout << "Reservations allocation failed" << std::endl;
		copyReservations(reservations, other.reservations, other.reservationsCount);
		capacity = other.capacity;
		reservationsCount = other.reservationsCount;
		number = other.number;
		beds = other.beds;
		taken = other.taken;
		//reservations_q = other.reservations_q; does not need this, it can be built from the array
	}
	return *this;
}

Room::Room(unsigned n, size_t res_c) : number(n), reservationsCount(res_c)
{
	capacity = MIN_CAP;
	setBeds();
	capacity = MIN_CAP;
	while (capacity < reservationsCount)
		capacity *= 2;

	if (res_c == 0)
		reservations = nullptr;
	else {
		reservations = new(std::nothrow) Reservation[capacity];
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

bool Room::checkPeriod(Period const& p) const
{
	Reservation r;
	for (size_t i = 0; i < reservationsCount; i++)
	{
		r = reservations[i];
		if (r.overlap(p))
			return false;
	}
	return true;
}

bool Room::reportRoom(Date& const from, Date& const to, unsigned& daysCount) const
{
	Date start;
	Date end;
	unsigned initial = daysCount;
	Reservation r;
	for (size_t i = 0; i < reservationsCount; i++)
	{
		r = reservations[i];

		if (!r.isAvailable())
			continue;

		start = r.getStartDate();
		end = r.getEndDate();
		if (from <= end) {
			if (from <= start && to >= end)
				daysCount += (end - start);
			else if (from > start && to < end)
				daysCount += (to - from);
			else if (from <= start && start < to && to <= end)
				daysCount += (to - start);
			else if (start <= from && from < end && end <= to)
				daysCount += (end - from);
		}
		else if(to<start) 
			return daysCount > initial; //we are past the head (from-to) now, so we return the value :)
	}
	return daysCount > initial;
}

void Room::makeReservation(Date& const sd, Date& const ed, char const* note, bool isAvailable, unsigned guestsCnt = 0)
{
	Date today;
	setCurrentDate(today);

	if (ed < today) {
		std::cout << "You are trying to make a reservation for a period that has passed, please try again!" << std::endl;
		return;
	}

	if (guestsCnt == 0)
		guestsCnt = beds;

	if (reservations == nullptr) {
		reservations = new(std::nothrow) Reservation[capacity];
		if (!reservations)
			std::cout << "Error locating memory for reservations!" << std::endl;
	}


	Period p(sd, ed);
	Reservation r(p, note, isAvailable, guestsCnt);

	if (!freeCheck(r)) {
		std::cout << "Room is taken in that period of time, please choose another!" << std::endl;
		return;
	}

	reservations[reservationsCount] = r;
	reservationsCount++;

	if (r.isDateInReservation(today))
		taken = true;

	sortReservations();
	if (checkBorder(true))
		resizeReservations(true);

	if (isAvailable)
		std::cout << "Reservation added!" << std::endl;
	else
		std::cout << "Room is set unavailable from" << p.getStartDate() << " to " << p.getEndDate() << std::endl;
}

void Room::makeReservation(Period p, char const* note, unsigned guestsCnt = 0)
{
	Date today;
	setCurrentDate(today);

	if (p.getEndDate() < today) {
		std::cout << "You are trying to make a reservation for a period that has passed, please try again!" << std::endl;
		return;
	}

	if (guestsCnt == 0)
		guestsCnt = beds;

	if (reservations == nullptr)
		reservations = new(std::nothrow) Reservation[capacity];
	Reservation r(p, note, true, guestsCnt);
	if (!freeCheck(r)) {
		std::cout << "Room is taken in that period of time, please choose another!" << std::endl;
		return;
	}

	reservations[reservationsCount] = r;
	reservationsCount++;

	if (r.isDateInReservation(today))
		taken = true;

	sortReservations();
	if (checkBorder(true))
		resizeReservations(true);

		std::cout << "Reservation added!" << std::endl;
}

void Room::printRoom(std::ostream& out) const
{
	out << "|Room: " << number << " |Beds: " << beds <<
		" |Reservations: " << reservationsCount << " |Currently: ";
	if (taken)
		out << "taken|";
	else
		out << "free|";

}
