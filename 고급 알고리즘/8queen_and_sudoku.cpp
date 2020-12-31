#include <stdio.h>
#include <string.h>
#include <math.h>
//�� ������
#define SZ 8
//������ ������
#define S_SZ 9
//���� �����̹Ƿ� ��� 0���� �ʱ�ȭ��
int board[SZ][SZ];
int sudoku[S_SZ][S_SZ] = {
	4,0,7,5,0,0,0,0,8,
	0,5,0,7,0,0,4,0,9,
	0,0,6,0,0,4,0,7,0,
	9,0,0,6,0,0,2,4,3,
	0,4,0,9,0,3,0,8,0,
	7,3,1,0,0,2,0,0,5,
	0,2,0,8,0,0,7,0,0,
	3,0,9,0,0,6,0,5,0,
	5,0,0,0,0,7,3,0,4
};
//backtracking ���� �� ���� ���·� ���ư��� ���� �ʿ��� �迭
int read_sudoku[S_SZ][S_SZ];

//board �迭 ��� 0���� �ʱ�ȭ
void init_board()
{
	/*
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			board[i][j] = 0;
		}
	}*/
	//board �ּҷκ��� 4*SZ*SZ��ŭ�� �ּҰ��� ��� 0���� �ʱ�ȭ
	//string.h �ȿ� ����
	memset(board, 0, sizeof(int) * SZ* SZ);
}
//���� ��ġ�� ���� ��ġ�ص� �Ǵ��� ���� Ȯ��
//��ǥ�� (r,c)
//���� �����Ѵٸ� 1, �ƴ϶�� 0 ��ȯ
//���� �˻� �� ����(������ ���� ��ġ�� �� �ִ� ����)�� Ȯ���Ѵ�.
//�Ʒ��� ������ ���߿� ���� �� Ȯ���ϹǷ� �̸����� Ȯ���� �ʿ䰡 ����.
int check_if(int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		//���� ��ġ���� �������� ���� ��ġ
		if (board[i][c] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < c; i++)
	{
		//���� �ٿ� ���� ����
		if (board[r][i] != 0)
		{
			return 0;
		}
	}
	//�밢�� �˻�
	//�밢���� ��ġ�� ���� => ���� ��ġ���� �� ���� = �� ����
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (abs(i - r) == abs(j - c) && board[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
void print_sol()
{
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("-----------------------\n");
}
//�� i�� 0���� �ʱ�ȭ
void clear_row(int i)
{
	memset(board[i], 0, sizeof(int)*SZ);
}
//���� row ��ġ�� chess �Ѽ� �ִ��� Ȯ�� �� �����ϴ� �Լ�
//���� �������� ���ϴ� ��찡 �ִٸ� �ش� ����� ����� �ʱ�ȭ �ؾ��Ѵ�.
void check_next(int row)
{
	for (int i = 0; i < SZ; i++)
	{
		//��ǥ (row,i)�� �� �� �� �ִ��� Ȯ��
		//���� �� ��ġ�ϰ� ���� ������ �̵��Ѵ�.
		//���� �� ������ ���̶�� 
		if (check_if(row, i))
		{
			board[row][i] = 1;
			//�� ������ ����� ���� �Ϸ�(4���� ���� ���� ��� �ϼ�)
			if (row == SZ - 1)
			{
				print_sol();
			}
			else
			{
				check_next(row + 1);
			}
		}
		clear_row(row);
		
	}
}
void do_queen_problem()
{
	for (int i = 0; i < SZ; i++)
	{
		if (check_if(0, i))
		{
			board[0][i] = 1;
			check_next(1);
		}
		clear_row(0);
	}
}


//read_sudoku �迭�� sudoku ����
void init_read_sudoku()
{
	memcpy(read_sudoku, sudoku, sizeof(int)*S_SZ*S_SZ);
}
//(row,col) ��ġ�� i���� �� �� �ִ��� Ȯ��
int check_sudoku_data(int row, int col, int data)
{
	//�� Ȯ��
	for (int i = 0; i < S_SZ; i++)
	{
		if (sudoku[i][col] == data && i != row)
		{
			return 0;
		}
	}
	//�� Ȯ��
	for (int i = 0; i < S_SZ; i++)
	{
		if (sudoku[row][i] == data && i != col)
		{
			return 0;
		}
	}
	//�簢�� Ȯ��
	for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
	{
		for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
		{
			if (sudoku[i][j] == data)
			{
				return 0;
			}
		}
	}
	return 1;
}
void print_result()
{
	for (int i = 0; i < S_SZ; i++)
	{
		for (int j = 0; j < S_SZ; j++)
		{
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("------------------------\n");
}
void do_sudoku_problem(int row, int col);
//(row,col) ���� ĭ���� �̵���Ű�� �Լ�
void check_next_sudoku(int row, int col)
{
	int r = row;
	int c = col;
	if (col == S_SZ - 1)
	{
		if (row == S_SZ - 1)
		{
			print_result();
			return;
		}
		r = r + 1;
		c = 0;
	}
	else
	{
		c = c + 1;
	}
	do_sudoku_problem(r, c);
}
//sudoku ������ backtracking �̿��� ���� �ذ�.
void do_sudoku_problem(int row, int col)
{
	//�̸� �Էµ� ���ڰ� �ִ� ���
	if (sudoku[row][col] != 0)
	{
		check_next_sudoku(row, col);
	}
	else
	{
		for (int i = 1; i <= 9; i++)
		{
			memcpy(&sudoku[row][col], &read_sudoku[row][col], sizeof(int)*((S_SZ*S_SZ) - (row*col)));
			//�ش� ���ڰ� �ش� ��ġ�� �� �� �ִ��� Ȯ��
			if (check_sudoku_data(row, col, i))
			{
				sudoku[row][col] = i;
				check_next_sudoku(row, col);
			}
		}
	}
}
int main()
{
	//init_board();
	//do_queen_problem();
	init_read_sudoku();
	do_sudoku_problem(0,0);
	return 0;
}