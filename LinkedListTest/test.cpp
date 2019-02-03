#include "pch.h"

#include "LLRB.h"

void testOutOfScope();
int Compare(int, int);
bool IsSomewhatValid(shared_ptr<RBNode<int>>);
bool IsValid(shared_ptr<LLRBTree<int>>);
int RecursiveValid(shared_ptr<RBNode<int>>);

TEST(LLRBTest, TestInsert) {
	auto llrb = std::make_shared<LLRBTree<int>>(&Compare);
	for (int i = 0; i < 1000; i++)
	{
		llrb->Insert(i);
	}


	EXPECT_TRUE(IsValid(llrb));
}

TEST(LLRBTest, TestIsValid)
{
	auto llrb = std::make_shared<LLRBTree<int>>(&Compare);
	for (int i = 0; i < 1000; i++)
	{
		llrb->Insert(i);
	}
	EXPECT_TRUE(IsValid(llrb));

	llrb->Head->RightChild->RightChild->RightChild->Red = !llrb->Head->RightChild->RightChild->RightChild->Red;
	EXPECT_FALSE(IsValid(llrb));

	llrb->Head->RightChild->RightChild->RightChild->Red = !llrb->Head->RightChild->RightChild->RightChild->Red;
	llrb->Head->RightChild->RightChild->RightChild->Value = 1001;

	EXPECT_FALSE(IsValid(llrb));
}

TEST(LLRBTest, TestRemoving)
{
	auto llrb = std::make_shared<LLRBTree<int>>(&Compare);
#pragma region InitTree
	llrb->Head = std::make_shared<RBNode<int>>(4, &Compare);
	llrb->Head->Red = false;
	llrb->Head->LeftChild = std::make_shared<RBNode<int>>(2, &Compare);
	llrb->Head->LeftChild->Red = true;
	llrb->Head->RightChild = std::make_shared<RBNode<int>>(6, &Compare);
	llrb->Head->RightChild->Red = true;
	llrb->Head->LeftChild->LeftChild = std::make_shared<RBNode<int>>(1, &Compare);
	llrb->Head->LeftChild->LeftChild->Red = false;
	llrb->Head->LeftChild->RightChild = std::make_shared<RBNode<int>>(3, &Compare);
	llrb->Head->LeftChild->RightChild->Red = false;
	llrb->Head->RightChild->LeftChild = std::make_shared<RBNode<int>>(5, &Compare);
	llrb->Head->RightChild->LeftChild->Red = false;
	llrb->Head->RightChild->RightChild = std::make_shared<RBNode<int>>(8, &Compare);
	llrb->Head->RightChild->RightChild->Red = false;
	llrb->Head->RightChild->RightChild->LeftChild = std::make_shared<RBNode<int>>(7, &Compare);
	llrb->Head->RightChild->RightChild->LeftChild->Red = true;
#pragma endregion
	for (int i = 1; i <= 8; i++)
	{
		EXPECT_TRUE(llrb->Remove(i) && IsValid(llrb));
	}
}



TEST(LLRBTest, TestDisposing) {

	EXPECT_NO_THROW(testOutOfScope());
}

void testOutOfScope()
{
	LLRBTree<int> llrb{ &Compare };
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

bool IsValid(shared_ptr<LLRBTree<int>> tree)
{
	return !IsRed(tree->Head) && (RecursiveValid(tree->Head) != -1);
}

int RecursiveValid(shared_ptr<RBNode<int>> node)
{
	int num = 0;
	if (node == nullptr)
	{
		return 0;
	}
	if (!IsRed(node))
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
	if ((node->LeftChild != nullptr && node->LeftChild->Value >= node->Value) || (node->RightChild != nullptr && node->RightChild->Value <= node->Value))
	{
		return -1;
	}
	int leftValid = RecursiveValid(node->LeftChild);
	if (leftValid == -1)
	{
		return -1;
	}

	int rightValid = RecursiveValid(node->RightChild);
	if (rightValid == -1)
	{
		return -1;
	}

	if (leftValid == rightValid)
	{
		return leftValid + num;
	}
	else
	{
		return -1;
	}

}