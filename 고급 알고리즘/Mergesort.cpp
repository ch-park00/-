#include <iostream>
#define num 10


int data[10] = { 10,9,8,7,6,5,4,3,2,1 };
int out[10];

void initOutput()
{
	memcpy(out, data, sizeof(int)*num);
}

void mergesort(int start, int end)
{
	//i=ù��° ����� ���� ���ľ� �� �ε���
	//j=�ι�° ����� ���� ���ľ� �� �ε���
	//g= ��ģ ����� ���� ��ġ(���� ������ �� �ε���)

	int m = ((start + end) / 2);
	int i = start;
	int j = m + 1;
	int g = start;
	//�պ� ���� üũ
	if (start < end)
	{
		//�׷� �ɰ��� ����.
		//
		mergesort(start, m);
		mergesort(m + 1, end);

		//�� �ɰ� ���� �ٽ� ��ġ�� ����

		while (i <= m && j <= end)
		{
			if (data[i] < data[j])
			{
				out[g] = data[i];
				i++;
			}
			else
			{
				out[g] = data[j];
				j++;
			}
			g++;
		}
		//�� �� ����� ���ڰ� ������ ���
		//�ٸ� �� ���� ��� �����ϴ� ��

		//������ ����� ��� ���
		if (i <= m && j > end)
		{
			for (int k = i; k <= m; k++)
			{
				out[g] = data[i];
				g++;
				i++;
			}
		}
		//���� ��� ���
		else
		{
			for (int k = j; k <= end; k++) 
			{
				out[g] = data[j];
				g++;
				j++;
			}
		}
		//�ΰ��� ��� ��� ��ġ�� �Ϸ��� ���
		
		memcpy(data + start, out + start, sizeof(int)*(end - start + 1));
		return;
	}
}
void showoutput()
{
	for (int i = 0; i < num; i++)
	{
		std::cout << out[i] << std::endl;
	}
}
int main()
{
	initOutput();
	mergesort(0, num - 1);
	showoutput();

	return 0;
}