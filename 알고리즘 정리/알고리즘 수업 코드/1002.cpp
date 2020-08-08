#include <stdio.h>
#include <stdlib.h>
#define Sz 6
//graph����
struct node
{
	char v;
	struct node *next; //stack(queue)�� ���
	struct node *left; //�� �ΰ��� bst���� ���(visited������)
	struct node *right;
};
struct node *graph[Sz] = { 0 };
//stack ����
struct node *stack = 0;
//queue ����
struct node *queue = 0;
//visited ����
struct node *visited = 0; 

void add2visited(char v) //visited�� ���ο� ���ؽ��� �߰�
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->v = v;
	new1->left = 0;
	new1->right = 0;

	if (visited == 0)
	{
		visited = new1;
	}
	else
	{
		struct node *temp = visited;
		while (1)
		{
			if (temp->v > v)
			{
				if (temp->left == 0)
				{
					temp->left = new1;
					return;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = new1;
					return;
				}
				temp = temp->right;
			}
		}
	}
}
int checkvisited(char v)
{
	struct node *temp = visited;
	while (temp != 0)
	{
		if (temp->v == v) //ã�� ���� ã����
		{
			return 1;
		}
		if (temp->v > v)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return 0; //while���� ���鼭 ã�°��� ã������
}
void enqueue(char t) //�� �ڿ� ����
{
	struct node *new1 = (struct node*)malloc(sizeof(struct node));
	new1->v = t;
	new1->next = 0;

	if (queue == 0)
	{
		queue = new1;
	}
	else
	{
		struct node *temp = queue;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
char dequeue() //�Ǿտ��� ������ dequeue
{
	if (queue == 0)
	{
		return '-';
	}
	char v = queue->v;
	struct node *temp = queue;
	queue = queue->next;
	free(temp);
	return v;
}
void push(char v)
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->v = v;
	new1->next = 0;

	new1->next = stack; //���� �Ǿտ� �ִ� �ָ� ���� ���� node�� ����
	stack = new1; //stack�� head�� �Ǿ����� �̵�
	return;
}
char pop()
{
	if (stack == 0)
	{
		return '-'; //������ ���� ����
	}
	else
	{
		struct node *temp = stack;
		char t = stack->v; 
		stack = stack->next;// ����(���)�� �ڷ� �̵�
		free(temp); //return�� ���� free�����ش�. ���ϸ� unreferenced space�� �ȴ�.
		return t;
	}
}
void addEdgemini(char src, char dst)
{
	int idx = src - 'A';
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->v = dst;
	new1->next = 0;

	if (graph[idx] == 0)
	{
		graph[idx] = new1;
	}
	else
	{
		struct node *temp = graph[idx];
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
void addEdge(char src, char dst) //edge�� vertex�� ����
{
	addEdgemini(src, dst);
	addEdgemini(dst, src);
}
void performDFS(char t)
{
	//1�ܰ�
	push(t);
	//2�ܰ�
	while (1)
	{
		char x = pop();
		if (x == '-')
		{
			return;
		}
		if (checkvisited(x) == 1)
		{
			continue;
		}
		else
		{
			printf("---->%c\n", x); //ȭ�鿡 �����
			add2visited(x); //visited�� �߰�
			int idx = x-'A'; //�׸��� ����� vertex���� stack�� push
			struct node *temp = graph[idx];
			while (temp != 0)
			{
				if (checkvisited(temp->v) == 0)
				{
					push(temp->v);
				}
				temp = temp->next;
			}
		}
	}
}
void performBFS(char t)
{
	//1�ܰ�
	enqueue(t);
	//2�ܰ�
	while (1)
	{
		char x = dequeue();
		if (x == '-')
		{
			return;
		}
		if (checkvisited(x) == 1)
		{
			continue;
		}
		else
		{
			printf("---->%c\n", x);
			add2visited(x);
			int idx = x - 'A';
			struct node *temp = graph[idx];
			while (temp != 0)
			{
				if (checkvisited(temp->v) == 0)
				{
					enqueue(temp->v);
				}
				temp = temp->next;
			}
		}
	}
}
//BFS �� DFS�� ����
int main()
{
 	addEdge('A', 'C'); //���� ������ ���⼭�� �������.������ BST�� �����Ҷ��� ������ �߿�
	addEdge('C', 'B');
	addEdge('C', 'F');
	addEdge('B', 'E');
	addEdge('D', 'B');
	addEdge('D', 'F');
	printf("DFS:\n");
	performDFS('C'); //
	printf("BFS:\n");
	visited = 0;
	performBFS('C'); //�� �ΰ��� visited�� �������� ���� ������ �Ϸ��� �߰��� visited�� �ʱ�ȭ�ؾ��Ѵ�.
	return 0;
}