#include <iostream>
#include <queue>
#include <string>
using namespace std;

class BTNode
{
public:
	string x;
	BTNode* lchild;
	BTNode* rchild;
	BTNode* parent;
	int flag;

	BTNode(string str)
	{
		flag = 0;
		this->x = str;
		lchild = rchild = parent = NULL;
	}
	BTNode()
	{
		lchild = rchild = parent = NULL;
		flag = 0;
	}
};

class BTree
{
public:
	BTNode* r;

	void CreateBTree(string str);
	void ShowBTree();

};

void BTree::ShowBTree()
{
	if (r == NULL) cout << "遍历失败" << endl;

	queue<BTNode*> qu;
	qu.push(r);
	while (!qu.empty())
	{
		BTNode* p = qu.front();
		qu.pop();
		cout << p->x << " ";
		if (p->lchild != NULL)qu.push(p->lchild);
		if (p->rchild != NULL)qu.push(p->rchild);
	}
}

void BTree::CreateBTree(string str)
{
	string x = "";
	int i = 1;//指向根节点的第一个数字
	while (str[i] >= '0' && str[i] <= '9')
	{
		x += str[i];
		i++;
	}

	BTNode* p = new BTNode(x);
	x = "";
	r = p;
	int k = 1;//表明当前的结点为左孩子还是右孩子
	queue<BTNode*> qu;
	qu.push(r);

	for (; i<str.size()-1; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			while (str[i] >= '0' && str[i] <= '9')
			{
				x += str[i];
				i++;
			}
			p = new BTNode(x);
			x = "";

			switch (k)
			{
			case 1:
				qu.front()->lchild = p;
				p->parent = qu.front();
				k = 2; break;
			case 2:
				qu.front()->rchild = p;
				p->parent = qu.front();
				k = 1;
				qu.pop(); break;
			default: break;
			}

			qu.push(p);
		}
		else if (str[i] == ',') ;
		else if (str[i] == '#')
		{
			switch (k)
			{
			case 1: k = 2; break;
			case 2: k = 1; qu.pop(); break;
			}
		}
	}
}

class Solution
{
public:
	string target;
	int k;
	BTNode* tar;
	queue<string> ans;

	void Find_target(BTree& bt);
	void Distance(BTree& bt);
};


void Solution::Distance(BTree& bt)
{
	BTNode* p = this->tar;
	p->flag = 1;
	queue<BTNode*> qu;

	qu.push(p);
	while (!qu.empty())
	{
		p = qu.front(); qu.pop();

		if (p->flag == k + 1)
		{
			ans.push(p->x);
			continue;
		}
		if (p->flag > k + 1) break;

		if (p->lchild != NULL&&p->lchild->flag == 0)
		{
			p->lchild->flag = p->flag + 1;
			qu.push(p->lchild);
		}
		if (p->rchild != NULL&&p->rchild->flag == 0)
		{
			p->rchild->flag = p->flag + 1;
			qu.push(p->rchild);
		}

		if (p->parent != NULL && p->parent->flag == 0)
		{
			p->parent->flag = p->flag + 1;
			qu.push(p->parent);
		}

	}
}

BTNode* Find_target1(BTNode* r, string target)
{
	if (r == NULL) return NULL;
	if (r->x == target) return r;
	else
	{
		if (Find_target1(r->lchild, target) != NULL) return Find_target1(r->lchild, target);
		else return Find_target1(r->rchild, target);
	}
}

void Solution::Find_target(BTree&bt)
{
	if (bt.r == NULL) return;

	BTNode* p = bt.r;

	tar = Find_target1(p, this->target);
}

int main()
{
	freopen("in.txt", "r", stdin);
	BTree bt;
	string str;
	while (cin >> str)
	{
		bt.CreateBTree(str);
		//bt.ShowBTree();
		Solution s;
		cin >> s.target;
		cin >> s.k;
		s.Find_target(bt);
		s.Distance(bt);
		string result = "[";
		while (!s.ans.empty())
		{
			string x = s.ans.front();
			s.ans.pop();
			result += x;
			result += ",";
		}
		result = result.substr(0, result.length() - 1);
		result += "]";

		cout << result << endl;
	}
}