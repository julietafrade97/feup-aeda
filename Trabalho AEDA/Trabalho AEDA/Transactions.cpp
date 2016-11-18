#include "Transactions.h"

Transaction::Transaction()
{
}

Transaction::Transaction(int id, Date date, float value)
{
	this->id = id;
	this->date = date;
	this->value = value;
}

int Transaction::GetId() const
{
	return id;
}

Date Transaction::GetDate() const
{
	return date;
}

float Transaction::GetValue() const
{
	return value;
}

ostream& operator<<(ostream & out, const Transaction & t) {

	out << setw(5) << t.GetId();

	if (t.GetDate().getDay() < 10)
		out << setw(19) << t.GetDate();
	else out << setw(20) << t.GetDate();

	out << setw(22) << setprecision(2) << fixed << t.GetValue();
	out << endl; return out;
}

void Transaction::save(ofstream & out) const {

	out << GetId() << ";" << GetDate() << ";" << GetValue() << endl;
}