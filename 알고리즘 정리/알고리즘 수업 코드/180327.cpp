#include <stdio.h>
#include <stdlib.h> //malloc�Լ� ���� �ʿ�

#if 0
void main()
{
	int *a = (int *)malloc(12); //malloc���� �ִ� �ּҸ� int ������������ ����
	printf("%x\n", a);  //16������ 10������ ��ȯ�ϴ� �������� ������ ��°���
	*a = 10;
	*(a + 1) = 20; //a ���� �ּҴ� int���̹Ƿ� 4Ŀ�� a+4�̴�
	*(a + 2) = 30;
	printf("%d %d %d\n", a[0],a[1],a[2]);
}
#endif

#if 0
void main()
{
	int *a = (int *)malloc(12); //malloc���� �ִ� �ּҸ� int������ ����
	int *b;
	b = a;
	printf("%d %d\n", a,b);  //16������ 10������ ��ȯ�ϴ� �������� ������ ��°���
	*b = 10;
	*(b + 1) = 20; //a ���� �ּҴ� int���̹Ƿ� 4Ŀ�� a+4�̴�
	*(b + 2) = 30;
	printf("%d %d %d\n", b[0], b[1], b[2]);
}
#endif
#if 0
void main()
{
	int *a = (int *)malloc(1024);
	int *b;
	b = a;
	free(b);
	*a = 2; //�����۵��Ѵ�. ������ Ư�� ������ ���� �׳� ����� �Ŷ� ����� ����
}
#endif
typedef struct
{
	int a;
	int b;
}A;
A a[10]; //80����Ʈ �Ҵ�
void main() //���� �Ҵ�
{
	A *pa = (A*)malloc(10 * sizeof(A)); //80����Ʈ �Ҵ�
	pa->a = 3; //����ü int a�� 3 ����
	pa->b = 5; 
	free(pa);
	A *pa1 = (A*)malloc(10 * sizeof(A)); 
	(pa1+9)->a = 3; //
	(pa1 + 9)->b = 5; //pa1 ������ �ּҰ��� ����
	/*pa1[9].a = 3;
	pa1[9].b = 5; 
	(pa1 + 9)->a = 3;
	(pa1 + 9)->b = 5;*/
	printf("%d %d\n", pa1[9].a, pa1[9].b);
}