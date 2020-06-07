//TODO: make reading from file in the constructor
//and writing in file in the destructor
#ifndef HOTEL_H
#define HOTEL_H
#include"Room.hpp"

/// How many rooms the hotel has. Can be changed any time.
const size_t MAX_ROOMS = 10;
/// Max line of characters when entering command.
///@note will use this in some cases when we need to clean the buffer when the command turns to be shorter then expected.
const size_t MAX_CHARLINE = 100;
/// How many symbols the note has.
///@note Dont worry, it is resizing dynamically.
const size_t NOTE_DEF_SIZE = 13;

const char FILE_NAME[10] = "file.txt";

class Hotel{
	Room rooms[MAX_ROOMS];

	template<typename T>
	void swap(T& t1, T& t2);
	/// <summary>
	/// reads note from a file or the console
	/// </summary>
	/// <param name="str">this is where the string is saved</param>
	/// <param name="size">size of the string</param>
	/// <param name="in">the desired stream</param>
	void getNote(char*& str, size_t& size, std::istream& in);
	/// <summary>
	/// resising the string dynamically
	/// </summary>
	/// <param name="str">the desired string to resize</param>
	/// <param name="size"> the size of the string</param>
	/// <param name="to">indicates where to copy the old memory to</param>
	void resizeStr(char*& str, size_t& size, size_t& to);
	/// <summary>
	/// clears data from a char*
	/// </summary>
	/// <param name="str"></param>
	void clearStr(char* str);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="in">the stream</param>
	/// <param name="">here the guests number are saved </param>
	void readGuestsCnt(std::istream& in, unsigned&);
	/// <summary>
	/// writes the data to a file
	/// </summary>
	void writeData();
	/// <summary>
	/// reads data from the file
	/// </summary>
	void readData();
public:
	/// <summary>
	/// @see Hotel::readData() is used
	/// </summary>
	/// <returns></returns>
	Hotel();
	///@see Hotel::writeData() is used
	~Hotel();
///Basically makes a reservation for a room, given a number, Period by start date and end date, and a note.
	void checkin(bool ia = true);
	/// sets room unavailable for a period of time
	///sets a reservation that indicates it's unavailbale
	///@see checkin(bool) is used
	void setUnavailable();
/// Executes command to show availability of rooms.
/// Reads a date with Date::readDate()
/// Prints all the rooms that are free on this date.
///@see Room::checkDate() Room::printRoom()
	void showAvailable();
///Executing command to print a report. Reads two dates, and prints how many days the room is used in that diapason.
///@see Room::reportRoom()
	void report();
	/// <summary>
	/// reads a room number from the console. If the room has reservation that is currently taken, clear it!
	/// </summary>
	void checkout();
	/// <summary>
	/// finds a room with a desired number of beds
	/// </summary>
	/// <returns>if there is such a room or not</returns>
	bool find();
	/// <summary>
	/// Searches for a room with desired bed count that is currently free.
	/// </summary>
	/// <param name="bed_cnt"> count of beds</param>
	/// <param name="p">desired period</param>
	/// <returns>if is found or not</returns>
	bool searchRoom(unsigned bed_cnt, Period const& p);
	/// <summary>
	/// Searches for a room with desired bed count that is currently free.
	/// </summary>
	/// <param name="bed_cnt">desired bed count</param>
	/// <param name="p">desired period</param>
	/// <param name="c">just to change the signature</param>
	/// <returns>the index of the room</returns>
	int searchRoom(unsigned bed_cnt, Period const& p, bool c);
	/// <summary>
	/// Finds a room urgently. if neccesary, moves some guests settled in bigger rooms to free space
	/// </summary>
	/// <returns>if the search is successful or not</returns>
	bool findUrgent();
	/// <summary>
	/// helps Hotel::findUrgent() Finds a reservation with less guests than beds from all rooms
	/// </summary>
	/// <param name="bed_cnt">desired bed count</param>
	/// <param name="room_index">the index of the room</param>
	/// <param name="p">the desired period</param>
	/// <returns>the index of the reservation</returns>
	int findUntakenBedsReservation(unsigned bed_cnt, int& room_index, Period const& p);
	/// <summary>
	/// just a test, afraid to delete :D
	/// </summary>
	Reservation& getReservationTest(size_t room, size_t reservation) const {return rooms[room].getReservation(reservation); }
};

#endif

/// <summary>
/// template function that swaps two objects passed by reference
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="t1"></param>
/// <param name="t2"></param>
template<typename T>
inline void Hotel::swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}
