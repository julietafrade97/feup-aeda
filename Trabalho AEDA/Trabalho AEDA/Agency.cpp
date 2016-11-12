#include "Agency.h"
Utilities ut;
Tools t;

/////////////////////
// EXCE�OES /////
///////////////////

class NonexistentStop
{
public:
	string stop;
	NonexistentStop(string name) { stop = name; }
};
ostream & operator<<(ostream &out, const NonexistentStop &obj)
{
	out << "ERROR: The stop '" << obj.stop << "' does not exist.\n"; return out;
}

class RepeatedStop
{
public:
	string stop;
	RepeatedStop(string name) { stop = name; }
};
ostream & operator<<(ostream &out, const RepeatedStop &obj)
{
	out << "ERROR: The stop '" << obj.stop << "' was already used.\n"; return out;
}

class InvalidDate
{
public:
	Date date;
	InvalidDate(Date d) { date = d; }
};
ostream & operator<<(ostream &out, const InvalidDate &obj)
{
	out << "ERROR: '" << obj.date.getDay() << '/' << obj.date.getMonth()
		<< '/' << obj.date.getYear() << "' is not a valid date format.\n"; return out;
};

class PassedDate
{
public:
	int day, month, year;
	PassedDate(int d, int m, int y) { day = d; month = m; year = y; }
};
ostream & operator<<(ostream &out, const PassedDate &obj)
{
	out << "ERROR: '" << obj.day << '/' << obj.month
		<< '/' << obj.year << "' has passed already.\n"; return out;
};

class TooLong
{
public:
	int day, month, year;
	TooLong(int d, int m, int y) { day = d; month = m; year = y; }
};
ostream & operator<<(ostream &out, const TooLong &obj)
{
	out << "ERROR: The trip must be within a year. You entered" << " '" << obj.day << '/' << obj.month
		<< '/' << obj.year << "' .\n"; return out;
};

class InvalidHour
{
public:
	int hour, minutes;
	InvalidHour(int h, int m) { hour = h; minutes = m; }
};
ostream & operator<<(ostream &out, const InvalidHour &obj)
{
	out << "ERROR: '" << obj.hour << ':' << obj.minutes << "' is invalid.\n"; return out;
};

class PassedHour
{
public:
	int hour, minutes;
	PassedHour(int h, int m) { hour = h; minutes = m; }
};
ostream & operator<<(ostream &out, const PassedHour &obj)
{
	out << "ERROR: '" << obj.hour << ':';
	if (obj.minutes < 10)
	{
		out << '0';
	}
	out << obj.minutes << "' as passed already.\n"; return out;
};

/// PRINT DA STRUCT STOP
ostream & operator<<(ostream &out, const stop &e) {
	out << "ERROR: " << e.code << " - " << e.name << endl; return out;
};

Agency::Agency()
{
}

Agency::~Agency()
{
}

/* CLASS GET AND SET */
vector<User *> Agency::getUsers() {
	return Users;
}

/* MENUS */

void Agency::registerUser()
{
	ut.clearScreen();
	string type, name, username, password;

	ut.menuHeader();
	cout << "|                      ";  ut.grey(); cout << "Create Account";  ut.white(); cout << "                     |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl; ut.white();
	cout << "    Types of accounts:\n      - Driver: You need to register your car and host\n      trips. You'll also earn some money.\n      - Passenger: You can only join existing trips.\n\n";
	ut.grey(); cout << "    > Do you want to register as a Driver? (y/n) "; ut.white(); cin >> type;  cout << endl;

	while (cin.fail() || ((type != "y") && (type != "Y") && (type != "n") && (type != "N")))
	{
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Invalid choice!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> type; cout << endl;
	}

	ut.grey(); cout << "    > Enter username: "; ut.white(); cin >> username;

	while (cin.fail() || validUser(username)) {
		if (cin.eof())
		{
			cin.clear();
			ut.clearScreen();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "\n> That username is taken!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> username;
	}

	bool a = false;
	while (!a) {
		ut.grey(); cout << "\n    > Enter password: "; ut.white();
		password = t.insertPassword();
		ut.grey(); cout << "\n    > Confirm password: "; ut.white();
		if (t.sameString(password, t.insertPassword()))
			a = true;
		else { ut.red(); cout << "\n> Password doesnt match! Try again.\n"; }
	}

	ut.grey(); cout << "\n\n    > Enter name: "; ut.white(); cin.ignore(); getline(cin, name);

	int nID = getLastId() + 1;

	if ((type == "y") || (type == "Y")) {
		User *u1 = new Driver(nID, name, 0.00, username, password);
		addUser(u1);
	}
	else {
		User *u1 = new Passenger(nID, name, 0.00, username, password);
		addUser(u1);
	}

	this->sessionID = nID;
	this->sessionPos = (int)Users.size() - 1;
	ut.red(); cout << "\n\n> Success! You just created your account!\n"; Sleep(2500); ut.white();

	optionsMainMenu_User();


	ut.clearScreen();
	return;
}

void Agency::loginUser()
{
	ut.clearScreen();
	int id;
	string username, password;

	ut.menuHeader();
	cout << "|                          ";  ut.grey(); cout << "Login";  ut.white(); cout << "                          |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.grey(); cout << "    > Enter username: "; ut.white(); cin >> username;

	while (cin.fail() || (validUser(username) == false && username != "admin"))
	{
		if (cin.eof())
		{
			cin.clear();
			ut.clearScreen();
			return;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Login failed!" << endl;
		ut.white(); cout << "Please try again.\n\n";
		ut.grey(); cout << "    > Enter username: "; ut.white(); cin >> username;
	}

	if (username == "admin") {
		ut.grey(); cout << "\n    > Enter password: "; ut.white();
		if (t.insertPassword() == "admin") {
			ut.red(); cout << "\n\n> Login successful as admin!\n"; Sleep(2000); ut.white();
			optionsMainMenu_Admin();
		}
		else {
			ut.red(); cout << "\n\n> Login failed!" << endl; ut.white();
			Sleep(2000);
			ut.clearScreen();
			return;
		}
	}
	else {
		id = findID(username);

		ut.grey(); cout << "\n    > Enter password: "; ut.white();
		password = t.insertPassword();
		if (validPassword(getPos(id), password)) {
			this->sessionID = id;
			this->sessionPos = getPos(sessionID);
			ut.red(); cout << "\n\n> Login successful!\n"; Sleep(2000); ut.white();
			optionsMainMenu_User();
		}
		else {
			ut.red(); cout << "\n\n> Login failed!" << endl; ut.white();
			Sleep(2000);
			ut.clearScreen();
			return;
		}
	}
	ut.clearScreen();
	return;
}

/* ADMINISTRADOR */
int Agency::mainMenu_Admin() {

	ut.clearScreen();
	ut.menuHeader();
	cout << "|~~~                   ";  ut.grey(); cout << "ADMINISTRATION";  ut.white(); cout << "                  ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< setw(18) << "1. Users" << setw(30) << "4. Relationships" << endl
		<< setw(24) << "2. Trip Record" << setw(16) << "5. Stops" << endl
		<< setw(25) << "3. Transactions" << setw(16) << "6. Search" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;  ut.white();
	cout << "|~~~                               ";  ut.grey(); cout << "< 0. Logout >";  ut.white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 6) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Invalid choice!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> option;
	}


	if (option == 0)
		return 0;
	return option;
}

void Agency::optionsMainMenu_Admin() {
	unsigned short int option;

	while (option = mainMenu_Admin())
		switch (option)
		{
		case 1:
			menuDisplayUsers();
			break;
		case 2:
			menuDisplayRecord();
			break;
		case 3:
			menuDisplayTransactions();
			break;
		case 4:
			menuDisplayBuddies();
			break;
		case 5:
			menuDisplayStops();
			break;
		case 6:
			break;
		}
	return;
}

int Agency::menuDisplayUsers() {
	ut.clearScreen();
	ut.menuHeader();
	cout << "|                          ";  ut.grey(); cout << "USERS";  ut.white(); cout << "                          |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(10) << "User" << setw(16) << "Name" << setw(16) << "Balance" << setw(10) << "Driver" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  displayUsers();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;  ut.setcolor(7);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.setcolor(7); cout << "< 0. Return >";  ut.setcolor(15); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option < 0) || ((option > 2)))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Invalid choice!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> option;
	}

	if (option == 0)
		return 0;
	return option;
}

void Agency::optionsDisplayUsers() {
	unsigned short int option;

	while (option = menuDisplayUsers())
		switch (option)
		{
		case 1:
			//TODO ordenar users
			break;
		case 2:
			//TODO ordenar users
			break;
		}
	return;
}

void Agency::menuDisplayBuddies() {
	ut.clearScreen();
	ut.menuHeader();
	cout << "|                      ";  ut.grey(); cout << "RELATIONSHIPS";  ut.white(); cout << "                      |" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  displayBuddies();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.red(); cout << "\n Press anything to go back."; ut.white(); getchar(); getchar();
	return;
}

void Agency::menuDisplayTransactions() {
	ut.clearScreen();
	ut.menuHeader();
	cout << "|~~~                     ";  ut.setcolor(7); cout << "TRANSACTIONS";  ut.setcolor(15); cout << "                  ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(5) << "ID" << setw(27) << "Date" << setw(22) << "Value" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  displayTransactions();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.red(); cout << "\n Press anything to go back."; ut.white(); getchar(); getchar();
	return;
}

void Agency::menuDisplayStops() {
	ut.clearScreen();
	ut.menuHeader();
	cout << "|~~~                       ";  ut.setcolor(7); cout << "STOPS";  ut.setcolor(15); cout << "                       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(15) << "Code" << setw(35) << "Name" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  displayStops();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.red(); cout << "\n Press anything to go back."; ut.white(); getchar(); getchar();
	return;
}

void Agency::menuDisplayRecord()
{
	ut.clearScreen();
	ut.menuHeader();
	cout << "|~~~                     ";  ut.setcolor(7); cout << "TRIP RECORD";  ut.setcolor(15); cout << "                   ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.setcolor(7); cout << setw(3) <<"ID" << setw(8) << "Driver" << setw(8) << "Origin" << setw(10) << "Destiny" << setw(9) << "Date" << setw(11) << "Start" << setw(7) << "End" << endl;
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.setcolor(15);  displayRecord();
	ut.setcolor(3); cout << "-----------------------------------------------------------" << endl;
	ut.red(); cout << "\n Press anything to go back."; ut.white(); getchar(); getchar();
	return;
}


/* MENUS USER */

int Agency::mainMenu_User() {
	ut.clearScreen();
	ut.menuHeader();
	cout << "|~~~                     ";  ut.grey(); cout << "MAIN MENU";  ut.white(); cout << "                     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.grey(); cout << setw(30) << "You are logged in as: "; ut.white(); cout << Users.at(getPos(sessionID))->getName() << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl; ut.white();

	cout << setw(18) << "1. Account" << setw(30) << "3. Add Buddy" << endl;

	if (Users.at(sessionPos)->car()) { //caso seja driver
		cout << setw(23) << "2. Create Trip\n";
	}
	else { // caso seja passenger
		cout << setw(21) << "2. Join Trip\n";
	}

	ut.blue(); cout << "-----------------------------------------------------------" << endl;  ut.white();
	cout << "|~~~                                ";  ut.grey(); cout << "< 0. Logout >";  ut.white(); cout << "       ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option > 2) || (option < 0))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Invalid choice!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> option;
	}

	if (option == 0) {
		return 0;
	}
	else
		return option;
}

void Agency::optionsMainMenu_User() {
	unsigned short int option;

	while (option = mainMenu_User())
		switch (option)
		{
		case 1:
			optionsMenuAccount();
			break;
		case 2:
			if (Users.at(sessionPos)->car())
				optionsCreateTrip();
			else optionsJoinTrip();
			break;
		case 3:
			//TODO add buddy
			break;
		}
}

int Agency::menuAccount()
{
	ut.clearScreen();
	ut.menuHeader();
	cout << "|                          ";  ut.grey(); cout << "USERS";  ut.white(); cout << "                          |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.grey(); cout << setw(5) << "ID" << setw(10) << "User" << setw(13) << "Name" << setw(15) << "Balance" << setw(13) << "Num Cars" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.white();

	cout << setw(5) << Users.at(getPos(sessionID))->getID() << setw(10) << Users.at(getPos(sessionID))->getUsername() << setw(15) <<
		Users.at(getPos(sessionID))->getName() << setw(13) << Users.at(getPos(sessionID))->getBalance() << setw(12) << 1 << endl;

	ut.blue(); cout << "-----------------------------------------------------------" << endl;  ut.grey();
	cout << setw(20) << "1. Deposit" << setw(31) << "2. smth else" << endl; ut.white();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
		<< "|~~~                                 ";  ut.grey(); cout << "< 0. Return >";  ut.white(); cout << "     ~~~|" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	unsigned short int option;
	cout << "Type your choice: ";
	cin >> option;

	while (cin.fail() || (option < 0) || ((option > 2)))
	{
		if (cin.eof())
		{
			cin.clear();
			return 0;
		}
		cin.clear();
		cin.ignore(1000, '\n');
		ut.red(); cout << "> Invalid choice!" << endl;
		ut.white(); cout << "Please try again: ";
		cin >> option;
	}

	if (option == 0)
		return 0;
	return option;
}

void Agency::optionsMenuAccount()
{
	unsigned short int option;
	while (option = menuAccount())
		switch (option)
		{
		case 1:
			deposit();
			break;
		case 2:
			//idk
			break;
		}
}

int Agency::menuCreateTrip()
{
	ut.clearScreen();
	ut.menuHeader();
	cout << "|                       ";  ut.grey(); cout << "TRIP PLANNER";  ut.white(); cout << "                      |" << endl
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	ut.grey(); cout << setw(16) << "Code" << setw(33) << "Town" << endl;
	ut.blue(); cout << "-----------------------------------------------------------" << endl;
	ut.white(); displayStops();
	ut.blue(); cout << "-----------------------------------------------------------" << endl; ut.white();

	addTrip();
	return 0;
}

void Agency::optionsCreateTrip()
{
	unsigned short int option;
	while (option = menuCreateTrip())
		switch (option)
		{
		case 1:
			//TODO depositar dinheiro em balance
			break;
		case 2:
			//idk
			break;
		}
}

int Agency::menuJoinTrip()
{
	return 0;
}

void Agency::optionsJoinTrip()
{
}


/*FILES*/

/* EXTRACT AND SAVE */
void Agency::extractData() {
	extractUsers();
	extractBuddies();
	extractStops();
	extractTransactions();
	extractRecord();
}

void Agency::saveData() {
	saveUsers();
	saveBuddies();
	saveTransactions();
	saveRecord();
	return;
}

void Agency::extractUsers()
{
	ifstream Userfile("Users.txt");
	string line;


	if (Userfile.is_open())
	{
		if (!Users.empty()) Users.clear();

		while (getline(Userfile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //nome+balance+carro+user+pass
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1); //balance+carro+user+pass
			size_t pos3 = str2.find(";"); //posi�ao 3
			string str3 = str2.substr(pos3 + 1); //balance+user+pass
			size_t pos4 = str3.find(";"); //posi�ao 4
			string str4 = str3.substr(pos4 + 1); //user+pass
			size_t pos5 = str4.find(";"); //posi�ao 5

			string ids = line.substr(0, pos1); //string id
			string nome = str1.substr(0, pos2);
			string scar = str2.substr(0, pos3); //string carro
			string sbalance = str3.substr(0, pos4); //string balance
			string user = str4.substr(0, pos5);
			string pass = str4.substr(pos5 + 1);

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int
			bool bcar;
			if (scar == "1") //passa a tring carro para bool
				bcar = true;
			else bcar = false;

			float balancef = stof(sbalance, NULL); //passa o balance de string para float

			if (bcar)
			{
				//se o User tiver carro, adiciona um novo driver
				User *d1 = new Driver(idi, nome, balancef, user, pass);
				Users.push_back(d1);
			}
			else
			{
				//caso contrario adiciona um novo passenger
				User *p1 = new Passenger(idi, nome, balancef, user, pass);
				Users.push_back(p1);
			}
		}
		Userfile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::saveUsers()
{
	ofstream UserFile("Users.txt");

	if (UserFile.is_open())
	{
		for (unsigned int i = 0; i < Users.size(); i++)
		{
			UserFile << Users.at(i)->getID() << ";" << Users.at(i)->getName() << ";";

			if (Users.at(i)->car())
				UserFile << "1";
			else UserFile << "0";

			UserFile << ";" << Users.at(i)->getBalance() << ";" << Users.at(i)->getUsername() << ";" << Users.at(i)->getPassword() << endl;
		}
		UserFile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::extractBuddies()
{
	ifstream Buddiesfile("Buddies.txt");
	string line;

	if (Buddiesfile.is_open())
	{
		while (getline(Buddiesfile, line))
		{
			size_t pos1 = line.find(";"); //posi?ao 1
			string ids = line.substr(0, pos1); //string id do user

			string buddiess = line.substr(pos1 + 1); //string buddies

			int id = stoi(ids, nullptr, 10); //passa o id do user de string para int

			for (unsigned int i = 0; i < Users.size(); i++)
			{
				if (Users.at(i)->getID() == id) //se o user na posi?ao i ? o user do ficheiro
				{
					if (!Users.at(i)->getBuddies().empty())  Users.at(i)->deleteBuddies(); //se o vetor buddies desse user nao est? vazio, apaga os elementos existentes

					buddiess.append(","); //adiciona ? string buddies uma virgula no final

					while (!(buddiess.empty()))
					{
						int idbuddy = stoi(buddiess.substr(0, buddiess.find_first_of(",")), nullptr, 10); //id do buddy a analisar

						for (unsigned int j = 0; j < Users.size(); j++)
						{
							if (Users.at(j)->getID() == idbuddy)
							{
								Users.at(i)->addBuddy(Users.at(j)); //adiciona esse buddy ao vetor de buddies do user
								buddiess.erase(0, buddiess.find_first_of(",") + 1); //apaga esse buddy e a virgula seguinte da string de buddies
								break;
							}
						}
					}
				}
			}
		}

		Buddiesfile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::saveBuddies()
{
	ofstream BuddiesFile("Buddies.txt");


	if (BuddiesFile.is_open())
	{
		for (unsigned int i = 0; i < Users.size(); i++)
		{
			BuddiesFile << Users.at(i)->getID() << ";";

			string buddies_s;

			for (unsigned int j = 0; j < Users.at(i)->getBuddies().size(); j++)
			{
				buddies_s.append(to_string(Users.at(i)->getBuddies().at(j)->getID()));
				buddies_s.append(",");
			}

			buddies_s.erase(buddies_s.size() - 1, 1); //apaga a ultima virgula
			BuddiesFile << buddies_s << endl;
		}
		BuddiesFile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::extractTransactions() {

	ifstream Transfile("Transactions.txt");
	string line;

	int i = 0;

	if (Transfile.is_open())
	{
		if (!Transactions.empty()) Transactions.clear();

		while (getline(Transfile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //id+date+value
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1); //date+value
			size_t pos3 = str2.find(";"); //posi�ao 3


			string ids = line.substr(0, pos1); //string id
			string date = str1.substr(0, pos2);
			string svalue = str2.substr(0, pos3); //string balance

			int idi = stoi(ids, nullptr, 10); //passa o id de string para int

			float valuef = stof(svalue, NULL); //passa o balance de string para float

			Date d1(date);

			Transactions.push_back(Transaction(idi, d1, valuef)); //cria um novo elemento no vector
			i++;
		}

		Transfile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::saveTransactions() {

	ofstream TransFile("Transactions.txt");

	if (TransFile.is_open())
	{
		for (unsigned int i = 0; i < Transactions.size(); i++)
		{
			Transactions.at(i).save(TransFile);
		}
		TransFile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::extractStops() {

	ifstream Stopsfile("Stops.txt");
	string line;

	if (Stopsfile.is_open())
	{
		while (getline(Stopsfile, line))
		{
			size_t pos1 = line.find(";"); //posi?ao 1
			string code = line.substr(0, pos1); //string codigo da paragem
			string name = line.substr(pos1 + 1); //string nome da paragem

			stop s;
			s.code = code;
			s.name = name;
			stopsAvailable.push_back(s);
		}
		Stopsfile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::extractRecord()
{
	
	ifstream Recfile("Record.txt");
	string line;
	
	if (Recfile.is_open())
	{
		if (!Trips.empty()) Trips.clear();

		while (getline(Recfile, line))
		{

			size_t pos1 = line.find(";"); //posi�ao 1
			string str1 = line.substr(pos1 + 1); //driver+stopStart+stopEnd+date+horaStart+horaEnd
			size_t pos2 = str1.find(";"); //posi�ao 2
			string str2 = str1.substr(pos2 + 1); //stopStart+stopEnd+date+horaStart+horaEnd
			size_t pos3 = str2.find(";"); //posi�ao 3
			string str3 = str2.substr(pos3 + 1); //stopEnd+date+horaStart+horaEnd
			size_t pos4 = str3.find(";"); //posi�ao 4
			string str4 = str3.substr(pos4 + 1); //date+horaStart+horaEnd
			size_t pos5 = str4.find(";"); //posi�ao 5
			string str5 = str4.substr(pos5 + 1); //horaStart+horaEnd
			size_t pos6 = str5.find(";"); //posi�ao 6

			string idT_s = line.substr(0, pos1); //string id trip
			string idD_s = str1.substr(0, pos2); //string id driver
			string stopStart_s = str2.substr(0, pos3);
			string stopEnd_s = str3.substr(0, pos4);
			string date_s = str4.substr(0, pos5);
			string horaStart_s = str5.substr(0, pos6);
			string horaEnd_s = str5.substr(pos6 + 1);

			int idT_i = stoi(idT_s, nullptr, 10); //passa o idT de string para int
			int idD_i = stoi(idD_s, nullptr, 10); //passa o idD de string para int
			Stop sS(stopStart_s, 0);
			Stop sE(stopEnd_s, 0);
			Date d(date_s);
			Hour hS(horaStart_s);
			Hour hE(horaEnd_s);

			vector <Stop> s = { sS,sE };

			Trip T(idT_i, idD_i, s, d, hS, hE);
			Trips.push_back(T);
		} 
		Recfile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}

void Agency::saveRecord() {

	ofstream RecordFile("Record.txt");

	if (RecordFile.is_open())
	{
		for (unsigned int i = 0; i < Trips.size(); i++)
		{
			Trips.at(i).save(RecordFile);
		}
		RecordFile.close();
	}
	else { ut.red(); cerr << "ERROR: unable to open file." << endl; ut.white(); }
}


/* FUNCTIONS */

bool Agency::validUser(string username) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (username == Users.at(i)->getUsername())
			return true;
	}
	return false;
}

bool Agency::validPassword(int pos, string password) {
	if (password == Users.at(pos)->getPassword())
		return true;
	return false;
}

int Agency::findID(string username) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (username == Users.at(i)->getUsername())
			return Users.at(i)->getID();
	}
	return -1;
}

int Agency::getPos(int id) {
	for (unsigned int i = 0; i < Users.size(); i++) {
		if (id == Users.at(i)->getID())
			return i;
	}
	return -1;
}

int Agency::getLastId()
{
	return Users.at(Users.size() - 1)->getID();
}

void Agency::addUser(User * u)
{
	Users.push_back(u);
}

void Agency::displayUsers() {

	for (unsigned int i = 0; i < Users.size(); i++)
	{
		cout << setw(5) << Users.at(i)->getID();
		cout << setw(10) << Users.at(i)->getUsername();
		cout << setw(20) << Users.at(i)->getName();
		cout << setw(10) << setprecision(2) << fixed << Users.at(i)->getBalance();

		if (Users.at(i)->car())
			cout << setw(10) << "[X]" << endl;
		else cout << setw(10) << "[ ]" << endl;
	}

	return;
}

void Agency::displayBuddies() {

	for (unsigned int i = 0; i < Users.size(); i++)
	{
		ut.setcolor(7); cout << setw(10) << "   USER"; ut.blue(); cout << " | ";
		ut.white(); cout << Users.at(i)->getName() << endl;
		ut.setcolor(7); cout << setw(10) << "BUDDIES"; ut.blue(); cout << " | ";
		ut.white();
		for (unsigned int j = 0; j < Users.at(i)->getBuddies().size(); j++)
		{
			cout << Users.at(i)->getBuddies().at(j)->getName() << "   ";
		}

		cout << endl << endl;
	}

	return;
}

void Agency::displayTransactions() {

	sort(Transactions.begin(), Transactions.end(), [](Transaction &a, Transaction &b) {return a.GetDate() < b.GetDate(); });

	for (unsigned int i = 0; i < Transactions.size(); i++)
	{
		cout << Transactions.at(i);
	}

	return;
}

void Agency::displayStops() {
	for (unsigned int i = 0; i < stopsAvailable.size(); i++)
	{
		cout << setw(15) << stopsAvailable.at(i).code;
		cout << setw(35) << stopsAvailable.at(i).name;
		cout << endl;
	}
	return;
}

void Agency::displayRecord()
{
	for (unsigned int i = 0; i < Trips.size(); i++)
	{
		cout << Trips.at(i);
	}
}


void Agency::addTrip() {

	vector<Stop> tripPlan;
	vector<string> stopCodes;
	string stopCode;
	Date tripDate, currentDate; 
	//initialize current system's date
	currentDate.setCurrent();
	Hour endHour, startHour, currentHour;
	//initialize current system's date
	currentHour.setCurrent();

	int stopNumber = 1;

	ut.yellow(); cout << "Please enter your stops (CTRL + Z to END):\n"; ut.white();

	/*for (size_t i = 0; i < stopsAvailable.size(); i++)
	{
		cout << stopsAvailable[i];
	}*/

	while (1)
	{
		cout << "Stop # " << stopNumber << " : ";

		cin >> stopCode;
		stopCode = t.convertUpper(stopCode);

		//enquanto o utilizador nao inserir ctrl+z
		if (!cin.eof())
		{
			try
			{
				//se a paragem existe
				if (checkStop(stopCode)) {
					//se a paragem ja foi inserida lan�a a exce�ao
					if (find(stopCodes.begin(), stopCodes.end(), stopCode) != stopCodes.end()) {
						throw RepeatedStop(stopCode);
					}
					//caso corra tudo bem � adicionada ao vetor
					else {
						stopCodes.push_back(stopCode);
						stopNumber++;
					}
				}
				//se nao existe lan�a a exce�ao
				else
					throw NonexistentStop(stopCode);

			}
			catch (const NonexistentStop &e)
			{
				ut.red(); cout << e; ut.white();
			}
			catch (const RepeatedStop &e)
			{
				ut.red(); cout << e; ut.white();
			}
		}

		//fim da introdu�ao das paragens
		else {

			if (stopCodes.size() < 2)
			{
				ut.red(); cout << "ERROR: You did not enter at least 2 distinct stops.\n"; ut.white();
				Sleep(2500);
				ut.clearScreen();
			}
			else
			{
				//introducao do numero de lugares disponiveis
				ut.blue(); cout << "\nPlease enter the number of seats available ( minimun: 1 , maximum: 6):\n > "; cin.clear(); ut.white();
				int numSeats = ut.readInt(1, 6); cin.clear();

				//id da nova viagem a ser criada
				int idTrip = (int)Trips.size() + 1;

				//vetor de estrutura STOP
				for (unsigned int i = 0; i < stopCodes.size(); i++) {
					tripPlan.push_back(Stop(stopCodes.at(i), numSeats));
				}

				while (1) {

					try
					{
						//data da viagem
						int day, month, year;
						ut.blue(); cout << "\nPlease enter the date:\n "; cin.clear(); ut.white();
						cout << "> Day: "; cin >> day; cout << " > Month: "; cin >> month; cout << " > Year: "; cin >> year;
						tripDate.setDay(day); tripDate.setMonth(month); tripDate.setYear(year);

						//se a data nao � valida
						if (!tripDate.valid()) 
						{
							throw InvalidDate(tripDate);
						}
						else if (tripDate < currentDate)
						{
							throw PassedDate(day, month, year);
						}
						else if (currentDate.daysBetween(tripDate) > 365)
						{
							throw TooLong(day, month, year);
						}
						else
						{
							break;
						}

					}
					catch (const InvalidDate &e)
					{
						ut.red(); cout << e; ut.white();
					}
					catch (const PassedDate &e)
					{
						ut.red(); cout << e; ut.white();
					}
					catch (const TooLong &e)
					{
						ut.red(); cout << e; ut.white();
					}
					
				}

				while (1) {

					int actualTime = getUnixCode(currentDate, currentHour);

					try
					{
					
						//hora inicio
						int hourS, minutesS;
						ut.blue(); cout << "\nPlease enter starting time:\n "; cin.clear(); ut.white();
						cout << "> Hour: "; cin >> hourS; cout << " > Minutes: "; cin >> minutesS;
						//Hour startHour(hourS, minutesS);
						startHour.setHour(hourS); startHour.setMinutes(minutesS);

						int startUnix = getUnixCode(tripDate, startHour);

						if (!startHour.validHour())
						{
							throw InvalidHour(startHour.getHour(), startHour.getMinutes());							
						}
						else if (startUnix <= actualTime +3600 && startUnix >= actualTime)	//if entered time is in less than 1 hour = 3600 seconds
						{
							ut.red(); cout << "ERROR: Departure time must be at least 1 hour from now.\n"; ut.white();
						}
						else if (startUnix < actualTime)
						{
							throw PassedHour(startHour.getHour(), startHour.getMinutes());
						}
						else
						{
							break;
						}
					}
					catch (const InvalidHour &e)
					{
						ut.red(); cout << e; ut.white();
					}
					catch (const PassedHour &e)
					{
						ut.red(); cout << e; ut.white();
					}
				}
						
				while (1) {

					try
					{
						//hora fim
						int hourE, minutesE;
						ut.blue(); cout << "\nPlease enter finish time:\n "; cin.clear(); ut.white();
						cout << "> Hour: "; cin >> hourE; cout << "> Minutes: "; cin >> minutesE;
						//Hour endHour(hourE, minutesE);
						endHour.setHour(hourE); endHour.setMinutes(minutesE);

						if (!endHour.validHour())
						{
							throw InvalidHour(endHour.getHour(), endHour.getMinutes());
						}
						else if (endHour < startHour)
						{
							ut.red(); cout << "ERROR: The finish time can not be previous to the departure time.\n"; ut.white();
						}
						else
						{
							break;
						}
					}
					catch (const InvalidHour &e)
					{
						ut.red(); cout << e; ut.white();
					}
				}
						

				//criacao do objeto trip
				Trip trp(idTrip, sessionID, tripPlan, tripDate, startHour, endHour);

				//adicao da viagem ao vetor na agencia
				ut.green();  cout << "\n\nStops and number of seats successfully added to your trip.\n\n"; ut.white();
				Sleep(2500);
				Trips.push_back(trp);
				Users.at(sessionPos)->addTrip(trp);			//adiciona a viagem criada ao utilizador correspondente (VIAGEM A DECORRER)

				/*for (unsigned int i = 0; i < Trips.size(); i++) {
					cout << Trips.at(i).getID() << endl;
					for (unsigned int j = 0; j < Trips.at(i).getStops().size(); j++) {
						cout << Trips.at(i).getStops().at(j).getCode() << endl;
					}
				}
				system("pause");*/
			}
			break;
		}
	}
}

bool Agency::checkStop(string s) {

	bool exists = false;

	for (size_t i = 0; i < stopsAvailable.size(); i++)
	{
		if (stopsAvailable.at(i).code == s)
			exists = true;
	}

	return exists;
}

float Agency::deposit()
{
	float value;
	ut.yellow(); cout << "\n > "; ut.grey(); cout << "Insert the amount of money you want to deposit in your account: "; ut.white();
	cin >> value;

	if ((value > 0) && (value < 500)) {
		Users.at(sessionPos)->deposit(value);
		ut.yellow(); cout << "\n Success!"; ut.white();
	}
	else {
		ut.red(); cout << "\n Not a valid value!"; ut.white();
	}
	Sleep(2000);
	cin.clear();
	cin.ignore(1000, '\n');
	return 0;
}

/*
void Agency::runTrip(int tripID) {

Trip t;
int tripIndex;
vector<int> passengersID;

for (unsigned int i = 0; i < Trips.size(); i++)
{
if (Trips[i].getID() == tripID) {
t = Trips[i];
tripIndex = i;
break;
}
}

passengersID = t.getPassengers();
vector<string> stops = t.getStops();

for (size_t i = 0; i < stops.size(); i++)
{
string currentStop = stops.at(i);

ut.clearScreen();
ut.green(); cout << "Running trip # " << t.getID() << " :\n";
ut.grey(); cout << "Origin: " << t.getOrigin() << endl; cout << "Destination: " << t.getDestination() << endl;
cout << "\nDriver: " << Users[getPos(t.getID())]->getName() << " \n";
ut.white();  cout << "\nCurrent stop is " << currentStop << "\n";

if (i == t.getStops().size() - 1)
{
ut.blue(); cout << "Final destination reached!\n"; ut.white();
}
else {
//saida de passageiros
vector<User *> usersAway;

for (size_t i = 0; i < passengersID.size(); i++)
{
unsigned int vectorPos = getPos(passengersID[i]);

//se o ID � positivo, procura-se no vetor Users
if (passengersID[i] > 0)
{
//se a ultima paragem � a atual, ele sai
if (Users[vectorPos]->getLast() == currentStop)
{
usersAway.push_back(Users[vectorPos]);
}
}

//se o ID � negativo, procura-se no vetor de Guest
if (passengersID[i] < 0)
{
for (size_t j = 0; j < Guests.size(); j++)
{
//encontrado o guest do ID respetivo
if (Guests[j]->getID() == passengersID[i])
{
//se a paragem final � a atual, ele sai
if (Guests[j]->getEnd() == currentStop)
{
//criacao de um user local para ser adicionado ao vetor de entradas
User *u = new Passenger(Guests[j]->getName());
usersAway.push_back(u);
//TODO: quando sair adicionar transacao
}
}
}
}
}

//se houve alguma saida de passageiros
if (usersAway.size() > 0)
{
ut.red(); cout << "\n->Exited:\n"; ut.white();
for (size_t i = 0; i < usersAway.size(); i++)
{
cout << usersAway[i]->getName() << endl;
}

cout << endl;
//atualizacao do numero de lugares disponiveis
t.setAvailableSeats(t.getNumSeats() + (int)usersAway.size());
}

///entrada de passageiros///
vector<User *> usersOnBoard;

if (t.getNumSeats() > 0)
{
for (size_t i = 0; i < passengersID.size(); i++)
{
unsigned int vectorPos = getPos(passengersID[i]);

//se o ID � positivo, procura-se no vetor Users
if (passengersID[i] > 0)
{
//se a primeira paragem � a atual, ele entra
if (Users[vectorPos]->getFirst() == currentStop)
{
usersOnBoard.push_back(Users[vectorPos]);
}
}

//se o ID � negativo, procura-se no vetor de Guest
if (passengersID[i] < 0)
{
for (size_t j = 0; j < Guests.size(); j++)
{
//encontrado o guest do ID respetivo
if (Guests[j]->getID() == passengersID[i])
{
//se a paragem inicial � a atual
if (Guests[j]->getStart() == currentStop)
{
//criacao de um user local para ser adicionado ao vetor de entradas
User *u = new Passenger(Guests[j]->getName());
usersOnBoard.push_back(u);
}
}
}
}
}

//se houve alguma entrada de passageiros
if (usersOnBoard.size() > 0)
{
ut.green(); cout << "\n->Entered:\n"; ut.white();
for (size_t i = 0; i < usersOnBoard.size(); i++)
{
cout << usersOnBoard[i]->getName() << endl;
}

cout << endl;
t.setAvailableSeats(t.getNumSeats() - (int)usersOnBoard.size());
}
}

else
{
cout << "All seats are full at this stop.\n";
}

}

//espera pelo input da tecla Enter para passar � proxima paragem
cout << "\n\n-> ENTER to go to the next stop <-";
ut.getEnter();
}
}
*/

/*
//retorna o total do mes
float Agency::endMonth() {

typename vector<User *>::iterator it;
float totalMonth = 0;

for (it = users.begin(); it != users.end(); it++) {

totalMonth += (*it)->payment();
(*it)->resetTrips();   //s� tem efeito nos passenger

}

return totalMonth;
}
*/
int Agency::getUnixCode(Date &d, Hour &h) {

	int ret;
	struct tm info;

	info.tm_year = d.getYear() - 1900;
	info.tm_mon = d.getMonth() - 1;
	info.tm_mday = d.getDay();
	info.tm_hour = h.getHour();
	info.tm_min = h.getMinutes();
	info.tm_sec = 0;
	info.tm_isdst = -1;

	ret = mktime(&info);
	return ret;
}
