#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Hour {
private:
	int hour;
	int minutes;
public:
	Hour() {};
	Hour(string hour);
	int getHour() const;
	int getMinutes() const;
	void setHour(int hour);
	void setMinutes(int mimnutes);
};