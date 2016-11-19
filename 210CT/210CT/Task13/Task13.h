#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include <vector>

/**
TASK (Advanced)

Using the graph structure previously implemented, implement a function isConnected(G) to check whether or not the graph is strongly connected. 
The output should be simply 'yes' or 'no'.
**/


namespace TASK_13
{
	typedef unsigned int uint;

	//Unweighted but not strictly undirected (Must be handled on input)
	class Graph
	{
	private:
		std::unordered_map<uint, std::set<uint>> adjacency_table;
		uint largest_node = 0;

	public:
		inline void CreateNode(uint key, std::set<uint> neighbours) { adjacency_table[key] = neighbours; }
		inline std::set<uint> GetNeighbours(uint key) { return adjacency_table[key]; }
		bool AreNeighbours(uint v, uint w);

		bool IsStronglyConnected();

		bool IsPath(uint v, uint w);
		inline const uint GetLargestNode() { return largest_node; }
	private:
		bool IsPath(uint v, uint w, bool* visited);

	public:
		static Graph Construct(std::string file_path);
	};

	void Execute();
}
