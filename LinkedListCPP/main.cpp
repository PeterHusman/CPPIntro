#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "Node.h"
#include "LLRB.h"
void TestF();
int Compare(int, int);
void VisualizeLLRB(shared_ptr<RBNode<int>>, int);

int main()
{
	LLRBTree<int> llrboi{ &Compare };
	while (true)
	{
		VisualizeLLRB(llrboi.Head, 20);
		std::string input{};
		std::cin >> input;
		char op = input.substr(0, 1).front();
		int n;
		if (input.size() > 1)
		{
			n = std::stoi(input.substr(1, input.size() - 1));
		}
		if (op == 'i')
		{
			llrboi.Insert(n);
		}
	}
}

void VisualizeLLRB(shared_ptr<RBNode<int>> head, int distance)
{
	system("CLS");
	if (head == nullptr)
	{
		return;
	}
	for (int i = 0; i < distance; i++)
	{
		std::cout << " ";
	}
	std::deque<shared_ptr<RBNode<int>>> deque{};
	int level = 0;
	deque.emplace_back(head);
	int i = 0;
	while (!deque.empty())
	{
		int len = 0;
		shared_ptr<RBNode<int>> node = deque.front();
		deque.pop_front();
		deque.emplace_back(node->LeftChild);
		deque.emplace_back(node->RightChild);
		if (IsRed(node))
		{
			std::cout << "R";
			len++;
		}
		else if (node != nullptr)
		{
			std::cout << "B";
			len++;
		}
		if (node != nullptr)
		{
			std::cout << node->Value;
		}
		for (int j = 0; j < (distance - len); j++)
		{
			std::cout << " ";
		}
		i++;
		if (i >= pow(2, level))
		{
			distance = distance / 2;
			i = 0;
			std::cout << std::endl;
		}
	}

}

int Compare(int a, int b)
{
	return a - b;
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

