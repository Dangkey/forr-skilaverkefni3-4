// Skilaverkefni3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//b�r til klasa fyrir flugin
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

//nota� til �ess a� b�a til flugin
FlightBooking::FlightBooking(int id, int capacity, int reserved) {
	this->id = id;
	this->capacity = capacity;
	this->reserved = reserved;
}

//skrifar �t uppl�singar um flugin
void FlightBooking::printStatus() {
	cout << "Flight " << id << ": " << reserved << "/" << capacity << " " << "(" << getPercentage() << "%) seats taken" << endl;
}

//returnar prosentut�lu eftir hve m�rg s�ti eru p�ntu� mi�a� vi� �au sem eru laus
int FlightBooking::getPercentage() {
	return 100 * reserved / capacity;
}
//function til a� taka fr� s�ti
bool FlightBooking::reserveSeats(int number_of_seats) {
	int percentage = 0, seats = 0;
	seats = number_of_seats + reserved;//b�r til breytu sem heldur utan um s�tin sem eru �egar tekin + s�tin sem eru a� vera a� panta
	percentage = 100 * seats / capacity;
	//ef prosentu talan er meira e�a j�fn 105% �� er ekki h�gt a� panta s�ti
	if (percentage >= 105)
	{
		cout << "Cannot perform this operation: capacity reached" << endl;
		return false;
	}
	else//annars eru s�tin tekin fr�
	{
		reserved += number_of_seats;
		return true;
	}
}
//function til a� eyja s�ta p�ntunum
bool FlightBooking::cancelReservations(int number_of_seats) {
	if ((reserved - number_of_seats) < 0)//ef �a� er reynt a� afpanta meiri s�ti en eru p�ntu� kemur villa
	{
		cout << "Cannot perform this operation: reservations cannot be less than 0" << endl;
		return false;
	}
	else//annars eru afp�ntu�u s�tin tekin fr� �eim p�ntu�u
	{
		reserved -= number_of_seats;
		return true;
	}
}
int main()
{
	//b�r til array sem heldur utan um flugin
	FlightBooking booking[10];
	//test flug
	booking[0] = FlightBooking(1, 400, 0);
	//breytur sem eru nota�ar � input skipunina
	int id = 0, n = 0;
	//breyta fyrir innsl�tt
	string command = " ";
	//b�i� til stringstream til a� lesa �r innsl�ttinum � r�ttan h�tt
	stringstream ss;
	//forriti� keyrir � me�an innsl�tturinn er ekki quit
	while (command != "quit") {
		//clearar stringstreami� svo �a� s� ekki a� rugla � neinu me� g�mlum skipunum
		ss.clear();
		//skrifar �t hvert flug � array-inum
		for (size_t i = 0; i < 10; i++)
		{
			//ef id-i� � fluginu er 0 �� er �a� ekki skrifa� �t �v� flug getur ekki haft id sem er 0
			if (booking[i].getId() != 0)
			{
				booking[i].printStatus();
			}
		}
		cout << "What would you like to do?: ";
		//getline virkar ekki r�tt ef �a� er whitespace � endanum � l�nunni �annig a� �etta lagar �a�
		cin >> std::ws;
		cout << endl;
		getline(cin, command);//setur innsl�ttinn � breytuna "command"
		ss << command;//setur innsl�ttin � stringstreami�
		ss >> command >> id >> n;//breytir innsl�ttin � 2 breytur
		//ef innsl�tturinn er "add" �� b�tir �a� vi� s�tum � flugi�
		if (command == "add")
		{
			//fer yfir arrayinn og ef �a� finnst flug me� r�tta id-i� �� eru tekin fr� s�ti � �v� flugi
			for (size_t i = 0; i < 10; i++)
			{
				//ef �etta flug er me� r�tt �d �� tekur �a� fr� s�ti
				if (booking[i].getId() == id)
				{
					booking[i].reserveSeats(n);
					break;
				}
				//annars ef loopan er � s��asta stakinu � array-inum og �a� fann ekki flug me� �etta id �� er flugi� ekki til
				else if (i == 9 && booking[i].getId() != id)
				{
					cout << "Cannot perform this operation: flight " << id << " does not exist" << endl;
				}
			}
		}
		//ef innsl�tturinn er "cancel" �� afpantar �a� s�ti
		else if (command == "cancel")
		{
			//fer yfir arrayinn og ef �a� finnst flug me� r�tta id-i� �� eru afp�ntu� s�ti � �v� flugi
			for (size_t i = 0; i < 10; i++)
			{
				//ef �etta flug er me� r�tt �d �� afpantar �a� s�tin
				if (booking[i].getId() == id)
				{
					booking[i].cancelReservations(n);
					break;
				}
				//annars ef loopan er � s��asta stakinu � array-inum og �a� fann ekki flug me� �etta id �� er flugi� ekki til
				else if (i == 9 && booking[i].getId() != id)
				{
					cout << "Cannot perform this operation: flight " << id << " does not exist" << endl;
				}
			}
		}
		//ef innsl�ttur er "create" �� er b�i� til flug me� id og capacity
		else if (command == "create")
		{
			//fer yfir arrayinn og ef �a� finnst flug me� r�tta id-i� �� eru afp�ntu� s�ti � �v� flugi
			for (size_t i = 0; i < 10; i++)
			{
				//ef �etta id er til �� kemur villa
				if (booking[i].getId() == id)
				{
					cout << "Cannot perform this operation: flight " << id << " already exists" << endl;
					break;
				}
				//ef �a� er engin flugv�l me� �etta id og id-i� er ekki 0 �� er b�i� til flug
				else if (booking[i].getId() == 0 && id != 0 && n != 0)
				{
					booking[i] = FlightBooking(id, n, 0);
					break;
				}
				//ef id-i� er 0 �� kemur villa
				else if (booking[i].getId() == 0 || id == 0)
				{
					cout << "Cannot perform this operation: The flight id/capacity cannot be 0" << endl;
					break;
				}
				//ef �a� eru til 10 flug �� er ekki h�gt a� b�a til fleiri
				else if (i == 9 && booking[i].getId() != 0)
				{
					cout << "Cannot perform this operation: There cannot be more than 10 flights" << endl;
				}

			}
		}
		//ef innsl�ttur er "delete" �� er eytt flugi eftir id
		else if (command == "delete")
		{
			//fer yfir arrayinn og ef �a� finnst flug me� r�tta id-i� �� er �a� flug eytt
			for (size_t i = 0; i < 10; i++)
			{
				//ef �a� finnst flug me� r�tt id �� er �llu � �v� breytt � 0 �v� �a� er ekki h�gt a� ey�a �r static size array
				if (booking[i].getId() == id)
				{
					booking[i] = FlightBooking(0, 0, 0);
					break;
				}
				//ef �a� finnst ekkert flug me� �etta id
				else if (i == 9 && booking[i].getId() == 0)
				{
					cout << "Cannot perform this operation: Flight " << id << " does not exist" << endl;
				}

			}
		}
		//ef innsl�ttur er ekki neitt af �essum a� ofan �� kemur villa
		else if (command == "quit")
		{
			cout << "Goodbye" << endl;
		}
		else
		{
			cout << "Cannot perform this operation: Incorrect Input" << endl;
		}

	}
	return 0;
}