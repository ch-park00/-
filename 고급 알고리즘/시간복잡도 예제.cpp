#include <stdio.h>
#include <time.h>
//clock()�Լ� ���=>�ð� ����
int main()
{
	clock_t start_time, end_time;
	start_time = clock();
	double k = 0;
	// ���� �˰��� ����
	for (int i = 1; i < 100000; i++)
	{
		k = (k*k*k*k) / double(i);
	}
	end_time = clock();
	//�ش� ���α׷� �����ϴ� ���� �ɸ� Ŭ�� ���� ����.
	//���� �Ҹ� �ð��� �˰� �ʹٸ� Ŭ�� ���ǵ�� ������ ���� �ҿ� �ð�(��)�� ���´�.
	printf("%d\n", end_time - start_time);
}