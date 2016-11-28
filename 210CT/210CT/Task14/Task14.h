#pragma once
#include <unordered_map>
#include <vector>
#include <string>

/**
TASK (Advanced)

Consider the structure of a undirected weighed graph. Implement an algorithm to find
its maximum cost spanning tree. The output should be the preorder and inorder
traversal of the tree. Describe the running time of this algorithm.
**/

/**
The implementation has 3 nested for loops that go through the length of the array
so has O(n^3).

The 3rd for loop will not run most of the time however, so it would be slightly lower
in actuallality. (However is still not great as Prims Algorithm is greedy)
**/


namespace TASK_14
{
	struct Arc
	{
		int from;
		int to;
		int weight;

		Arc() : from(-1), to(-1), weight(-1) {};
		Arc(const int from, const int to, const int weight) : from(from), to(to), weight(weight) {};
	};

	class Node
	{
	private:
		struct Branch 
		{
			Node* node;
			int weight;

			Branch(Node* node, int weight) : node(node), weight(weight) {};
		};

		std::vector<Branch> children;
		int id;

	public:
		Node(const int id) : id(id) {};

		~Node() 
		{
			for (Branch& branch : children)
				delete branch.node;
		}

		bool AddChild(Arc arc);

		void PrintInOrder(std::string tab = "");
		void PrintPreOrder(std::string tab = "");
	};

	class Graph //Square + Undirected
	{
	private:
		std::vector<int> raw_matrix;
		int matrix_size;

		inline int Get(const int x, const int y) { return raw_matrix[y * matrix_size + x]; }
		inline void Set(const int x, const int y, const int value) { raw_matrix[y * matrix_size + x] = value; }

	public:
		static Graph Construct(std::string file_path);
		inline const int GetNodeCount() { return matrix_size; }
		
		/*Performs Prims algorithm to get a graph containing the maximum spanning tree*/
		Node* GetMaximumSpanningTree();

		void Print();
	};

	void Execute();
}
