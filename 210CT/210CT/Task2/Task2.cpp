#include "Task2.h"
#include <iostream>
#include <exception>
#include <sstream>

using namespace TASK_2;

void TASK_2::Execute() 
{
	Matrix m0(3, 2);
	m0[0][0] = 1;
	m0[1][0] = 2;
	m0[2][0] = 3;
	m0[0][1] = 4;
	m0[1][1] = 5;
	m0[2][1] = 6;

	Matrix m1(1, 3);
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[0][2] = 3;

	std::cout << "TEST 1:\n";
	std::cout << "A:\n" << m0 << "\n";
	std::cout << "B:\n" << m1 << "\n";
	std::cout << "A*B=\n" << *(m0*m1) << "\n";
	std::cout << "A*3=\n" << *(m0*3) << "\n";
	std::cout << "A sparse? " << (m0.IsSparse() ? "True" : "False") << "\n";
	std::cout << "B sparse? " << (m1.IsSparse() ? "True" : "False") << "\n";
	std::cout << "==================================================\n";

	Matrix m2(3, 3);
	m2[0][0] = 2;
	m2[1][0] = 1;
	m2[2][0] = 5;
	m2[0][1] = 3;
	m2[1][1] = 2;
	m2[2][1] = 8;
	m2[0][2] = 6;
	m2[1][2] = 9;
	m2[2][2] = 4;

	Matrix m3(3, 3);
	m3[0][0] = 2;
	m3[1][0] = 6;
	m3[2][0] = 3;
	m3[2][1] = 1;

	std::cout << "TEST 2:\n";
	std::cout << "A:\n" << m2 << "\n";
	std::cout << "B:\n" << m3 << "\n";
	std::cout << "A+B=\n" << *(m2*m3) << "\n";
	std::cout << "A-B=\n" << *(m2*m3) << "\n";
	std::cout << "A*B=\n" << *(m2*m3) << "\n";
	std::cout << "A sparse? " << (m2.IsSparse() ? "True" : "False") << "\n";
	std::cout << "B sparse? " << (m3.IsSparse() ? "True" : "False") << "\n";
	std::cout << "==================================================\n";
}

Matrix::Matrix(const int width, const int height) : width(width), height(height)
{
	raw_values = new float*[width];
	for (int i = 0; i < width; i++)
		raw_values[i] = new float[height] {0};
}

Matrix::~Matrix() 
{
	for (int i = 0; i < width; i++)
		delete[] raw_values[i];
	delete[] raw_values;
}

Matrix* Matrix::operator+(Matrix& other)
{
	if (width != other.width || height != other.height)
		throw std::exception("Trying to add matrices of different sizes");

	Matrix* out = new Matrix(width, height);
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			(*out)[x][y] = raw_values[x][y] + other[x][y];
	return out;
}

void Matrix::operator+=(Matrix& other)
{
	if (width != other.width || height != other.height)
		throw std::exception("Trying to add matrices of different sizes");

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			raw_values[x][y] += other[x][y];
}

Matrix* Matrix::operator-(Matrix& other)
{
	if (width != other.width || height != other.height)
		throw std::exception("Trying to subtract matrices of different sizes");

	Matrix* out = new Matrix(width, height);
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			(*out)[x][y] = raw_values[x][y] - other[x][y];
	return out;
}

void Matrix::operator-=(Matrix& other)
{
	if (width != other.width || height != other.height)
		throw std::exception("Trying to subtract matrices of different sizes");

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			raw_values[x][y] -= other[x][y];
}

Matrix* Matrix::operator*(Matrix& other)
{
	if (width != other.height)
		throw std::exception("Trying to multiply matrices of invalid sizes");

	Matrix* out = new Matrix(other.width, height);
	for (int x = 0; x < other.width; x++)
		for (int y = 0; y < height; y++)
		{
			float value = 0;
			for (int i = 0; i < width; i++)
				value += raw_values[i][y] * other[x][i];

			(*out)[x][y] = value;
		}
	return out;
}

void Matrix::operator*=(Matrix& other)
{
	if (width != other.width || height != other.height)
		throw std::exception("Trying to multiply matrices of invalid sizes");

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			float value = 0;
			for (int i = 0; i < width; x++)
			{
				value += raw_values[i][y] * other[x][i];
			}
			raw_values[x][y] = value;
		}
}

Matrix* Matrix::operator*(float factor)
{
	Matrix* out = new Matrix(width, height);
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			(*out)[x][y] = raw_values[x][y] * factor;
	return out;
}
void Matrix::operator*=(float factor)
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			raw_values[x][y] *= factor;
}

Matrix::operator const char *()
{
	std::stringstream ss;

	for (int y = 0; y < height; y++)
	{
		ss << (y ? y == height - 1 ? "\\" : "|" : "/");
		for (int x = 0; x < width; x++)
		{
			if (x)
				ss << ",";
			ss << raw_values[x][y];
		}
		ss << (y ? y == height - 1 ? "/" : "|\n" : "\\\n") ;
	}
	pretty_string = ss.str();
	return pretty_string.c_str();
}


bool Matrix::IsSparse() 
{
	int empty_count = 0;
	int filled_count = 0;


	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (raw_values[x][y])
				filled_count++;
			else
				empty_count++;

	return empty_count > filled_count;
}