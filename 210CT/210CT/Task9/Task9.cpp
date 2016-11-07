#include "Task9.h"
#include <iostream>

using namespace TASK_9;


Matrix::Matrix(const int size) : size(size)
{
	raw_data = new float*[size];
	working_buffer = new float*[size];

	for (int i = 0; i < size; i++)
	{
		raw_data[i] = new float[size];
		working_buffer[i] = new float[size];
	}
}

Matrix::Matrix(Matrix& other) : Matrix(other.size)
{
	for (int y = 0; y < size;y++)
		for (int x = 0; x < size;x++)
			raw_data[x][y] = other[x][y];
}

Matrix::~Matrix()
{
	for (int i = 0; i < size; i++)
	{
		delete[] raw_data[i];
		delete[] working_buffer[i];
	}

	delete[] raw_data;
	delete[] working_buffer;
}

void Matrix::SetIdentity() 
{
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			raw_data[x][y] = (x == y) ? 1 : 0;
}

void Matrix::operator^=(const int n)
{
	if (n == 0)
	{
		SetIdentity();
		return;
	}

	Matrix pow_1(*this);
	

	for (int i = 1; i < n;i++)
	{
		//Copy of current matrix into working buffer
		for (int x = 0; x < size; x++)
			for (int y = 0; y < size; y++)
				working_buffer[x][y] = raw_data[x][y];


		for (int x = 0; x < size; x++)
			for (int y = 0; y < size; y++)
			{
				float total = 0;
				for (int n = 0; n < size; n++)
					total += working_buffer[n][y] * pow_1[x][n];
				raw_data[x][y] = total;
			}
	}
}

void Matrix::Print() 
{
	for (int y = 0; y < size; y++)
	{
		std::cout << (y ? y == size - 1 ? "\\" : "|" : "/");
		for (int x = 0; x < size; x++)
		{
			if (x)
				std::cout << ",";
			std::cout << raw_data[x][y];
		}
		std::cout << (y ? y == size - 1 ? "/" : "|\n" : "\\\n");
	}
	std::cout << '\n';
}

void TASK_9::Execute() 
{
	std::cout << "Input matrix size: ";
	int size;
	std::cin >> size;

	Matrix matrix(size);

	std::cout << "Input values in row-column format: \n";
	for (int y = 0; y<size; y++)
		for (int x = 0; x < size; x++)
		{
			int value;
			std::cin >> value;
			matrix[x][y] = value;
		}

	matrix.Print();


	std::cout << "Input power to raise matrix to: ";
	int power;
	std::cin >> power;
	matrix ^= power;

	matrix.Print();
}