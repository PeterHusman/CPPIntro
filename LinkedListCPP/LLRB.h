#pragma once
#include <memory>

using std::unique_ptr;
using std::shared_ptr;

template <typename T>
class RBNode
{
public:
	shared_ptr<RBNode<T>> RightChild;
	shared_ptr<RBNode<T>> LeftChild;
	bool Red;
	T Value;
	RBNode(T);
	void ColorFlip();
	bool Insert(T);
};

template<typename T>
bool RBNode<T>::Insert(T value)
{
	bool result;
	if (IsRed(LeftChild) && IsRed(RightChild))
	{
		ColorFlip();
	}
	if (value == Value)
	{
		return false;
	}
	if (value > Value)
	{
		if (RightChild == nullptr)
		{
			RightChild = std::make_shared<RBNode<T>>(value);
		}
		else
		{
			result = RightChild.Insert(value);
		}
	}
	if (value < Value)
	{
		result = LeftChild.Insert(value);
	}
}

template<typename T>
RBNode<T>::RBNode(T value)
{
	this->Value = value;
	Red = true;
}

template<typename T>
void RBNode<T>::ColorFlip()
{
	Red = !Red;
	if (RightChild != nullptr)
	{
		RightChild->Red = !(RightChild->Red);
	}
	if (LeftChild != nullptr)
	{
		LeftChild->Red = !(LeftChild->Red);
	}
}


template<typename T>
class LLRBTree
{
public:
	shared_ptr<RBNode<T>> Head;
	bool Insert(T);
	int(*Comparer)(T, T);
};

template<typename T>
bool IsRed(shared_ptr<RBNode<T>> node)
{
	if (node == nullptr || !(node->Red))
	{
		return false;
	}

	return true;
}

template<typename T>
bool LLRBTree<T>::Insert(T value)
{
	if (Head == nullptr)
	{
		shared_ptr<RBNode<T>> newNode = std::make_shared<RBNode<T>>(value);
		Head = newMode;
		Head->Red = false;
		return true;
	}

	return Head->Insert(value);
}