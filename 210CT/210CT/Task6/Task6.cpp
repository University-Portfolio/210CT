#include "Task6.h"
#include "../Definitions.h"

#include <iostream>
#include <time.h>
#include <list>

#define CUBE_SIZE_MAX 100


using namespace TASK_6;

struct Node;
typedef std::list<Cube> Cubes;
typedef std::list<Node> Nodes;
typedef std::list<Node*> PtrNodes;

/**
Node is per cube and stores all cubes that could come before or after.

**/
struct Node 
{
	const Cube cube;

	//Values used during Dijkstra's 
	int working_value = 0;
	Node* working_previous = nullptr;
	bool locked = false;

	//All possible cubes that could come before or after the cube
	PtrNodes above;
	PtrNodes below;

private:
	Node(Cube cube) : cube(cube) {}

public:
	static void BuildGraph(Cubes& cubes, Nodes& output)
	{
		//Convert cubes to nodes
		for (Cube& cube : cubes)
			output.push_back(Node(cube));

		//Generate relationships
		for(Node& node: output)
			for (Node& other: output) 
			{
				if (node.cube.colour != other.cube.colour)
				{
					if (node.cube.size < other.cube.size)
						node.above.push_back(&other);

					else if (node.cube.size > other.cube.size)
						node.below.push_back(&other);
				}
			}
	}

	void LockNode(Node* previous, int value)
	{
		working_previous = previous;
		working_value = value;
		locked = true;
	}

	void LockAsRoot()
	{
		working_previous = nullptr;
		working_value = -cube.size;
		locked = true;
	}

	void ResetNode() 
	{
		working_previous = nullptr;
		working_value = 0;
		locked = false;
	}

	inline bool operator==(Node& other) { return cube == other.cube; }
	inline bool operator!=(Node& other) { return cube != other.cube; }

	inline bool IsTopCube() { return above.size() == 0; }
	inline bool IsBottomCube() { return below.size() == 0; }
};



/**
Prints out a list of cubes in a table containing colour and size

@param	cubes			list containing cubes to print
@param	column_count	The number of columns for the table to have (default is 4)
**/
void Print(Cubes& cubes, int column_count = 4)
{
	int column = 0;

	for (int i = 0; i < column_count; i++)
		std::cout << "#===============";
	std::cout << "#\n";

	for (int i = 0; i < column_count; i++)
		std::cout << "#SIZE\tCOLOUR\t";
	std::cout << "#\n";

	for (int i = 0; i < column_count; i++)
		std::cout << "#===============";
	std::cout << "#\n";


	for (Cube c : cubes)
	{
		std::cout << "#" << c.size << '\t' << COLOUR::ToString(c.colour) << '\t';

		if (column++ == column_count - 1)
		{
			column = 0;
			std::cout << "#\n";
		}
	}

	//Fill in rest of row with blank
	if (column != 0)
	{
		for (;column < column_count;column++)
		{
			std::cout << "#               ";
		}
		std::cout << "#\n";
	}


	for (int i = 0; i < column_count; i++)
		std::cout << "#===============";
	std::cout << "#\n";
}


/**
Randomly generate cubes a specific amount of cubes and store then in the list

@param	cubes	The list to which the cubes should be stored
@param	amount	The amount of cubes to generate
**/
void RandomlyPopulate(Cubes& cubes, const int amount)
{
	srand(time(nullptr));

	for (int i = 0; i < amount; i++)
	{
		float size = rand() % CUBE_SIZE_MAX + 1;
		Colour colour = Colour(rand() % 4);

		cubes.push_back(Cube(size, colour));
	}
}

/**
Perform Dijkstra's algorithm to find longest(largest path) from source to sink

@param	source		The source node
@param	sink		The sink node
@param	output		List to store the output nodes in

@return	The length of the path
**/
int FindHighestPath(Node* source, Node* sink, Nodes& output) 
{
	//For pretty printing
#define NODE(sink) (*sink).cube.size << ":" << COLOUR::ToString((*sink).cube.colour)

	LOG(NODE(source) << " to " << NODE(sink));

	if (source == sink)
	{
		output.push_back(*source);
		return source->cube.size;
	}

	PtrNodes set_nodes;
	source->LockAsRoot();
	set_nodes.push_back(source);

	int current_cheapest_value = 0;
	Node* current_cheapest = nullptr;
	Node* current_previous = nullptr;

	while (true)
	{
		LOG("=======================");
		current_cheapest_value = 0;
		current_cheapest = nullptr;
		current_previous = nullptr;

		for (Node* current_node : set_nodes)
		{
			LOG(NODE(current_node) << " possible: " << current_node->above.size());

			for (Node* next_node : current_node->above)
				if (!next_node->locked)
				{

					int weight = current_node->working_value;
					LOG("\t\t" << NODE(next_node) << " " << -weight << "(" << (next_node->cube.size - weight) << ")");
					
					if (weight < next_node->working_value)
					{
						next_node->working_value = weight;
						next_node->working_previous = current_node;
					}

					if (next_node != sink && (next_node->working_value > current_cheapest_value || !current_cheapest))
					{
						current_cheapest_value = next_node->working_value;
						current_cheapest = next_node;
						current_previous = next_node->working_previous;
					}
				}
		}
		
		//If no element has been chosen assume all possiblities have been exhausted
		if (!current_cheapest)
		{
			current_cheapest_value = sink->working_value;
			current_cheapest = sink;
			current_previous = sink->working_previous;
		}

		current_cheapest_value -= current_cheapest->cube.size;

		LOG("\tLocking " << NODE(current_cheapest) << " for " << -current_cheapest_value << " from " << NODE(current_previous));
		current_cheapest->LockNode(current_previous, current_cheapest_value);
		set_nodes.push_back(current_cheapest);

		//Solution found
		if (current_cheapest == sink)
		{
			LOG("SOLUTION FOUND (" << current_cheapest_value << ")");
			break;
		}
	}

	//Build output
	Node* next_node = current_cheapest;

	while (next_node != nullptr)
	{
		output.push_back(*next_node);
		next_node = next_node->working_previous;
	}
	LOG("LEAVING return:" << -current_cheapest_value);
	return -current_cheapest_value;
}

/**
Finds the largest possible stack that can be made

@param	cubes		The list of all cubes
@param	solution	The list to be used to store the solution

@return	whether a solution is found
**/
bool StoreSolution(Cubes& cubes, Cubes& solution, int& solution_amount)
{
	//Generate all key nodes
	Nodes nodes;
	PtrNodes sources;
	PtrNodes sinks;

	Node::BuildGraph(cubes, nodes);
	for (Node& node : nodes)
	{
		if (node.IsTopCube())
			sinks.push_back(&node);

		if (node.IsBottomCube())
			sources.push_front(&node);
	}

	LOG("Found " << sources.size() << " sources");
	LOG("Found " << sinks.size() << " sinks");
	LOG("For " << nodes.size() << " nodes");

	//Find all possible paths from all sources to all sinks
	Nodes highest_path;
	int highest_path_amount = 0;
	Nodes current_path;

	for (Node* source : sources)
		for (Node* sink : sinks)
		{
			current_path.clear();
			int current_amount = FindHighestPath(source, sink, current_path);
			
			for (Node& node : nodes)
				node.ResetNode();

			if (current_amount > highest_path_amount)
			{
				highest_path_amount = current_amount;
				highest_path = current_path;
			}
		}


	if (highest_path_amount)
	{
		//Convert nodes just to cubes
		for (Node& node : highest_path)
			solution.push_back(node.cube);

		solution_amount = highest_path_amount;
		return true;
	}
	else
		return false;
}

void TASK_6::Execute() 
{
	std::cout << "How many cubes: ";
	int n;
	std::cin >> n;

	Cubes cubes;
	RandomlyPopulate(cubes, n);
	std::cout << "Generated Cubes:\n";
	Print(cubes);

	Cubes solution;
	int solution_amount;

	if (StoreSolution(cubes, solution, solution_amount))
	{
		std::cout << "Solution found of height " << solution_amount << ":\n";
		Print(solution, 1);
	}
	else
	{
		std::cout << "No solution found\n";
	}


}
