#include <iostream>
#include <vector>
#include<fstream>
#define file "abc.out"
using namespace std;

class Solution
{
public:
	vector<vector<int>> v1; //第一个矩阵
	vector<vector<int>> v2;//第二个矩阵
	vector<vector<int>> v; //结果
	int m1, n1; //m1行
	int m2, n2;
	int m, n;
	int a, b;

	Solution();
	void create_v1();
	void create_v2();
	void display();
	void add_v1_v2();
	void add_line(int line1,int line2);
	void down_file();
};

void Solution::down_file()
{
	fstream f;
	f.open(file, ios::out);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n1+n2; j++)
		{
			f << v[i][j] << " ";
		}
		f << "\n";
	}
}

Solution::Solution()
{
	m1 = m2 = n1 = n2 = 0;
	a = b = 0;
	m = n = 0;
}

void Solution::create_v2()
{
	cin >> m2;
	cin >> n2;
	for (int i = 0; i < m2; i++)
	{
		vector<int>v21;
		for (int j = 0; j < n2; j++)
		{
			int x = 0;
			cin >> x;
			v21.push_back(x);
		}
		v2.push_back(v21);
	}
}

void Solution::create_v1()
{
	cin >> m1;
	cin >> n1;
	for (int i = 0; i < m1; i++)
	{
		vector<int>v11;
		for (int j = 0; j < n1; j++)
		{
			int x = 0;
			cin >> x;
			v11.push_back(x);
		}

		v1.push_back(v11);
	}
}

void Solution::display()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n1+n2; j++)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
}

void Solution::add_line(int line1, int line2)
{
	vector<int> temp;
	for (int i = 0; i < n1; i++)
	{
		int x = v1[line1][i];
		temp.push_back(x);
	}

	for (int i = 0; i < n2; i++)
	{
		int x = v2[line2][i];
		temp.push_back(x);
	}

	this->m++;
	v.push_back(temp);
}

void Solution::add_v1_v2()
{
	cin >> a;
	cin >> b;
	a--; b--;
	for (int i = 0; i < m1; i++)
	{
		int same = v1[i][a];
		for (int j = 0; j < m2; j++)
		{
			if (v2[j][b] == same)
			{
				this->add_line(i, j);
			}
		}
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	Solution s;
	s.create_v1();
	//s.display();
	s.create_v2();
	s.add_v1_v2();
	//s.display();
	s.down_file();
}