#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "Node.h"
#include "LLRB.h"
#include "Graphs.h"
#include <random>

#include <vector>
#include <array>

void TestF();
int Compare(int, int);
void VisualizeLLRB(shared_ptr<RBNode<int>>, int);

int main()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	
	std::array<std::array<int, 70>, 70> positions;
	int radius = 30;
	const char esc = 27;

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
		else if (input.size() <= 0)
		{
			op = ' ';
		}
		if (op == 'i')
		{
			goi.AddVertex(value);
		}
		else if (op == 'e')
		{
			goi.AddEdge(goi.LinearSearch(value), goi.LinearSearch(value2), value3, true);
		}
		else if (op == 'N')
		{
			goi.Nodes.clear();
			goi.Edges.clear();
			for (int i = 0; i < value; i++)
			{
				goi.AddVertex(i);
			}
			std::uniform_int_distribution<> distr(0, value);
			while (goi.BreadthFirst(value - 1, goi.Nodes[0]) == nullptr)
			{
				auto n1 = goi.Nodes[distr(eng)];
				auto n2 = goi.Nodes[distr(eng)];
				goi.AddEdge(n1, n2, 1, true);
				goi.AddEdge(n2, n1, 1, true);

			}
		}
		else if (op == 'r')
		{
			goi.RemoveVertex(value);
		}
		else if (op == 'R')
		{
			goi.RemoveEdge(goi.LinearSearch(value), goi.LinearSearch(value2));
		}
		else if (op == 'c')
		{
			auto node = goi.LinearSearch(value);
			for (auto&& edge : goi.Edges)
			{
				if (edge->Start == node)
				{
					edge->End->Value *= -1;
				}
			} 
		}
		else if (op == 'd')
		{
			auto path = goi.Dijkstras(goi.LinearSearch(value), goi.LinearSearch(value3));
			while (!path.empty())
			{
				std::cout << path.top()->Value << " ";
				path.pop();
			}
			system("PAUSE");
		}

		for (auto&& row : positions)
		{
			row.fill(32767);
		}

		int i = 0;
		int len = goi.Nodes.size(); 
		for (auto&& node : goi.Nodes)
		{
			double angle = 2 * 3.141592653589793238462643383f * (double)i / (double)len;
			positions[(int)(sin(angle) * radius) + radius][(int)(cos(angle) * radius) + radius] = node->Value;
			if (node->Value < 0)
			{
				node->Value *= -1;
			}
			i++;
		}
		system("CLS");
		for (auto&& row : positions)
		{
			int xtra = 0;
			for (auto&& pixel : row)
			{
				if (pixel != 32767)
				{
					bool resetColor = false;
					if (pixel < 0)
					{
						pixel *= -1;
						resetColor = true;
						std::cout << esc << "[31m";
					}
					std::cout << pixel;
					xtra = (int)log10(pixel);
					if (resetColor)
					{
						std::cout << esc << "[0m";
					}
				}
				else
				{
					if (xtra == 0)
					{
						std::cout << " ";
					}
					else
					{
						xtra--;
					}
				}
			}
			std::cout << std::endl;
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

