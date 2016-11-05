#include "Task7.h"
#include "../Definitions.h"

#include <fstream>
#include <iostream>


using namespace TASK_7;


void Path::Print(Maze& maze)
{
	for (int i = 0; i < size; i++)
		std::cout << "(" << (stack[i].x + 1) << "," << (maze.height - stack[i].y) << ")->";
	std::cout << '\n';
}

void Maze::Print(const bool print_person /*= true */, Path* path /*= nullptr*/) const
{
	//Coordinate
	std::cout << ' ';
	for (int y = 0; y < width - 1; y++)
		std::cout << ' ';
	std::cout << "|(" << width << "," << height << ")\n";

	//Line
	std::cout << '+';
	for (int y = 0; y < width; y++)
		std::cout << '-';
	std::cout << "+\n";

	//Grid
	for (int y = 0; y < width; y++)
	{
		std::cout << '|';

		for (int x = 0; x < height; x++)
		{
			const bool is_path = path ? path->Contains(Coord(x, y)) : false;
			std::cout << (print_person && (person.x == x && person.y == y) ? '$' : walls[x][y] ? '#' : is_path ? '~' : ' ');
		}

		std::cout << "|\n";
	}

	//Line
	std::cout << '+';
	for (int y = 0; y < width; y++)
		std::cout << '-';
	std::cout << "+\n";

	//Coordinate
	std::cout << " |(1,1)\n";
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
	path.Push(person);
	Visit(person);
	

	while (path.Size())
	{
		Coord current = path.Pop();
		const Coord check[]{ current + Coord(0, 1),current + Coord(0, -1), current + Coord(-1, 0), current + Coord(1, 0) };
		bool moved = false;

		for (const Coord coord : check)
		{
			//LOG("Check (" << coord.x << "," << coord.y << ")");
			//LOG("\tValid:" << IsValid(coord));
			//LOG("\tVisited:" << Visited(coord));

			if (IsValid(coord) && !Visited(coord))
			{
				//LOG("Adding (" << coord.x << "," << coord.y << ")");

				Visit(coord);
				path.Push(current);
				path.Push(coord);
				if (IsExit(coord))
				{
					std::cout << "=================================\n";
					LOG("Solution found at (" << coord.x << "," << coord.y << ")");
					Print(true, &path);
					path.Print(*this);
					std::cout << '\n';
				}
				moved = true;
				break;
			}
		}

		if (!moved)
		{
			//LOG("Removing (" << current.x << "," << current.y << ")");
			//Unvisit(current);
		}
	}

	std::cout << "Searched all paths.\n";
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

	std::cout << "Input width of maze: ";
	std::cin >> n;

	std::cout << "Input height of maze: ";
	std::cin >> m;

	//std::cout << "Input path of file contain maze: " << "\n(Example maze file for n:4, m:5)\n";
	//std::cout << "\t0100\n";
	//std::cout << "\t1101\n";
	//std::cout << "\t0111\n";
	//std::cout << "\t0100\n";
	//std::cout << "\t1110\n";

	while (!ReadFile(file_path.c_str(), raw_input))
	{
		std::cout << "Invalid file path!\n";
		//PLEASE INPUT A CORRECT FILE PATH
	}

	Maze maze(n, m);
	maze.Parse(raw_input);
	maze.Print(false);


	Coord person;
	std::cout << "Please input the coordinates of the person:\n";

	do {
		std::cout << "x:";
		std::cin >> person.x;
		std::cout << "y:";
		std::cin >> person.y;
		
		//Convert x,y to correct indices
		person.x--;
		person.y = maze.height - person.y;
		
		if(!maze.IsValid(person))
			std::cout << "Invalid input! (The person cannot be placed in a wall)\nPlease input the coordinates of the person:\n";
		else
			break;
	} while (true);

	maze.person = person;
	maze.Print();

	maze.PrintAllPaths();
}