#include <iostream>
using namespace std;
//�� ������ ���� 0
int number[9] = { 0,0,0,0,5,0,0,0,0 };
//��귮 �񱳸� ���� ����.
int cnt;

int makeNumber(int idx)
{
	int sum = 0;
	for (int i = 0; i < idx; i++)
	{
		sum = sum * 10 + number[i];
	}
	return sum;
}
void showNumber()
{
	for (int i = 0; i < 9;i++)
	{
		std::cout << number[i];
	}
	std::cout << 0 << std::endl;
}
void checkNumber(int idx)
{
	cnt++;
	//�տ� �ߺ��Ǵ� ���ڰ� �ִ��� Ȯ��
	//������ ����
	for(int i = 0; i < idx; i++)
	{
		if (number[i] == number[idx])
		{
			return;
		}
	}
	//���� �˻縦 ���� ������ ���� ����� ����
	int divisor = idx + 1;
	// ���� �ڸ��������� ���ڸ� ����� �Լ�
	// ���� ��� �ι�° �ڸ����, �� �ڸ� ���ڸ� return
	int tmp = makeNumber(divisor);

	//�ڸ��� ���� ����
	if (tmp%divisor == 0)
	{
		// �� �������� ���(��� ��츦 �����ϴ� ���� ã��)
		//���� �迭�� ���
		if (divisor == 9)
		{
			std::cout << "magic num : ";
			showNumber();
			return;

		}
		// 5��° �ڸ��� 5�̹Ƿ� 5�� �ְ� Ȯ���� ��.
		if (divisor == 4)
		{
			number[divisor] = 5;
			checkNumber(divisor);
		}
		// 6~8��° �ڸ� Ȯ��
		//
		else
		{
			// ��� ���ڿ� ���� Ȯ��
			for (int i = 1; i <= 9; i++)
			{
				//5�� �̹� ���Ǿ��� ������ ��ŵ��.
				
				if (i == 5)
				{
					continue;
				}
				number[divisor] = i;
				checkNumber(divisor);
			}
		}
	}
}
int main()
{
	int idx = 0;
	for (int i=1;i<=9;i+=2)
	{
		if (i == 5)
		{
			continue;
		}
		number[idx] = i;
		checkNumber(idx);
	}
	//printf("cnt is %d\n", cnt);
	//c++ ��¹���.
	//endl : �ٹٲ� ������ ���
	//cout : printf
	//check_num  �Լ� ȣ�� Ƚ��
	std::cout << "cnt is : " << cnt << std::endl;
	return 0;
}