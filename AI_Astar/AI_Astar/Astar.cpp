#include"Node.h"
void Search(LinkNode*& nowNode) {
LinkNode* newNode0 = new LinkNode(nowNode);
	if (MoveUp(newNode0->state, newNode0->empty / n, newNode0->empty % n)) {
		newNode0->empty -= n;
		AddToList(nowNode, newNode0);
	}//�ո����Ʋ���
LinkNode* newNode1 = new LinkNode(nowNode);
	if (MoveRight(newNode1->state, newNode1->empty / n, newNode1->empty % n)) {
		newNode1->empty++;
		AddToList(nowNode, newNode1);
	}//�ո����Ʋ���
LinkNode* newNode2 = new LinkNode(nowNode);
	if (MoveDown(newNode2->state, newNode2->empty / n, newNode2->empty % n)) {
		newNode2->empty += n;
		AddToList(nowNode, newNode2);
	}//�ո����Ʋ���
LinkNode* newNode3 = new LinkNode(nowNode);
	if (MoveLeft(newNode3->state, newNode3->empty / n, newNode3->empty % n)) {
		newNode3->empty--;
		AddToList(nowNode, newNode3);
	}
	}//�ո����Ʋ���

void Astar() {
	//��һ��������Open���Close�����ߵ����Open��
	OpenList = new LinkNode;

	CloseList = new LinkNode;

	LinkNode* p = new LinkNode;
	OpenList->next = p;
	InitTableX(p->state, Table);
	p->h = getH(Table);
	p->f = p->g + p->h;


	//�ڶ��������Open��Ϊ����ʧ���˳�
second:
	if (OpenList->next == NULL) {
		cout << "δ�ҵ����е�·����";
		return;
	}

	//����������Open����f(n)��С�Ľڵ���Ϊ����ڵ�"best"�������Open����ɾ��������Close��Ȼ��������̽ڵ����Open��
	LinkNode* best = GetBest();
	Search(best);

	//���Ĳ������Ŀ��״̬��Open���У���ɹ��˳�
	if (ExistTableX(OpenList, Target)) {
		system("cls");
		cout << "���������С��� ��ɶȣ�" << n * n << "/" << n * n << endl;
		Sleep(1000);
		cout << endl << "�ɹ��ҵ�·�ߣ�������չʾ�ƶ����̣�" << endl << endl;
		Sleep(2000);
		LinkNode* destination = new LinkNode;
		GetTableX(Target, destination);
		Display(destination);
		return;
	}

	//���岽����ת���ڶ���	
	goto second;
}
int main() {
	randomConstruct();	//�����������һ������
	Astar();			//����A*�㷨
	cout << "��������չʾ��ϣ���������˳�����";
	char stop_to_input = _getch();
	return 0;
}
