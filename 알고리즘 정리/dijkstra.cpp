#include <stdio.h>
#include <stdlib.h>

struct edge //edge������ �����ϴ� ����ü
{
	char v1;
	char v2;
	int weight;
	struct edge* next;
};

struct vertex //vertex ������ �����ϰ� edge�� ����
{
	char v;
	struct vertex* next; //vertex���� ����
	struct edge* connected; //vertex�� ����� edge������ �����ϴ� ��
};
//dijkstra table
struct dikjstra
{
	char v;
	int found;
	int dist;
	char prev;
};
struct edge* edges = 0;
struct vertex* vertexes = 0;
struct dikjstra* dtable = 0;
int howmanyvertexes()
{
	int cnt = 0;
	struct vertex* temp = vertexes;
	while (temp != 0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}
int isvertexinsll(char v) //v�� sll�� ������ 1��ȯ.�ƴϸ� 0��ȯ
{
	struct vertex* temp = vertexes;
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
void addvertex(char v) //vertex SLL�� v�� �ִ��� Ȯ�� �� ���� �ÿ��� �߰�
{
	if (isvertexinsll(v) == 0) //v�� vertex sll�� �ִ��� Ȯ��
	{
		struct vertex* new1 = (struct vertex*)malloc(sizeof(struct vertex));
		new1->v = v;
		new1->next = 0;
		new1->connected = 0;
		if (vertexes == 0)
		{
			vertexes = new1;
			return;
		}
		else
		{
			struct vertex* temp = vertexes;
			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = new1;
		}
	}
}
void addedge(char v1, char v2, int w)
{
	//vertex ������ vertex SLL�� �߰�
	addvertex(v1);
	addvertex(v2);
	struct edge* new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->v1 = v1;
	new1->v2 = v2;
	new1->weight = w;
	new1->next = 0;

	if (edges == 0)
	{
		edges = new1;
	}
	else
	{
		struct edge* temp = edges;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
struct vertex* findvertex(char v) //vertex SLL���� v1�� �ش��ϴ� ���� �ּ� ��ȯ
{
	struct vertex* temp = vertexes;
	while (temp != 0)
	{
		if (temp->v == v)
		{
			return temp;
		}
		temp = temp->next;
	}
}
void addedgeinfo(struct vertex* v1, struct vertex* v2, int w) //v1->v2 �����Ѵ�. �׸��� �׶� weight�� �Է�. edge��� ���� �����ؼ� ���
{
	struct edge* new1 = (struct edge*)malloc(sizeof(struct edge));
	new1->v2 = v2->v;
	new1->weight = w;
	new1->next = 0;

	struct edge* temp = v1->connected;
	if (temp == 0)
	{
		v1->connected = new1;
	}
	else
	{
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void processedges()
{
	struct edge* edgetemp = edges;
	while (edgetemp != 0)
	{
		//������ �ϳ��� �������鼭 �׷������� �Է�
		//1. vertex ã�� ���� ����
		struct vertex* v1 = findvertex(edgetemp->v1);
		struct vertex* v2 = findvertex(edgetemp->v2);
		addedgeinfo(v1, v2, edgetemp->weight);
		addedgeinfo(v2, v1, edgetemp->weight);
		edgetemp = edgetemp->next;
	}
}
void initdijkstratable()
{
	//vertex���� �ľ� �� table ���� �� �ʱ�ȭ
	int vcnt = howmanyvertexes();
	dtable = (struct dikjstra*)malloc(sizeof(struct dikjstra) * vcnt);
	struct vertex* temp = vertexes;
	for (int i = 0; i < vcnt; i++)
	{
		dtable[i].v = temp->v;
		dtable[i].found = 0;
		temp = temp->next;
		dtable[i].dist = 100000000; //����� ū ��
		dtable[i].prev = 0;
	}
}
int findvertexindexfromdtable(char v)//�ش� ���ؽ��� �ش��ϴ� dtable ��ġ ��ȯ
{
	int vcnt = howmanyvertexes();
	for (int i = 0; i < vcnt; i++)
	{
		if (dtable[i].v == v)
		{
			return i;
		}
	}
}
//�������� �ִܰ�ΰ� �������� �ʰ� �ּ� dist�� ���� vertex�� dtable������ id�� ��ȯ
//���� �����ϴ� vertex�� ���ٸ� -1�� ��ȯ
int nextshortvertex()
{
	int vcnt = howmanyvertexes();
	int shortest = 100000000;
	int shortestidx = -1;
	for (int i = 0; i < vcnt; i++)
	{
		if (dtable[i].found == 0 &&
			dtable[i].dist < shortest)
		{
			shortestidx = i;
			shortest = dtable[i].dist;
		}
	}
	return shortestidx;
}
void rundijkstra(char svertex) //s���ؽ����� ����
{
	int idx = findvertexindexfromdtable(svertex);
	dtable[idx].dist = 0;

	while (1)
	{
		int i = nextshortvertex();
		if (i == -1) //��� table���� found�� T
		{
			return;
		}
		else
		{
			dtable[i].found = 1; //found 'T'�� ����
			struct edge* con = findvertex(dtable[i].v)->connected; //�� �� vertex�� ����� vertex���� ������ update
			while (con != 0)
			{
				int neighoridx = findvertexindexfromdtable(con->v2);
				if (dtable[neighoridx].dist > dtable[i].dist + con->weight)
					//�������ִ� �ε����� ����Ǿ� �ִ� dist��
					//�������� dist�� ���°� �Ÿ��� �պ���Ŭ���� ������Ʈ
				{
					dtable[neighoridx].dist = dtable[i].dist + con->weight;
					dtable[neighoridx].prev = dtable[i].v;
				}
				con = con->next;
			}
		}
	}
}
int main()
{
	//������ �������� ������ ����
	addedge('A', 'B', 8);
	addedge('A', 'C', 2);
	addedge('B', 'D', 5);
	addedge('B', 'D', 40);
	addedge('B', 'C', 4);
	//������ �׷��� ����
	processedges();
	//������� dikjstra ����
	initdijkstratable();
	rundijkstra('A');
	int c = howmanyvertexes();
	for (int i = 0; i < c; i++)
	{
		printf("%c %d %d %c\n", dtable[i].v, dtable[i].found, dtable[i].dist, dtable[i].prev);
	}
	return 0;
}