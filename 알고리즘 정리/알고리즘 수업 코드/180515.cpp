#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
};
struct node *root = 0;
struct node *removenode(struct node* p,int i);
struct node * Findleast(struct node *n) //node n���� ������ ���� ���� ��� ã�� �� �ּ� ��ȯ�ϴ� �Լ�
{
	struct node *p = n;
	while (1)
	{
		if (p->left != 0)
		{
			p = p->left;
		}
		else
		{
			return p;
		}
	}
}
struct node * foundMatch(struct node *n) //������ ��� n ����
{
	if (n->left == 0 && n->right == 0) //child�� �������� �ʴ´�
	{
		free(n);
		return 0; //child�� �����ϱ� 0��ȯ
	}
	else if (n->left != 0 && n->right != 0)//child 2�� ����
	{
		struct node *successor = Findleast(n->right); //�İ��� ã��.�����ʿ��� ���� ������ ã��
		n->data = successor->data; //�İ����� �����ͷ� n�� �����.
		n->right = removenode(n->right, successor->data); //�����ʿ��� �Ͼ �̵��� ó��
		return n;
	}
	else if (n->left != 0) //�������� ���������
	{
		struct node *temp = n->left;
		free(n);
		return temp; //child �ּҸ� ��ȯ��
	}
	else //������ ������� ��
	{
		struct node *temp = n->right;
		free(n);
		return temp;
	}
}
struct node * removenode(struct node *n, int i)
{
	if (n == 0) //ã�� �����͸� ���� ��尡 �������� �ʴ´�
	{
		return 0;
	}

	if (n->data == i) // ���� ��带 ã����
	{
		return foundMatch(n); 
	}
	else if (n->data > i) //�� ��尪�� ���� �����ͺ��� ũ�� �������� ����������
	{
		n->left=removenode(n->left, i); //���� ��尡 ���� child�� ����.�׸��� �����ϴ� ����
		return n;
	}
	else
	{
		n->right=removenode(n->right, i);
		return n;
	}
}


struct node * CreateNode(int i)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	p->data = i;
	p->left = 0;
	p->right = 0;
	return p;
}
void addToBST(int i)
{
	struct node *p = CreateNode(i);
	if (root == 0)
	{
		root = p;
		return;
	}
	else
	{
		struct node *q = root;
		while (1)
		{
			if (p->data > q->data)
			{
				if (q->right == 0)
				{
					q->right = p;
					return;
				}
				else
				{
					q = q->right;
				}
			}
			else
			{
				if (q->left == 0)
				{
					q->left = p;
					return;
				}
				else
				{
					q = q->left;
				}
			}
		}
	}
}

void main()
{
	addToBST(50);
	addToBST(25);
	addToBST(75);
	addToBST(10);
	addToBST(35);
	addToBST(30);

	printf("%d\n", root->left->right->data);

	root = removenode(root, 35);
	printf("%d\n", root->left->right->data);
}