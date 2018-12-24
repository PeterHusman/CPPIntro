#pragma once
#include <memory>

using std::unique_ptr;
using std::shared_ptr;

template <typename T>
class Node
{
public:
	shared_ptr<Node<T>> Next;
	shared_ptr<Node<T>> Previous;
	T Value;
	//Constructor
	Node(T);
	//Would-be destructor
	//~Node();
};

template<typename T>
Node<T>::Node(T value)
{
	this->Value = value;
}

template <typename T>
class LinkedList
{
private:
	void remove(shared_ptr<Node<T>>);
	bool Circular;
	shared_ptr<Node<T>> last;
public:
	shared_ptr<Node<T>> Head;
	int Length();
	bool IsSpecifiedCircular();
	void MakeCircular();
	void MakeNotCircular();
	bool ToggleCircular();
	T GetAtIndex(int);
	void SetAtIndex(int, T);
	shared_ptr<Node<T>> Last();
	void Insert(T);
	bool HasCycle();
	bool Remove(T);
};

template<typename T>
void LinkedList<T>::MakeCircular() {
	Circular = true;
	if (Head == nullptr)
	{
		return;
	}
	shared_ptr<Node<T>> last = Last();
	Head->Previous = last;
	last->Next = Head;
}

template<typename T>
void LinkedList<T>::MakeNotCircular() {
	Circular = false;
	if (Head == nullptr)
	{
		return;
	}
	shared_ptr<Node<T>> last = Last();
	Head->Previous = nullptr;
	last->Next = nullptr;
}

template<typename T>
bool LinkedList<T>::ToggleCircular()
{
	if (Circular)
	{
		MakeNotCircular();
	}
	else
	{
		MakeCircular();
	}
	return Circular;
}



template<typename T>
bool LinkedList<T>::IsSpecifiedCircular() {
	return IsSpecifiedCircular();
}

template<typename T>
bool LinkedList<T>::HasCycle() {
	shared_ptr<Node<T>> node = Head;
	if (node == nullptr)
	{
		return false;
	}
	shared_ptr<Node<T>> nodeTwo = Head->Next;
	if (nodeTwo == nullptr)
	{
		return false;
	}
	while (true)
	{
		node = node->Next;
		for (int i = 0; i < 2; i++)
		{
			nodeTwo = nodeTwo->Next;
			if (nodeTwo == nullptr)
			{
				return false;
			}
			else if (node == nodeTwo)
			{
				return true;
			}
		}
	}
}

template<typename T>
int LinkedList<T>::Length() {
	shared_ptr<Node<T>> node = Head;
	if (node == nullptr)
	{
		return 0;
	}
	int len = 1;
	while (node->Next != nullptr && node->Next != Head)
	{
		len++;
		node = node->Next;
	}
	return len;
}

template<typename T>
T LinkedList<T>::GetAtIndex(int index)
{
	shared_ptr<Node<T>> node = Head;
	if (node == nullptr)
	{
		return {};
	}
	for (int i = 0; i < index; i++)
	{
		node = node->Next;
		if (node == nullptr)
		{
			return {};
		}
	}
	return node->Value;
}

template<typename T>
void LinkedList<T>::SetAtIndex(int index, T value)
{
	shared_ptr<Node<T>> node = Head;
	if (node == nullptr)
	{
		return {};
	}
	for (int i = 0; i < index; i++)
	{
		node = node->Next;
		if (node == nullptr)
		{
			return {};
		}
	}
	node->Value = value;
}

template<typename T>
shared_ptr<Node<T>> LinkedList<T>::Last()
{
	shared_ptr<Node<T>> node = Head;
	if (node == nullptr)
	{
		throw;
	}
	while (node->Next != nullptr && node->Next != Head)
	{
		node = node->Next;
	}
	return node;
}

template<typename T>
void LinkedList<T>::Insert(T value)
{
	shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(value);
	if (Head == nullptr)
	{
		Head = newNode;
		last = Head;
	}
	else
	{
		shared_ptr<Node<T>> node = last;
		node->Next = newNode;
		node->Next->Previous = node;
		last = newNode;
	}
	if (Circular)
	{
		newNode->Next = Head;
		Head->Previous = newNode;
	}
}
template<typename T>
bool LinkedList<T>::Remove(T value)
{
	shared_ptr<Node<T>> node = Head;
	if (node == nullptr)
	{
		return false;
	}
	if (node->Value == value)
	{
		remove(node);
		return true;
	}
	shared_ptr<Node<T>> nodeTwo = Head->Next;
	if (nodeTwo == nullptr)
	{
		return false;
	}
	else if (nodeTwo->Value == value)
	{
		remove(nodeTwo);
		return true;
	}
	while (true)
	{
		node = node->Next;
		for (int i = 0; i < 2; i++)
		{
			nodeTwo = nodeTwo->Next;
			if (nodeTwo == nullptr)
			{
				return false;
			}
			else if (nodeTwo->Value == value)
			{
				remove(nodeTwo);
				return true;
			}
			else if (node == nodeTwo)
			{
				return false;
			}
		}
	}
}
template<typename T>
void LinkedList<T>::remove(shared_ptr<Node<T>> node)
{
	if (Head == node)
	{
		Head = node->Next;
	}
	if (node->Next != nullptr)
	{
		node->Next->Previous = node->Previous;
	}
	if (node->Previous != nullptr)
	{
		node->Previous->Next = node->Next;
	}
}