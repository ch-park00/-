//��ȭ��ȣ, �̸��� �����ϴ� �ּҷ� ���� �� �˻��ϴ� ���α׷�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	char *name;
	char *num;
	struct node *left;
	struct node *right;
};
struct node *root = 0;

void add2bst(char *name, char *num)
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->left = new1->right = 0;
	new1->name = (char*)malloc(strlen(name) + 1);
	strcpy(new1->name, name);
	new1->num = (char*)malloc(strlen(num) + 1);
	strcpy(new1->num, num);

	if (root == 0)
	{
		root = new1;
		return;
	}
	else
	{
		struct node *tmp = root;
		while (tmp != 0)
		{
			int tmp1 = strcmp(tmp->name, name);
			if (tmp1 > 0)
			{
				if (tmp->left == 0)
				{
					tmp->left = new1;
					return;
				}
				tmp = tmp->left;
			}
			else if (tmp1 < 0)
			{
				if (tmp->right == 0)
				{
					tmp->right = new1;
					return;
				}
				tmp = tmp->right;
			}
			else
			{
				/*
				int tmp2 = strcmp(tmp->num, num);
				if (tmp2 > 0)
				{
					if (tmp->left == 0)
					{
						tmp->left = new1;
						return;
					}
					tmp = tmp->left;
				}
				else
				{
					if (tmp->right == 0)
					{
						tmp->right = new1;
						return;
					}
					tmp = tmp->right;
				}
				*/
				printf("same");
				return;
			}

		}
	}
}
int main()
{
	add2bst("��ö��", "1234");
	add2bst("�¿��", "1111");
	add2bst("�̸���", "5556");
	return 0;
}