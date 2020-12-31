#include <stdio.h>
// n���� ���ø� from���� to���� �̵�. tmp�� �ӽ÷� Ȱ���Ѵ�.
void hanoi(int n, int from, int tmp, int to)
{
	if (n == 1)
	{
		printf("%d=>%d\n", from, to);
	}
	else
	{
		//�� ������ ������ ��� ���� ������ �̵�.
		hanoi(n - 1, from, to, tmp);
		//�� ������ ���� �������� �̵���Ų��.
		hanoi(1, from, tmp, to);
		//������ �ű� ���� �ٽ� �� ���´�� �̵���Ų��.
		hanoi(n - 1, tmp, from, to);
	}
}
int main()
{
	hanoi(10,1,2,3);
	return 0;
}