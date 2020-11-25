#pragma once
#include"Table.h"
struct LinkNode
{
	int** state = NULL;	//��ά����state[i][j]Ϊ��i+1�е�j+1�е�����
	int empty = Empty;	//���ж�Ӧ�ڵ�Ŀ�λ���ڵ�λ��
	int g = 0;			//g(n)
	int h = INF;		//h(n)
	int f = INF;		//f(n)=g(n)+f(n)
	LinkNode* next = NULL;
	LinkNode* Parent = NULL;
	LinkNode* Sons[4]{ Sons[0] = Sons[1] = Sons[2] = Sons[3] = NULL };
	LinkNode()
	{
		InitTableX(state);
	};
	LinkNode(LinkNode* x) :empty(x->empty), g(x->g), h(x->h), f(x->f)
	{
		InitTableX(state, x->state);
	};
};
LinkNode* OpenList;	//����Open��
LinkNode* CloseList;//����Close��


LinkNode* GetBest() {
	LinkNode* p = OpenList;
	LinkNode* prebest = OpenList;
	LinkNode* best = OpenList->next;

	//ɨ��f(n)��С�Ľڵ�
	while (p->next != NULL) {
		if (p->next->f < best->f) {
			best = p->next;
			prebest = p;
		}
		p = p->next;
	}

	//���˽ڵ��Open����ɾ��
	best = prebest->next;
	prebest->next = best->next;

	//���˽ڵ����Close����
	best->next = CloseList->next;
	CloseList->next = best;

	return best;
}
void Display(LinkNode* s)
{
	if (s->Parent != NULL)
		Display(s->Parent);

	system("cls");
	Show(s->state);
	Sleep(1000);
}

bool ExistTableX(LinkNode* s, int** tableX) {
	LinkNode* p = s;
	while (p != NULL && !Equal(p->state, tableX)) {
		p = p->next;
	}
	return (p != NULL);
}

bool GetTableX(int** tableX, LinkNode*& x) {
	LinkNode* p = OpenList;
	while (p != NULL && !Equal(p->state, tableX)) {
		p = p->next;
	}
	if (p != NULL) {
		x = p;
	}
	return (p != NULL);
}

void AddToTree(LinkNode*& p, LinkNode*& s) {
	for (int i = 0; i < 4; i++) {
		if (p->Sons[i] == NULL) {
			p->Sons[i] = s;
			s->Parent = p;
			system("cls");
			cout << "������������ ��ɶȣ�" << n * n - s->h << "/" << n * n << endl;
			return;
		}
	}
}

void Del(LinkNode*& s) {
	for (int i = 0; i < 4; i++) {
		if (s->Parent->Sons[i] == s) {
			s->Parent->Sons[i] = NULL;
			s->Parent = NULL;
			return;
		}
	}
}//ɾ���ڵ�

void AddToList(LinkNode*& p, LinkNode*& s)
{
	//����Ѿ���Close���оͲ����в���
	if (ExistTableX(CloseList, s->state)) return;

	//����g(n)��ֵ
	s->g = p->g + 1;

	//����Ѿ���Open���У��ж��Ƿ����
	LinkNode* tmp = new LinkNode;
	if (GetTableX(s->state, tmp)) {

		//������ţ�����Tree���ƶ��Ѵ��ڽڵ��λ�ã��������Ѵ��ڽ���g(n)��f(n)
		if (s->g < tmp->g) {
			Del(tmp);
			AddToTree(p, tmp);
			tmp->g = s->g;
			tmp->f = tmp->g + tmp->h;
		}

		//�ͷ��½ڵ���ڴ�
		delete s;
		return;
	}

	//����h(n)��g(n)
	s->h = getH(s->state);
	s->f = s->g + s->h;

	//���ɽڵ���½ڵ㽨�����ӹ�ϵ
	AddToTree(p, s);

	//���½ڵ����Open��
	s->next = OpenList->next;
	OpenList->next = s;
}