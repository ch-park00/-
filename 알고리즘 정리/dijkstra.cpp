#include <stdio.h>
#include <stdlib.h>

struct edge //edge정보를 저장하는 구조체
{
	char v1;
	char v2;
	int weight;
	struct edge* next;
};

struct vertex //vertex 정보를 저장하고 edge를 연결
{
	char v;
	struct vertex* next; //vertex끼리 연결
	struct edge* connected; //vertex에 저장된 edge정보를 저장하는 곳
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
int isvertexinsll(char v) //v가 sll에 있으면 1반환.아니면 0반환
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
void addvertex(char v) //vertex SLL에 v가 있는지 확인 후 없을 시에만 추가
{
	if (isvertexinsll(v) == 0) //v가 vertex sll에 있는지 확인
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
	//vertex 정보를 vertex SLL에 추가
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
struct vertex* findvertex(char v) //vertex SLL에서 v1에 해당하는 곳의 주소 반환
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
void addedgeinfo(struct vertex* v1, struct vertex* v2, int w) //v1->v2 연결한다. 그리고 그때 weight값 입력. edge노드 새로 생성해서 사용
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
		//엣지를 하나씩 뒤져가면서 그래프정보 입력
		//1. vertex 찾고 서로 연결
		struct vertex* v1 = findvertex(edgetemp->v1);
		struct vertex* v2 = findvertex(edgetemp->v2);
		addedgeinfo(v1, v2, edgetemp->weight);
		addedgeinfo(v2, v1, edgetemp->weight);
		edgetemp = edgetemp->next;
	}
}
void initdijkstratable()
{
	//vertex개수 파악 후 table 생성 및 초기화
	int vcnt = howmanyvertexes();
	dtable = (struct dikjstra*)malloc(sizeof(struct dikjstra) * vcnt);
	struct vertex* temp = vertexes;
	for (int i = 0; i < vcnt; i++)
	{
		dtable[i].v = temp->v;
		dtable[i].found = 0;
		temp = temp->next;
		dtable[i].dist = 100000000; //충분히 큰 수
		dtable[i].prev = 0;
	}
}
int findvertexindexfromdtable(char v)//해당 버텍스에 해당하는 dtable 위치 반환
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
//아직까지 최단경로가 결정되지 않고 최소 dist를 가진 vertex를 dtable에서의 id를 반환
//만약 만족하는 vertex가 없다면 -1을 반환
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
void rundijkstra(char svertex) //s버텍스에서 시작
{
	int idx = findvertexindexfromdtable(svertex);
	dtable[idx].dist = 0;

	while (1)
	{
		int i = nextshortvertex();
		if (i == -1) //모든 table에서 found가 T
		{
			return;
		}
		else
		{
			dtable[i].found = 1; //found 'T'로 수정
			struct edge* con = findvertex(dtable[i].v)->connected; //이 때 vertex와 연결된 vertex들의 정보를 update
			while (con != 0)
			{
				int neighoridx = findvertexindexfromdtable(con->v2);
				if (dtable[neighoridx].dist > dtable[i].dist + con->weight)
					//인접해있는 인덱스에 저장되어 있는 dist가
					//나까지의 dist와 가는게 거리의 합보다클때만 업데이트
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
	//들어오는 데이터의 정보만 저장
	addedge('A', 'B', 8);
	addedge('A', 'C', 2);
	addedge('B', 'D', 5);
	addedge('B', 'D', 40);
	addedge('B', 'C', 4);
	//실제로 그래프 생성
	processedges();
	//여기부터 dikjstra 구현
	initdijkstratable();
	rundijkstra('A');
	int c = howmanyvertexes();
	for (int i = 0; i < c; i++)
	{
		printf("%c %d %d %c\n", dtable[i].v, dtable[i].found, dtable[i].dist, dtable[i].prev);
	}
	return 0;
}