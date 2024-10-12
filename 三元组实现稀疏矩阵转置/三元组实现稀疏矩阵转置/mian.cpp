//要求遍历数组一次就完成转置
// 稀疏矩阵采取顺序储存
//行和列互换——要知道每一列的数字有多少个，便可以在顺序储存的时候将对应列数直接插入新矩阵对应的行数，就只用遍历一次
#include <iostream>
using namespace std;

class Data
{
public:
	int val;
	int col;//列
	int row;//排

	Data(int row,int col,int val):row(row),col(col),val(val){}
	Data(){}
};

class Matrix
{
public:
	int m, n, t;
	Data* mat;
	Matrix(int m, int n, int t)
	{
		this->m = m; this->n = n; this->t = t;
		mat = new Data[t];
	}
	Matrix(){}

	void Show()
	{
		cout << m << " " << n << " " << t << endl;
		for (int i = 0; i < t; i++)
		{
			cout << mat[i].row << " " << mat[i].col << " " << mat[i].val;
			if (i != t - 1) cout << endl;
		}
	}

};

class Solution
{
public:
	Matrix M, T;
	void CreateM(int m, int n, int t);
	void Turn();
};

void Solution::CreateM(int m, int n, int t)
{
	M = Matrix(m, n, t);
	T = Matrix(n, m, t);
	int row, col, val;
	for (int i = 0; i < t; i++)
	{
		cin >> row; cin >> col; cin >> val;
		M.mat[i] = Data(row, col, val);
	}
}

void Solution::Turn()
{
	int* num = new int[T.m];
	int* posi = new int[T.m];
	for (int i = 0; i < T.m; i++)
		num[i] = 0;
	for (int i = 0; i < M.t; i++)
		num[M.mat[i].col]++;
	
	//转置后的位置
	posi[0] = 0;
	for (int i = 1; i < T.m; i++)
	{
		posi[i] = posi[i - 1] + num[i-1];
	}

	//转置
	for (int i = 0; i < T.t; i++)
	{
		int col = M.mat[i].col;
		int j = posi[col]; //转置后的位置

		T.mat[j].row = M.mat[i].col;
		T.mat[j].col = M.mat[i].row;
		T.mat[j].val = M.mat[i].val;

		posi[col]++;
	}
}

int main()
{
	Solution s;
	int m, n, t;
	cin >> m; cin >> n; cin >> t;
	s.CreateM(m, n, t);
	s.Turn();
	s.T.Show();
}