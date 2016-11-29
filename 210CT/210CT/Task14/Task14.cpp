#include "Task14.h"
#include "../IO.h"

#include <math.h>
#include <fstream>
#include <set>

using namespace TASK_14;


void Graph::Print() 
{
	for (int i = 0; i < raw_matrix.size(); i++)
		IO::out << ((i%matrix_size) ? "" : "\n") << (raw_matrix[i] < 10 ? "  " : raw_matrix[i] < 100 ? " " : "") << raw_matrix[i];
	IO::out << '\n';
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
	std::string current_line = "";
	bool end_of_file = false;

	while (!end_of_file)
	{
		end_of_file = !file.get(c);

		if (end_of_file || c == ',' || c == '\n')
		{
			const int w = std::stoi(current_line);
			g.raw_matrix.push_back(w);
			current_line = "";
		}
		else
			current_line += c;
	}
	file.close();
	
	g.raw_matrix.shrink_to_fit();
	g.matrix_size = (int)sqrt(g.raw_matrix.size());
	
	return g;
}

bool Node::AddChild(Arc arc) 
{
	if (arc.from == id)
	{
		children.push_back(Branch(new Node(arc.to), arc.weight));
		return true;
	}

	for (Branch branch : children)
		if (branch.node->AddChild(arc))
			return true;

	return false;
}

Node* Graph::GetMaximumSpanningTree()
{
	Node* spanning_tree;
	int total_weight = 0;

	std::vector<bool> row_unlocked(matrix_size, true);
	std::vector<bool> column_unlocked(matrix_size, false);

	//Start with index 0
	spanning_tree = new Node(0);
	row_unlocked[0] = false;
	column_unlocked[0] = true;

	for (int count = 0; count < matrix_size - 1; count++)
	{
		Arc max_arc;
		IO::out_debug << "Count " << count << "\n";

		for (int column = 0; column < matrix_size; column++)
		{
			if (column_unlocked[column])
			{
				IO::out_debug << "\tColumn " << column << "\n";

				for (int row = 0; row < matrix_size; row++)
					if (row_unlocked[row])
					{
						int weight = Get(column, row);
						IO::out_debug << "\t\t->" << row << " (" << weight << ")\n";

						if (weight != 0 && (weight < max_arc.weight || max_arc.from == -1))
						{
							max_arc.from = column;
							max_arc.to = row;
							max_arc.weight = weight;
						}
					}
			}
		}

		spanning_tree->AddChild(max_arc);
		IO::out_debug << "Using arc: " << max_arc.from << "-(" << max_arc.weight << ")->" << max_arc.to << "\n";

		row_unlocked[max_arc.to] = false;
		column_unlocked[max_arc.to] = true;
		total_weight += max_arc.weight;
	}

	return spanning_tree;
}

void Node::PrintPreOrder()
{
	IO::out << id << ", ";

	if (children.size())
		for (Branch& branch : children)
			branch.node->PrintPreOrder();
}

void Node::PrintPreOrderPretty(std::string tab)
{
	IO::out << tab << (tab == "" ? " " : "|") << "(";
	IO::out << (id < 10 ? " " : id < 100 ? " " : "") << id << (id < 10 ? " " : "");
	IO::out << ")\n";

	if (children.size())
		for (Branch& branch : children)
			branch.node->PrintPreOrderPretty(tab + "   ");
	else
		IO::out << tab << "|\n";
}

void Node::PrintPostOrder()
{
	if (children.size())
		for (Branch& branch : children)
			branch.node->PrintPostOrder();

	IO::out << id << ", ";
}

void Node::PrintPostOrderPretty(std::string tab)
{
	if (children.size())
		for (Branch& branch : children)
			branch.node->PrintPostOrderPretty(tab + "   ");
	else
		IO::out << tab << "|\n";

	IO::out << tab << (tab == "" ? " " : "|") << "(";
	IO::out << (id < 10 ? " " : id < 100 ? " " : "") << id << (id < 10 ? " " : "");
	IO::out << ")\n";
}

void TASK_14::Execute() 
{
	std::string file_path;
	IO::out << "Input the square graph file path \n(File should be in matrix comma separated format where entry is arc and '' is no connection):\n";
	IO::out << "e.g.\t0, 1, 0, 10, 0\n";
	IO::out << "\t0, 1, 0, 2, 0\n";
	IO::out << "\t3, 1, 8, 0, 0\n";
	IO::out << "\t0, 1, 0, 0, 5\n";
	IO::out << "\t3, 1, 0, 3, 0\n";
	IO::in >> file_path;

	Graph g = Graph::Construct(file_path);
	IO::out << "Input:\n";
	g.Print();	

	Node* spanning_tree = g.GetMaximumSpanningTree();
	IO::out << "POST ORDER:\n";
	spanning_tree->PrintPostOrder();
	IO::out << "\n";
	spanning_tree->PrintPostOrderPretty();
	IO::out << "\nPRE ORDER:\n";
	spanning_tree->PrintPreOrder();
	IO::out << "\n";
	spanning_tree->PrintPreOrderPretty();

	delete spanning_tree;
}