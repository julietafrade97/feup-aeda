#include "User.h"

/*USER CLASS*/
int User::maintenanceFee = 20;

User::User()
{
}

User::User(string name) :name(name)
{
}

User::User(int ID, string name, float balance, string username, string password) : ID(ID), name(name) {
	this->username = username;
	this->password = password;
	this->balance = balance;
}

User::~User()
{
}

void User::setUsername(string username)
{
	this->username = username;
}

void User::setID(int ID)
{
	this->ID = ID;
}

int User::getID() const
{
	return ID;
}

string User::getName() const
{
	return name;
}

string User::getUsername() const
{
	return username;
}

string User::getPassword() const
{
	return password;
}

float User::getBalance() const
{
	return balance;
}

void User::deposit(float value)
{
	balance += value;
}

void User::payment()
{
	return;
}

void User::addBuddy(User * user)
{
	buddies.push_back(user);
}

bool User::car() const
{
	return false;
}

/*
bool User::searchTrip(vector<Trip>& vec)
{
	return false;
}
*/
string User::getFirst() const
{
	return string();
}

string User::getLast() const
{
	return string();
}

bool User::operator ==(const User *u) const {

	if (this->ID == u->ID||this->username==u->username)
		return true;
	else
		return false;

}

/*DRIVER CLASS*/
Driver::Driver(int ID, string name, float balance, string username, string password) : User(ID, name, balance, username, password) {
}

int Driver::getNumSeats() const
{
	return numSeats;
}

void Driver::payment()
{
	balance -= maintenanceFee;
}

bool Driver::car() const
{
	return true;
}

/*PASSENGER CLASS*/

Passenger::Passenger(string name) : User(name) {
}

Passenger::Passenger(int ID, string name, float balance, string username, string password) : User(ID, name, balance, username, password) {
	numTrips = 0;
}

int Passenger::getNumTrips() const
{
	return numTrips;
}

vector<pTrip> Passenger::getPTrips()
{
	return pTrips;
}

void Passenger::setNumTrips()
{
	numTrips++;
}

void Passenger::payment()
{
	balance -= (maintenanceFee + numTrips); //TODO metodo de pagamento estupido
}

bool Passenger::car() const
{
	return false;
}

void Passenger::resetTrips(void)
{
	numTrips = 0;
}

void Passenger::addTrip(int tripID, string first, string last)
{
	pTrip pt;
	pt.id = tripID;
	pt.first = first;
	pt.last = last;
	pTrips.push_back(pt);
	numTrips++;
}

/*bool Passenger::searchTrip(vector<Trip> &vec)  //vec = vetor das viagens da agencia
{
	unsigned int posBeg = -1, posEnd = -1;
	for (size_t i = 0; i < vec.size(); i++)
	{
		vector<string> stops = vec[i].getStops();
		for (unsigned int j = 0; j < stops.size(); i++)
		{
			if (stops[j] == this->first)
				posBeg = j;

			if (stops[j] == this->last)
				posEnd = j;
		}

		//se ambos os indices foram atualizados
		if (posBeg != -1 && posEnd != -1)
			//se a paragem inicial do guest vem antes da final, para a viagem indicada, return true;
			if (posBeg < posEnd) {
				this->currentTrip = vec[i].getID();
				vec[i].addPassenger(this->ID);
				return true;
			}

	}

	//nenhuma das condi�oes de aceita��o foi obtida
	return false;
}*/