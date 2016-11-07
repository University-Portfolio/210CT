#pragma once

/**
TASK (Advanced)

Write a function to calculate the kth power of a square matrix, using pointers to access to the elements of the matrix. 
The resulted matrix will be displayed in natural form.

**/

namespace TASK_9
{
	struct Matrix //Squares
	{
	private:
		float** raw_data;
		float** working_buffer;

	public:
		const int size;

		Matrix(const int size);
		Matrix(Matrix& other);
		~Matrix();

		void Print();
		void operator^=(const int n);

		void SetIdentity();
		inline float* operator[](const int i) { return raw_data[i]; }
	
	};

	void Execute();
}
