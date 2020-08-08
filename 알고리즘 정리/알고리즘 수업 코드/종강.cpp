#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Sz 100

struct value //value�� �����ϴ� ����ü
{
	int age;
	char *hometown;
	char *hobby;
};
struct hash //hash table
{
	char *key;
	struct value val;
	struct hash *left;
	struct hash *right;
};
struct hash *hashtable[Sz]; 


//�� ������ �ƽ�Ű�ڵ尪�� ���ϰ� 100���� ���� �������� �ε�����ġ ����
int myhashfucntion(char *key)
{
	int sum = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		sum = sum + key[i];
	}
	return (sum%Sz);
}

//hashtable���� ã�� key���� �ִ��� Ȯ��
struct hash * searchhashtable(char *key)
{
	int loc = myhashfucntion(key);
	struct hash * cur = hashtable[loc];

	while (1)
	{
		if (cur == 0)
		{
			return 0;
		}
		else
		{
			if (strcmp(cur->key, key) > 0)
			{
				cur = cur->left;
			}
			else if (strcmp(cur->key,key)<0)
			{
				cur = cur->right;
			}
			else
			{
				return cur;
			}
		}
	}
}
void add2hash(char *name, int age, char *city, char *hobby)
{
	int location = -1;
	if (searchhashtable(name) != 0) //Ű���� ���� �����Ͱ� ���� ���
	{
		return;
	}
	struct hash *cur = (struct hash *)malloc(sizeof(struct hash));
	cur->left = 0;
	cur->right = 0;
	cur->val.age = age;
	cur->val.hometown = (char *)malloc(strlen(city) + 1); //�ڿ��� null���ڰ� �־�� �Ѵ�
	strcpy(cur->val.hometown, city);
	cur->val.hobby = (char *)malloc(strlen(hobby) + 1);
	strcpy(cur->val.hobby, hobby);
	cur->key = (char *)malloc(strlen(name) + 1);
	strcpy(cur->key, name);
	location = myhashfucntion(name);
	if (hashtable[location] == 0) //collision ����
	{
		hashtable[location] = cur;
		return;
	}
	else
	{
		struct hash *temp = hashtable[location];
		while (1)
		{
			if (strcmp(temp->key, cur->key) > 0)
			{
				if (temp->left == 0)
				{
					temp->left = cur;
					return;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = cur;
					return;
				}
				temp = temp->right;
			}
		}
	}
}

void main()
{
	struct hash *result = 0;
	add2hash("kim", 19, "seoul", "travel");
	add2hash("james", 20, "newyork", "cooking");
	add2hash("jane", 21, "incheon", "book");
	add2hash("tom", 22, "jeju", "hiking");
	add2hash("lee", 18, "busan", "fising");
	add2hash("����", 18, "busan", "fising");
	result = searchhashtable("");
	if (result == 0)
	{
		printf("no key\n");
	}
	else
	{
		printf("%s: %s %d %s\n", result->key, result->val.hometown,
			result->val.age, result->val.hobby);
	}
}