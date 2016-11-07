#include "Tools.h"
Utilities uu;

Tools::Tools()
{
}

Tools::~Tools()
{
}

bool Tools::outputName(string output)
{
	if ((int)output.at(0) >= 48 && (int)output.at(0) <= 57) // verifica se o primeiro elemento da string corresponde a um inteiro no codigo ascii (entre 0 e 9)
		return false;
	else return true;
}

string Tools::insertPassword() {
	string password;
	char pass[32];
	char x;
	int i = 0;

	for (i = 0;;) {
		x = _getch();
		if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x >= '0'&& x <= '9')) {
			pass[i] = x;
			++i;
			cout << "*";
		}
		if (x == '\b' && i >= 1)
		{
			cout << "\b \b";
			--i;
		}
		if (x == '\r')
		{
			pass[i] = '\0';
			break;
		}
	}
	password = pass;
	cin.clear();
	//cin.ignore();
	return password;
}

bool Tools::sameString(string a, string b)
{
	if (a == b)
		return true;
	return false;
}
