#pragma once
#include "C:\Users\Екатерина Иванова\source\repos\map_v4\map_v4\map.h"
#include "QuickSort.h"
using namespace std;

class Huffaman_binTree
{
private:

	class Node
	{
	public:
		string code;
		string value;
		unsigned frequency;
		Node *left, *right;

		Node(const string& value = "", unsigned frequency = 0, Node *left = nullptr, Node *right = nullptr)
		{
			this->value = value;
			this->code = "";
			this->frequency = frequency;
			this->left = left;
			this->right = right;
		}
	};

	Node *root;
	map<string, string> Table_FromSymbolsToCodes, Table_FromCodesToSymbols;


	void build_Huffaman_binTree(string string_for_coding)
	{
		string s = "";
		unsigned frequencies[256] = { 0 }, size_mas = 256;
		int array_symbols[256], j = 0;

		
		for (auto i = 0; i < string_for_coding.length(); i++)
		{
			j = static_cast<int>(string_for_coding[i]);
			frequencies[128 + j]++;
		}

		for (int i = -128; i < 128; i++)
			array_symbols[i + 128] = i;

		basic_function_QuickSort(frequencies, array_symbols, size_mas);

		List<Node*> list_symbols; 
		for (int i = 0; i < 256; i++)
			if (frequencies[i] > 0)
			{
				Node *node = new Node(s = (char)array_symbols[i], frequencies[i]);
				list_symbols.push_back(node);
			}

		while (list_symbols.get_size() != 1)
		{
			Node *left_child = list_symbols.front();
			list_symbols.pop_front();
			Node *right_child = list_symbols.front();
			list_symbols.pop_front();

			Node *parent = new Node(left_child->value + right_child->value, left_child->frequency + right_child->frequency, left_child, right_child);

			if (list_symbols.get_size() == 0 || (list_symbols.front() && parent->frequency <= list_symbols.front()->frequency))
				list_symbols.push_front(parent);
			else
				if (list_symbols.back() && parent->frequency >= list_symbols.back()->frequency)
					list_symbols.push_back(parent);
				else
					for (auto i = 0; i < list_symbols.get_size(); i++)
						if (parent->frequency >= list_symbols.at(i)->frequency && parent->frequency <= list_symbols.at(i + 1)->frequency)
						{
							list_symbols.insert(parent, i + 1);
							break;
						}
		}
		root = list_symbols.front();
		list_symbols.pop_front();
	}

	void print_table_frequencies_and_codes()
	{
		cout << endl << "TABLE OF FREQUENCY OF SYMBOLS AND THEIR CODES" << endl;
		print_table(root);
	}

	void print_table(Node *node)
	{
		if (node != nullptr)
		{
			print_table(node->left);
			print_table(node->right);
			if (node->left == nullptr && node->right == nullptr)
				cout << node->value << " : " << node->frequency << " : " << node->code << endl;
		}
	}

	void get_codes(Node *node, string code)
	{
		node->code = code;
		if (node->left != nullptr || node->right != nullptr)
		{
			get_codes(node->left, code + "0");
			get_codes(node->right, code + "1");
		}
		else
			if (node->left == nullptr && node->right == nullptr)
			{
				node->code = code;
				Table_FromSymbolsToCodes.insert(node->value, code);
				Table_FromCodesToSymbols.insert(code, node->value);
			}
	}

	void clear(Node *node)
	{
		if (node != nullptr)
		{
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
		root = nullptr;
	}
	

public:
	Huffaman_binTree() : root(nullptr) {}
	~Huffaman_binTree() { clear(root); }


	void creating_symbol_and_code_table(string string_for_coding)
	{
		if (string_for_coding.empty())
			throw invalid_argument("The entered string is empty.");

		build_Huffaman_binTree(string_for_coding);
		get_codes(root, "");
		print_table_frequencies_and_codes();
		clear(root);
	}

	string coding(string string_for_coding)
	{
		if (Table_FromSymbolsToCodes.get_size() == 0)
			throw invalid_argument("No symbol and code table created or the entered string is empty.");

		string coded_string = "", character = "";
		for (auto i = 0; i < string_for_coding.size(); i++)
		{
			character = string_for_coding[i];
			coded_string += Table_FromSymbolsToCodes[character];
			character.clear();
		}

		return coded_string;
	}

	string decoding(string string_for_decoding)
	{
		if (Table_FromCodesToSymbols.get_size() == 0)
			throw invalid_argument("No symbol and code table created or the entered string is empty.");

		string decoded_string = "", character = "";
		for (auto i = 0; i < string_for_decoding.size(); i++)
		{
			character += string_for_decoding[i];
			if (Table_FromCodesToSymbols.key_contains(character) == true)
			{
				decoded_string += Table_FromCodesToSymbols[character];
				character.clear();
			}
		}

		return decoded_string;
	}

	float size_CodedString(string coded_string)
	{
		return (float)coded_string.size();
	}

	float size_DecodedString(string decoded_string)
	{
		return 8 * (float)decoded_string.size();
	}
};