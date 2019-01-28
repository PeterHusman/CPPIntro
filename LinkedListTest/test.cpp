#include "pch.h"

#include "LLRB.h"

void testOutOfScope();
int Compare(int, int);
bool IsSomewhatValid(shared_ptr<RBNode<int>>);
int RecursiveValid(shared_ptr<RBNode<int>>, int);

TEST(LLRBTest, TestInsert) {
	LLRBTree<int> llrb{ &Compare };
	for (int i = 0; i < 1000; i++)
	{
		llrb.Insert(i);
	}
	EXPECT_TRUE(!llrb.Head->Red && IsSomewhatValid(llrb.Head));
}



TEST(LLRBTest, TestDisposing) {
	
	EXPECT_NO_THROW(testOutOfScope());
}

void testOutOfScope()
{
	LLRBTree<int> llrb{&Compare};
	for (int i = 0; i < 100000; i++)
	{
		llrb.Insert(i);
	}
}

int Compare(int a, int b)
{
	return a - b;
}

bool IsSomewhatValid(shared_ptr<RBNode<int>> node)
{
	if (node == nullptr)
	{
		return true;
	}
	if (IsRed(node->RightChild) && !IsRed(node->LeftChild))
	{
		return false;
	}
	if (IsRed(node) && (IsRed(node->LeftChild) || IsRed(node->RightChild)))
	{
		return false;
	}
	return IsSomewhatValid(node->LeftChild) && IsSomewhatValid(node->RightChild);
}

int RecursiveValid(shared_ptr<RBNode<int>> node, int num)
{
	if (node == nullptr)
	{
		return -2;
	}
	if (!node->Red)
	{
		num++;
	}
	if (IsRed(node->RightChild) && !IsRed(node->LeftChild))
	{
		return -1;
	}
	if (IsRed(node) && (IsRed(node->LeftChild) || IsRed(node->RightChild)))
	{
		return -1;
	}

}