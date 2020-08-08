//Huffman tree encoding
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
struct node
{
	char c;
	char *code;
	struct node *next;
};
struct hnode
{
	char c;
	struct hnode *left;
	struct hnode *right;
};
struct hnode *root;
struct node *head;
void addHuffcode(char a, const char *code)
{
	struct node *new1 = (struct node *)malloc(sizeof(struct node));
	new1->c = a;
	new1->next = 0;
	new1->code = (char *)malloc(strlen(code) + 1);
	strcpy(new1->code, code);

	if (head == 0)
	{
		head = new1;
	}
	else
	{
		struct node *temp = head;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new1;
	}
}
int getNumofcode()
{
	int cnt = 0;
	struct node *temp = head;
	while (temp != 0)
	{
		temp = temp->next;
		cnt++;
	}
	return cnt;
}
//���� �ڵ�.������ a,b,c,d�� �ǹ��Ѵ�.
char *codetable[4] = { (char*)"100",(char*)"11",(char*)"101",(char*)"0" };
//file ����
int main()
{
	
	FILE *f = fopen("alice.bit", "rb");
	int numofbits = 0;
	fread(&numofbits, sizeof(int), 1, f);
	printf("�� ���� ��Ʈ:%d\n", numofbits);
	
	char andMask = 0x80;

	while (1)
	{
		char readbuf;
		int n=fread(&readbuf, sizeof(char), 1, f);
		// �� ���� ���
		if (n <= 0)
		{
			break;
		}
		while (1)
		{
			if (!(readbuf&andMask))
			{
				printf("0");
			}
			else
			{
				printf("1");
			}
			andMask = (andMask >> 1) & 0x7F; //�� ��� �� ���� ��Ʈ�� ��ȣ ��Ʈ�ε� ����Ʈ �� 0�� ���� 1�� ���� �˼� ����
			numofbits--;
			//readbuf = readbuf << 1; //�̰͵� ����  
			if (andMask == 0 || numofbits <= 0)
			{
				andMask = 0x80;
				break;
			}
		}
	}
	fclose(f);
	return 0;
}


int main99()
{
	char *str2write = (char *)"abbccdccbba";
	
	FILE *f = fopen("alice.bit", "wb");
	//���� ��ġ �̵�
	//�Լ��� �Է°��� ���Ϲ���,������ ��,������
	//seek_set=��ó�� ��ġ
	fseek(f, 4, SEEK_SET);
	//���Ͽ� �� 1��Ʈ ����
	char oneBytebuffer = 0;
	//7,6,5,4,3,2,1 �̷������� ����Ʈ�ϸ鼭 �����.0�Ǵ¼��� 1����Ʈ�� �� á���� �ǹ�
	int shiftcnt = 7;
	// ��Ʈ ���� ����
	int numofbits = 0;
	//bit ������ ���Ͽ� �Է�
	for (int i = 0; i < strlen(str2write); i++)
	{
		char c = str2write[i];
		char *code = codetable[c - 'a'];
		
		for (int j = 0; j < strlen(code); j++)
		{
			//or��ų ��Ʈ
			char bitvaule = 0x00;
			if (code[j] == '1')
			{
				bitvaule = 1;
				bitvaule = bitvaule << shiftcnt;
				oneBytebuffer = oneBytebuffer | bitvaule;
			}
			shiftcnt--;
			numofbits+=1;
			if (shiftcnt < 0)
			{
				fwrite(&oneBytebuffer, sizeof(char), 1, f);
				oneBytebuffer = 0;
				shiftcnt = 7;
			}
		}
	}
	if (shiftcnt < 7)
	{
		fwrite(&oneBytebuffer, sizeof(char), 1, f);
	}
	fseek(f, 0, SEEK_SET);
	fwrite(&numofbits, sizeof(int), 1, f);
	fclose(f);
	return 0;
}
int main3(void)
{
	FILE *f = fopen("alice.encoded", "rb");
	//1. ��� ���ĺ��� �ִ��� Ȯ��
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("%d\n", num);

	root = (struct hnode*)malloc(sizeof(struct hnode));
	root->left = root->right = 0;
	for (int i = 0; i < num; i++)
	{
		struct hnode *temp = root;
		char c;
		fread(&c, sizeof(char), 1, f);
		char len;
		fread(&len, sizeof(char), 1, f);
		printf("%c %d :", c, len);
		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, f);
			if (v == '0')
			{
				//�������� ��������
				if (temp->left == 0)
				{
					temp->left = (struct hnode*)malloc(sizeof(struct hnode));
					temp->left->left = temp->left->right = 0;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = (struct hnode*)malloc(sizeof(struct hnode));
					temp->right->left = temp->left->right = 0;
				}
				temp = temp->right;
			}
		}
		temp->c = c;
	}
	return 0;
}

int main2(void)
{
	FILE *f = fopen("alice.encoded", "rb");
	//huffman tree ����

	//1. ��� ���ĺ��� �ִ��� Ȯ��
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("%d\n", num);
	for (int i = 0; i < num; i++)
	{
		char c;
		fread(&c, sizeof(char), 1, f);
		char len;
		fread(&len, sizeof(char), 1, f);
		printf("%c %d :", c, len);
		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, f);
			printf("%c", v);
		}
		printf("\n");
	}
	return 0;
}
int main1(void)
{
	addHuffcode('a', "0");
	addHuffcode('b', "10");
	addHuffcode('c', "11");

	//file�ϳ� �����ؼ� ���̳ʸ� ���� ����. �б���� ����
	FILE *f = fopen("alice.encoded", "wb");//wb->���̳ʸ��б�
	// fwrite ���Ͽ� ����
	//1�ܰ�. �� ��� �ڵ尡 �ʿ����� Ȯ�� �� 1����Ʈ�� ���
	char numofchars = (char)getNumofcode();
	fwrite(&numofchars, sizeof(char), 1, f); //numofchars�� ������ ���Ͽ� �Է�
	//2�ܰ�. �� ���ڸ� '����'+'����'+'�ڵ�'�� ���
	//3�ܰ�. �� ������ �ݺ�
	struct node *temp = head;
	while (temp != 0)
	{
		char c = temp->c;
		char len = (char)strlen(temp->code);
		fwrite(&c, sizeof(char), 1, f);
		fwrite(&len, sizeof(char), 1, f);

		for (int i = 0; i < len; i++)
		{
			/*
			if code[i]==0
				fwrite(0)-->�̷������ε� ����
			*/
			fwrite(&(temp->code[i]), sizeof(char), 1, f);
		}
		temp = temp->next;
	}
	
	
	// fread ���Ͽ��� �б�
	fclose(f);
	return 0;
}