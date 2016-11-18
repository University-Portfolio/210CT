#include "Task12.h"
#include <fstream>
#include "../IO.h"


using namespace TASK_12;


bool Graph::AreNeighbours(int v, int w) 
{
	std::set<int>& v_n = adjacency_table[v];
	std::set<int>& w_n = adjacency_table[w];

	if (v_n.find(w) != v_n.end())
		return true;

	//Check other way round (Only matters in weighted graph)
	else if (w_n.find(v) != w_n.end())
		return true;

	return false;
}

bool Graph::IsPath(int v, int w, std::vector<int>& out)
{
	if (AreNeighbours(v, w))
	{
		out.push_back(v);
		out.push_back(w);
		return true;
	}


	out.push_back(v);
	for (int n : GetNeighbours(v))
		if (IsPath(n, w, out))
			return true;
	out.pop_back();

	return false;
}

Graph Graph::Construct(std::string file_path) 
{
	Graph g;

	std::ifstream file;
	file.open(file_path, std::ifstream::in);

	if (!file.is_open())
	{
		IO::out << "Invalid path!\n";
		return g;
	}

	char c;
	int node = 1;
	int relation = 1;
	std::set<int> neighbours;

	while (file.get(c))
	{
		if (c == '\n')
		{
			g.CreateNode(node, neighbours);
			node++;
			relation = 1;
			neighbours.clear();
		}
		else 
		{
			if (c == '1')
				neighbours.insert(relation);
			relation++;
		}
	}
	g.CreateNode(node, neighbours);
	file.close();

	return g;
}

void TASK_12::Execute() 
{
	std::string file_path;
	IO::out << "Input the graph file path (File should be in matrix format where 1 is arc and 0 is no connection):\n";
	IO::in >> file_path;

	Graph g = Graph::Construct(file_path);

	int v, w;
	std::vector<int> path;

	IO::out << "Which 2 nodes would you like to find a path for?\n";
	IO::in >> v;
	IO::in >> w;
	bool path_found = g.IsPath(v, w, path);

	if (path_found)
	{
		IO::out << "Path found\n";

		IO::out << "Path:\n\t";
		for (int& i : path)
			IO::out << i << ",";
		IO::out << "\n";
	}
	else if(v == w)
		IO::out << "No additional path found.";
	else
		IO::out << "No path found.";

}