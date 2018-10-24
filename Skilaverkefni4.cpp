// Skilaverkefni4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

//býr til klasa fyrir flugin
class FlightBooking {
private:
	int id;
	int capacity;
	int reserved;
	int getPercentage();
public:
	FlightBooking();
	FlightBooking(int id, int capacity, int reserved);
	~FlightBooking();
	void printStatus();
	bool reserveSeats(int number_of_seats);
	bool cancelReservations(int number_of_seats);
	int getId() { return id; };
};

FlightBooking::FlightBooking() {
	id = 0;
	capacity = 0;
	reserved = 0;
}
FlightBooking::~FlightBooking() {
}

//notað til þess að búa til flugin
FlightBooking::FlightBooking(int id, int capacity, int reserved) {
	this->id = id;
	this->capacity = capacity;
	this->reserved = reserved;
}

//skrifar út upplýsingar um flugin
void FlightBooking::printStatus() {
	cout << "Flight " << id << ": " << reserved << "/" << capacity << " " << "(" << getPercentage() << "%) seats taken" << endl;
}

//returnar prosentutölu eftir hve mörg sæti eru pöntuð miðað við þau sem eru laus
int FlightBooking::getPercentage() {
	return 100 * reserved / capacity;
}
//function til að taka frá sæti
bool FlightBooking::reserveSeats(int number_of_seats) {
	int percentage = 0, seats = 0;
	seats = number_of_seats + reserved;//býr til breytu sem heldur utan um sætin sem eru þegar tekin + sætin sem eru að vera að panta
	percentage = 100 * seats / capacity;
	//ef prosentu talan er meira eða jöfn 105% þá er ekki hægt að panta sæti
	if (percentage >= 105)
	{
		cout << "Cannot perform this operation: capacity reached" << endl;
		return false;
	}
	else//annars eru sætin tekin frá
	{
		reserved += number_of_seats;
		return true;
	}
}
//function til að eyja sæta pöntunum
bool FlightBooking::cancelReservations(int number_of_seats) {
	if ((reserved - number_of_seats) < 0)//ef það er reynt að afpanta meiri sæti en eru pöntuð kemur villa
	{
		cout << "Cannot perform this operation: reservations cannot be less than 0" << endl;
		return false;
	}
	else//annars eru afpöntuðu sætin tekin frá þeim pöntuðu
	{
		reserved -= number_of_seats;
		return true;
	}
}
int main()
{
	//býr til Vector sem heldur utan um flugin
	vector<FlightBooking> booking;
	//iterator fyrir for loop
	vector<FlightBooking>::iterator it;
	//breytur sem eru notaðar í input skipunina
	int id = 0, n = 0;
	//breyta fyrir innslátt
	string command = " ";
	//búið til stringstream til að lesa úr innsláttinum á réttan hátt
	stringstream ss;
	//forritið keyrir á meðan innslátturinn er ekki quit
	while (command != "quit") {
		//clearar stringstreamið svo það sé ekki að rugla í neinu með gömlum skipunum
		ss.clear();
		if (booking.empty())
		{
			cout << "There are no flights in the system" << endl;
		}
		else
		{
			//skrifar út hvert flug í array-inum
			for (it = booking.begin(); it != booking.end(); ++it)
			{
				it->printStatus();
			}
		}
		cout << "What would you like to do?: ";
		//getline virkar ekki rétt ef það er whitespace á endanum á línunni þannig að þetta lagar það
		cin >> std::ws;
		cout << endl;
		getline(cin, command);//setur innsláttinn í breytuna "command"
		ss << command;//setur innsláttin í stringstreamið
		ss >> command >> id >> n;//breytir innsláttin í 2 breytur
		//ef innslátturinn er "add" þá bætir það við sætum í flugið
		if (command == "add")
		{
			//fer yfir arrayinn og ef það finnst flug með rétta id-ið þá eru tekin frá sæti í því flugi
			for (it = booking.begin(); it != booking.end(); ++it)
			{
				//ef þetta flug er með rétt íd þá tekur það frá sæti
				if (it->getId() == id)
				{
					it->reserveSeats(n);
					break;
				}
				//annars ef loopan er á síðasta stakinu í array-inum og það fann ekki flug með þetta id þá er flugið ekki til
				else if (it == booking.end() - 1 && it->getId() != id)
				{
					cout << "Cannot perform this operation: flight " << id << " does not exist" << endl;
				}
			}
		}
		//ef innslátturinn er "cancel" þá afpantar það sæti
		else if (command == "cancel")
		{
			//fer yfir arrayinn og ef það finnst flug með rétta id-ið þá eru afpöntuð sæti í því flugi
			for (it = booking.begin(); it != booking.end(); ++it)
			{
				//ef þetta flug er með rétt íd þá afpantar það sætin
				if (it->getId() == id)
				{
					it->cancelReservations(n);
					break;
				}
				//annars ef loopan er á síðasta stakinu í array-inum og það fann ekki flug með þetta id þá er flugið ekki til
				else if (it == booking.end() - 1 && it->getId() != id)
				{
					cout << "Cannot perform this operation: flight " << id << " does not exist" << endl;
				}
			}
		}
		//ef innsláttur er "create" þá er búið til flug með id og capacity
		else if (command == "create")
		{
			if (booking.empty())
			{
				booking.push_back(FlightBooking(id, n, 0));
			}
			else
			{
				//fer yfir arrayinn og ef það finnst flug með rétta id-ið þá eru afpöntuð sæti í því flugi
				for (it = booking.begin(); it != booking.end(); ++it)
				{
					//ef þetta id er til þá kemur villa
					if (it->getId() == id)
					{
						cout << "Cannot perform this operation: flight " << id << " already exists" << endl;
						break;
					}
					//ef id-ið er 0 þá kemur villa
					else if (it->getId() == 0 || id == 0 || n == 0)
					{
						cout << "Cannot perform this operation: The flight id/capacity cannot be 0" << endl;
						break;
					}
					//ef það er engin flugvél með þetta id og id-ið er ekki 0 þá er búið til flug
					else if (it == booking.end() - 1 && it->getId() != id)
					{
						booking.push_back(FlightBooking(id, n, 0));
						break;
					}									
				}
			}			
		}
		//ef innsláttur er "delete" þá er eytt flugi eftir id
		else if (command == "delete")
		{
			if (booking.empty())
			{
				cout << "Cannot perform this operation: Flight " << id << " does not exist" << endl;
			}
			else
			{
				//fer yfir arrayinn og ef það finnst flug með rétta id-ið þá er það flug eytt
				for (it = booking.begin(); it != booking.end(); ++it)
				{
					//ef það finnst flug með rétt id þá er því eytt
					if (it->getId() == id)
					{
						booking.erase(it);
						break;
					}
					//ef það finnst ekkert flug með þetta id
					else if (it == booking.end() - 1 && it->getId() != id)
					{
						cout << "Cannot perform this operation: Flight " << id << " does not exist" << endl;
					}
				}
			}
			
		}
		//ef innsláttur er ekki neitt af þessum að ofan þá kemur villa
		else
		{
			cout << "Cannot perform this operation: Incorrect Input" << endl;
		}

	}
	return 0;
}