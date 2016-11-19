#include "Task13.h"
#include <fstream>
#include "../IO.h"


using namespace TASK_13;


bool Graph::AreNeighbours(uint v, uint w)
{
	std::set<uint> v_n = GetNeighbours(v);
	std::set<uint> w_n = GetNeighbours(w);

	if (v_n.find(w) != v_n.end())
		return true;
	//Check other way round (Only matters in weighted graph)
	else if (w_n.find(v) != w_n.end())
		return true;

	return false;
}

bool Graph::IsPath(uint v, uint w)
{
	bool* visited = new bool[largest_node + 1]{false};
	bool answer = IsPath(v, w, visited);
	delete[] visited;
	return answer;
}

bool Graph::IsPath(uint v, uint w, bool* visited)
{
	if (AreNeighbours(v, w))
		return true;

	for (uint n : GetNeighbours(v))
	{
		if (!visited[n])
		{
			visited[n] = true;
			if (IsPath(n, w, visited))
				return true;
			else
				visited[n] = false;
		}
	}

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
	uint node = 1;
	uint relation = 1;
	std::set<uint> neighbours;

	while (file.get(c))
	{
		if (c == '\n')
		{
			//Print
			{
				IO::out_debug << "(" << node << "):{";
				for (const uint i : neighbours)
					IO::out_debug << i << ",";
				IO::out_debug << "}\n";
			}

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
	g.largest_node = node - 1;
	file.close();

	return g;
}

bool Graph::IsStronglyConnected()
{
	for (uint v = 1; v <= largest_node; v++)
		for (uint w = 1; w <= largest_node; w++)
		{
			IO::out_debug << "Checking " << w << "-" << v << '\n';
			if (w != v && !IsPath(w, v))
			{
				IO::out_debug << "No path for " << w << "-" << v << '\n';
				return false;
			}
		}

	return true;
}

void TASK_13::Execute()
{
	std::string file_path;
	IO::out << "Input the graph file path (File should be in matrix format where 1 is arc and 0 is no connection):\n";
	IO::in >> file_path;

	Graph g = Graph::Construct(file_path);

	if (g.IsStronglyConnected())
		IO::out << "Yes; Graph is strongly connected.\n";
	else
		IO::out << "No; Graph is not strongly connected.\n";
}