#include"Node.h"
void Search(LinkNode*& nowNode) {
LinkNode* newNode0 = new LinkNode(nowNode);
	if (MoveUp(newNode0->state, newNode0->empty / n, newNode0->empty % n)) {
		newNode0->empty -= n;
		AddToList(nowNode, newNode0);
	}//空格上移操作
LinkNode* newNode1 = new LinkNode(nowNode);
	if (MoveRight(newNode1->state, newNode1->empty / n, newNode1->empty % n)) {
		newNode1->empty++;
		AddToList(nowNode, newNode1);
	}//空格右移操作
LinkNode* newNode2 = new LinkNode(nowNode);
	if (MoveDown(newNode2->state, newNode2->empty / n, newNode2->empty % n)) {
		newNode2->empty += n;
		AddToList(nowNode, newNode2);
	}//空格下移操作
LinkNode* newNode3 = new LinkNode(nowNode);
	if (MoveLeft(newNode3->state, newNode3->empty / n, newNode3->empty % n)) {
		newNode3->empty--;
		AddToList(nowNode, newNode3);
	}
	}//空格左移操作

void Astar() {
	//第一步：建立Open表和Close表并将七点加入Open表
	OpenList = new LinkNode;

	CloseList = new LinkNode;

	LinkNode* p = new LinkNode;
	OpenList->next = p;
	InitTableX(p->state, Table);
	p->h = getH(Table);
	p->f = p->g + p->h;


	//第二步：如果Open表为空则失败退出
second:
	if (OpenList->next == NULL) {
		cout << "未找到可行的路径！";
		return;
	}

	//第三步：将Open表中f(n)最小的节点设为考察节点"best"并将其从Open表中删除，加入Close表，然后搜索后继节点加入Open表
	LinkNode* best = GetBest();
	Search(best);

	//第四步：如果目标状态在Open表中，则成功退出
	if (ExistTableX(OpenList, Target)) {
		system("cls");
		cout << "过程搜索中…… 完成度：" << n * n << "/" << n * n << endl;
		Sleep(1000);
		cout << endl << "成功找到路线，接下来展示移动过程：" << endl << endl;
		Sleep(2000);
		LinkNode* destination = new LinkNode;
		GetTableX(Target, destination);
		Display(destination);
		return;
	}

	//第五步：跳转到第二步	
	goto second;
}
int main() {
	randomConstruct();	//首先随机生成一个矩阵
	Astar();			//运行A*算法
	cout << "搜索过程展示完毕，按任意键退出程序。";
	char stop_to_input = _getch();
	return 0;
}
