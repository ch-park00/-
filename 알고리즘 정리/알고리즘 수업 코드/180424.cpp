#include <stdio.h>
#define Sz 4
int Queue[Sz]; //ť ����
int front = 0;
int rear = 0;

int isQempty() //ť�� ����ִ��� Ȯ��. ��������� 1��ȯ.�ٸ��� 0��ȯ
{
	return (rear == front);
}
int isQfull() //ť�� �� �� �ִ��� Ȯ��. �� �������� 1��ȯ.�ƴϸ� 0
{
	return ((rear + 1) % Sz == front);
}

void enqueue(int v)
{
	if (isQfull() == 1) //�� �� ������ �׳� �Լ� ����
	{
		return;
	}
	Queue[rear] = v;
	rear = (rear + 1) % Sz; //queue�� circular�̱� ������ �� ��츦 ���
}
int dequeue()
{
	int a;
	if (isQempty() == 1)
	{
		return -1111; //ť�� ����ٴ� ��
	}
	a = Queue[front];
	front = (front + 1) % Sz;
	return a;
}
void dequeue_()
{
	int a;
	if (isQempty() == 1)
	{
		printf("����� �����Ͱ� �����ϴ�.\n");
	}
	else
	{
		printf("%d\n", Queue[front]);
		front=(front+1)%Sz;
	}
}
void main()
{
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	printf("%d\n", dequeue()); // 1
	printf("%d\n", dequeue()); // 2
	printf("%d\n", dequeue()); // 3
	printf("%d\n", dequeue()); // -1111
	printf("%d\n", dequeue()); // -1111
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	for (int i = 0; i < 5; i++)
	{
		dequeue_();
	}
}