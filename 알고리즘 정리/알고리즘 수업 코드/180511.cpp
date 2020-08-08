#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;

	struct node * leftPtr;  //���� ����Ű�� ������
	struct node * right; //������ ����Ű�� ������
};
typedef struct node TreeNode;
TreeNode * root = 0; //root�� 0�̸� bst�� ���� ��
TreeNode * createNode(int i)
{
	TreeNode * new_one = (TreeNode*)malloc(sizeof(TreeNode));
	new_one->leftPtr = 0;
	new_one->right = 0;
	new_one->data = i;
	return new_one;
}
void addtoBST(int i)
{
	TreeNode *cur = createNode(i);
	TreeNode *p = root;
	if (root == 0)
	{
		root = cur;
		return;
	}
	while (1)
	{
		if (p->data > cur->data) //�������� ���������Ѵ�.
		{
			if (p->leftPtr == 0)
			{
				p->leftPtr = cur;
				return;
			}
			else
			{
				p = p->leftPtr;
			}
		}
		else
		{
			if (p->right == 0)
			{
				p->right = cur;
				return;
			}
			else
			{
				p = p->right;
			}
		}
	}
}
void main()
{
	addtoBST(50); //�ƹ��͵� �����ϱ� root�� ����
	addtoBST(25); //�� �� �����ϱ� �ؿ� �����ϴµ� �����ϱ� ���� ����
	addtoBST(75); //root���� ũ�ϱ� ������. ��������ϱ� �ű� ����
	addtoBST(10); //25���� �����ϱ� 25 �� ���� ����
	addtoBST(35); //25���� ũ�� 50���� �����ϱ� 25 �� ������ ����

	printf("%d\n", root->leftPtr->right->data);
}