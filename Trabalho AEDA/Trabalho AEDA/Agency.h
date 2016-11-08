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
#include "Transactions.h"

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
	vector<Guest *> Guests;
	vector<string> stopsAvailable = { "a","b","c" };
	vector<Transaction> Transactions;

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

	//Files

	void extractUsers();
	void writeUsers();
	void extractBuddies();
	void writeBuddies();
	void extractTransactions();
	void writeTransactions();

	//Basic Functions

	bool validUser(string username); //existe user com name
	bool validPassword(int pos, string password); //verifica se password esta correta
	int findID(string name); //retorna id de name, id = -1 caso nao exista
	int getPos(int id); //retorna posicao no vetor de users de id UTIL!!!
	vector<User *> getUsers();
	int getLastId();


	//Functions
	void addUser(User* u);

	void addTrip();
	bool checkStop(string s);
	void runTrip(int tripID);


	void displayUsers();
	int menuDisplayUsers();
	
	void displayBuddies(); 
	int menuDisplayBuddies();

	void displayTransactions();
	int menuDisplayTransactions();

	/*
	void imprimeTrips();					//function that uses the Trips class' operator<< method to
	//print all agency's trips to screen
	void readUsers(std::ifstream & infile);    //TODO

	void readTrips(std::ifstream & infile);


	float endMonth();
	*/


};