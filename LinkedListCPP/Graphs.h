#pragma once
#include <memory>
#include <map>
#include <vector>
#include <deque>
#include <set>

using std::unique_ptr;
using std::shared_ptr;
using std::map;
using std::vector;
using std::deque;
using std::set;

template<typename T>
class GraphNode
{
	
public:
	T Value;
	GraphNode(T);
};



template<typename T>
GraphNode<T>::GraphNode(T value)
{
	Value = value;
}

template<typename T>
class Edge {
	typedef shared_ptr<GraphNode<T>> NodePtr;
public:
	NodePtr Start;
	NodePtr End;
	double Cost;
	Edge(NodePtr, NodePtr, double);
};

template<typename T>
Edge<T>::Edge(NodePtr start, NodePtr end, double cost)
{
	Start = start;
	End = end;
	Cost = cost;
}

template<typename T>
class Graph
{
private:
	shared_ptr<GraphNode<T>> DepthFirstRecursive(T, shared_ptr<GraphNode<T>>, set<GraphNode<T>*>&);
public:
	vector<shared_ptr<GraphNode<T>>> Nodes;
	vector<shared_ptr<Edge<T>>> Edges;
	Graph();
	bool AddEdge(shared_ptr<GraphNode<T>>, shared_ptr<GraphNode<T>>, double, bool);
	bool RemoveEdge(shared_ptr<GraphNode<T>>, shared_ptr<GraphNode<T>>);
	shared_ptr<GraphNode<T>> AddVertex(T);
	bool RemoveVertex(T);
	shared_ptr<GraphNode<T>> BreadthFirst(T, shared_ptr<GraphNode<T>>);
	shared_ptr<GraphNode<T>> DepthFirst(T, shared_ptr<GraphNode<T>>);
	shared_ptr<GraphNode<T>> LinearSearch(T);
};

template<typename T>
Graph<T>::Graph()
{
}

template<typename T>
bool Graph<T>::AddEdge(shared_ptr<GraphNode<T>> start, shared_ptr<GraphNode<T>> end, double cost, bool overrideIfAlreadyPresent)
{
	for (shared_ptr<Edge<T>> edge : Edges)
	{
		if (edge->Start == start && edge->End == end)
		{
			if (overrideIfAlreadyPresent)
			{
				edge->Cost = cost;
				return true;
			}
			return false;
		}
	}
	Edges.push_back(std::make_shared<Edge<T>>(start, end, cost));
	return true;
}

template<typename T>
bool Graph<T>::RemoveEdge(shared_ptr<GraphNode<T>> start, shared_ptr<GraphNode<T>> end)
{
	auto iterator = Edges.begin();
	auto End = Edges.end();
	while(iterator != End)
	{
		if ((*iterator)->Start == start && (*iterator)->End == end)
		{
			Edges.erase(iterator);
			return true;
		}
		++iterator;
	}
	return false;
}

template<typename T>
shared_ptr<GraphNode<T>> Graph<T>::AddVertex(T value)
{
	for (shared_ptr<GraphNode<T>> node : Nodes)
	{
		if (node->Value == value)
		{
			return nullptr;
		}
	}
	auto nodePtr = std::make_shared<GraphNode<T>>(value);
	Nodes.push_back(nodePtr);
	return nodePtr;
}

template<typename T>
bool Graph<T>::RemoveVertex(T value)
{
	auto iterator = Nodes.begin();
	auto end = Nodes.end();
	while (iterator != end)
	{
		if ((*iterator)->Value == value)
		{
			Nodes.erase(iterator);
			return true;
		}
		++iterator;
	}
	return false;
}

template<typename T>
shared_ptr<GraphNode<T>> Graph<T>::BreadthFirst(T value, shared_ptr<GraphNode<T>> start)
{
	set<GraphNode<T>*> visited{};
	deque<shared_ptr<GraphNode<T>>> queue{};
	queue.push_back(start);
	while (true)
	{
		auto current = queue.front();
		queue.pop_front();
		for (shared_ptr<Edge<T>> edge : Edges)
		{
			if (edge->Start == current && visited.count(edge->End.get()) == 0)
			{
				if (edge->End->Value)
				{
					return edge->End;
				}
				queue.push_back(edge->End);
				visited.insert(edge->End.get());
			}
		}
		if (queue.empty())
		{
			return nullptr;
		}
	}
}

template<typename T>
shared_ptr<GraphNode<T>> Graph<T>::DepthFirst(T value, shared_ptr<GraphNode<T>> start)
{
	set<GraphNode<T>*> visited{};
	return DepthFirstRecursive(value, start, visited);
}

template<typename T>
shared_ptr<GraphNode<T>> Graph<T>::DepthFirstRecursive(T value, shared_ptr<GraphNode<T>> node, set<GraphNode<T>*>& visited )
{
	for (shared_ptr<Edge<T>> edge : Edges)
	{
		if (edge->Start == node && visited.count(edge->End.get()) == 0)
		{
			visited.insert(edge->End.get());
			auto potentialOut = DepthFirstRecursive(value, edge->End, visited);
			if (potentialOut != nullptr)
			{
				return potentialOut;
			}
		}
	}
	return nullptr;
}

template<typename T>
shared_ptr<GraphNode<T>> Graph<T>::LinearSearch(T value)
{
	for (shared_ptr<GraphNode<T>> node : Nodes)
	{
		if (value == node->Value)
		{
			return node;
		}
	}
	return nullptr;
}