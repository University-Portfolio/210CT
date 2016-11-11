#pragma once
#include <string>

/**
TASK (Advanced)

Build a Binary Search Tree (BST) to hold English language words in its nodes. 
Use a paragraph of any text in order to extract words and to determine their frequencies.
Input: You should read the words and frequencies from a file in a suitable format, such as .csv. 
The following tree operations should be implemented: a) Listing (word, frequency) pairs for each of the tree nodes. b) Printing the tree in preorder. C) Finding a word. Regardless whether found or not found your program should output the path traversed in determining the answer, followed by yes if found or no, respectively.
**/


namespace TASK_11
{
	typedef unsigned int uint;

	struct Word 
	{
		std::string string = "";
		uint count = 0;
		Word(std::string string, uint count = 1) : string(string), count(count) {};
	};

	class Node 
	{
	private:
		Node* lhs_child = nullptr;
		Node* rhs_child = nullptr;

	public:
		Word word;
		Node(Word word) : word(word) {};
		~Node();

		inline const bool operator<(Node& other) { return word.string < other.word.string; }
		inline const bool operator>(Node& other) { return word.string > other.word.string; }
		inline const bool operator<=(Node& other) { return word.string <= other.word.string; }
		inline const bool operator>=(Node& other) { return word.string >= other.word.string; }
		inline const bool operator==(Node& other) { return word.string == other.word.string; }
		inline const bool operator!=(Node& other) { return word.string != other.word.string; }

		inline const bool operator<(std::string& word) { return this->word.string < word; }
		inline const bool operator>(std::string& word) { return this->word.string > word; }
		inline const bool operator<=(std::string& word) { return this->word.string <= word; }
		inline const bool operator>=(std::string& word) { return this->word.string >= word; }
		inline const bool operator==(std::string& word) { return this->word.string == word; }
		inline const bool operator!=(std::string& word) { return this->word.string != word; }

		void PrintInOrder();
		void PrintPreOrder();
		void PrintPostOrder();
		void AddChild(Node* child);
		uint Count(std::string& word, const bool report = false);
	};

	Node* GenerateBSTFromTxt(std::string& file_path);
	Node* GenerateBSTFromCsv(std::string& file_path);

	void Execute();
}
