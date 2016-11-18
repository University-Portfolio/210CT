#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include <vector>

/**
TASK (Advanced)

Implement the structure for an unweighted, undirected graph G, where nodes consist of positive integers. 
Also, implement a function isPath(v, w), where v and w are vertices in the graph, to check if there is a path between the two nodes. 
The path found will be printed to a text file as a sequence of integer numbers (the node values).
**/


namespace TASK_12
{
	typedef unsigned int uint;

	//Unweighted but not strictly undirected (Must be handled on input)
	class Graph 
	{
	private:
		std::unordered_map<int, std::set<int>> adjacency_table;

	public:
		inline void CreateNode(int key, std::set<int> neighbours) { adjacency_table[key] = neighbours; }
		inline std::set<int>& GetNeighbours(int key) { return adjacency_table[key]; }
		bool AreNeighbours(int v, int w);

		bool IsPath(int v, int w, std::vector<int>& out);

		static Graph Construct(std::string file_path);
	};

	void Execute();
}
