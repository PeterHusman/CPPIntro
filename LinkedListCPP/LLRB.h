#pragma once
#include <memory>
#include <iostream>

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
private:
	shared_ptr<RBNode<T>> RecursiveRemove(shared_ptr<RBNode<T>>, T);

public:
	shared_ptr<RBNode<T>> Head;
	int Count;
	bool Insert(T);
	bool Remove(T);
	int(*Comparer)(T, T);
	LLRBTree(comparer_func);
	shared_ptr<RBNode<T>> MoveRedLeft(shared_ptr<RBNode<T>>);
	shared_ptr<RBNode<T>> MoveRedRight(shared_ptr<RBNode<T>>);
	shared_ptr<RBNode<T>> GetMinimum(shared_ptr<RBNode<T>>);
	shared_ptr<RBNode<T>> Fixup(shared_ptr<RBNode<T>>);
	LLRBTree();
	~LLRBTree();
};

template<typename T>
shared_ptr<RBNode<T>> LLRBTree<T>::MoveRedRight(shared_ptr<RBNode<T>> node)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	node->ColorFlip();
	if (node->LeftChild != nullptr && IsRed(node->LeftChild->LeftChild))
	{
		node = Rotate(node, false);
		node->ColorFlip();
	}
	return node;
}

template<typename T>
shared_ptr<RBNode<T>> LLRBTree<T>::MoveRedLeft(shared_ptr<RBNode<T>> node)
{
	node->ColorFlip();
	if (node->RightChild != nullptr && IsRed(node->RightChild->LeftChild))
	{
		node->RightChild = Rotate(node->RightChild, false);
		node = Rotate(node, true);
		if (node->RightChild != nullptr && IsRed(node->RightChild->RightChild))
		{
			node->RightChild = Rotate(node->RightChild, true);
		}
		node->ColorFlip();
	}
	return node;
}

template<typename T>
shared_ptr<RBNode<T>> LLRBTree<T>::RecursiveRemove(shared_ptr<RBNode<T>> node, T value)
{
	if ((*Comparer)(value, node->Value) < 0)
	{
		if (node->LeftChild != nullptr)
		{

			if (!IsRed(node->LeftChild) && !IsRed(node->LeftChild->LeftChild))
			{
				node = MoveRedLeft(node);
			}

			node->LeftChild = RecursiveRemove(node->LeftChild, value);
		}
	}
	else
	{
		if (IsRed(node->LeftChild))
		{
			node = Rotate(node, false);
		}
		if ((*Comparer)(value, node->Value) == 0 && node->RightChild == nullptr)
		{
			Count--;
			return nullptr;
		}

		if (node->RightChild != nullptr)
		{
			if (!IsRed(node->RightChild) && !IsRed(node->RightChild->LeftChild))
			{
				node = MoveRedRight(node);
			}
			if ((*Comparer)(value, node->Value) == 0)
			{
				shared_ptr<RBNode<T>> minNode = GetMinimum(node->RightChild);
				node->Value = minNode->Value;
				node->RightChild = RecursiveRemove(node->RightChild, minNode->Value);
			}
			else
			{
				node->RightChild = RecursiveRemove(node->RightChild, value);
			}
		}
	}

	return Fixup(node);
}

template<typename T>
shared_ptr<RBNode<T>> LLRBTree<T>::Fixup(shared_ptr<RBNode<T>> node)
{
	if (IsRed(node->RightChild))
	{
		node = Rotate(node, true);
	}
	if (IsRed(node->LeftChild) && IsRed(node->LeftChild->LeftChild))
	{
		node = Rotate(node, false);
	}
	if (IsRed(node->LeftChild) && IsRed(node->RightChild))
	{
		node->ColorFlip();
	}
	if (node->LeftChild != nullptr && IsRed(node->LeftChild->RightChild) && !IsRed(node->LeftChild->LeftChild))
	{
		node->LeftChild = Rotate(node->LeftChild, true);
		if (IsRed(node->LeftChild))
		{
			node = Rotate(node, false);
		}
	}
	return node;
}

template<typename T>
shared_ptr<RBNode<T>> LLRBTree<T>::GetMinimum(shared_ptr<RBNode<T>> node)
{
	while (node->LeftChild != nullptr)
	{
		node = node->LeftChild;
	}
	return node;
}

template<typename T>
bool LLRBTree<T>::Remove(T value)
{
	int initCount = Count;
	if (Head != nullptr)
	{
		Head = RecursiveRemove(Head, value);
		if (Head != nullptr)
		{
			Head->Red = false;
		}
	}
	return initCount != Count;
}

template<typename T>
LLRBTree<T>::~LLRBTree()
{
	//Comparer.Dispose();
}


//
//template <typename T, int V = 4>
//T add2(T a, T b)
//{
//	T data[V];
//	std::cout << "Integral Enable If" << std::endl;
//	return a + b;
//}


//template <typename T>
//void add(T a, T b, typename std::enable_if <!std::is_integral<T>::value && !std::is_floating_point<T>::value>::type* = 0)
//{
//	std::cout << "Non Enabled If" << std::endl;
//}

//struct MyStruct;
//
//template <typename T>
//T add(T a, T b)
//{
//	if constexpr (std::is_integral<T>::value) {
//		printf("Integral Enable If\n");
//		return a + b;
//		//return;
//	}
//	else if constexpr (std::is_floating_point<T>::value) {
//		printf("Floating Enable If\n");
//		return a - b;
//		//return;
//	}
//	else if constexpr (std::is_same<T, MyStruct>::value) {
//		printf("Custom Thing\n");
//		return a;
//	}
//	else {
//		printf("Total Else");
//		return b;
//	}
//}



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
		Count++;
		return true;
	}

	bool result = Head->Insert(value);
	if (result)
	{
		Count++;
	}
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
	Count = 0;
	this->Comparer = comparer;
}

template<typename T>
LLRBTree<T>::LLRBTree()
{
}
