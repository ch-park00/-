#include <stdio.h>
#include <stdlib.h>
struct edge
{
	char src;
	char dst;
	int weight;
	struct edge *next;
};
struct vertex //vertex SLL�� �߰��Ǵ� ���
{
	char v;
	char family; //family ������ vertex SLL�� �߰�=>�� SLL�� family table�� Ȱ��
	struct vertex *next;
};
struct edge *edges = 0; //edge�� ����� ������ ���⿡ �߰��Ǽ� ��� ������ sll�� �����
struct vertex *vertexes = 0; //vertex �� ���� ����Ű�� ������
int checkVertex(char v) //v�� vertex�� ������ 1�� ��ȯ
{
	struct vertex *temp = vertexes;

	while (temp != 0)
	{
		if (temp->v == v)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}
int findfamily(char v) 
{
	struct vertex *temp = vertexes;

	while (temp != 0)
	{
		if (temp->v == v)
		{
			return temp->family; //���������� ��ȯ
		}
		temp = temp->next;
	}
	return 0;
}
void addVertex(char v)
{
	//vertex SLL�� v�� �����ÿ��� SLL�� �߰�.

	//1.v�� vertex�� �߰��Ǿ����� Ȯ��
	if (checkVertex(v) == 1)
	{
		return;
	}
	//2. ������ ���ο� �������� �ǳ��� �߰�
	else
	{
		struct vertex *new1 = (struct vertex *)malloc(sizeof(struct vertex));
		new1->v = v;
		new1->family = v; //�ʱ⿡ ������ �ڱ� �ڽ�
		new1->next = 0;
		if (vertexes == 0)
		{
			vertexes = new1;
			return;
		}
		else
		{
			struct vertex *temp = vertexes;
			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = new1;
		}
	}
}
int arewefam(char v1, char v2) //v1�� v2�� ���� �����̸� 1.�ƴϸ� 0��ȯ
{
	//v1�� v2�� ���� ���� Ȯ��
	if (findfamily(v1) == findfamily(v2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void changefam(char src, char dst)
{
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		if (temp->family == src)
		{
			temp->family = dst;
		}
		temp = temp->next;
	}
}
void justmarried(char v1, char v2) //v1�� v2�� ���� �������� �հ�
{
	struct vertex *temp = vertexes;
	struct vertex *temp1 = vertexes;
	while (temp->v != v1) 
	{
		temp = temp->next;
	}
	while (temp1->v!=v2)
	{
		temp1 = temp1->next;
	}
	changefam(temp1->family, temp->family);
}
//���ο� edge �߰�
void addEdge(char _src, char _dst, int _weight)
{
	struct edge *new1 = (struct edge *)malloc(sizeof(struct edge));
	new1->src = _src;
	new1->dst = _dst;
	new1->weight = _weight;
	new1->next = 0;
	if (edges == 0)
	{
		edges = new1;
	}
	else
	{
		struct edge *temp = edges;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
//sll�� ����ִ� �������� Ȯ��
int countsll(struct edge *head)
{
	int cnt = 0;
	struct edge *temp = head;
	while (temp != 0)
	{
		cnt += 1;
		temp = temp->next;
	}
	return cnt;
}
int findvertex()
{
	int cnt = 0;
	struct vertex *temp = vertexes;
	while (temp != 0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}
int main()
{
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 5);
	addEdge('A', 'D', 3);
	addEdge('B', 'E', 13);
	addEdge('B', 'C', 7);
	addEdge('C', 'E', 20);
	addEdge('C', 'D', 4);
	addEdge('C', 'F', 80);
	addEdge('C', 'G', 17);
	addEdge('E', 'F', 15);
	addEdge('D', 'G', 2);
	//edge ����
	//bubble sort �̿�(array�̿�)
	int n = countsll(edges); //edge�� ���� count
	//������ �迭 ����
	struct edge *edgeArray = (struct edge *)malloc(sizeof(struct edge)*n);
	//sll�迭�� ����
	struct edge *temp = edges;
	for (int i = 0; i < n; i++)
	{
		edgeArray[i].src = temp->src;
		edgeArray[i].dst = temp->dst;
		edgeArray[i].weight = temp->weight;
		temp = temp->next;
	}
	//������ �迭�� ���� bubble sort ����
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			if (edgeArray[j].weight > edgeArray[j + 1].weight)
			{
				struct edge temp = edgeArray[j];
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = temp;
			}
		}
	}
	// family table �� ���ϱ� ���� vertex ������ ���ؾ��Ѵ�.
	//vertex�� �� ���̰� �̸��� ���� �˱� ���� �迭�� �����鼭 �ϳ��� ã�Ƴ���.
	for (int i = 0; i < n; i++)
	{
		//vertex�� ���ο� SLL�� �߰�.��, �ߺ��� ����
		addVertex(edgeArray[i].src);
		addVertex(edgeArray[i].dst);
	}
	int mstCnt = 0;
	for (int i = 0; i < n; i++) //edge���� ������������ �ϳ��� �˻��ϸ鼭 MST�� �߰��Ҽ��ִ��� Ȯ��
	{
		if (arewefam(edgeArray[i].src, edgeArray[i].dst) == 0)
		{
			printf("add edge %c - %c to MST\n", edgeArray[i].src, edgeArray[i].dst);
			mstCnt += 1;
			if (mstCnt == findvertex() - 1)
			{
				break;
			}
			justmarried(edgeArray[i].src, edgeArray[i].dst); //�Ϻ��ϰ� �����غ���
		}
		else
		{
			continue;
		}
	}
	return 0;
}