#pragma once
#include"Table.h"
struct LinkNode
{
	int** state = NULL;	//二维数组state[i][j]为第i+1行第j+1列的数字
	int empty = Empty;	//表中对应节点的空位所在的位置
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
LinkNode* OpenList;	//建立Open表
LinkNode* CloseList;//建立Close表


LinkNode* GetBest() {
	LinkNode* p = OpenList;
	LinkNode* prebest = OpenList;
	LinkNode* best = OpenList->next;

	//扫描f(n)最小的节点
	while (p->next != NULL) {
		if (p->next->f < best->f) {
			best = p->next;
			prebest = p;
		}
		p = p->next;
	}

	//将此节点从Open表中删除
	best = prebest->next;
	prebest->next = best->next;

	//将此节点加入Close表中
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
			cout << "正在搜索…… 完成度：" << n * n - s->h << "/" << n * n << endl;
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
}//删除节点

void AddToList(LinkNode*& p, LinkNode*& s)
{
	//如果已经在Close表中就不进行操作
	if (ExistTableX(CloseList, s->state)) return;

	//更新g(n)的值
	s->g = p->g + 1;

	//如果已经在Open表中，判断是否更优
	LinkNode* tmp = new LinkNode;
	if (GetTableX(s->state, tmp)) {

		//如果更优，则在Tree中移动已存在节点的位置，并更新已存在结点的g(n)和f(n)
		if (s->g < tmp->g) {
			Del(tmp);
			AddToTree(p, tmp);
			tmp->g = s->g;
			tmp->f = tmp->g + tmp->h;
		}

		//释放新节点的内存
		delete s;
		return;
	}

	//更新h(n)和g(n)
	s->h = getH(s->state);
	s->f = s->g + s->h;

	//将旧节点和新节点建立父子关系
	AddToTree(p, s);

	//将新节点加入Open表
	s->next = OpenList->next;
	OpenList->next = s;
}