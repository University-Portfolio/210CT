#include "Task10.h"
#include "../IO.h"

using namespace TASK_10;


void TASK_10::Execute() 
{
	int n;
	IO::out << "Input number of children: ";
	IO::in >> n;
	Child* root = nullptr;

	//Populate
	{
		Child* last_child = nullptr;

		IO::out << "Input names of each child: \n";
		for (int i = 0; i < n; i++)
		{
			std::string name;
			IO::in >> name;

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

		IO::out << "From 1-" << n << ", which child should start? ";
		int index;
		IO::in >> index;
		index--;

		for (;index > 0;index--)
			start = start->GetNext();

		IO::out << start->GetName() << " starts\n";


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
					IO::out << '\t' << current->GetName() << " goes out\n";
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

		IO::out << current->GetName() << " wins!\n";
		delete start;
		delete current;
	}

}