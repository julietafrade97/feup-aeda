#include "Guest.h"

Guest::Guest()
{
}

Guest::~Guest()
{
}

string Guest::getName() const
{
	return name;
}

string Guest::getStart() const
{
	return start;
}

string Guest::getEnd() const
{
	return end;
}

int Guest::getID() const
{
	return guestID;
}

bool Guest::searchTrip(vector<Trip> &vec)  //vec = vetor das viagens da agencia
{
	unsigned int posBeg = -1, posEnd = -1;
	for (size_t i = 0; i < vec.size(); i++)
	{
		vector<string> stops = vec[i].getStops();
		for (size_t j = 0; j < stops.size(); i++)
		{
			if (stops[j] == this->start)
				posBeg = j;

			if (stops[j] == this->end)
				posEnd = j;
		}

		//se ambos os indices foram atualizados
		if (posBeg != -1 && posEnd != -1)
			//se a paragem inicial do guest vem antes da final, para a viagem indicada, return true;
			if (posBeg < posEnd) {
				this->currentTrip = vec[i].getID();
				vec[i].addPassenger(this->guestID);
				return true;
			}
		
	}
	
	//nenhuma das condi�oes de aceita��o foi obtida
	return false;
}
