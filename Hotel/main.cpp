#include<iostream>
#include "Room.hpp"
//using namespace std;
const size_t MAX_ROOMS = 50;
const size_t MAX_COMMAND = 13;
const size_t NOTE_DEF_SIZE = 13;
const size_t MAX_CHARLINE = 100;
const char STOP_CMD[MAX_COMMAND] = "close";
const char CHECKIN_CMD[MAX_COMMAND] = "checkin";
const char AVAILABLE_CMD[MAX_COMMAND] = "availability";
const char REPORT_CMD[MAX_COMMAND] = "report";
const char UNAVAILABLE_CMD[MAX_COMMAND] = "unavailable";
const char CHECKOUT_CMD[MAX_COMMAND] = "checkout";
const char FIND_CMD[MAX_COMMAND] = "find";
const char FIND_URGENT_CMD[MAX_COMMAND] = "find!";


template<typename T>
void swap(T& t1, T& t2) {
	T temp = t1;
	t1 = t2;
	t2 = temp;
}

void report(Room Hotel[]) {
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
		if (Hotel[i].reportRoom(from, to, count)) {
			std::cout << "Room: " << Hotel[i].getNumber() << " |Days used: " << count << std::endl;
			if(!hasUsedRooms)
				hasUsedRooms = true;
			count = 0;
		}
	}
	if (!hasUsedRooms)
		std::cout << "No rooms are used in this period";

}

void available(Room Hotel[]) {
	Date date;
	//TODO: get current date if date is not set
	date.readDate(std::cin);
	for (size_t i = 0; i < MAX_ROOMS; i++)
	{
		if (Hotel[i].checkDate(date)) {
			Hotel[i].printRoom(std::cout);
			std::cout << std::endl;
		}
	}
}

void clearStr(char* str) {
	delete[] str;
	str = nullptr;
}

void resizeStr(char*& str, size_t& size, size_t& to) {
	if (to == size) {
		size *= 2;
		char* new_name = new(std::nothrow) char[size];
		if (!new_name) {
			std::cout << "Could not locate memory!" << std::endl;
		}

		for (size_t j = 0; j < to; j++)
		{
			new_name[j] = str[j];
		}

		clearStr(str);
		str = new_name;
	}
}

void getNote(char*& str, size_t& size, std::istream& in) {
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

void checkin(Room Hotel[MAX_ROOMS], bool setAvailable) {
	unsigned room;
	std::cin >> room;
	if (room > MAX_ROOMS) {
		std::cerr << "Room " << room << " does not exist." << std::endl;
		char line[MAX_CHARLINE];
		std::cin.getline(line,MAX_CHARLINE);
		return;
	}
	Date from;
	Date to;
	if (from > to)
		swap(from, to);
	size_t initial_size = NOTE_DEF_SIZE;
	char* note = new (std::nothrow) char[initial_size];
	from.readDate(std::cin);
	to.readDate(std::cin);
	getNote(note, initial_size, std::cin);

	Hotel[room - 1].makeReservation(from, to, note, setAvailable);
	if (setAvailable)
		std::cout << "Reservation made successfuly" << std::endl;
	else
		std::cout << "Room is set unavailable from" << from<<" to "<<to<< std::endl;
}

bool commandController(char command[MAX_COMMAND], Room Hotel[MAX_ROOMS]) {

	if (strcmp(command, STOP_CMD) == 0)
		return false;
	else if (strcmp(command, CHECKIN_CMD) == 0)
		checkin(Hotel, true);
	else if (strcmp(command, AVAILABLE_CMD) == 0)
		available(Hotel);
	else if (strcmp(command, REPORT_CMD) == 0)
		report(Hotel);
	else if (strcmp(command, UNAVAILABLE_CMD) == 0)
		checkin(Hotel, false); //sets a reservation that indicates it's unavailbale
	else if (strcmp(command, CHECKOUT_CMD) == 0)
		std::cout << "Under construction..." << std::endl;
	else if (strcmp(command, FIND_CMD) == 0)
		std::cout << "Under construction..." << std::endl;
	else if (strcmp(command, FIND_URGENT_CMD) == 0)
		std::cout << "Under construction..." << std::endl;



	return true;
}

void openCommandLine(Room Hotel[MAX_ROOMS]) {
	std::cout << "Command line is open (checkin, availability, checkout, report, find, find!, unavailable): " << std::endl;
	char command[MAX_COMMAND];

	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
	} while (commandController(command, Hotel));

}

int main() {

	Room Hotel[MAX_ROOMS];
	openCommandLine(Hotel);

	
}