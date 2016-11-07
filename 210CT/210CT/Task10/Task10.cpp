#include "Task10.h"
#include <iostream>

using namespace TASK_10;


void TASK_10::Execute() 
{
	int n;
	std::cout << "Input number of children: ";
	std::cin >> n;
	Child* root = nullptr;

	//Populate
	{
		Child* last_child = nullptr;

		std::cin.get(); //Clear
		std::cout << "Input names of each child:\n";
		for (int i = 0; i < n; i++)
		{
			std::string name;
			std::getline(std::cin, name);

			if (last_child)
				last_child = new Child(name, last_child);
			else
				last_child = new Child(name);
		}

		root = last_child->GetRoot();
		root->SetLast(last_child);
	}

	//Play game
	{
		Child* start = root;

		std::cout << "From 1-" << n << ", which child should start? ";
		int index;
		std::cin >> index;
		index--;

		for (;index > 0;index--)
			start = start->GetNext();

		std::cout << start->GetName() << " starts\n";


		Child* current = start;
		int count = 0;

		while (true)
		{
			if (current->GetNext() == start)
			{
				if (count == 1)
					break;
				else
				{
					std::cout << '\t' << current->GetName() << " goes out\n";
					count = 0;
					current->Remove();
					delete current;
					current = start;
				}
			}
			else 
			{
				count++;
				current = current->GetNext();
			}
		}

		std::cout << current->GetName() << " wins!\n";
		delete start;
		delete current;
	}

}