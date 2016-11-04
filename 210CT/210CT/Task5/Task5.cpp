#include "Task5.h"
#include "../Definitions.h"
#include <iostream>


using namespace TASK_5;


inline float sign(const float a)
{
	if (a < 0.0f) return -1.0f;
	else if (a > 0.0f) return 1.0f;
	return 0.0f;
}

inline float modulus(const float a)
{
	return a * sign(a);
}

void TASK_5::Execute() 
{
	std::cout << "For an + b = cn + d\n";
	float a, b, c, d;
	
	std::cout << "Input coefficient for a: ";
	std::cin >> a;
	std::cout << "Input coefficient for b: ";
	std::cin >> b;
	std::cout << "Input coefficient for c: ";
	std::cin >> c;
	std::cout << "Input coefficient for d: ";
	std::cin >> d;

	LinearLine lhs(a, b);
	LinearLine rhs(c, d);

	LOG("Expected n:" << (d - b) / (a - c));

	//Determine starting range
	//Gradients of both equations
	const float g0 = sign(a);
	const float g1 = sign(c);

	if (g0 == 0.0f && g1 == 0.0f) 
	{
		std::cout << "Error: gradients of both equations are 0, " << (b == d ? "They cross infinitly\n" : "They never cross\n");
		return;
	}

	//Find range
	int step = 1;
	int start_range = -100000000;
	int end_range = 100000000;
	
	while (step)
	{
		std::cout << "Testing " << start_range << " to " << end_range << "(step:" << step  << ")\n";

		const float start_lhs = lhs.f(start_range);
		const float end_lhs = lhs.f(end_range);

		const float start_rhs = rhs.f(start_range);
		const float end_rhs = rhs.f(end_range);

		const float start_dif = start_lhs - start_rhs;
		const float end_dif = end_lhs - end_rhs;


		LOG("\tlhs start:" << start_lhs << " end:" << end_lhs);
		LOG("\trhs start:" << start_rhs << " end:" << end_rhs);
		LOG("\tdif start:" << start_dif << " end:" << end_dif);
				
		if (modulus(start_dif) < modulus(end_dif))
			end_range -= step;
		else
			start_range += step;

		step = (end_range - start_range) / 2.0f;
	}

	const int solution = start_range;

	LOG("Solution: " << solution);

	if (rhs.f(solution - 1) > rhs.f(solution + 1))
		std::cout << "lhs becomes more efficient after " << solution << std::endl;
	else
		std::cout << "rhs becomes more efficient after " << solution << std::endl;
}