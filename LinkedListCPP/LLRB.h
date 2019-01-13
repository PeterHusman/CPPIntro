#pragma once
#include <memory>

using std::unique_ptr;
using std::shared_ptr;


template <typename T>
class RBNode
{
	typedef int(*comparer_func)(T, T);
public:
	shared_ptr<RBNode<T>> RightChild;
	shared_ptr<RBNode<T>> LeftChild;
	bool Red;
	T Value;
	RBNode(T, comparer_func);
	void ColorFlip();
	bool Insert(T);
	int(*Comparer)(T, T);
	
};

template<typename T>
shared_ptr<RBNode<T>> Rotate(shared_ptr<RBNode<T>> node, bool rotateLeft)
{
	if (rotateLeft)
	{
		node->RightChild->Red = false;
		node->Red = true;
		shared_ptr<RBNode<T>> newParent = node->RightChild;
		node->RightChild = newParent->LeftChild;
		newParent->LeftChild = node;
		return newParent;
	}
	else
	{
		node->LeftChild->Red = false;
		node->Red = true;
		shared_ptr<RBNode<T>> newParent = node->LeftChild;
		node->LeftChild = newParent->RightChild;
		newParent->RightChild = node;
		return newParent;
	}

}

template<typename T>
bool RBNode<T>::Insert(T value)
{
	bool result = true;
	if (IsRed(LeftChild) && IsRed(RightChild))
	{
		ColorFlip();
	}
	if ((*Comparer)(value, Value) == 0)
	{
		return false;
	}
	else if ((*Comparer)(value, Value) > 0)
	{
		if (RightChild == nullptr)
		{
			RightChild = std::make_shared<RBNode<T>>(value, Comparer);
		}
		else
		{
			result = RightChild->Insert(value);
		}
	}
	else
	{
		result = LeftChild->Insert(value);
	}

	if (RightChild != nullptr && IsRed(RightChild->RightChild))
	{
		RightChild = Rotate(RightChild, true);
	}
	if (LeftChild != nullptr && IsRed(LeftChild->RightChild))
	{
		LeftChild = Rotate(LeftChild, true);
	}
	if (RightChild != nullptr && IsRed(RightChild->LeftChild) && IsRed(RightChild->LeftChild->LeftChild))
	{
		RightChild = Rotate(RightChild, false);
	}
	if (LeftChild != nullptr && IsRed(LeftChild->LeftChild) && IsRed(LeftChild->LeftChild->LeftChild))
	{
		LeftChild = Rotate(LeftChild, false);
	}
	return result;
}

template<typename T>
RBNode<T>::RBNode(T value, comparer_func comparer)
{
	this->Value = value;
	Red = true;
	this->Comparer = comparer;
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
	typedef int(*comparer_func)(T, T);
public:
	shared_ptr<RBNode<T>> Head;
	bool Insert(T);
	int(*Comparer)(T, T);
	LLRBTree(comparer_func);
	LLRBTree();
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
		shared_ptr<RBNode<T>> newNode = std::make_shared<RBNode<T>>(value, Comparer);
		Head = newNode;
		Head->Red = false;
		return true;
	}

	bool result = Head->Insert(value);

	if (IsRed(Head->RightChild))
	{
		Head = Rotate(Head, true);
	}
	if (IsRed(Head->LeftChild) && IsRed(Head->LeftChild->LeftChild))
	{
		Head = Rotate(Head, false);
	}
	Head->Red = false;
	return result;
}

template<typename T>
LLRBTree<T>::LLRBTree(comparer_func comparer)
{
	this->Comparer = comparer;
}

template<typename T>
LLRBTree<T>::LLRBTree()
{

}
