#include <stdio.h>

struct TEST //�� ����ü�� �̸��� struct TEST
{
	int a;
	char b;
};
/*struct D
{
	int a;
	int b;
	struct D a; //������ ���� �ʾƼ� ����� �Ұ�����
};*/
struct D1 //�ڽ���������ü
{
	int a;
	int b;
	struct D1 *A; // 3��° �濡 4����Ʈ�� ��Ƽ� �ּҸ� ���� ���� ����
};
 struct BD
{
	int a;
	char b;
	struct TEST A; // ����ü �ȿ� ����ü�� �� �� �ִ�.
};

 struct VBD
 {
	 int a;
	 char b;
	 struct BD A1;
 };


#if 0


void main()
{
	typedef struct TEST TEST;
	struct TEST aa; //����ü ����
	char i[10];int k;
	for (k = 0; k < 10; k++)
	{
		printf("%d\n", &i[k]);
	}
}



//2��° ����ü �������
typedef struct
{
	int a;
	char b;
}TEST;


void main()
{
	struct TEST aa, bb;
	aa.a = 1;
	aa.b = 'a';
	bb = aa; //�׳��� ���� �����
/*	if (aa == bb) //���� => ����ü���� ���� ���� �� ���г��� ���ؾ� �Ѵ�.
	{
		printf("%d %c\n", bb.a, bb.b);
	}*/
	if (aa.a == bb.a && aa.b == bb.b)
	{
		printf("1234\n");
	}
}


struct BD aaa;
struct VBD x;
void main()
{
	aaa.a = 10;
	aaa.b = 'a';
	aaa.A.a = 20;
	aaa.A.b = 'b';
	x.a = 10;
	x.b = 'c';
	x.A1.a = 10;
	x.A1.b = 'd';
	x.A1.A.a = 30;
	x.A1.A.b = 'e';
}
#endif
void main()
{
	int i = 10;
	int *j;
	int **jj;
	j = &i;
	*j = 20; //j�� ����Ǿ� �ִ� �ּҰ��� ���� 20�� �����Ѵ�.
	jj = &j;
	**jj = 30;

	printf("%d\n", i);
}