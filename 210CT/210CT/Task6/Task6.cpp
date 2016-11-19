#include "Task6.h"
#include "../IO.h"
#include <time.h>
#include <vector>

#define CUBE_SIZE_MAX 1000

using namespace TASK_6;


void CubeStack::Print(int column_count/*= 4*/)
{
	int column = 0;

	for (int i = 0; i < column_count; i++)
		IO::out << "#===============";
	IO::out << "#\n";

	for (int i = 0; i < column_count; i++)
		IO::out << "#SIZE\tCOLOUR\t";
	IO::out << "#\n";

	for (int i = 0; i < column_count; i++)
		IO::out << "#===============";
	IO::out << "#\n";


	for (CubeInfo c : cubes)
	{
		IO::out << "#" << c.cube.size << '\t' << COLOUR::ToString(c.cube.colour) << '\t';

		if (column++ == column_count - 1)
		{
			column = 0;
			IO::out << "#\n";
		}
	}

	//Fill in rest of row with blank
	if (column != 0)
	{
		for (; column < column_count; column++)
		{
			IO::out << "#               ";
		}
		IO::out << "#\n";
	}


	for (int i = 0; i < column_count; i++)
		IO::out << "#===============";
	IO::out << "#\n";
}

void CubeTower::Print()
{
	IO::out << "#===============#\n";
	IO::out << "#SIZE\tCOLOUR\t#\n";
	IO::out << "#===============#\n";

	for (CubeInfo* c : cubes)
		IO::out << "#" << c->cube.size << '\t' << COLOUR::ToString(c->cube.colour) << "\t#\n";

	IO::out << "#===============#\n";
}

void CubeStack::Add(Cube cube)
{
	if (cubes.size() == 0)
		cubes.push_back(cube);

	//Add cube in correct order (Doesn't matter the order of cubes the same size)
	else
	{
		for (auto it = cubes.begin(); it != cubes.end(); ++it)
			if (it->cube < cube)
			{
				cubes.insert(it, cube);
				return;
			}

		//Only gets here if smaller than anything else in the list
		cubes.push_back(cube);
	}
}

CubeTower GetLargestSubTower(std::list<CubeInfo>& cubes, std::list<CubeInfo>::iterator& node)
{
	auto next_node = node; ++next_node;

	if (next_node == cubes.end())
	{
		CubeTower tower;
		tower.Add(*node);
		return tower;
	}
	
	//Reset solution flag
	for (auto it = next_node; it != cubes.end(); ++it)
		it->found_temp_solution = false;

	std::vector<CubeTower> towers;

	for (auto it = next_node; it != cubes.end(); ++it)
	{
		if (!it->found_temp_solution && it->cube.colour != node->cube.colour && it->cube.size != node->cube.size)
		{
			it->found_temp_solution = true;
			CubeTower tower = GetLargestSubTower(cubes, it);
			towers.push_back(tower);
		}
	}

	CubeTower largest_tower;

	for (CubeTower tower : towers)
		if (tower.GetSize() > largest_tower.GetSize())
			largest_tower = tower;
	
	largest_tower.Add(*node);
	return largest_tower;
}

CubeTower CubeStack::GetLargestTower()
{
	CubeTower output;

	//Should realistically reset all found_solid_solution values here, but doesn't matter for example

	//Go through all cubes treating them as the bottom of the tower
	for (auto node = cubes.begin(); node != cubes.end(); ++node)
	{
		//Previous solution was found involving cube (So not point considering it for bottom of tower)
		if (node->found_solid_solution)
			continue;
		
		IO::out_debug << "\tFinding size for base " << node->cube.size << ":" << COLOUR::ToString(node->cube.colour) << " ";
		CubeTower tower = GetLargestSubTower(cubes, node);
		IO::out_debug << " Found: " << tower.GetSize() << '\n';

		//Flag found_solution
		for (CubeInfo* c : tower.cubes)
			c->found_solid_solution = true;

		if (output.GetSize() < tower.GetSize())
			output = tower;
	}

	return output;
}

/**
Randomly generate cubes a specific amount of cubes and store then in the list

@param	cubes	The list to which the cubes should be stored
@param	amount	The amount of cubes to generate
**/
void RandomlyPopulate(CubeStack& cube_stack, const int amount)
{
	srand(time(nullptr));

	for (int i = 0; i < amount; i++)
	{
		float size = rand() % CUBE_SIZE_MAX + 1;
		Colour colour = Colour(rand() % 4);

		cube_stack.Add(Cube(size, colour));
	}
}


void TASK_6::Execute() 
{
	IO::out << "Would you like to randomly generate the cubes? (y/n) ";
	char random;
	IO::in >> random;

	CubeStack cube_stack;

	if (random == 'y' || random == 'Y')
	{
		IO::out << "How many cubes: ";
		int n;
		IO::in >> n;
		RandomlyPopulate(cube_stack, n);
	}
	else 
	{
		IO::out << "Input a number then a character for each cube(Colours are Red, Green, Blue, Yellow). Onces finsihed, type '0'\n\te.g. '100' then 'r' for a red cube of size 100\n";

		int size;
		char colour;

		while (true)
		{
			IO::in >> size;
			if (!size)
				break;

			IO::in >> colour;
			if (colour == '0')
				break;

			//Convert into lowercase
			if (colour < 97)
				colour += 32;

			switch (colour)
			{
			case 'r':
				cube_stack.Add(Cube(size, RED));
				break;

			case 'g':
				cube_stack.Add(Cube(size, GREEN));
				break;

			case 'y':
				cube_stack.Add(Cube(size, YELLOW));
				break;

			case 'b':
				cube_stack.Add(Cube(size, BLUE));
				break;

			default:
				IO::out << "Character '" << colour << "' is not associated with any colour.\n";
				break;
			}
		}


	}


	IO::out << "All Cubes:\n";
	cube_stack.Print();

	CubeTower tower = cube_stack.GetLargestTower();
	IO::out << "Largest tower found (" << tower.GetSize() << "):\n";
	tower.Print();
}
