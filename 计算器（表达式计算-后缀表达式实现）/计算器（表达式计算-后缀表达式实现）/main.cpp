#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution
{
public:
	string exp;//后缀表达式
	stack<char> oppr;//符号
	string s;
	int result;

	Solution() { result = 0; }
	void get_s();
	void get_exp();
	void get_result();
};

void Solution::get_s()
{
	char c;
	while (cin >> c)
	{
		if (c == '=') break;
		s = s + c;
	}
}

void Solution::get_exp() //获取逆波兰表达式
{
	string x;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			x = x + s[i];
		}
		else
		{
			//将数字放入表达式
			if (s[i] == ' ') continue;
			else if (x != "")
			{
				exp = exp + x + ',';
				x = "";
			}

			//开始判断符号
			if (s[i] == '(') oppr.push(s[i]);
			else if (s[i] == ')')
			{
				while (oppr.top() != '(')
				{
					char temp = oppr.top();
					oppr.pop();
					exp = exp + temp + ',';
				}
				oppr.pop();//将左括号出栈
			}
			else if (s[i] == '*' || s[i] == '/')
			{
				while (!oppr.empty() && oppr.top() != '(' && (oppr.top() == '*' || oppr.top() == '/'))
				{
					exp = exp + oppr.top() + ',';
					oppr.pop();
				}
				oppr.push(s[i]);
			}
			else if (s[i] == '+' || s[i] == '-')
			{
				while (!oppr.empty()&&oppr.top() != '(')
				{
					exp = exp + oppr.top() + ',';
					oppr.pop();
				}
				oppr.push(s[i]);
			}
		}
	}
	exp = exp + x + ',';
	while (!oppr.empty())
	{
		exp = exp + oppr.top()+',';
		oppr.pop();
	}
	exp.pop_back(); //去掉结尾的，号
}

void Solution::get_result()
{
	stack<int> num;
	int x = 0;
	int flag = 0;
	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] >= '0' && exp[i] <= '9')
		{
			x = x * 10 + (exp[i] - '0');
			flag = 1;
		}
		else if (exp[i] == ',')
		{
			if (flag == 1)
			{
				num.push(x);
				x = 0;
				flag = 0;
			}
		}
		else
		{
			char opp = exp[i];
			int b = num.top();
			num.pop();
			int a = num.top();
			num.pop();
			int sum = 0;

			if (opp == '+') sum = a + b;
			else if (opp == '-')sum = a - b;
			else if (opp == '*')sum = a * b;
			else if (opp == '/') sum = a / b;

			num.push(sum);
		}
	}

	this->result = num.top();
}

int main()
{
	//freopen("in.txt", "r", stdin);
	Solution s;
	s.get_s();
	//cout << s.s;
	s.get_exp();
	//cout << s.exp << endl;
	s.get_result();
	cout << s.result << endl;
}