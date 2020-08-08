#include <stdio.h>

#define STACK_Sz 10
int stack[STACK_Sz];
int top = -1;
char stk[STACK_Sz];
int tp = -1;
int isEmpty()
{
	return (top == -1);
}
int isEmptystk()
{
	return (tp == -1);
}
int isFull()
{
	return (top == STACK_Sz - 1);
}
int isFullstk()
{
	return (top == STACK_Sz - 1);
}
void push(int i)
{
	if (isFull() == 1)
	{
		return;
	}
	top++;
	stack[top] = i;
	return;
}
void pushstk(char a)
{
	if (isFullstk() == 1)
	{
		return;
	}
	tp++;
	stk[tp] = a;
}
char popstk()
{
	if (isEmptystk() == 1)
	{
		return 0;
	}
	else
	{
		char res = stk[tp];
		tp--;
		return res;
	}
}
int pop()
{
	if (isEmpty() == -1)
	{
		return -999;
	}
	else
	{
		int res = stack[top];
		top--;
		return res;
	}
}
void calcPostfixOperand(int i)
{
	push(i);
}
void calcPostfixOperator(char op)
{
	int a, b, c;
	a = pop();
	b = pop();
	if (a == -999 || b == -999)
	{
		printf("Unexpected error\n");
		return;
	}
	switch (op) 
	{
	case '+':
		c = a + b;  //or push(a+b);
		break;
	case '-':
		c = b - a; //�����߿�. ������������ �ڷο;��Ѵ�.
		break;
	case '*':
		c = a*b;
		break;
	case '/':
		c = b / a;
		break;
	default:
		printf("Can't handle the operator\n");
		return;
	}
	push(c);


#if 0
	if (op == '+')
	{
		c = a + b;
	}
	else if (op == '*')
	{
		c = a*b;
	}
	else if (op == '-')
	{
		c = b - a;
	}
	else
	{
		c = b / a;
		
	}
	push(c);
#endif
}

void showresult()
{
	int res = 0;
	while (isEmptystk()!=1) //stk�� �����ִ� ���� ��� ��� �� ���
	{
		calcPostfixOperator(popstk());
	}
	res = pop();
	if (res == -999) //stack�� ���������
	{
		printf("Unexpected error\n");
		return;
	}
	printf("���:%d\n", res);
}
void tfpostfixoperand(int i)
{
	calcPostfixOperand(i);
}
void tfpostfixoperator(char op)
{
	//ó���� �˸´� op�� ���Դ��� �˻��ϴ� �ڵ� �ʿ�
	if (isEmptystk() == 1) //������ ��������� push
	{
		pushstk(op);
	}
	else
	{
		char temp = stk[tp];
		//op�� �켱������ stack���� ���� ���
		if ((op == '*' || op == '/') && (stk[tp] == '+' || stk[tp] == '-'))
		{
			pushstk(op);
		}
		//�켱������ ���� ���
		else
		{
			char temp = popstk(); //���ÿ� �ִ� �� ����� 
			calcPostfixOperator(temp); //����ϰ�
			pushstk(op); //�Է¹��� ������ push
		}
	}

}
//stack�� �̿��� ������(postfix) ����ϱ�
void main()
{
	//345+* ���
	/*
	calcPostfixOperand(3);
	calcPostfixOperand(4);
	calcPostfixOperand(5);
	calcPostfixOperator('+');
	calcPostfixOperator('*');

	showresult();
	*/
	//3+4*5-->345*+ �������� ���������� �ٲٰ� ����ϱ�
	tfpostfixoperand(3); //3����� stack����
	tfpostfixoperator('+');
	tfpostfixoperand(4);
	tfpostfixoperator('*');
	tfpostfixoperand(5); //(3+4)*5��ȯ�İ��
	showresult();
	
}