#include <iostream>
#include <string>
#include "Node.h"
#include "LLRB.h"
void TestF();

int main()
{
	LLRBTree<int> llrboi{};

}


int LLmain()
{
	TestF();
	LinkedList<int> lloi{};

	//lloi.Insert(25);
	//lloi.Insert(34);
	//lloi.Insert(46);
	lloi.MakeNotCircular();
	while (true)
	{
		system("CLS");
		Node<int>* node = lloi.Head.get();
		int len = lloi.Length();
		for (int i = 0; i < len; i++)
		{
			std::cout << "Value " << node->Value;
			if (node->Previous != nullptr)
			{
				std::cout << " Prev " << node->Previous->Value;
			}
			if (node->Next != nullptr)
			{
				std::cout << " Next " << node->Next->Value;
				node = node->Next.get();
			}

			std::cout << "\n";

		}

		std::string input{};
		std::cin >> input;
		char op = input.substr(0, 1).front();
		int n;
		if (input.size() > 1)
		{
			n = std::stoi(input.substr(1, input.size() - 1));
		}
		if (op == 'r')
		{
			lloi.Remove(n);
		}
		else if (op == 'i')
		{
			lloi.Insert(n);
		}
		else if (op == 'c')
		{
			lloi.ToggleCircular();
		}
	}
}

void TestF() {
	LinkedList<int> lloi{};
	for (int i = 0; i < 100000; i++)
	{
		lloi.Insert(i);
	}
}

