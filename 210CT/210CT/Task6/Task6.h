#pragma once
#include <list>

/**
TASK (Advanced)

Consider having n cubes, each being characterized by their edge length and their
colour. Use the cubes (not necessarily all of them) in order to build a tower of
maximum height, under the following conditions:
a) any two neighbouring cubes must be of different colours.
b) the edge length of a cube is lower than the edge length of the cube placed
below it.

**/

namespace TASK_6
{
	void Execute();

	//Could be more complex for colour, but enum will fit for purpose
	enum Colour { RED, GREEN, BLUE, YELLOW };

	namespace COLOUR 
	{
		static char* ToString(Colour c) 
		{
			switch (c) 
			{
			case Colour::RED:
				return "Red";
			case Colour::GREEN:
				return "Green";
			case Colour::BLUE:
				return "Blue";
			case Colour::YELLOW:
				return "Yellow";
			};
			return "Unknown";
		}
	};

	class Cube 
	{
	public:
		int size;
		Colour colour;

		Cube() {}
		Cube(float size, Colour colour) : size(size), colour(colour) {}
		
		//Operators needed to store in list
		inline bool operator<(Cube& other) const { return size < other.size; }
		inline bool operator>(Cube& other) const { return size > other.size; }
		inline bool operator==(const Cube& other) const { return colour == other.colour && size == other.size; }
		inline bool operator!=(const Cube& other) const { return colour != other.colour || size != other.size; }
	};
	
	struct CubeInfo 
	{
		Cube cube;
		bool found_solid_solution = false;
		bool found_temp_solution = false;

		CubeInfo(Cube cube) : cube(cube) {};
	};

	class CubeStack
	{
	private:
		std::list<CubeInfo> cubes;

	public:
		/**
		Add a cube to the stack (In order of largest to smallest)

		@param	cube	The desired cube to add
		**/
		void Add(Cube cube);

		/**
		Clears the stack of all cubes
		**/
		void Clear() { cubes.clear(); }

		/**
		Print all cubes in a table

		@param	column_count	The number of columns to include (Includes Size and Colour per 1 column count)
		**/
		void Print(int column_count = 4);

		/**
		Gets the largest possible tower of cubes
		**/
		class CubeTower GetLargestTower();
	};

	class CubeTower 
	{
	private:
		int size = 0;

	public:
		std::list<CubeInfo*> cubes;

		void Add(CubeInfo& cube) 
		{
			size += cube.cube.size;

			if (cubes.size() == 0)
				cubes.push_back(&cube);

			//Add cube in correct order (Doesn't matter the order of cubes the same size)
			else
			{
				for (auto it = cubes.begin(); it != cubes.end(); ++it)
					if ((*it)->cube > cube.cube)
					{
						cubes.insert(it, &cube);
						return;
					}

				//Only gets here if smaller than anything else in the list
				cubes.push_back(&cube);
			}
		}
		inline int GetSize() { return size; }
		void Print();

	};
};