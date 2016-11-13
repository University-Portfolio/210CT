#pragma once
#include <vector>
#include "../IO.h"

/**
TASK (Advanced)

Adapt the quick sort algorithm to find the mth smallest element out of a sequence of
n integers.

**/

namespace TASK_8
{
	void Execute();


	template<typename Type>
	void Print(std::vector<Type>& arr)
	{
		IO::out << '(';
		for (Type& t : arr)
			IO::out << t << ',';
		IO::out << ")\n";
	}

	template<typename Type>
	void Swap(std::vector<Type>& arr, int a, int b)
	{
		if (a == b)
			return;

		Type temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}

	template<typename Type>
	void QuickSort(std::vector<Type>& arr, int& swap_count, int low = -1, int high = -1)
	{
		if (low == -1)
			low = 0;
		if (high == -1)
			high = arr.size() - 1;

		if (low < high)
		{
			int wall = low;
			const Type pivot = arr[high];

			//Put everything less pivot below wall 
			for (int i = low; i < high; i++)
				if (arr[i] < pivot)
				{
					Swap(arr, i, wall);
					wall++;
					swap_count++;
				}

			Swap(arr, high, wall);
			swap_count++;

			const int lhs_low = low;
			const int lhs_high = wall - 1;
			const int rhs_low = wall + 1;
			const int rhs_high = high;
			QuickSort(arr, swap_count, lhs_low, lhs_high);
			QuickSort(arr, swap_count, rhs_low, rhs_high);
		}
	}

	template<typename Type>
	Type QuickSortSearch(std::vector<Type>& arr, int m, int& swap_count, int low = -1, int high = -1)
	{
		if (low == -1)
			low = 0;
		if (high == -1)
			high = arr.size() - 1;

		if (low < high)
		{
			int wall = low;
			const Type pivot = arr[high];

			//Put everything less pivot below wall 
			for (int i = low; i < high; i++)
				if (arr[i] < pivot)
				{
					Swap(arr, i, wall);
					wall++;
					swap_count++;
				}

			Swap(arr, high, wall);
			swap_count++;

			if (wall != m)
			{
				const int lhs_low = low;
				const int lhs_high = wall - 1;
				const int rhs_low = wall + 1;
				const int rhs_high = high;

				if (lhs_low <= m && m <= lhs_high)
					return QuickSortSearch(arr, m, swap_count, lhs_low, lhs_high);

				if (rhs_low <= m && m <= rhs_high)
					return QuickSortSearch(arr, m, swap_count, rhs_low, rhs_high);
			}
			else
				return pivot;
		}

		return arr[m];
	}
}