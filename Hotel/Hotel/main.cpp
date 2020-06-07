#include<iostream>
#include "Room.hpp"
#include "Hotel.h"

/// Max value of symbols a user command should have. According to the paper, the longest command has 13 symbols (including the teminating zero).
const size_t MAX_COMMAND = 13;
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
const char HELP_CMD[MAX_COMMAND] = "help";

void help() {
	std::cout << "Currently available rooms are from 1 to " << MAX_ROOMS << std::endl;
	std::cout <<"To make a reservation enter command checkin <room> <from> <to> <note> [<guests>]"<<std::endl;
	std::cout <<"To check availability an a date enter command availability [<date>]"<<std::endl;
	std::cout <<"To print a report for rooms in a period enter command report <from> <to>"<<std::endl;
	std::cout <<"To find a free room with desired beds count enter command find <beds> <from> <to>"<<std::endl;
	std::cout <<"To find a free room with desired beds count with urgent necessity enter command find! <beds> <from> <to>"<<std::endl;
	std::cout <<"To set a room unavailable for a period enter command unavailable <room> <from> <to> <note>"<<std::endl;
}

///The command controller executes a single command.
bool commandController(char command[MAX_COMMAND], Hotel& hotel) {

	if (strcmp(command, STOP_CMD) == 0)
		return false;
	else if (strcmp(command, CHECKIN_CMD) == 0)
		hotel.checkin();
	else if (strcmp(command, HELP_CMD) == 0)
		help();
	else if (strcmp(command, AVAILABLE_CMD) == 0)
		hotel.showAvailable();
	else if (strcmp(command, REPORT_CMD) == 0)
		hotel.report();
	else if (strcmp(command, UNAVAILABLE_CMD) == 0)
		hotel.showAvailable();
	else if (strcmp(command, CHECKOUT_CMD) == 0)
		hotel.checkout();
	else if (strcmp(command, FIND_CMD) == 0)
		hotel.find();
	else if (strcmp(command, FIND_URGENT_CMD) == 0)
		if (!hotel.findUrgent())
			std::cout << "Task failed, no room found!" << std::endl;
		
	else {
		std::cout << "Invalid command!" << std::endl;
	}

	return true;
}

///Opens the commandController()
///Takes commands intil the command is STOP_CMD, then commandController returns false and the cycle here stops.
///@see commandController(char command[MAX_COMMAND], Room Hotel[MAX_ROOMS])
void openCommandLine(Hotel& hotel) {
	std::cout << "Command line is open: " << std::endl;
	char command[MAX_COMMAND];

	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
	} while (commandController(command, hotel));

}

///Initializes array "Hotel" consisting of MAX_ROOMS rooms and executes openCommandLine() with "Hotel" as a parameter.
///@see openCommandLine()
int main() {
	Hotel hotel;
	openCommandLine(hotel);
	return 0;
}