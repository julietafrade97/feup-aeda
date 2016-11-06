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
#include "Tools.h"
#include "User.h"
#include "Guest.h"
#include "Trip.h"

using namespace std;

class Agency
{
private:
	static Agency* singleton_instance;

	int sessionID;
	int sessionPos;
	//Global Vectors
	vector<User *> Users;
	vector<Trip> Trips;
	//vector<Transaction> Transactions;

public:
	Agency();
	~Agency();

	//Cria uma nova inst�ncia.
	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

	//Elimina a inst�ncia atual e cria outra.
	/*void logout() {
	delete singleton_instance;
	singleton_instance = NULL;
	instance()->importInfo();
	}*/

	//Menu's

	void registerUser();
	void loginUser();

	int mainMenu_Admin();
	void optionsMainMenu_Admin();

	int mainMenu_User();
	void optionsMainMenu_User();

	//Ficheiros
	void extractUsers();
	void writeUsers();
	void extractBuddies();
	void writeBuddies();

	//Functions

	bool validUser(string name);
	bool validPassword(string password);
	int findID(string name);
	int getPos(int id);
	vector<User *> getUsers();
	void addUsers(User* u);

	/*void imprimeUsers();					//function that uses the Users class' operator<< method to
	//print all agency's users to screen

	void imprimeTrips();					//function that uses the Trips class' operator<< method to
	//print all agency's trips to screen
	void readUsers(std::ifstream & infile);    //TODO

	void readTrips(std::ifstream & infile);

	static float getFee() { return maintenaceFee; }

	static void changeFee(float newValue) { maintenaceFee = newValue; }

	float endMonth();*/


};