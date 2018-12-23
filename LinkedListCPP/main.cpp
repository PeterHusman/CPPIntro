#include <iostream>
#include <string>
#include "Node.h"

int main()
{
	LinkedList<int> lloi{};

	lloi.Insert(25);
	lloi.Insert(34);
	lloi.Insert(46);
	while (true)
	{
		system("CLS");
		Node<int>* node = lloi.Head.get();
		int len = lloi.Length();
		for (int i = 0; i < len; i++)
		{
			std::cout << "Value " << node->Value;
			if (i > 0)
			{
				std::cout << " Prev " << node->Previous->Value;
			}
			if (i < len - 1)
			{
				std::cout << " Next " << node->Next->Value;
				node = node->Next.get();
			}

			std::cout << "\n";

		}

		std::string input{};
		std::cin >> input;
		char op = input.substr(0, 1).front();
		int n = std::stoi(input.substr(1,input.size()-1));

		if (op == 'r')
		{
			lloi.Remove(n);
		}
		else
		{
			lloi.Insert(n);
		}
	}
}

