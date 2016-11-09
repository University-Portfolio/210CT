#pragma once
#include <string>
#include <iterator>

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

	class Coord
	{
	public:
		int x, y;

		Coord() : x(0), y(0) {};
		Coord(const int x, const int y) : x(x), y(y) {};

		inline Coord operator+(Coord& other) { return Coord(x + other.x, y + other.y); }
		inline Coord operator-(Coord& other) { return Coord(x - other.x, y - other.y); }
		inline bool operator==(Coord& other) { return x == other.x && y == other.y; }
		inline void operator=(Coord& other) { x = other.x; y = other.y; }
	};
	

	struct Path 
	{
	private:
		int size = 0;
		const int capacity = 256;
		Coord* stack;

	public:
		Path() 
		{
			stack = new Coord[capacity];
		}

		~Path() { delete[] stack; }

		inline const int Size() { return size; }

		void Push(Coord node) { stack[size++] = node; }
		Coord& Pop() { Coord node = stack[--size]; return node; }

		bool Contains(Coord node)
		{
			for (int i = 0; i < size; i++)
				if (stack[i] == node)
					return true;
			return false;
		}

		void Print(class Maze& maze);
	};

	struct Maze
	{
	public:
		const int width, height;
		Coord person;

	private:
		bool** walls;
		bool** visited;

	public:
		Maze(const int n, const int m) : width(n), height(m)
		{
			walls = new bool*[n];
			for (int i = 0; i < m; i++)
				walls[i] = new bool[m];

			visited = new bool*[n];
			for (int i = 0; i < m; i++)
				visited[i] = new bool[m] {0};
		}

		void Parse(const std::string& raw_input);

		inline bool* operator[](const int i) { return walls[i]; }
		void Print(const bool print_person = true, Path* path = nullptr) const;
		void PrintAllPaths();

		inline void Visit(const Coord coord) { visited[coord.x][coord.y] = true; }
		inline void Unvisit(const Coord coord) { visited[coord.x][coord.y] = false; }
		inline bool Visited(const Coord coord) { return visited[coord.x][coord.y]; }

		inline bool IsValid(const Coord coord) { return (coord.x >= 0 && coord.x < width && coord.y >= 0 && coord.y < height) && !walls[coord.x][coord.y]; }
		inline bool IsExit(const Coord coord) { return !walls[coord.x][coord.y] && (coord.x == 0 || coord.y == 0 || coord.x == width - 1 || coord.y == height - 1); }

		~Maze()
		{
			for (int i = 0; i < width; i++)
				delete[] walls[i];
			delete[] walls;

			for (int i = 0; i < width; i++)
				delete[] visited[i];
			delete[] visited;
		}

	};

};