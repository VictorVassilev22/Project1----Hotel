#include<iostream>
#include "Room.hpp"
using namespace std;
const size_t MAX_ROOMS = 50;
const size_t MAX_COMMAND = 13;
const size_t NOTE_DEF_SIZE = 13;
const char STOP_CMD[MAX_COMMAND] = "close";
const char CHECKIN_CMD[MAX_COMMAND] = "checkin";

void clearStr(char* str) {
	delete[] str;
	str = nullptr;
}

void resizeStr(char*& str, size_t& size, size_t& to) {
	if (to == size) {
		size *= 2;
		char* new_name = new(nothrow) char[size];
		if (!new_name) {
			cout << "Could not locate memory for Username!" << endl;
		}

		for (size_t j = 0; j < to; j++)
		{
			new_name[j] = str[j];
		}

		clearStr(str);
		str = new_name;
	}
}

void getNote(char*& str, size_t& size, istream& in) {
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

void checkin(Room Hotel[MAX_ROOMS]) {
	unsigned room;
	Date from;
	Date to;
	size_t initial_size = NOTE_DEF_SIZE;
	char* note = new (nothrow) char[initial_size];
	cin >> room;
	from.readDate(cin);
	to.readDate(cin);
	getNote(note, initial_size, cin);

	Hotel[room - 1].makeReservation(from, to, note);
}

bool commandController(char command[MAX_COMMAND], Room Hotel[MAX_ROOMS]) {

	if (strcmp(command, STOP_CMD) == 0)
		return false;
	else if (strcmp(command, CHECKIN_CMD) == 0)
		checkin(Hotel);

	return true;
}

void openCommandLine(Room Hotel[MAX_ROOMS]) {
	cout << "Command line is open (checkin, availability, checkout, report, find, find!, unavailable): " << endl;
	char command[MAX_COMMAND];

	do {
		cout << "Enter your command: ";
		cin >> command;
	} while (commandController(command, Hotel));

}

int main() {

	Room Hotel[MAX_ROOMS];
	openCommandLine(Hotel);

	
}