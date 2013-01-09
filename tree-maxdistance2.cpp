#include <iostream>
using namespace std;

// 数据结构定义
struct NODE
{
	NODE* pLeft;       	// 左子树
	NODE* pRight;      	// 右子树
	int nMaxLeft;      	// 左子树中的最长距离
	int nMaxRight;     	// 右子树中的最长距离
	char chValue;    	// 该节点的值
};

int nMaxLen = 0;

// 寻找树中最长的两段距离
void FindMaxLen(NODE* pRoot)
{
	// 遍历到叶子节点，返回
	if(pRoot == NULL)
	{
		return;
	}

	// 如果左子树为空，那么该节点的左边最长距离为0
	if(pRoot -> pLeft == NULL)
	{
		pRoot -> nMaxLeft = 0; 
	}

	// 如果右子树为空，那么该节点的右边最长距离为0
	if(pRoot -> pRight == NULL)
	{
		pRoot -> nMaxRight = 0;
	}

	// 如果左子树不为空，递归寻找左子树最长距离
	if(pRoot -> pLeft != NULL)
	{
		FindMaxLen(pRoot -> pLeft);
	}

	// 如果右子树不为空，递归寻找右子树最长距离
	if(pRoot -> pRight != NULL)
	{
		FindMaxLen(pRoot -> pRight);
	}

	// 计算左子树最长节点距离
	if(pRoot -> pLeft != NULL)
	{
		int nTempMax = 0;
		if(pRoot -> pLeft -> nMaxLeft > pRoot -> pLeft -> nMaxRight)
		{
			nTempMax = pRoot -> pLeft -> nMaxLeft;
		}
		else
		{
			nTempMax = pRoot -> pLeft -> nMaxRight;
		}
		pRoot -> nMaxLeft = nTempMax + 1;
	}

	// 计算右子树最长节点距离
	if(pRoot -> pRight != NULL)
	{
		int nTempMax = 0;
		if(pRoot -> pRight -> nMaxLeft > pRoot -> pRight -> nMaxRight)
		{
			nTempMax = pRoot -> pRight -> nMaxLeft;
		}
		else
		{
			nTempMax = pRoot -> pRight -> nMaxRight;
		}
		pRoot -> nMaxRight = nTempMax + 1;
	}

	// 更新最长距离
	if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen)
	{
		nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
	}
}

void Link(NODE* nodes, int parent, int left, int right)
{
	if (left != -1)
		nodes[parent].pLeft = &nodes[left]; 
	if (right != -1)
		nodes[parent].pRight = &nodes[right];
}
int main()
{
	// P. 241 Graph 3-12
	NODE test1[9] = { 0 };
	Link(test1, 0, 1, 2);
	Link(test1, 1, 3, 4);
	Link(test1, 2, 5, 6);
	Link(test1, 3, 7, -1);
	Link(test1, 5, -1, 8);
	nMaxLen = 0;
	FindMaxLen(&test1[0]);
	cout << "test1: " << nMaxLen << endl;
	// P. 242 Graph 3-13 left
	NODE test2[4] = { 0 };
	Link(test2, 0, 1, 2);
	Link(test2, 1, 3, -1);
	nMaxLen = 0;
	FindMaxLen(&test2[0]);
	cout << "test2: " << nMaxLen << endl;
	// P. 242 Graph 3-13 right
	NODE test3[9] = { 0 };
	Link(test3, 0, -1, 1);
	Link(test3, 1, 2, 3);
	Link(test3, 2, 4, -1);
	Link(test3, 3, 5, 6);
	Link(test3, 4, 7, -1);
	Link(test3, 5, -1, 8);
	nMaxLen = 0;
	FindMaxLen(&test3[0]);
	cout << "test3: " << nMaxLen << endl;
	// P. 242 Graph 3-14
	// Same as Graph 3-2, not test
	// P. 243 Graph 3-15
	NODE test4[9] = { 0 };
	Link(test4, 0, 1, 2);
	Link(test4, 1, 3, 4);
	Link(test4, 3, 5, 6);
	Link(test4, 5, 7, -1);
	Link(test4, 6, -1, 8);
	nMaxLen = 0;
	FindMaxLen(&test4[0]);
	cout << "test4: " << nMaxLen << endl;

	return 0;
}


