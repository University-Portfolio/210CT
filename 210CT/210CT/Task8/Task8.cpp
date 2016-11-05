#include "Task8.h"
#include <time.h>
#include <iostream>


using namespace TASK_8;


void TASK_8::Execute() 
{
	srand(time(nullptr));

	std::cout << "How many integers would you like to be in the array? ";
	int size;
	std::cin >> size;

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
	std::cout << '\n';
	Print(standard_qs);
	std::cout << '\n';

	std::cout << "Which sorted index you like to fetch? ";
	int m;
	std::cin >> m;

	QuickSort(standard_qs, standard_swaps);
	std::cout << "Standard (Full sort then fetch):\n";
	Print(standard_qs);
	std::cout << '\t' << standard_qs[m] << " with " << standard_swaps << " swaps\n";

	std::cout << '\n';

	int val = QuickSortSearch(partial_qs, m, partial_swaps);
	std::cout << "Partial (Prioritize index until in place):\n";
	Print(partial_qs);
	std::cout << '\t' << val << " with " << partial_swaps << " swaps\n";

}