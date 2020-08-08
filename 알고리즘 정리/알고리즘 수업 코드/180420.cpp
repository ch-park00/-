#include <stdio.h>

#define STACK_SZ 10 //���û����� 10���� ����.
int stack[STACK_SZ];
int top = -1; //�������̸� ������ ����ٴ� �� �ǹ�.

/*������ ����������� 1��ȯ
 �ƴ϶�� 0��ȯ*/
int isEmpty() 
{
	return (top == -1); //top==-1�̸� 1��ȯ.�ƴϸ� 0 ��ȯ
						//���迬����.���̸� 1,�����̸� 0
}
/* ������ �� �� ������ 1��ȯ
   �ƴ϶�� 0 ��ȯ*/
int isFull()
{
	return (top == STACK_SZ - 1); //stack�� 10���̹Ƿ� ������ �ε����� 9�̴�.
								//9�϶��� 1��ȯ.
}

void push(int d) //stack�� �� �� ������ ������ ������ ����.
{
	if (isFull() == 1)
	{
		return;
	}
	top++;
	stack[top] = d;
	//stack[++top]=d �̰͵� ���������� ����
	return;
}
int pop()
{
	int temp;
	if (isEmpty() == 1) //stack�� ������� ��
	{
		return -666; //������ ����ִٴ� ���� �����ϴ� ����.stack�� ������ �ʴ� ���� ���� �ȴ�.
	}
	temp = stack[top];
	top--; //pop�ص� �����Ͱ� ���������� �ʴ´�.
	return temp;
}
void main()
{
	int i;
	push(1); //push�� �Է�
	push(2);
	push(3);
	push(4);
	push(5);

	for (i = 0; i < 5; i++) //pop���� ������ ���
	{
		printf("%d\n", pop());
	}
}

#if 0
void main()
{
addoperad(2);
addoperand(3);
addoperator('+');
showanswer();
#endif