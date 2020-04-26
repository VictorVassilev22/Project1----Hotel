#ifndef ROOM_H
#define ROOM_H
#include"Reservation.hpp"

/// The program keeps room count automatically.
/// The number of the rooms gets assigned according to the room count.
static unsigned room_count = 1;

///Realisation of Room class
///
///Guests in the hotel can book several types of rooms differing in how many rooms they have.
///@note *TODO:* Maybe needs a member variable number of guests, which will defaulty initialize as 0,
///and takes the number of guests as value when a reservation is made.
///@see Room::setBeds()

class Room {
	///Number of the Room
	unsigned number;
	///How many beds does this Room have
	unsigned beds;
	///List of the reservations
	///@note *IDEA:* Maybe create a queue for the reservations and when someone makes Reservation put it there.
	/// The queue must stay always sorted so with the command checkout the first(sooner) Reservation in the queue pops.
	Reservation* reservations;
	/// Keeps the current count of the reservations
	///@note *TODO:* create variable size_t reservationsCapacity and resize the list of reservations dynamically
	/// (Or maybe it will be a linked queue?)
	size_t reservationsCount;
	///To keep track if the requested room is currently taken by a guest.
	/// @note *IDEA:* Somehow get the current Date in real time and say if the date is contained in the first Reservation in the queue?
	/// @note *IDEA:* at start pop all reservations from the queue which Reservation::endDate < the current (real time) date.
	///This way we will see which room is currently taken.
	bool taken;

	/// @note automatically sets a number of beds according
	///
	///~~~~~~~~.cpp
	///unsigned lastDigit = number % 10;
	///	switch (lastDigit) {
	///	case 0:
	///		beds = 6; // VIP appartement
	///		break;
	///	case 9:
	///		beds = 5; // appartement
	///		break;
	///	case 8:
	///	case 7:
	///	case 6:
	///		beds = 4; // family
	///		break;
	///	case 5:
	///	case 4:
	///	case 3:
	///		beds = 3; // small family
	///		break;
	///	case 2:
	///		beds = 2; // couple
	///		break;
	///	case 1:
	///		beds = 1; // single
	///		break;
	///	default:
	///		std::cout << "Invalid room number! What is happening?" << std::endl;
	///		break;
	///	}
	///}
	///~~~~~~~~
	void setBeds();
	/// Checks is reservation a guest wants to make is free (e.g if it does not overlap with another one) @see Reservation::overlap()
	bool freeCheck(Reservation& const);

public:
	///Deletes dynamically alocated data from the heap
	~Room();
	/// Creates room with initial values.
	///Room::number gets assigned according to Room::room_count which is a static member and increases itself when we call a constructor
	///(but not a copy constructor).
	///@note Speaking of copy, we need copy constuctor and operator=, will be done along with sorting the reservations. Is it needed now?
	Room();
	///sets number, reservations count and allocates memory for the reservations
	///@note if Room::reservationsCount is 0, the list is nullptr.
	Room(unsigned number, size_t reservationsCount = 0);
	///@returns Room::beds
	unsigned getBeds() const { return beds; }
	///@returns Room::number
	unsigned getNumber() const { return number; }
	///@returns Room::reservationsCount
	size_t getReservationsCount() const { return reservationsCount; }
	///@returns Room::taken
	bool isTaken() const { return taken; }
	/// sets taken to false e.g frees reservation
	void checkOut() { taken = false; }
	/// shows if the room is available on this date
	bool checkDate(Date& const) const;
	///@returns Basically returns if the room is used in a certain diapason
	///@param from Indicates start date
	///@param to Indicates end date
	///@param date_count is also passed by reference as te function returns bool value but I also want to extract
	///how many days the room is used.
	bool reportRoom(Date& const from, Date& const to, unsigned& days_count) const; 
	/// Makes a reservation and adds it in the list.
	///@param isAvailable sets the room available or unavailable for this reservation.
	///@note If we want to make a room unavailable, instead of writing new method for it, just make a Reservation for a Period
	///and check the Reservation::available to false.
	void makeReservation(Date& const sd, Date& const ed, char const* note, bool isAvailable);
	///same as room::makeReservation(Date& const, Date& const, char const*, bool) but automatically sets the Reservation::available to true
	void makeReservation(Period p, char const* note);
	/// Prints Room attributes to console or to file.
	///@param stream shows what stream we want to use. To print on a file, or on console.
	void printRoom(std::ostream& stream) const;
};

#endif
