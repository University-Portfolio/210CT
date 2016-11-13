#include "Task1.h"
#include "../IO.h"

void TASK_1::Execute()
{
	int lay_rate, hatch_time, total_days;

	IO::out << "Eggs per day: ";
	IO::in >> lay_rate;

	IO::out << "Egg hatch time: ";
	IO::in >> hatch_time;

	IO::out << "For how many days? ";
	IO::in >> total_days;

	Population aliens(1, hatch_time, lay_rate);

	for (int i = 1; i <= total_days; i++)
	{
		aliens.LayEggs();
		IO::out << "Day " << i << "\tPopulation: " << aliens.total << '\n';
	}
}

void TASK_1::Population::LayEggs()
{
	//Hatch eggs
	total += egg_buffer[0];

	//Shift rest of eggs by a day
	for (int i = 0; i < hatch_delay - 1; i++)
		egg_buffer[i] = egg_buffer[i + 1];

	//Lay eggs
	egg_buffer[hatch_delay - 1] = total * lay_amount;

}