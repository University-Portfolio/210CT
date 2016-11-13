#include "Task8.h"
#include "../IO.h"
#include <time.h>


using namespace TASK_8;


void TASK_8::Execute() 
{
	srand(time(nullptr));

	IO::out << "How many integers would you like to be in the array? ";
	int size;
	IO::in >> size;

	std::vector<int> standard_qs;
	std::vector<int> partial_qs;
	int standard_swaps = 0;
	int partial_swaps = 0;


	for (int i = 0; i < size; i++)
	{
		const int val = rand() % 100;
		standard_qs.push_back(val);
		partial_qs.push_back(val);
	}
	IO::out << '\n';
	Print(standard_qs);
	IO::out << '\n';

	IO::out << "Which sorted index you like to fetch? ";
	int m;
	IO::in >> m;

	QuickSort(standard_qs, standard_swaps);
	IO::out << "Standard (Full sort then fetch):\n";
	Print(standard_qs);
	IO::out << '\t' << standard_qs[m] << " with " << standard_swaps << " swaps\n";

	IO::out << '\n';

	int val = QuickSortSearch(partial_qs, m, partial_swaps);
	IO::out << "Partial (Prioritize index until in place):\n";
	Print(partial_qs);
	IO::out << '\t' << val << " with " << partial_swaps << " swaps\n";

}