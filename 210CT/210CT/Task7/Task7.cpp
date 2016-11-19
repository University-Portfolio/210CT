#include "Task7.h"
#include "../IO.h"

#include <fstream>


using namespace TASK_7;

bool Path::Contains(Coord coord)
{
	for (Node& n : stack)
		if (n.coord == coord)
			return true;
	return false;
}

void Path::Print(Maze& maze)
{
	for (int i = 0; i < stack.size(); i++)
		IO::out << (i==0?"":"->") << "(" << (stack[i].coord.x + 1) << "," << (maze.height - stack[i].coord.y) << ")";
	IO::out << '\n';
}

void Maze::Print(const bool print_person /*= true */, Path* path /*= nullptr*/) const
{
	//Coordinate
	IO::out << ' ';
	for (int y = 0; y < width - 1; y++)
		IO::out << ' ';
	IO::out << "|(" << width << "," << height << ")\n";

	//Line
	IO::out << '+';
	for (int y = 0; y < width; y++)
		IO::out << '-';
	IO::out << "+\n";

	//Grid
	for (int y = 0; y < width; y++)
	{
		IO::out << '|';

		for (int x = 0; x < height; x++)
		{
			const bool is_path = path ? path->Contains(Coord(x, y)) : false;
			IO::out << (print_person && (person.x == x && person.y == y) ? '$' : walls[x][y] ? '#' : is_path ? '~' : ' ');
		}

		IO::out << "|\n";
	}

	//Line
	IO::out << '+';
	for (int y = 0; y < width; y++)
		IO::out << '-';
	IO::out << "+\n";

	//Coordinate
	IO::out << " |(1,1)\n";
}

void Maze::Parse(const std::string& raw_input)
{
	int i = 0;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			walls[x][y] = (raw_input[i++] == '0');
}

void Maze::PrintAllPaths() 
{
	Path path;
	path.Push(Node(person));

	while (!path.IsEmpty())
	{
		Node current_node = path.Pop();
		bool found_next = false;

		//Search adjacent tiles
		while (!found_next && current_node.search_index < 4)
		{
			switch (current_node.search_index++)
			{
			case 0: //Up
				if (current_node.from_index != 2)
				{
					Coord next(current_node.coord.x, current_node.coord.y + 1);
					if (!path.Contains(next) && IsValid(next))
					{
						found_next = true;
						path.Push(current_node);
						path.Push(Node(next, 0));
						
						if (IsExit(next))
						{
							Print(true, &path);
							path.Print(*this);
						}
					}
				}
				break;

			case 1: //Right
				if (current_node.from_index != 3)
				{
					Coord next(current_node.coord.x + 1, current_node.coord.y);
					if (!path.Contains(next) && IsValid(next))
					{
						found_next = true;
						path.Push(current_node);
						path.Push(Node(next, 1));

						if (IsExit(next))
						{
							Print(true, &path);
							path.Print(*this);
						}
					}
				}
				break;

			case 2: //Down
				if (current_node.from_index != 0)
				{
					Coord next(current_node.coord.x, current_node.coord.y - 1);
					if (!path.Contains(next) && IsValid(next))
					{
						found_next = true;
						path.Push(current_node);
						path.Push(Node(next, 2));

						if (IsExit(next))
						{
							Print(true, &path);
							path.Print(*this);
						}
					}
				}
				break;

			case 3: //Left
				if (current_node.from_index != 1)
				{
					Coord next(current_node.coord.x - 1, current_node.coord.y);
					if (!path.Contains(next) && IsValid(next))
					{
						found_next = true;
						path.Push(current_node);
						path.Push(Node(next, 3));

						if (IsExit(next))
						{
							Print(true, &path);
							path.Print(*this);
						}
					}
				}
				break;
			}
		}
	}

	IO::out << "Searched all paths.\n";
}

bool ReadFile(const char* path, std::string& raw_output)
{
	std::ifstream file;
	file.open(path, std::ifstream::in);
	
	if (!file.is_open())
		return false;
	
	char c;
	while (file.get(c))
		if (c != '\n' && c != ' ')
			raw_output += c;
	file.close();
	
	return true;
}


void TASK_7::Execute() 
{
	std::string raw_input;
	std::string file_path = "H:/210CT - Programming/Portfolio/210CT/210CT/Task7/input.txt";

	int n, m;

	IO::out << "Input width of maze: ";
	IO::in >> n;

	IO::out << "Input height of maze: ";
	IO::in >> m;

	IO::out << "Input path of file contain maze: " << "\n(Example maze file for n:4, m:5)\n";
	IO::out << "\t0100\n";
	IO::out << "\t1101\n";
	IO::out << "\t0111\n";
	IO::out << "\t0100\n";
	IO::out << "\t1110\n";
	
	IO::in >> file_path;

	while (!ReadFile(file_path.c_str(), raw_input))
	{
		IO::out << "Invalid file path!\nInput path of file contain maze:\n";
		IO::in >> file_path;
	}

	Maze maze(n, m);
	maze.Parse(raw_input);
	maze.Print(false);


	Coord person;
	IO::out << "Please input the coordinates of the person:\n";

	do {
		IO::out << "x:";
		IO::in >> person.x;
		IO::out << "y:";
		IO::in >> person.y;
		
		//Convert x,y to correct indices
		person.x--;
		person.y = maze.height - person.y;
		
		if(!maze.IsValid(person))
			IO::out << "Invalid input! (The person cannot be placed in a wall)\nPlease input the coordinates of the person:\n";
		else
			break;
	} while (true);

	maze.person = person;
	maze.Print();

	maze.PrintAllPaths();
}