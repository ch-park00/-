#include <stdio.h>
#include <stdlib.h>
struct node
{
	int i;
	struct node *next;
	struct node *prev;
};
struct node *head = 0;


struct node * createDLLNode(int _i)  //DLL��� ����
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->i = _i;
	new_node->next=new_node->prev=0;  //�̷��� prev�� 0�� ���� �׿� ���� next�� 0�� ����.
	//new_node->next = 0;
	//new_node->prev = 0;
	return new_node;
}
struct node * findlastNode() //DLL������ ��� �ּ� ��ȯ, DLL�� ���� ��Ȳ������ 0�� ��ȯ
{
	/*
	struct node *p = head;
	while (1)
	{
		if (head == 0)
		{
			return 0;
		}
		if (p->next == 0)
		{
			return p;
		}
		p = p->next;
	}
	*/
	if (head == 0)
	{
		return 0;
	}
	{
		struct node *cur = head; //�� ������ �� ��� �ȿ����� ��� �ִ�.
		//c������ ���� ���ۿ��� ������ �������� �ʴ´ٸ� ����. ��� ������ �� �����ϴ°��� ������.
		//{} �̰ž����� ������ ����(���� ����)
		while (1)
		{
			if (cur->next == 0)
			{
				return cur;
			}
			cur = cur->next;
		}
	}
}
void addToDLL(int i) //��� ������ DLL�ǵڿ� �̾����
{
	struct node * new_node = createDLLNode(i);
	struct node *lastnode = 0;
	if (head == 0) //���ܻ�Ȳ
	{
		head = new_node;
		return;
	}
	lastnode = findlastNode();
	new_node->prev = lastnode;
	lastnode->next = new_node;

}
struct node * Findnode(int i) //i���� �ִ� ��� ã��.���ٸ� 0 ��ȯ
{
	if (head == 0)
	{
		return 0;
	}     //�Ʒ����� �ɷ����Ƿ� �Ƚᵵ �����ϴ�.
	{
		struct node *cur = head;
		while (1)
		{
			if (cur == 0) //i�� ��� �ִ� ��尡 ���� ���
			{
				return 0;
			}
			if (cur->i == i)
			{
				return cur;
			}
			cur = cur->next;
		}
	}
}
void insertAfterDLL(int _where, int _what)
{
	struct node *cur = Findnode(_where);
	struct node *newnode = createDLLNode(_what);
	if (cur == 0)
	{
		return;
	}
	if (cur->next == 0) //�� ������ ��� �ڿ� �߰�
	{
		newnode->prev = cur; 
		cur->next = newnode;
	}
	else
	{
		newnode->prev = cur;
		newnode->next = cur->next; //���� �����ϴ� ��� ����
		cur->next->prev = newnode; 
		cur->next = newnode; //���� ��带 ���ο� ���� ����
	}
}
void insertBeforeDLL(int _where, int _what) //where�տ� ��� ����.
{
	struct node *cur = Findnode(_where);
	struct node *newnode = createDLLNode(_what);
	if (cur == 0)
	{
		return;
	}
	if (cur == head)
	{
		newnode->next = cur;
		cur->prev = newnode;
		head = newnode;
	}
	else
	{
		newnode->next = cur;
		newnode->prev = cur->prev;
		cur->prev = newnode;
		newnode->prev->next = newnode;
	}
}
void deleteFromDLL(int _what)
{
	struct node *cur = Findnode(_what);
	if (cur == 0)
	{
		return;
	}
	if (cur == head)
	{
		// DLL�� head �ϳ��� �ִ� ���
		if (head->next == 0) //��尡 head �Ѱ��� ����
		{
			head = 0;
			free(cur);
			return;
		}
		else //head �ڿ� ���� ���� ��尡 �ִ�.
		{
			head = head->next;
			head->prev = 0;
			free(cur);
			return;
		}
	}
	else if (cur->next == 0)//�ǵڿ� ��带 ����
	{
		cur->prev->next = 0;
		free(cur);
		return;
	}
	else //�����Ϸ��� ��� �յڷ� �����ϴ� ���
	{
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		free(cur);
		return;
	}
}

void showDLL() //DLL���.�� �տ������� �� ���� ������ ����Ѵ�.
{
	struct node *cur = head;
	while (1)
	{
		if (cur == 0)
		{
			return;
		}
		printf("%d\n", cur->i);
		cur = cur->next;
	}
}
void showReverseDLL() //DLL�� �Ųٷ� ����ϴ� �ڵ�.
{
	struct node *cur = findlastNode();
	/*if (cur == 0) //���ܰ�� : DLL�� ����ִ� ���
	{
		return;
	}*/ //while�����ȿ� �� ������ �����Ƿ� ���� �ʿ����.
	while (1)
	{
		if (cur == 0)
		{
			return;
		}
		printf("%d\n", cur->i);
		cur = cur->prev;
	}
}
void destroyDLL()
{
	struct node *p = head;
	while (1)
	{
		if (head == 0)
		{
			printf("�ı�\n");
			break;
		}
		head = head->next;
		free(p);
		p = head;
	}
}
void main()
{
	addToDLL(3);
	addToDLL(4);
	addToDLL(5);
	
	showDLL();
	showReverseDLL();
	insertAfterDLL(3, 1);
	insertBeforeDLL(4, 2);
	showDLL();
	deleteFromDLL(3);
	showDLL();
	destroyDLL(); //SLL�� ����
}