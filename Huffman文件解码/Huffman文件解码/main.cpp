#include <iostream>
using namespace std;
//首先构建树
class BTNode
{
public:
	string val;
	BTNode* lchild;
	BTNode* rchild;

	BTNode(string x) :val(x),rchild(NULL),lchild(NULL){}
	BTNode() { val = "#"; }
};

class BTree
{
public:
	BTNode* r;
	BTree():r(NULL){}

	void CreateBTree();
	void show_tree(BTNode*r);
	void show_result();
};

void BTree::show_tree(BTNode* r)
{
	if (r == NULL) return;

	cout << r->val;
	this->show_tree(r->lchild);
	this->show_tree(r->rchild);
}

void BTree::CreateBTree()
{
	int max = 0;
	cin >> max;
	string str;

	r = new BTNode();
	BTNode* p = r;
	for (int i = 0; i < max; i++)
	{
		cin >> str;
		int Max = str.size();
		string val = "";
		int flag = 0;//标志编码字符是否被识别
		p = r;
		for (int j = 0; j < Max; j++)
		{
			if (str[j] == ':') { flag = 1; continue; }
			if (flag == 0)
			{
				val += str[j]; continue;
			}

			BTNode* q = p;
			switch (str[j])
			{
			case '0':
				if (q->lchild == NULL)
				{
					p = new BTNode();
					q->lchild = p;
				}
				else p = q->lchild;
				break;
			case '1':
				if (q->rchild == NULL)
				{
					p = new BTNode();
					q->rchild = p;
				}
				else p = q->rchild;
			}
		}

		p->val = val;
	}
}

void BTree::show_result()
{
	string secret;
	cin >> secret;
	int Max = secret.size();
	BTNode* p = this->r;
	for (int i = 0; i < Max; i++)
	{
		switch (secret[i])
		{
		case '0':
			p = p->lchild; break;
		case '1':
			p = p->rchild; break;
		}

		if (p->lchild == NULL && p->rchild == NULL&&p!=NULL)
		{
			cout << p->val;
			p = this->r;
		}
	}
}

int main()
{
	BTree bt;
	bt.CreateBTree();
	//bt.show_tree(bt.r);
	//freopen("in.txt", "r", stdin);
	bt.show_result();
	return 0;
}