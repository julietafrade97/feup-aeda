#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <Windows.h>
#include <algorithm>
#include "Utilities.h"
#include "User.h"

using namespace std;

class Agency
{
private:
	static Agency* singleton_instance;
	static unsigned int lastID;			//last ID attributed to a User
	//vector<User *> users;				//vector including all the registred Users of the agency
	//vector<Trip *> trips;
	//vector<Transaction>
	static float maintenaceFee;
public:
	Agency();
	~Agency();

	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

	//Menu's

	void registerUser();
	void loginUser();

	//Functions

	static unsigned int getLastID();		//function that return the lastID of the agency and increments it by 1

	void imprimeUsers();					//function that uses the Users class' operator<< method to
											//print all agency's users to screen

	void imprimeTrips();					//function that uses the Trips class' operator<< method to
											//print all agency's trips to screen
	void readUsers(std::ifstream & infile);    //TODO

	void readTrips(std::ifstream & infile);

	static float getFee() { return maintenaceFee; }

	static void changeFee(float newValue) { maintenaceFee = newValue; }

	float endMonth();

};


