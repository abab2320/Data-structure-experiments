#include <iostream>
using namespace std;

class Node
{
public:
	int id; //开始时纸牌的位置
	int val;//纸牌被拿出来是的序号
	Node* next;
	Node() { id = 0; val = 0; next = NULL; }
	Node(int id) { this->id = id; val = 0; next = NULL; }
};

class queue
{
public:
	Node* front;
	Node* rear;
	int size;

	queue();

	void create_q();
	void display(); //测试
	void pop(); //将牌抽出
};

void queue::display()
{
	Node* q = front;
	for (int i = 0; i < size; i++)
	{
		cout << q->id << " ";
		q = q->next;
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << q->val << " ";
		q = q->next;
	}
	cout << endl;
}

queue::queue()
{
	front = rear = NULL;
	size = 0;
}

void queue::create_q()
{
	cin >> size;
	int i = 1;

	Node* p = new Node(1);
	front = p;
	rear = front;

	for (i = 2; i <= size; i++)
	{
		p = new Node(i);
		rear->next = p;
		rear = p;
	}

	rear->next = front; //循环队列
}

void queue::pop()
{
	Node* p = front;
	front = front->next;
	rear->next = front;
}

class Solution
{
public:
	queue q;
	Node* result;
	
	void get_result();
	void display(); //展示结果
};

void Solution::get_result()
{
	q.create_q();
	result = new Node[q.size];

	int cnt = 1;//记录是第几轮

	while (cnt != q.size+1) //当牌没有被抽完
	{
		for (int i = 0; i < cnt; i++)
		{
			q.front = q.front->next;
			q.rear = q.rear->next;
		}

		result[q.front->id-1].val = cnt;
		q.pop();
		cnt++;
	}
}

void Solution::display()
{
	for (int i = 0; i < q.size; i++)
	{
		cout << result[i].val;
		if (i != q.size - 1) cout << " ";
	}
}

int main()
{
	Solution s;
	int m = 0;
	cin >> m;

	for (int i = 0; i < m; i++)
	{
		s.get_result();
		//s.q.display();
		s.display();
		if (i != m - 1) cout << endl;
	}
}