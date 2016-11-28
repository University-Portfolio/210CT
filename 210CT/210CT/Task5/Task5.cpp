#include "Task5.h"
#include "../IO.h"


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
	IO::out << "For an + b = cn + d\n";
	float a, b, c, d;
	
	IO::out << "Input coefficient for a: ";
	IO::in >> a;
	IO::out << "Input coefficient for b: ";
	IO::in >> b;
	IO::out << "Input coefficient for c: ";
	IO::in >> c;
	IO::out << "Input coefficient for d: ";
	IO::in >> d;

	LinearLine lhs(a, b);
	LinearLine rhs(c, d);

	IO::out_debug << "Expected n:" << (d - b) / (a - c) << '\n';

	//Determine starting range
	//Gradients of both equations
	const float g0 = sign(a);
	const float g1 = sign(c);

	if (g0 == 0.0f && g1 == 0.0f) 
	{
		IO::out << "Error: gradients of both equations are 0, " << (b == d ? "They cross infinitely\n" : "They never cross\n");
		return;
	}

	//Find range
	int step = 1;
	int start_range = -100000000;
	int end_range = 100000000;
	
	while (step)
	{
		IO::out << "Testing " << start_range << " to " << end_range << "(step:" << step  << ")\n";

		const float start_lhs = lhs.f(start_range);
		const float end_lhs = lhs.f(end_range);

		const float start_rhs = rhs.f(start_range);
		const float end_rhs = rhs.f(end_range);

		const float start_dif = start_lhs - start_rhs;
		const float end_dif = end_lhs - end_rhs;


		IO::out_debug << "\tlhs start:" << start_lhs << " end:" << end_lhs << '\n';
		IO::out_debug << "\trhs start:" << start_rhs << " end:" << end_rhs << '\n';
		IO::out_debug << "\tdif start:" << start_dif << " end:" << end_dif << '\n';
				
		if (modulus(start_dif) < modulus(end_dif))
			end_range -= step;
		else
			start_range += step;

		step = (end_range - start_range) / 2.0f;
	}

	const int solution = start_range;

	IO::out_debug << "Solution: " << solution << '\n';

	if (rhs.f(solution - 1) > rhs.f(solution + 1))
		IO::out << "lhs becomes more efficient after " << solution << '\n';
	else
		IO::out << "rhs becomes more efficient after " << solution << '\n';
}