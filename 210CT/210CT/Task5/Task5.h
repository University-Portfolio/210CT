#pragma once

/**
TASK (Advanced)

Write a function that takes four parameters representing the constant and multiplier of two linearly growing (as in O(m × n + k) ) functions and 
determines the critical value of n (which should be an integer) at which the relative run-time of the two algorithms switches. 
That is, at which input size is algorithm A slower than B and at which is B slower than A? Use an iterative approach rather than solving the equations.

an + b = cn + d.
**/

namespace TASK_5
{
	void Execute();

	class LinearLine 
	{
	public:
		const float gradient;
		const float intercept;

		LinearLine(const float gradient, const float intercept) : gradient(gradient), intercept(intercept) {}

		inline float f(float x) { return gradient * x + intercept; }
	};

};