#pragma once

/**
TASK (Advanced)

Write a program to predict the number of creatures in a fictional alien invasion. An
alien lays X eggs each day (there are no genders in this species) and the eggs
hatch after Y days. If X is 3 and Y is 5, how many aliens will there be 30 days after a
single alien invades?
**/

namespace TASK_1 
{
	void Execute();

	struct Population 
	{
		unsigned int total;
		unsigned int* egg_buffer;

		const unsigned int hatch_delay;
		const unsigned int lay_amount;

		Population(const int starting_amount, const int hatch_delay, const int lay_amount)
			: total(starting_amount), hatch_delay(hatch_delay), lay_amount(lay_amount)
		{
			if (hatch_delay)
				egg_buffer = new unsigned int[hatch_delay]{0};
		}

		~Population() 
		{
			if(egg_buffer)
				delete[] egg_buffer;
		}

		void LayEggs();
	};
};