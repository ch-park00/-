#include <stdio.h>
// MAX Heap ����
#define Sz 30
#define root 1
int heap[Sz] = { 0, 3,8,23,213,21,11,42 };
int heap_size = 7;

// ���� �� ���� child ��带 ���� �ٲ�� �ϴ� ���� �ִ��� �˻��ϰ� �ٲ۴�.
// �� ��, �ٲ� ��쿡�� �ٲ� �Ŀ� �Ʒ� �ʿ����� �ٲ�� �ϴ� ��찡 ���� �� �����Ƿ� 
// �ٲ� �Ʒ��ʵ� �˻��ϴ� ������ �ִ�.
void findLocation(int cur)
{
	int left = cur * 2;
	int right = left + 1;
	int big = cur;
	if (left <= heap_size && heap[big] < heap[left]) {
		big = left;
	}
	if (right <= heap_size && heap[big] < heap[right]) {
		big = right;
	}
	if (big == cur)	return;
	else
	{
		int tmp = heap[cur];
		heap[cur] = heap[big];
		heap[big] = tmp;
		findLocation(big);
	}
}
// ���� heap �迭�� max heap�� �°� ��ȯ
void heapify()
{
	int cur = heap_size / 2;
	while (1)
	{
		if (cur < 1)	break;
		findLocation(cur);
		cur--;
	}
}
void add2heap(int data)
{
	int parent;
	int cur;
	heap_size++;
	parent = heap_size / 2;
	cur = heap_size;
	heap[heap_size] = data;
	while (1)
	{
		if (parent < 1)	return;
		if (heap[cur] < heap[parent])	return;
		else
		{
			int tmp = heap[cur];
			heap[cur] = heap[parent];
			heap[parent] = tmp;
			cur = parent;
			parent = parent / 2;
		}
	}
}

int del_root()
{
	int max = heap[root];
	heap[root] = heap[heap_size];
	heap_size--;
	findLocation(root);
	return max;
}
int main()
{
	int max = -1;
	heapify();
	for (int i = 1; i <= heap_size; i++)
	{
		printf("%d\n", heap[i]);
	}
	add2heap(111);
	printf("---------------\n");
	for (int i = 1; i <= heap_size; i++)
	{
		printf("%d\n", heap[i]);

	}
	max = del_root();
	printf("max num:%d\n", max);
	for (int i = 1; i <= heap_size; i++)
	{
		printf("%d\n", heap[i]);
	}
	return 0;
}