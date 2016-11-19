#pragma once
#include <string>
#include <iterator>
#include <vector>

/**
TASK (Advanced)

Let's consider a labyrinth as a n × m matrix, where the corridors are denoted by 1s situated in consecutive positions on the same line or column. 
The rest of the elements are 0. Within the labyrinth, a person is considered to be in position (i, j). 
Write a program that lists all exit routes which do not pass the same place twice.
Input: n, m, the rows of the matrix, the coordinates of the exit and the coordinates of the person (row, column). 
Output: a sequence of row/column pairs representing the person's successive position.

**/

namespace TASK_7
{
	void Execute();

	struct Coord
	{
		int x, y;

		Coord() : x(0), y(0) {};
		Coord(const int x, const int y) : x(x), y(y) {};

		inline Coord operator+(Coord& other) { return Coord(x + other.x, y + other.y); }
		inline Coord operator-(Coord& other) { return Coord(x - other.x, y - other.y); }
		inline bool operator==(Coord& other) { return x == other.x && y == other.y; }
		inline void operator=(Coord& other) { x = other.x; y = other.y; }
	};
	
	struct Node 
	{
		Coord coord;

		//Index refers to direction e.g. 0 left, 1 down, 2 right, 3 up
		int search_index = 0;
		int from_index;

		Node(Coord coord, int from_index = -1) : coord(coord), from_index(from_index) {};
	};

	class Path 
	{
	private:
		std::vector<Node> stack; //Acts almost like a stack, but we have to be able to print without removing everything
	public:
		void Print(class Maze& maze);

		inline Node Pop() { Node v = stack[stack.size() - 1]; stack.pop_back(); return v; }
		inline void Push(Node node) { stack.push_back(node); }
		
		bool Contains(Coord coord);
		inline bool IsEmpty() { return !stack.size(); }
	};

	class Maze
	{
	public:
		const int width, height;
		Coord person;

	private:
		bool** walls;

	public:
		Maze(const int n, const int m) : width(n), height(m)
		{
			walls = new bool*[n];
			for (int i = 0; i < m; i++)
				walls[i] = new bool[m];
		}

		void Parse(const std::string& raw_input);

		inline bool* operator[](const int i) { return walls[i]; }
		void Print(const bool print_person = true, Path* path = nullptr) const;
		void PrintAllPaths();

		inline bool IsValid(const Coord coord) { return (coord.x >= 0 && coord.x < width && coord.y >= 0 && coord.y < height) && !walls[coord.x][coord.y]; }
		inline bool IsExit(const Coord coord) { return !walls[coord.x][coord.y] && (coord.x == 0 || coord.y == 0 || coord.x == width - 1 || coord.y == height - 1); }

		~Maze()
		{
			for (int i = 0; i < width; i++)
				delete[] walls[i];
			delete[] walls;
		}

	};

};