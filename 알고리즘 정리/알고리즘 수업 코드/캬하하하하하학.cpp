#include <stdio.h>
#include <stdlib.h>
#define STACK_SZ 10
struct node * STACK[STACK_SZ];
int top = -1;
int count[2] = { 0 };
struct node
{
	int data;

	struct node *left;
	struct node *right;
};
struct node *root = 0;
void push(struct node *n)
{
	if (top == STACK_SZ - 1)
	{
		printf("stack full\n");
		return;
	}
	top++;
	STACK[top] = n;
	return;
}
struct node *pop()
{
	if (top == -1)
	{
		printf("stack empty\n");
		return 0;
	}
	top--;
	return STACK[top + 1];
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
void showinorder(struct node *p) //recursive�� § inorder traversal
{
	if (p == 0)
	{
		return;
	}
	showinorder(p->left);
	printf("%d\n", p->data);
	showinorder(p->right);
}
/* ���� ��尡 ������ �� ��带 ���ÿ� �����ϰ� �������� �̵�
   ���� ��尡 ������ �� ��� ��� �� ���������� �̵�(������ ��尡 ������ ����)
   �� �� ������ ��尡 ������ stack���� pop�� pop�� ����� ������ ����� 95���� �湮 
*/
void inoreder_nonrecursive(struct node *n) //n�� ���� ����ּ�. nonrecursive�� ����(�����÷ο�)�ϰ� ����.
{
	while (n != 0 && top == -1)
	{
		if (n->left != 0)
		{
			count[1] = count[0];
			push(n);
			n = n->left;
		}
		else
		{
			printf("%d\n", n->data);
			if (n->right != 0)
			{

			}
		}
	}
	top = -1;
}
struct node * findnode(int i)
{
	struct node *temp = root;
	while (1)
	{
		if (temp == 0)
		{
			return 0;
		}
		if (temp->data == i)
		{
			if (temp == root)
			{
				push(root);
			}
			return temp;
		}
		else if (temp->data > i)
		{
			push(temp);
			temp = temp->left;
		}
		else
		{
			push(temp);
			temp = temp->right;
		}
	}
}
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
void remove_nonrecursive(int i)
{
	struct node *me = findnode(i);
	struct node *parent = pop();
	if (me == 0)
	{
		return;
	}
	if (me == root)
	{
		if (root->left == 0 && root->right == 0)
		{
			free(root);
			root = 0;
		}
		else if (root->left != 0 && root->right == 0)
		{
			struct node *temp = root->left;
			free(root);
			root = temp;
		}
		else if (root->left == 0 && root->right != 0)
		{
			struct node *temp = root->right;
			free(root);
			root = temp;
		}
		else
		{
			struct node *successor = Findleast(me);
			me->data = successor->data;
			free(successor);
		}
	}
	else
	{
		if (me->left == 0 && me->right == 0)
		{
			if (parent->left == me)
			{
				parent->left = 0;
				free(me);
			}
			else
			{
				parent->right = 0;
				free(me);
			}
		}
		else if ((me->left != 0 && me->right == 0))
		{
			if (parent->left == me)
			{
				parent->left = me->left;
			}
			else
			{
				parent->right = me->left;
			}
		}
		else if (me->left == 0 && me->right != 0)
		{
			if (parent->left == me)
			{
				parent->left = me->right;
			}
			else
			{
				parent->right = me->right;
			}
		}
		else
		{
			struct node *successor = Findleast(me);
			me->data = successor->data;
			free(successor);
		}
	}
	top = -1;
}
void main()
{
	addToBST(50);
	addToBST(45);
	addToBST(35);
	addToBST(65);
	addToBST(40);
	remove_nonrecursive(50);
	showinorder(root);
}