#include <stdio.h>
#include <stdlib.h>
#define STACK_SZ 10
struct node * STACK[STACK_SZ];
int top = -1;
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
struct node * handle()
{
	if (top==-1) 
	{
		return 0;
	}
	else
	{
		struct node *n = pop();
		while (1)
		{
			printf("%d\n", n->data);
			if (n->right != 0)
			{
				return n->right;
			}
			else
			{
				if (top == -1) //node�� root�� root->left�� �����ϴ� ��� ó��
				{
					return 0;
				}
				n = pop();
			}
		}
	}
}
/* ���� ��尡 ������ �� ��带 ���ÿ� �����ϰ� �������� �̵�
���� ��尡 ������ �� ��� ��� �� ���������� �̵�(������ ��尡 ������ ����)
�� �� ������ ��尡 ������ stack���� pop�� pop�� ����� ������ ����� �� ó������ �̵�
*/
void inorder_nonrecursive(struct node *n) //n�� ���� ����ּ�. nonrecursive�� �����ϰ� ����.
{
	while (1)
	{
		if (n == 0)
		{
			top = -1;
			break;
		}
		if (n->left != 0)
		{
			push(n);
			n = n->left;
		}
		else
		{
			printf("%d\n", n->data);
			if (n->right != 0)
			{
				n = n->right;
			}
			else
			{
				n=handle();
			}
		}
	}
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
		if (p == n && p->left == 0) //ã�� ���̶� �Է��� ���̶� ������ push�� �ȵǼ� ���� ó���ؾ��Ѵ�.
		{
			push(p);
			return p;
		}
		if (p->left != 0)
		{
			push(p);
			p = p->left;
		}
		else
		{
			return p;
		}
	}
}
void remove_twochildnode(struct node *n) //child��尡 2�϶� 
{
	struct node *successor = Findleast(n->right);
	struct node *parent = pop();
	n->data = successor->data;
	if (successor == parent)
	{
		n->right = successor->right;
		free(successor);
		top = -1;
		return;
	}
	if (successor == parent->left) //succesor�� 0�ڳ� or 1�ڳ�(������)
	{
		if (successor->left == 0 && successor->right == 0)
		{
			parent->left = 0;
			free(successor);
		}
		else if (successor->left != 0 && successor->right == 0)
		{
			parent->left = successor->left;
			free(successor);
		}
		else
		{
			parent->left = successor->right;
			free(successor);
		}
	}
	else
	{
		if (successor->left == 0 && successor->right == 0)
		{
			parent->right = 0;
			free(successor);
		}
		else if (successor->left != 0 && successor->right == 0)
		{
			parent->right = successor->left;
			free(successor);
		}
		else
		{
			parent->right = successor->right;
			free(successor);
		}
	}
}
void remove_nonrecursive(int i)
{
	struct node *me = findnode(i);
	struct node *parent = pop();
	top = -1; // findnode�ϸ鼭 stack�� �������Ƿ�
	if (me == 0)
	{
		top = -1;
		return;
	}
	if (me == root)
	{
		if (me->left == 0 && me->right == 0)
		{
			root = 0;
			free(me);
		}
		else if (me->left != 0 && me->right == 0)
		{
			root = root->left;
			free(me);
		}
		else if (me->left == 0 && me->right != 0)
		{
			root = root->right;
			free(me);
		}
		else
		{
			remove_twochildnode(me);
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
				free(me);
			}
			else
			{
				parent->right = me->left;
				free(me);
			}
		}
		else if (me->left == 0 && me->right != 0)
		{
			if (parent->left == me)
			{
				parent->left = me->right;
				free(me);
			}
			else
			{
				parent->right = me->right;
				free(me);
			}
		}
		else
		{
			remove_twochildnode(me);
		}
	}
	top = -1;
}
void main()
{
	addToBST(50);
	addToBST(60);
	showinorder(root);
	remove_nonrecursive(50);
	printf("���� ��:");
	inorder_nonrecursive(root);
}