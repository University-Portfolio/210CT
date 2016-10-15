#include "Task1.h"
#include <iostream>

void TASK_1::Execute()
{
	int lay_rate, hatch_time, total_days;

	std::cout << "Eggs per day: ";
	std::cin >> lay_rate;

	std::cout << "Egg hatch time: ";
	std::cin >> hatch_time;

	std::cout << "For how many days? ";
	std::cin >> total_days;

	Population aliens(1, hatch_time, lay_rate);

	for (int i = 1; i <= total_days; i++)
	{
		aliens.LayEggs();
		std::cout << "Day " << i << "\tPopulation: " << aliens.total << std::endl;
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