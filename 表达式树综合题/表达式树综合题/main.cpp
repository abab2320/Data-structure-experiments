#include <iostream>
#include <string>
#include <queue>
using namespace std;
//原来的表达式就是树中序遍历的结果
//逆波兰表达式是后序遍历的结果


class BTNode
{
public:
	string val;
	BTNode* lchild;
	BTNode* rchild;

	BTNode(){}
	BTNode(string x):val(x),lchild(NULL),rchild(NULL){}
	BTNode(char x)
	{
		val = "";
		val += x;
		lchild = rchild = NULL;
	}
};

class BTree
{
public:
	BTNode* r;
	BTree():r(NULL){}
};

class Solution
{
public:
	string str;//记录原表达式
	string postexp;//逆波兰表达式

	void GetPost(string str);//获得逆波兰
	void GetStr(BTree&bt);//获得中序遍历的表达式
	void GetStr1(BTNode* r);
	void CreateBT(BTree &bt);
	void show_xian(BTree& bt);
	void show_ceng(BTree& bt);
	void get_result(BTree& bt);
	int get_result1(BTNode* r);
};

void Solution::GetStr(BTree&bt)
{
	GetStr1(bt.r);
}

void Solution::GetStr1(BTNode* r)
{
	if (r == NULL) return;

	GetStr1(r->lchild);
	cout << r->val;
	if (r->val >= "0" && r->val <= "9") cout << "#";
	GetStr1(r->rchild);
}

void Solution:: show_ceng(BTree& bt)
{
	queue<BTNode*> q;

	q.push(bt.r);
	while (!q.empty())
	{
		BTNode* p = q.front(); q.pop();
		if (p != NULL)
		{
			cout << p->val;
			if (p->val >= "0" && p->val <= "9") cout << "#";
			q.push(p->lchild);
			q.push(p->rchild);
		}
	}
}

int Solution::get_result1(BTNode* r)
{
	if (r == NULL) return 0;
	if (r->lchild == NULL && r->rchild == NULL)
	{
		int x = 0;
		int max = r->val.size();
		for (int i = 0; i < max; i++)
		{
			x = x * 10 + (r->val[i] ^ '0');
		}
		return x;
	}

	char ch = r->val[0];
	switch (ch)
	{
	case'+':  return this->get_result1(r->lchild) + this->get_result1(r->rchild);
	case'-':return this->get_result1(r->lchild) - this->get_result1(r->rchild);
	case '*':return this->get_result1(r->lchild) * this->get_result1(r->rchild);
	case '/': return this->get_result1(r->lchild) / this->get_result1(r->rchild);
	}
}

void Solution::get_result(BTree& bt)
{
	int x = get_result1(bt.r);
	cout << x;
}

void show_xian1(BTNode* r)
{
	if (r == NULL) return;

	cout << r->val;
	if (r->val >= "0" && r->val <= "9")
	{
		cout << "#";
	}

	show_xian1(r->lchild);
	show_xian1(r->rchild);
}

void Solution::show_xian(BTree& bt)
{
	show_xian1(bt.r);
}

void Solution::CreateBT(BTree &bt)
{
	int Max = postexp.size();
	if (Max == 0) return;
	BTNode** St = new BTNode*[Max];
	int top = -1;
	BTNode* p = NULL;

	for (int i = 0; i < Max; i++)
	{
		char ch = postexp[i];
		if (ch >= '0' && ch <= '9')
		{
			int j = i;
			string x = "";
			while (postexp[j] != '#')
			{
				
				x += postexp[j];
				j++;
			}
			p = new BTNode(x);
			top++;
			St[top] = p;
			i = j;
		}
		else
		{
			p = new BTNode(ch);
			p->rchild = St[top];
			top--;
			p->lchild = St[top];
			top--;

			top++;
			St[top] = p;
		}
	}

	bt.r = St[top];
}


void Solution:: GetPost(string str)
{
	this->postexp = "";
	int Max = str.size();
	if (Max == 0) return;

	char* oppr = new char[Max];
	int top = -1;

	for (int i = 0; i < Max; i++)
	{
		char ch = str[i];
		if (ch == '(')
		{
			top++;
			oppr[top] = '(';
		}
		else if (ch == ')')
		{
			while (oppr[top] != '(')
			{
				postexp = postexp + oppr[top];
				top--;
			}
			top--;//将‘（’退栈
		}
		else if ('0' <= ch && ch <= '9')
		{
			int j = i;
			while (str[j] >= '0' && str[j]<='9')
			{
				postexp = postexp + str[j];
				j++;
			}
			postexp += '#';
			i = j - 1;
		}
		else
		{
			if (ch == '+' || ch == '-')
			{
				while (top != -1&&oppr[top] != '(')
				{
					postexp = postexp + oppr[top];
					top--;
				}
				top++;
				oppr[top] = ch;
			}
			else if (ch == '*' || ch == '/')
			{
				while ((oppr[top] == '*' || oppr[top] == '/')&&top!=-1)
				{
					postexp = postexp + oppr[top];
					top--;
				}
				top++;
				oppr[top] = ch;
			}
		}
	}
	while (top != -1)
	{
		postexp += oppr[top];
		top--;
	}
	//postexp = postexp.substr(0, postexp.length() - 1);//去掉最后一个‘#’
}

int main()
{
	Solution s;
	string str;
	cin >> str;
	s.str = str;
	s.GetPost(s.str);
	//cout << s.postexp << endl;
	//cout << s.str << endl;
	BTree bt;
	s.CreateBT(bt);
	s.show_xian(bt);
	cout << endl;
	s.GetStr(bt);
	cout << endl;
	cout << s.postexp << endl;
	s.show_ceng(bt);
	cout << endl;
	s.get_result(bt);
}