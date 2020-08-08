#include<stdio.h>
#include<stdlib.h>
#define SZ 6
char family[SZ];
struct edge {
	char src;
	char dst;
	int weight;
};      //edge�� ���� �־��ֱ� ���� ���� ��� ����Ǿ� �ְ� weight�� ������
int graph[SZ][SZ]; //all zeros  ���������� �ʱ�ȭ �����൵ 0��
int edge_cnt = 0;
void addEdge(char src, char dst, int weight)
{
	graph[src - 'A'][dst - 'A'] = weight;
	graph[dst - 'A'][src - 'A'] = weight;
	family[src - 'A'] = src;
	edge_cnt += 1; //�� ������ ����� count
}

struct edge* BuildEdgeArray(void)
{
	struct edge *edgeArray =  (struct edge*)malloc(sizeof(struct edge)*edge_cnt);
	return edgeArray;

}


int areWeFamily(char v1, char v2)
{
	int idx_1 = v1 - 'A';
	int idx_2 = v2 - 'A';
	if (family[idx_1] == family[idx_2])
	{
		return 1;
	}
	return 0;
}

void justMarried(char v1, char v2)
{

	char familyMark_v1 = family[v1 - 'A'];
	char familyMark_v2 = family[v2 - 'A'];//���� family��ũ�� �˾ƾ��� 

	char newFamilyMark;
	char toBeChanged;
	if (familyMark_v1 < familyMark_v2)
	{
		newFamilyMark = familyMark_v1;
		toBeChanged = familyMark_v2;
	}
	else
	{
		newFamilyMark = familyMark_v2;
		toBeChanged = familyMark_v1;
	}
	//family���� tobevchanged �� ã�Ƽ� �ٲ� 
	for (int i = 0; i < SZ; i++)
	{
		if ( family[i] == toBeChanged )
		{
			family[i] = newFamilyMark;
		}
	}
}



int main(void)
{
	addEdge('A','C',1);
	addEdge('A', 'B', 23);
	addEdge('B', 'C', 10);
	addEdge('B', 'D', 173);
	addEdge('B', 'E', 10);
	addEdge('C', 'D', 10);
	addEdge('C', 'F', 5);
	addEdge('D', 'E', 9);
	addEdge('D', 'F', 12);
	addEdge('E', 'F', 9);
	struct edge *edgeArray = BuildEdgeArray();
	int idx = 0; //edgeArray�� �ֱ� ���� index
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (graph[i][j] > 0 && i < j) //�ߺ��Ǵ� edge�� ���ϱ� ���ؼ�
			{
				edgeArray[idx].src = 'A' + i;
				edgeArray[idx].dst = 'A' + j;
				edgeArray[idx].weight = graph[i][j];
				idx += 1;

			}
		}
	}
	//edgeArray�� weight�� ������������ ����
	for (int i = 0; i < edge_cnt; i++)
	{
		for (int j = 0; j < edge_cnt - 1 - i; j++)
		{
			if (edgeArray[j].weight > edgeArray[j + 1].weight)
			{
				struct edge temp = edgeArray[j]; //�迭�� ���´� ����Ű�� �ִ°ſ� ��������
				edgeArray[j] = edgeArray[j + 1];
				edgeArray[j + 1] = temp;
			}
		}
	}
	//edgeArray�� ���
	for (int i = 0; i < edge_cnt; i++)
	{
		printf("%c %c %d\n", edgeArray[i].src, edgeArray[i].dst, edgeArray[i].weight);
	}

	//MST�� ã�Ƴ��� ����ϴ� �κ�
	// --->MST�� ���� edge�鸸 ��� ���

	int mst_edge_cnt = 0;

	for (int i = 0; i < edge_cnt; i++) // ��� edge�� �ϳ��� ���ʷ�
	{
		struct edge E = edgeArray[i];
		if (areWeFamily(E.src, E.dst) == 0) //�ٸ� ����
		{
			mst_edge_cnt += 1;
			printf("MST Edge %c --- %c : %d\n", E.src, E.dst,E.weight);
			justMarried(E.src, E.dst);

			if (mst_edge_cnt == SZ - 1)
			{
				break;
			}
		}
		
	}
	return 0;
} 