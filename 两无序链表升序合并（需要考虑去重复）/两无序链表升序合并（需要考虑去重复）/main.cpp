#include <iostream>
using namespace std;

class Node
{
public:
	int val;
	Node* next;
	Node() { next = NULL; }
	Node(int a) { val = a; next = NULL; }
};

class List
{
public:
	Node* head;
	Node* back;
	int size;
	List();

	void push_back(int a);
};

List::List()
{
	head = back = NULL;
}

void List::push_back(int a)
{
	Node* p = new Node(a);
	if (head == NULL)
	{
		head = p;
		back = p;
		size = 1;
	}
	else
	{
		back->next = p;
		back = p;
		size++;
	}
}

class Solution
{
public:
	List a, b; //两个链表
	void get_list();
	void sort_list();
};

void Solution::get_list()//将两个链表输入
{
	int x = 0;
	while (cin >> x)
	{
		a.push_back(x);
		if (cin.get() == '\n') break;
	}

	while (cin >> x)
	{
		b.push_back(x);
		if (cin.get() == '\n') break;
	}
}

void Solution::sort_list()
{
	List c;
	Node* p = a.head;
	for (int i = 0; i < a.size; i++)
	{
		int x = p->val;
		if (c.head == NULL)
		{
			c.push_back(x);
		}
		else
		{
			Node* j = c.head;
			//int flag = 1;
			while (j != NULL)
			{
				if (j->val == x)//去重
				{
					break;
				}
				else if (x > j->val)
				{
				
					if (j->next == NULL)
					{
						c.push_back(x);
						break;
					}
					else if (x < j->next->val)
					{
						Node* temp = new Node(x);
						temp->next = j->next;
						j->next = temp;
						break;
					}
				}
				else if (j->val>x)
				{
					Node* temp = new Node(x);
					temp->next = j;
					c.head = temp;
					break;
				}
				j = j->next;
			}
		}
		p = p->next;
	}

	Node* q = b.head;
	for (int i = 0; i < b.size; i++)
	{
		int x = q->val;
		Node* j = c.head;
		//int flag = 1;
		while (j != NULL)
		{
			if (j->val == x)
			{
				break;
			}
			else if (x > j->val)
			{
				if (j->next == NULL)
				{
					c.push_back(x);
					break;
				}
				else if (x < j->next->val)
				{
					Node* temp = new Node(x);
					temp->next = j->next;
					j->next = temp;
					break;
				}
			}
			else if (j->val > x)
			{
				Node* temp = new Node(x);
				temp->next = j;
				c.head = temp;
				break;
			}
			j = j->next;
		}
		q = q->next;
	}

	Node* rear = c.head;//输出结果
	while (rear != NULL)
	{
		cout << rear->val << " ";
		rear = rear->next;
	}
}

int main()
{
	Solution s;
	s.get_list();
	s.sort_list();
}