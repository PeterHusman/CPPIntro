#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "Node.h"
#include "LLRB.h"
#include "Graphs.h"

#include <vector>
#include <array>

void TestF();
int Compare(int, int);
void VisualizeLLRB(shared_ptr<RBNode<int>>, int);

int main()
{

	std::array<std::array<int, 15>, 15> positions;

	Graph<int> goi{};
	while (true)
	{
		std::string input{};
		std::cin >> input;
		char op = input.substr(0, 1).front();
		int value;
		int value2;
		int value3;
		if (input.size() > 1)
		{
			size_t index = input.find_first_of(',');
			if (index == std::string::npos)
			{
				value = std::stoi(input.substr(1, input.size()-1));
			}
			else
			{
				value = std::stoi(input.substr(1, index - 1));
				size_t index2 = input.find_last_of(',');
				value2 = std::stoi(input.substr(index + 1, index2 - 1));
				value3 = std::stoi(input.substr(index2 + 1, input.size()));
			}
		}
		if (op == 'n')
		{
			goi.AddVertex(value);
		}
		else if (op == 'e')
		{
			goi.AddEdge(goi.LinearSearch(value), goi.LinearSearch(value2), value3, true);
		}

		for (auto&& node : goi.Nodes)
		{
			//Add draw-er
		}
	}
}


int llrbMain()
{
	////std::chrono::time_point<std::chrono::steady_clock> epoch = std::chrono::steady_clock::now();

	////if (std::chrono::steady_clock::now() > epoch + std::chrono::milliseconds(50)) {

	////}

	//int a = 4;
	//int b = 2;

	//float c = 3;
	//float d = 12;

	//std::vector<int> e;
	//std::vector<int> f;

	//add2(a, b);


	//add2<double, 18>(c, d);
	//add(e, f);


	LLRBTree<int> llrboi{ &Compare };
	while (true)
	{
		VisualizeLLRB(llrboi.Head, 80);
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
		else if (op == 'r')
		{
			llrboi.Remove(n);
		}
	}
}

int Power(int base, int exponent)
{
	int output = 1;
	for (int i = 0; i < exponent; i++)
	{
		output *= base;
	}
	return output;
}

void VisualizeLLRB(shared_ptr<RBNode<int>> head, int distance)
{
	system("CLS");
	if (head == nullptr)
	{
		return;
	}
	std::deque<shared_ptr<RBNode<int>>> deque{};
	int level = 0;
	deque.emplace_back(head);
	int i = 0;
	int numNull = 0;
	int actualDist = distance;
	for (int j = 0; j < actualDist; j++)
	{
		std::cout << " ";
	}
	const char esc = 27;
	while (!deque.empty())
	{
		int len = 0;
		shared_ptr<RBNode<int>> node = deque.front();
		deque.pop_front();
		if (IsRed(node))
		{
			len++;
			std::cout << esc << "[31mR" << esc << "[0m";
		}
		else if (node != nullptr)
		{
			std::cout << "B";
			len++;
		}
		if (node != nullptr)
		{
			numNull = 0;
			std::cout << node->Value;
			len += (std::to_string(node->Value)).size();
			deque.emplace_back(node->LeftChild);
			deque.emplace_back(node->RightChild);
		}
		else
		{
			numNull++;
			deque.emplace_back(nullptr);
			deque.emplace_back(nullptr);
		}
		for (int j = 0; j < (distance * 2 - len); j++)
		{
			std::cout << " ";
		}
		i++;
		if (i >= pow(2, level))
		{
			distance = distance / 2;
			actualDist = distance;
			level++;
			std::cout << std::endl;
			if (numNull == i)
			{
				return;
			}
			for (int j = 0; j < actualDist; j++)
			{
				std::cout << " ";
			}
			i = 0;
			numNull = 0;
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

