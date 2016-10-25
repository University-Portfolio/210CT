#pragma once
#include <string>

/**
TASK (Advanced)

A sparse matrix is a matrix where the number of elements which are zero is bigger
than the number of elements which are not zero. Find a way to store sparse
matrices, and write the functions to add, subtract, and multiply pairs of such
matrices. Do not use predefined functions for the operations on matrices in your
programming language of choice.
**/

namespace TASK_2
{
	void Execute();

	class Matrix 
	{
	protected:
		float** raw_values;
		const int width;
		const int height;
		std::string pretty_string;

	public:

		Matrix(const int width, const int height);
		~Matrix();

		inline float* operator[](int x) { return raw_values[x]; }

		inline Matrix* operator+(Matrix&);
		inline Matrix* operator-(Matrix&);
		inline Matrix* operator*(Matrix&);
		inline Matrix* operator*(float);

		inline void operator+=(Matrix&);
		inline void operator-=(Matrix&);
		inline void operator*=(Matrix&);
		inline void operator*=(float);

		operator const char*();

		bool IsSparse();
		inline bool IsDense() { !IsSparse(); }
	};
};