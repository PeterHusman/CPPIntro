#pragma once
#include <memory>
#include <map>
#include <vector>
#include <deque>
#include <set>
#include <queue>
#include <concurrent_priority_queue.h>
#include <stack>
#include <functional>

using std::unique_ptr;
using std::shared_ptr;
using std::map;
using std::vector;
using std::deque;
using std::set;
using std::priority_queue;
using std::queue;
using std::stack;

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
	stack<shared_ptr<GraphNode<T>>> Pathfind(shared_ptr<GraphNode<T>>, shared_ptr<GraphNode<T>>, bool, std::function<float(GraphNode<T>*)>);
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
	stack<shared_ptr<GraphNode<T>>> Dijkstras(shared_ptr<GraphNode<T>>, shared_ptr<GraphNode<T>>);
	stack<shared_ptr<GraphNode<T>>> AStar(shared_ptr<GraphNode<T>>, shared_ptr<GraphNode<T>>, std::function<float(GraphNode<T>*)>);
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
				if (edge->End->Value == value)
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

template<typename T>
struct GraphNodeData
{
	bool Visited;
	float Distance;
	float FinalDistance;
	bool Queued;
	shared_ptr<GraphNode<T>> Founder;
	GraphNodeData(bool, float, float, shared_ptr<GraphNode<T>>, bool);
};

template<typename T>
GraphNodeData<T>::GraphNodeData(bool visited, float distance, float finalDistance, shared_ptr<GraphNode<T>> founder, bool queued)
{
	Visited = visited;
	Distance = distance;
	FinalDistance = finalDistance;
	Founder = founder;
	Queued = queued;
}

template<typename T>
stack<shared_ptr<GraphNode<T>>> Graph<T>::Dijkstras(shared_ptr<GraphNode<T>> start, shared_ptr<GraphNode<T>> end)
{
	return Pathfind(start, end, false, nullptr);
}

template<typename T>
stack<shared_ptr<GraphNode<T>>> Graph<T>::AStar(shared_ptr<GraphNode<T>> start, shared_ptr<GraphNode<T>> end, std::function<float(GraphNode<T>*)> heuristic)
{
	return Pathfind(start, end, true, heuristic);
}

template<typename T>
stack<shared_ptr<GraphNode<T>>> Graph<T>::Pathfind(shared_ptr<GraphNode<T>> start, shared_ptr<GraphNode<T>> end, bool useHeuristic, std::function<float(GraphNode<T>*)> heuristic)
{
	map<GraphNode<T>*, shared_ptr<GraphNodeData<T>>> pathFindData{};
	for (auto&& node : Nodes)
	{
		GraphNodeData<T> data{ false, INFINITY, INFINITY, nullptr, false };
		pathFindData.emplace(node.get(), std::make_shared<GraphNodeData<T>>(data));
	}
	std::function<bool(GraphNode<T>*, GraphNode<T>*)> compare = [pathFindData](GraphNode<T>* left, GraphNode<T>* right)
	{
		float dist1 = pathFindData.at(left)->Distance;
		return dist1 > pathFindData.at(right)->Distance;
	};
	if (useHeuristic)
	{
		compare = [pathFindData](GraphNode<T>* left, GraphNode<T>* right)
		{
			float dist1 = pathFindData.at(left)->FinalDistance;
			return dist1 > pathFindData.at(right)->FinalDistance;
		};
	}
	priority_queue<GraphNode<T>*, vector<GraphNode<T>*>, decltype(compare)> priorityQ(compare);
	pathFindData.at(start.get())->Distance = 0;
	pathFindData.at(start.get())->Queued = true;
	if (useHeuristic)
	{
		pathFindData.at(start.get())->FinalDistance = heuristic(start.get());
	}
	priorityQ.push(start.get());
	while (true)
	{
		auto node = priorityQ.top();
		pathFindData.at(node)->Queued = false;
		priorityQ.pop();
		for (auto&& edge : Edges)
		{
			if (edge->Start.get() == node)
			{
				auto endN = edge->End.get();
				auto endData = pathFindData.at(endN);
				if (endData->Distance > pathFindData.at(node)->Distance + edge->Cost)
				{
					endData->Visited = false;
					endData->Distance = pathFindData.at(node)->Distance + edge->Cost;
					if (useHeuristic)
					{
						endData->FinalDistance = endData->Distance + heuristic(endN);
					}
					endData->Founder = edge->Start;
				}
				if (!endData->Visited && !endData->Queued)
				{
					endData->Queued = true;
					priorityQ.push(endN);
				}
			}
		}
		pathFindData.at(node)->Visited = true;
		if (node == end.get())
		{
			break;
		}
	}
	stack<shared_ptr<GraphNode<T>>> path;
	shared_ptr<GraphNode<T>> currentNode = end;
	while (true)
	{
		path.push(currentNode);
		if (currentNode == start)
		{
			return path;
		}
		currentNode = pathFindData.at(currentNode.get())->Founder;
	}
}