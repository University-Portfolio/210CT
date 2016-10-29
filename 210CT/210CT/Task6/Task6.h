#pragma once

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


	struct Cube 
	{
		float size;
		Colour colour;

		Cube() {}
		Cube(float size, Colour colour) : size(size), colour(colour) {}

		//Operators needed to store in list
		inline bool operator<(Cube& other) const
		{
			return size < other.size;
		}
		inline bool operator>(Cube& other) const
		{
			return size > other.size;
		}
		inline bool operator==(const Cube& other) const
		{
			return colour == other.colour && size == other.size;
		}
		inline bool operator!=(const Cube& other) const
		{
			return colour != other.colour || size != other.size;
		}
	};
};