#include "Hotel.h"

void Hotel::getNote(char*& str, size_t& size, std::istream& in)
{
	char ch;
	size_t i = 0;
	while (in.peek() != EOF) {
		ch = in.peek();

		if (ch == '\n' || ch == '\r' || ch == '\0') {
			str[i] = '\0';
			return;
		}

		in.get(ch);
		resizeStr(str, size, i);
		str[i] = ch;

		i++;
	}
}

void Hotel::resizeStr(char*& str, size_t& size, size_t& to)
{
	if (to == size) {
		size *= 2;
		char* new_name = new(std::nothrow) char[size];
		if (!new_name) {
			std::cout << "Could not locate memory!" << std::endl;
			return;
		}

		for (size_t j = 0; j < to; j++)
		{
			new_name[j] = str[j];
		}

		clearStr(str);
		str = new_name;
	}
}

void Hotel::clearStr(char* str)
{
	delete[] str;
	str = nullptr;
}

void Hotel::readGuestsCnt(std::istream& in, unsigned& cnt)
{
	char ch;
	in.ignore();
	std::cout << "Please, specify number of guests (press enter to skip): ";
	ch = in.peek();
	if (ch == '\n')
		return;
	in >> cnt;
}

void Hotel::writeData()
{
	std::ofstream os(FILE_NAME, std::ios::out | std::ios::trunc);
	Room room;
	Reservation reserv;
	size_t reserv_cnt;
	size_t i = 0;
	while (i < MAX_ROOMS && !os.eof()) {
		room = rooms[i];
		os << i;
		reserv_cnt = room.reservationsCount;
		if (reserv_cnt > 0) {
			room.sortReservations();
			os << ' ' << true << std::endl;
		}
		else
			os << ' ' << false << std::endl;
		for (size_t j = 0; j < reserv_cnt; j++)
		{
			reserv = room.getReservation(j);
			os << reserv << std::endl;
		}
		i++;
	}
	std::cout << "Data saved successfuly!"<<std::endl;
}

void Hotel::readData()
{
	std::cout << "Loading reservations..." << std::endl;
	std::ifstream is(FILE_NAME, std::ios::in);
	size_t room = 0;
	bool hasReservations = false;
	Date startDate;
	Date endDate;
	Date today;
	size_t note_size = 15;
	char* note = new(std::nothrow) char[note_size];
	if (!note) {
		std::cout << "Error reading note!" << std::endl;
		return;
	}
	bool isAvailable = false;
	unsigned guestsCount = 0;

	char ch;
	setCurrentDate(today);

	while (is.good() && !is.eof() && room < MAX_ROOMS) {
		ch = is.peek();
		if (ch == '\n') {
			is.ignore(); // ignores new line
			ch = is.peek();
		}
		if (ch < '0' || ch > '9') {
			break;
		}
		is >> room;
		is >> hasReservations;

		if (!hasReservations)
			continue;
		ch = is.peek();
		if(ch=='\n')
			is.ignore(); // ignores new line
		getNote(note, note_size, is);
		ch = is.peek();
		if (ch == '\n')
			is.ignore(); // ignores new line
		is >> isAvailable;
		is >> guestsCount;
		ch = is.peek();
		if (ch == '\n')
			is.ignore(); // ignores new line
		startDate.readDate(is);
		endDate.readDate(is);

		//just to keep everything up to date, do not add past reservations
		if (endDate < today)
			continue;

		rooms[room].makeReservation(startDate, endDate, note, isAvailable, guestsCount);
	}
	std::cout << "Reservations loaded successfuly!" << std::endl;
}

Hotel::Hotel()
{
	readData();
}

Hotel::~Hotel()
{
	writeData();
}


void Hotel::checkin(bool setAvailable)
{
	unsigned room;
	std::cin >> room;
	if (room > MAX_ROOMS) {
		std::cerr << "Room " << room << " does not exist." << std::endl;
		char line[MAX_CHARLINE];
		///cleaning the buffer
		///@see MAX_CHARLINE
		std::cin.getline(line, MAX_CHARLINE);
		return;
	}
	Date from;
	Date to;
	if (from > to)
		swap(from, to);
	size_t initial_size = NOTE_DEF_SIZE;
	char* note = new (std::nothrow) char[initial_size];
	if (!note)
		std::cout << "Error locating memory for note" << std::endl;
	from.readDate(std::cin);
	to.readDate(std::cin);
	std::cin.ignore();//ignores ' ' (space)
	getNote(note, initial_size, std::cin);
	unsigned guests_cnt = rooms[room - 1].getBeds();
	readGuestsCnt(std::cin, guests_cnt);

	//can do it so that more people wanting room with less beds cant book the room :)
	//should i?

	rooms[room - 1].makeReservation(from, to, note, setAvailable, guests_cnt);
}

void Hotel::setUnavailable()
{
	checkin(false);
}

void Hotel::showAvailable()
{
	Date date;
	if (std::cin.peek() == '\n')
		setCurrentDate(date);
	else
		date.readDate(std::cin);
	for (size_t i = 0; i < MAX_ROOMS; i++)
	{
		if (rooms[i].checkDate(date)) {
			rooms[i].printRoom(std::cout);
			std::cout << std::endl;
		}
	}
}

void Hotel::report()
{
	Date from;
	Date to;
	unsigned count = 0;
	from.readDate(std::cin);
	to.readDate(std::cin);
	bool hasUsedRooms = false;
	if (from > to)
		swap(from, to);
	for (size_t i = 0; i < MAX_ROOMS; i++)
	{
		if (rooms[i].reportRoom(from, to, count)) {
			std::cout << "Room: " << rooms[i].getNumber() << " |Days used: " << count << std::endl;
			if (!hasUsedRooms)
				hasUsedRooms = true;
			count = 0;
		}
	}
	if (!hasUsedRooms)
		std::cout << "No rooms are used in this period";

}

void Hotel::checkout()
{
	unsigned room;
	std::cin >> room;
	if (room > MAX_ROOMS) {
		std::cerr << "Room " << room << " does not exist." << std::endl;
		char line[MAX_CHARLINE];
		///cleaning the buffer
		///@see MAX_CHARLINE
		std::cin.getline(line, MAX_CHARLINE);
		return;
	}

	rooms[room-1].freeReservation();
}

bool Hotel::find()
{
	unsigned bed_cnt;
	std::cin >> bed_cnt;

	Date startDate;
	Date endDate;

	startDate.readDate(std::cin);
	endDate.readDate(std::cin);

	Period p(startDate, endDate);

	return searchRoom(bed_cnt, p);
}

bool Hotel::searchRoom(unsigned bed_cnt, Period const& p)
{
	size_t room_index = 0;

	Room r;

	unsigned leastBedCnt = UINT_MAX;
	unsigned currBedCnt = 0;

	for (size_t i = 0; i < MAX_ROOMS; i++)
	{
		r = rooms[i];
		currBedCnt = r.getBeds();
		if (r.checkPeriod(p) && currBedCnt >= bed_cnt) {
			if (currBedCnt < leastBedCnt) {
				leastBedCnt = currBedCnt;
				room_index = i;
			}
		}
	}

	if (leastBedCnt == UINT_MAX) {
		std::cout << "Desired room is not found, we do not have room with this many beds :(" << std::endl;
		return false;
	}
	else {
		std::cout << "Room " << room_index + 1 << " has " << leastBedCnt << " beds and is free on this period! You can proceed with reservation!" << std::endl;
		return true;
	}
}

int Hotel::searchRoom(unsigned bed_cnt, Period const& p, bool c)
{
	int room_index = -1;

	Room r;

	unsigned leastBedCnt = UINT_MAX;
	unsigned currBedCnt = 0;

	for (size_t i = 0; i < MAX_ROOMS; i++)
	{
		r = rooms[i];
		currBedCnt = r.getBeds();
		if (r.checkPeriod(p) && currBedCnt >= bed_cnt) {
			if (currBedCnt < leastBedCnt) {
				leastBedCnt = currBedCnt;
				room_index = i;
			}
		}
	}

	return room_index;
}

bool Hotel::findUrgent()
{
	unsigned bed_cnt;
	std::cin >> bed_cnt;

	Date startDate;
	Date endDate;

	startDate.readDate(std::cin);
	endDate.readDate(std::cin);

	Period p(startDate, endDate);

	if (searchRoom(bed_cnt, p))
		return true;

	std::cout << "Rearranging some guests to find a place... " << std::endl;

	//finding the room we want for the important person
	int room_index = -1;
	int reserv_index = findUntakenBedsReservation(bed_cnt, room_index, p);
	if (reserv_index < 0 || room_index < 0)
		return false;

	//getting information for the guests currently in that room with a reservation
	Reservation r1 = rooms[room_index].getReservation(reserv_index);
	Period p1(r1.getStartDate(), r1.getEndDate());
	unsigned bed_cnt1 = r1.getGuestsCnt();

	//finding a room for these people
	int room_index1 = searchRoom(bed_cnt1, p1, true);
	if (room_index1 >= 0) {
		rooms[room_index1].makeReservation(p1, r1.getNote(), r1.getGuestsCnt());
		//free the room for the important person
		rooms[room_index].removeReservation(reserv_index);
		//settle the important person there
		std::cout << "Room "<<room_index+1<<" with "<<bed_cnt<<" beds was freed, you can proceed with reservation!" << std::endl;
		return true;
	}
	int reserv_index1 = findUntakenBedsReservation(bed_cnt1, room_index1, p1);
	if (reserv_index1 < 0)
		return false;

	//in that room there are other people, getting info about their reservation
	Reservation r2 = rooms[room_index1].getReservation(reserv_index1);
	Period p2(r2.getStartDate(), r2.getEndDate());
	unsigned bed_cnt2 = r2.getGuestsCnt();

	//checking if there is a free room for them
	int room_index2 = searchRoom(bed_cnt2, p2, true);
	if (room_index2 < 0)
		return false;

	//if there is, take that room
	rooms[room_index2].makeReservation(p2, r2.getNote(), r2.getGuestsCnt());
	//free the other
	rooms[room_index1].removeReservation(reserv_index1);
	//settle previous guests
	rooms[room_index1].makeReservation(p1, r1.getNote(), r1.getGuestsCnt());
	//free the room for the important person
	rooms[room_index].removeReservation(reserv_index);
	std::cout << "Room " << room_index + 1 << " with " << bed_cnt << " beds was freed, you can proceed with reservation!" << std::endl;
	return true;
}

int Hotel::findUntakenBedsReservation(unsigned bed_cnt, int& room_index, Period const& p)
{
	Room r;
	int reserv_index = -1;
	size_t reserv_curr = 0;
	unsigned beds = 0;
	unsigned guests = 0;
	unsigned less_guests = UINT_MAX;

	for (size_t i = 0; i < MAX_ROOMS; i++)
	{
		r = rooms[i];
		beds = r.getBeds();
		if (beds == bed_cnt) {
			reserv_curr = r.getReservationWithLessGuests(guests, p);
			if (guests < less_guests) {
				less_guests = guests;
				reserv_index = reserv_curr;
				room_index = i;
			}
		}
	}

	return reserv_index;
}
