#include <stdio.h>
int data[20] = { 0,6,3,5,7,10,1,2 }; //�� ó�� 0�� ���� �ε����� �ƴϴ�.

void swap(int i, int j)
{
	int temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}
void findlocation(int cur, int i) //max heap�� �°� ��ġ�� ã�ư��� �Լ�.cur�� ���� �ε��� ��ȣ,i�� �ִ� �ε��� ��ȣ.
{
	int left = cur * 2;
	int right = left + 1;
	int big = cur; //���� ū ���� �����ϰ� �ִ� �ε��� ��ȣ�� ����
	if (left <= i && data[left] > data[cur]) //���� �ڽ��� ���� ũ�� left�� �ε��� ���� �ȿ� �ִ�.
	{
		big = left; 
	}
	if (right <= i && data[right] > data[big]) //������ �ڽ��� ���� ũ�� right�� �ε��� ���� �ȿ� �ִ�.
	{
		big = right; 
	}
	if (big == cur) //�ٲ�� ����
	{
		return;
	}
	else
	{
		swap(cur, big); //cur�� big�� �ε��� �����͸� ���� �ٲ۴�
		findlocation(big, i); //�ٲ� ��ġ���� �ٲ� �� ������ ������ Ȯ���ϴ� ������ �ʿ��ϴ�.
	}
}
void heapify(int i) //i�� �� ������ �ε��� ��ȣ
{
	int cur = i / 2; //cur�� �θ� ����� �ε��� ��ȣ
	while (cur >= 1) 
	{
		findlocation(cur, i);
		cur--;
	}
}
void addToheap(int v, int i)//v�� �߰��� ������,i�� ���� �ִ� �ε��� ��ȣ
{
	int cur = i + 1;
	int parent = cur / 2;
	data[cur] = v;
	while (1)
	{
		if (data[parent] > data[cur])
		{
			return;
		}
		else
		{
			swap(parent, cur);
			cur = parent;
			parent = parent / 2;
			if (parent < 1)
			{
				return;
			}
		}
	}
}
int removeroot(int i)
{
	int temp = data[1];
	data[1] = data[i];
	findlocation(1, i - 1);
	return temp;
}
void main()
{
	int a;
	heapify(7); 
	printf("root:%d\n", data[1]);
	addToheap(20, 7);
	printf("root:%d\n", data[1]);
	addToheap(30, 8);
	printf("root:%d\n", data[1]);
	a=removeroot(9);
	printf("������ ���:%d\nroot���:%d\n", a, data[1]);
	for (int i = 1; i <= 8; i++)
	{
		printf("%d\n", data[i]);
	}
}