#pragma once
#include <string>

/**
TASK (Advanced)

Using the model of a circular single-linked list, implement the following scenario:
N children stand in a circle; one of the children starts counting the others clockwise. Every Nth child leaves the game. The winner is the one who remains.
Notes: Read the number of children, the childrens' names and the one starting to count from the standard input. Input: 4; Diana, Michael, David, Mary; Start: Diana; Winner: Michael.

**/

namespace TASK_10
{
	struct Child 
	{
	private:
		std::string child;
		
		Child* root = nullptr;
		Child* last = nullptr;
		Child* next = nullptr;

	public:
		Child(std::string name) : child(name), root(this)
		{}

		Child(std::string name, Child* last) : child(name), root(last->root), last(last)
		{
			last->next = this;
		}

		void SetLast(Child* last)
		{
			this->last = last;
			last->next = this;
		}

		Child* GetNext()
		{
			//Assume at next is null at loop point
			return next ? next : root;
		}

		Child* GetRoot() { return root; }
		inline bool IsRoot() { return root == this; }

		void Remove() 
		{
			last->next = next;

			if(next)
				next->last = last;
		}

		inline const char* GetName() { return child.c_str(); }
	};

	void Execute();
}
