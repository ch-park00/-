#include <stdio.h>
#include <stdlib.h>
#define Sz 8
//���������̹Ƿ� 0���� �ʱ�ȭ��.
int board[Sz][Sz]; 

// �� ���ʿ� �ִ� ������ �ִ��� ������ �˻�
// ���� �����ϸ� 1, ������ 0 ��ȯ
int checkUpside(int i, int j) //i�� j��
{
	for (int k = i - 1; k >= 0; k--)
	{
		if (board[k][j] != 0)
		{
			return 1;
		}
	}
	return 0;
}
//v�� ���밪 ��ȯ
int makeAbs(int v) 
{
	if (v < 0)
	{
		return -v;
	}
	return v;
}
// �밢���� ������ �����ϴ��� �˻�
//�밢���� ��쵵 ���� ���⸸ �ִ��� �˻�
// �Ȱ��� �����ϸ� 1, ������ 0��ȯ
int checkDiagonal(int _i, int _j)
{
	// �� ������ ��� ���� ���� ���밪�� ������ 
	//���� �밢���� �ִ� ����
	for (int i = 0; i < _i; i++)
	{
		for (int j = 0; j < Sz; j++)
		{
			if (board[i][j] != 0) //���� �˻��ϴ� ���� �����ϴ��� �˻�
			{
				if (makeAbs(i - _i) == makeAbs(j - _j)) //�밢������ �ƴ��� �˻�
				{
					return 1;
				}
				else
				{
					//�ش� �࿡ ���� �����ϴµ� �밢�� �ƴѰ��� �����ϹǷ�
					//�ش� ���� �� �̻� �˻��� �ʿ䰡 ����
					//���� ���� �Ѿ�� �˻��Ѵ�.
					break; 
				}
			}
		}
	}
	return 0;
}
void showBoard()
{
	printf("-------------\n");
	for (int i = 0; i < Sz; i++)
	{
		for (int j = 0; j < Sz; j++)
		{
			printf("%d ", board[i][j]);
		}

		printf("\n");
	}
	printf("-------------\n");
}
//Queen�� ���� �ڸ��� [row, 0 ~ (Sz-1)]�κп� ���� �˻�
void doBacktracking(int row) 
{
	for (int i = 0; i < Sz; i++)
	{
		//�ش� ��ġ�� ���� ������ �ִ��� ������ �˻��غ���
		if (checkUpside(row, i) == 0 && checkDiagonal(row, i) == 0)
		{
			board[row][i] = 1; //queen�� �ش� ��ġ�� ���´�
			if (row  < Sz - 1) 			
			{
				//queen�� ���� ���µ� ��� ���� ���� �� ���� �࿡ ���� �˻� �ǽ�
				doBacktracking(row + 1);
			}
			else
			{
				// �� ������ �ٿ� ���������Ƿ� ü���� ��� �� ����
				showBoard();
			}
			board[row][i] = 0; //�ش� ������ �����ϰ� �� �Ŀ��� �ٸ� ������ �����غ����� �ش� ���� ġ�����Ѵ�.
		}
	}
}
//backtracking ����(4queen problem)
int main()
{
	doBacktracking(0); //0����� queen�� ���� backtracking ����
	return 0;
}