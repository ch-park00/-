#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};
struct node *head = 0;
void addToSLL(int _data) // _���ΰ� ���ú������ ��
{
	struct node *p = (struct node *)malloc(sizeof(node));
	p->data = _data;
	p->next = 0;

	if (head == 0)
	{
		head = p;
	}
	else
	{
		struct node *temp = head; //�ӽ� ����
		while (1)
		{
			if (temp->next == 0) // �� ������ ����� ��
			{
				break; // while���� Ż��
			}
			temp = temp->next; // �� ������ ��尡 �ƴ� ���� ���� ���� �̵�
		}
		temp->next = p;
	}
}

struct node * Findnode(int n) //n�� �� ��� ã�� �Լ�
{
	struct node *cur = head;
	while (1)
	{
		if (cur == 0)
		{
			break; //�ؿ��� return 0���� ���⼭ �ص� ����.
		}
		if (cur->data == n)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	return 0;
}
void insertSLL(int where, int what) //�߰��� SLL�����ϴ� �Լ�
{
	struct node *cur = Findnode(where); //��� �߰��Ұ��� ��ġ �ľ�
	if (cur == 0) //�߰��Ϸ��� SLL�� ��ġ�� �������� �ʴ´� 
	{
		return; //�Լ� ����. break�� ��� �Ұ�
	}
	struct node *neW = (struct node *)malloc(sizeof(struct node)); //���� �Է��� ��� ����
	neW->data = what; //���� ������ ��忡 �Է°� �Է�
	neW->next = 0; //

	neW->next = cur->next;
	cur->next = neW;
}
struct node * findByindex(int n) //n��° SLL�� ��� �ּҸ� ��ȯ���ִ� �Լ�
{
	struct node *cur = head;
	int cnt = n;
	while (1)
	{
		if (cur == 0 || cnt == 0)
		{
			return cur;
		}
		cur = cur->next;
		cnt--;
	}
}
struct node * findnodePointingme(struct node *me) //�����ϴ� ����� �� ��� ã�� �Լ�
{
	struct node *cur = head;
	while (1)
	{
		if (cur->next == me) //���� ��尡 ���� ���� ����� ��.
		{
			return cur; //����� �� �ּ� ��ȯ
		}
		cur = cur->next;
	}
}
void delFromSLL(int n) //SLL���� Ư�� ��� �����ϴ� �Լ�
{
	struct node *del = Findnode(n);
	if (del == 0) //������� �ְ� �������� ����.
	{
		return;
	}
	if (del == head)
	{
		head = head->next; //��常 �̵�.��尡 �ϳ��Ͻ� ���� ��尪�� 0�̹Ƿ� ��������.head�� 0�� ���� ����.
		free(del);
		return;
	}
	else
	{
		struct node *del_before = findnodePointingme(del);
		del_before->next = del->next;
		free(del);
	}
}

void destroySLL() //SLL�����ϴ� �Լ�
{
	struct node *cur = head;
	while (1)
	{
		if (head == 0)
		{
			break;
		}
		head = head->next; //��� �̵�
		free(cur); //�� ó�� ��������
		cur = head; //cur�� head �Է�.
	}
	if (head == 0)
	{
		printf("SLL �ı��Ϸ�\n");
	}
}
void displaySLL()
{
	struct node *cur = head;
	while (1)
	{
		if (cur == 0)
		{
			break;
		}
		printf("%d\n", cur->data);
		cur = cur->next;
	}

}
void main()
{
	addToSLL(5); //��� �Ǿտ� 5 �Է�
	addToSLL(4); //�״��� ��� 4 �Է�
	addToSLL(3); //3 �Է�
	addToSLL(2); //2 �Է�
	addToSLL(1); //1 �Է�

	displaySLL(); // ��忡 �Է��� �� ��� ���

	insertSLL(3, 10); //3�����͸� ã�Ƽ� �׵ڿ� 10�����͸� �̾����
	displaySLL();
	struct node *q = findByindex(2);
	if (q == 0) //(q>0)�� ����
	{
		printf("����\n");
	}
	else
	{
		printf("%d\n", q->data);
	}
	delFromSLL(1);
	displaySLL();
	destroySLL();
}