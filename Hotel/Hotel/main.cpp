#include<iostream>
#include "Room.hpp"

/// How many rooms the hotel has. Can be changed any time.
const size_t MAX_ROOMS = 50;
/// Max value of symbols a user command should have. According to the paper, the longest command has 13 symbols (including the teminating zero).
const size_t MAX_COMMAND = 13;
/// How many symbols the note has.
///@note Dont worry, it is resizing dynamically.
const size_t NOTE_DEF_SIZE = 13;
/// Max line of characters when entering command.
///@note will use this in some cases when we need to clean the buffer when the command turns to be shorter then expected.
const size_t MAX_CHARLINE = 100;
/// This command closes the command line.
const char STOP_CMD[MAX_COMMAND] = "close";
/// Command for checkin
const char CHECKIN_CMD[MAX_COMMAND] = "checkin";
/// Command for showing availability
const char AVAILABLE_CMD[MAX_COMMAND] = "availability";
/// Command for showing report
const char REPORT_CMD[MAX_COMMAND] = "report";
/// Command for setting room unavailable
const char UNAVAILABLE_CMD[MAX_COMMAND] = "unavailable";
/// Command for checkout
const char CHECKOUT_CMD[MAX_COMMAND] = "checkout";
/// Command for finding rooms
const char FIND_CMD[MAX_COMMAND] = "find";
/// Command for finding rooms for someone important fast.
const char FIND_URGENT_CMD[MAX_COMMAND] = "find!";


/// template function that swaps the values of two variables
template<typename T>
void swap(T& t1, T& t2) {
	T temp = t1;
	t1 = t2;
	t2 = temp;
}

///Executing command to print a report. Reads two dates, and prints how many days the room is used in that diapason.
///@see Room::reportRoom()
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

/// Executes command to show availability of rooms.
/// Reads a date with Date::readDate()
/// Prints all the rooms that are free on this date.
///@see Room::checkDate() Room::printRoom()
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

/// Clears memory of char* from the heap.
void clearStr(char* str) {
	delete[] str;
	str = nullptr;
}

/// Resizes char*. Enables writing endless notes.
/// @see getNote()
void resizeStr(char*& str, size_t& size, size_t& to) {
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

/// Gets a note much long as we want.
///@see resizeStr()
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

///Basically makes a reservation for a room, given a number, Period by start date and end date, and a note.
///@note *TODO:* Make not obligatory option to select number of guests
void checkin(Room Hotel[MAX_ROOMS], bool setAvailable) {
	unsigned room;
	std::cin >> room;
	if (room > MAX_ROOMS) {
		std::cerr << "Room " << room << " does not exist." << std::endl;
		char line[MAX_CHARLINE];
		///cleaning the buffer
		///@see MAX_CHARLINE
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

///The command controller executes a single command.
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

///Opens the commandController()
///Takes commands intil the command is STOP_CMD, then commandController returns false and the cycle here stops.
///@see commandController(char command[MAX_COMMAND], Room Hotel[MAX_ROOMS])
void openCommandLine(Room Hotel[MAX_ROOMS]) {
	std::cout << "Command line is open (checkin, availability, checkout, report, find, find!, unavailable): " << std::endl;
	char command[MAX_COMMAND];

	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
	} while (commandController(command, Hotel));

}

///Initializes array "Hotel" consisting of MAX_ROOMS rooms and executes openCommandLine() with "Hotel" as a parameter.
///@see openCommandLine()
int main() {

	Room Hotel[MAX_ROOMS];
	openCommandLine(Hotel);
	return 0;
}