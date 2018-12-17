#pragma once
#include <memory>

using std::unique_ptr;

template <typename T>
class Node
{
public:
	unique_ptr<Node<T>> Next;
	Node<T>* Previous;
	T Value;
	Node(T);
};

template<typename T>
Node<T>::Node(T value)
{
	this->Value = value;
}

template <typename T>
class LinkedList
{
public:
	unique_ptr<Node<T>> Head;
	int Length();
	T GetAtIndex(int);
	void SetAtIndex(int, T);
	Node<T>* Last();
	void Insert(T);
};

template<typename T>
int LinkedList<T>::Length() {
	Node<T>* node = Head.get();
	if (node == nullptr)
	{
		return 0;
	}
	int len = 1;
	while (node->Next != nullptr)
	{
		len++;
		node = node->Next.get();
	}
	return len;
}

template<typename T>
T LinkedList<T>::GetAtIndex(int index)
{
	Node<T>* node = Head.get();
	if (node == nullptr)
	{
		return {};
	}
	for (int i = 0; i < index; i++)
	{
		node = node->Next.get();
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
	Node<T>* node = Head.get();
	if (node == nullptr)
	{
		return {};
	}
	for (int i = 0; i < index; i++)
	{
		node = node->Next.get();
		if (node == nullptr)
		{
			return {};
		}
	}
	node->Value = value;
}

template<typename T>
Node<T>* LinkedList<T>::Last()
{
	Node<T>* node = Head.get();
	if (node == nullptr)
	{
		throw;
	}
	while (node->Next != nullptr)
	{
		node = node->Next.get();
	}
	return node;
}

template<typename T>
void LinkedList<T>::Insert(T value)
{
	if (Head == nullptr)
	{
		Head = std::make_unique<Node<T>>(value);
		return;
	}
	Last()->Next = std::make_unique<Node<T>>(value);
}