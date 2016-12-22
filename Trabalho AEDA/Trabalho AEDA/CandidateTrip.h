#pragma once

#include <string>
#include <vector>
#include "User.h"

using namespace std;


class CandidateTrip
{
private:
	User *passanger;
	User *driver;
	float distance; //distancia desde o inicio da viagem at� onde o user entra

public:
	CandidateTrip(User *u, User *d, float dist);
	User *getPassanger();
	User *getDriver();
	float getDistance();
	bool areBuddies();
	bool operator<(CandidateTrip & ct1); 
};



