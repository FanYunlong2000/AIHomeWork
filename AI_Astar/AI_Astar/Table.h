#pragma once
#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define INF MAXINT  //INF��ʾ�����

using namespace std;
int** Table;	//table[i][j]Ϊ��i+1�е�j+1��
int** Target;	//����Ŀ����
int n = 3;
int Empty;//Empty��ʾ�ո�

bool MoveUp(int**& a, int x, int y) {
	if (x == 0)return false;
	a[x][y] = a[x - 1][y];
	a[x - 1][y] = 0;
	return true;
}//���Ʋ���
bool MoveDown(int**& a, int x, int y) {
	if (x == n - 1)return false;
	a[x][y] = a[x + 1][y];
	a[x + 1][y] = 0;
	return true;
}//���Ʋ���
bool MoveLeft(int**& a, int x, int y) {
	if (y == 0)return false;
	a[x][y] = a[x][y - 1];
	a[x][y - 1] = 0;;
	return true;
}//���Ʋ���
bool MoveRight(int**& a, int x, int y) {
	if (y == n - 1)return false;
	a[x][y] = a[x][y + 1];
	a[x][y + 1] = 0;
	return true;
}//���Ʋ���

bool Equal(int** TableA, int** TableB) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (TableA[x][y] != TableB[x][y])
				return false;
		}
	}
	return true;
}
void Show(int** tableX) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (!tableX[x][y]) {
				cout << "\t";
				continue;
			}
			cout << tableX[x][y] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void InitTable() {
	cout << "ʵ��Ŀ�����ƶ��ո�ʹ��ʼ״̬ת��ΪĿ��״̬\n\n�˴ν�ʹ��A*�㷨���������������ɹ������ת��·����\n\n";
	cout << endl;
	Table = new int* [n];
	Target = new int* [n];
	for (int i = 0; i < n; i++) {
		Table[i] = new int[n];
		Target[i] = new int[n];
	}
	for (int i = 0; i < n * n - 1; i++) {
		Table[i / n][i % n] = i + 1;//���ɵ���Ŀ��˳��Ȼ���õ��Ʒ�����һ����������Ŀ
		Target[i / n][i % n] = i + 1;
	}
	Table[n - 1][n - 1] = 0;
	Target[n - 1][n - 1] = 0;
	Empty = n * n - 1;
	cout << "Ŀ��״̬��" << endl;
	Show(Table);
}
void randomConstruct() {
	InitTable();
	Sleep(1000);
	cout << "������ɳ�ʼ״̬..." << endl << endl;
	Sleep(1000);
	srand(unsigned(time(NULL)));

generate:
	for (int i = 0; i < n + 30; i++) {
		switch (rand() % 4)
		{
		case 0:
			if (MoveUp(Table, Empty / n, Empty % n))
				Empty = Empty - n;
			break;
		case 1:
			if (MoveRight(Table, Empty / n, Empty % n))
				Empty = Empty + 1;
			break;
		case 2:
			if (MoveDown(Table, Empty / n, Empty % n))
				Empty = Empty + n;
			break;
		case 3:
			if (MoveLeft(Table, Empty / n, Empty % n))
				Empty = Empty - 1;
			break;
		}
	}
	if (Equal(Table, Target))
		goto generate;
	cout << "��ʼ״̬��" << endl;
	Show(Table);
	Sleep(1000);
	cout << "�밴�������ʼ��";
	char stop_to_input = _getch();
	cout << "\n\n��ʼ��������";
	Sleep(3000);
}
void InitTableX(int**& TableA) {
	TableA = new int* [n];
	for (int i = 0; i < n; i++) {
		TableA[i] = new int[n];
	}
	for (int i = 0; i < n * n; i++) {
		TableA[i / n][i % n] = 0;
	}
}
void InitTableX(int**& TableA, int** TableB) {
	TableA = new int* [n];
	for (int i = 0; i < n; i++) {
		TableA[i] = new int[n];
	}
	for (int i = 0; i < n * n; i++) {
		TableA[i / n][i % n] = TableB[i / n][i % n];
	}
}
int getH(int** TableA) {
	int h = 0;
	for (int i = 0; i < n * n; i++) {
		int x = i / n,		//����
			y = i % n,		//����
			n = TableA[x][y];	//��Ӧ����
		if (n)
			h += (i != n - 1);
		else
			h += (i != (n * n - 1));
	}
	return h;
}

