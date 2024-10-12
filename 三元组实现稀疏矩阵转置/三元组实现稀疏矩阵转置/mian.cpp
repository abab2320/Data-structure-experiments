//Ҫ���������һ�ξ����ת��
// ϡ������ȡ˳�򴢴�
//�к��л�������Ҫ֪��ÿһ�е������ж��ٸ����������˳�򴢴��ʱ�򽫶�Ӧ����ֱ�Ӳ����¾����Ӧ����������ֻ�ñ���һ��
#include <iostream>
using namespace std;

class Data
{
public:
	int val;
	int col;//��
	int row;//��

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
	
	//ת�ú��λ��
	posi[0] = 0;
	for (int i = 1; i < T.m; i++)
	{
		posi[i] = posi[i - 1] + num[i-1];
	}

	//ת��
	for (int i = 0; i < T.t; i++)
	{
		int col = M.mat[i].col;
		int j = posi[col]; //ת�ú��λ��

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