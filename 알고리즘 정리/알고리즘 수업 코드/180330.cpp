#include <stdio.h>
#include <stdlib.h>

struct node // 
{
	int data;
	struct node *next; //�ڱ���������ü, ���� ����� �ּ� �Է¹���
};
struct node *head = 0;


#if 0
void main()
{
	int *a = (int *)malloc(4);
	*a = 10; //a�� ����Ű�� �ִ� ������ 10 ����
	printf("%d\n", *a);
	free(a);
}

void main()
{
	int *a = (int *)malloc(sizeof(int) * 5);
	for (int k = 0; k <= 4; k++)
	{
		a[k] = k;
		printf("%d\n", a[k]);
	}
	free(a);
}

typedef struct
{
	int a;
	char b;
}A;
void main()
{
	A *aa = (A *)malloc(sizeof(A));
	aa->a = 10; aa->b = 'a';
	printf("%d\n%c\n", aa->a, aa->b);
	free(aa);
}

typedef struct
{
	int a;
	char b;
}A;
void main()
{
	A *aa = (A *)malloc(sizeof(A) * 10);
	for (int i = 0; i <= 9; i++)
	{
		aa[i].a = 10; //(aa+i)->a=10; (*(aa+i)).a=10; �� �� ���� ���
		aa[i].b = 'a';
		printf("%d %c\n", aa[i].a, aa[i].b);
	}
	free(aa);
} //malloc�� free


void main()
{
	struct node *p, *q, *t, *head;
	int i;
	p = (struct node *)malloc(sizeof(struct node));
	p->data = 1;
	p->next = 0;
	head = p;
	//p->next=(struct node *)malloc(sizeof(struct node)); �̰Ŵ� �ؿ� ����� ���� ����
	q = (struct node *)malloc(sizeof(struct node)); //���⼭ p�� ���� �տ� ������ unreferenced space�� �ȴ�
	q->data = 2;
	q->next = 0;
	p->next = q; // ��ũ ����

	t = head;
	for (i = 0; i < 2; i++)
	{
		printf("%d\n", t->data);
		t = t->next; //t�� q ����.
	}
}
#endif

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

struct node * Findnode(int n)
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
void insertSLL(int where, int what)
{
	struct node *cur = Findnode(where); //��� �߰��Ұ��� ��ġ �ľ�
	if (cur == 0)
	{
		return; //�Լ� ����. break�� ��� �Ұ�
	}
	struct node *neW = (struct node *)malloc(sizeof(struct node)); //���� �Է��� ��� ����
	neW->data = what; //���� ������ ��忡 �Է°� �Է�
	neW->next = 0; //

	neW->next = cur->next;
	cur->next = neW;
}
struct node * findByindex(int n)
{
	/*
	struct node *p = head;
	int a = 0;
	while (1)
	{
	if (a == n)
	{
	return p;
	}
	if (p->next == 0)
	{
	return 0;
	}
	else
	{
	p = p->next;
	a++;
	}
	}*/
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

struct node * findnodePointingme(struct node *me)
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
void delFromSLL(int n)
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

void destroySLL()
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

}
void displaySLL()
{
	/*
	struct node *temp = head;
	do
	{
	printf("%d\n", temp->data);
	temp = temp->next;
	} while (temp->next != 0);
	printf("%d\n", temp->data);
	*/
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
	if (head == 0)
	{
		printf("SLL �ı��Ϸ�\n");
	}
}
