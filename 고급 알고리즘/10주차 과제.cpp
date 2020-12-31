#include <iostream>
#define num 20
struct node
{
	int data;
	int idx;
	struct node *next;
};
struct node *head = 0;
struct node *merge_result=0;
struct node *quick_result = 0;
int max_merge = 0;
int max_quick = 0;

//�׶��׶� �ٲ㰡�� ���
int data[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

void mergesort(int start, int end, int cur_level)
{
	//i=ù��° ����� ���� ���ľ� �� �ε���
	//j=�ι�° ����� ���� ���ľ� �� �ε���
	//g= ��ģ ����� ���� ��ġ(���� ������ �� �ε���)
	int m = ((start + end) / 2);
	int i = start;
	int j = m + 1;
	int g = 0;
	//�պ� ���� üũ
	if (start < end)
	{
		//�׷� �ɰ��� ����.
		mergesort(start, m, cur_level+1);
		mergesort(m + 1, end, cur_level+1);
		//�� �ɰ� ���� �ٽ� ��ġ�� ����
		struct node **my_arr = (struct node**)malloc(sizeof(struct node**)*(end - start + 1));
		struct node *i_com = head;
		struct node *j_com = head;
		struct node *s = head;
		struct node *e = head;
		struct node *tmp = head;
		for (int k = 0; k < end + 1; k++)	e = e->next;
		for (int k = 0; k < start - 1; k++)	s = s->next;
		for (int k = 0; k < start; k++)	i_com = i_com->next;
		for (int k = 0; k < j; k++)	j_com = j_com->next;
		while (i <= m && j <= end)
		{
			if (i_com->data <= j_com->data)
			{
				my_arr[g] = i_com;
				i++;
				i_com = i_com->next;
			}
			else
			{
				my_arr[g] = j_com;
				j++;
				j_com = j_com->next;
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
				my_arr[g] = i_com;
				g++;
				i++;
				i_com = i_com->next;
			}
		}
		//���� ��� ���
		else
		{
			for (int k = j; k <= end; k++)
			{
				my_arr[g] = j_com;
				g++;
				j++;
				j_com = j_com->next;
			}
		}
		//�ΰ��� ��� ��� ��ġ�� �Ϸ�
		//������ �κа� ����
		if (start == 0)
		{
			head = my_arr[0];
			tmp = head;
			for (int k = 1; k < g; k++)
			{
				tmp->next = my_arr[k];
				tmp = tmp->next;
			}
			tmp->next = e;
		}
		else
		{
			s->next = my_arr[0];
			tmp = s->next;
			for (int k = 1; k < g; k++)
			{
				tmp->next = my_arr[k];
				tmp = tmp->next;
			}
			tmp->next = e;
		}
		if (max_merge < cur_level)	max_merge = cur_level;
		free(my_arr);
	}
}

int check_ok(struct node *L, struct node *R)
{
	struct node *tmp = head;
	while (tmp != 0)
	{
		if (tmp == R)	return 1;
		if (tmp == L)	return 0;
		tmp = tmp->next;
	}
}
void q_sort(int pivot, int left, int right, int cur_level)
{
	if (left > right)	return;
	int R_idx = 0;
	struct node *P, *L, *R, *left_node, *right_node;
	P = L = R = head;
	for (int i = 0; i < pivot; i++)	P = P->next;
	for (int i = 0; i < right; i++)
	{
		if (i < left)
		{
			L = L->next;
		}
		R = R->next;
	}
	left_node = L;
	right_node = R;
	while (1)
	{
		while (L->data <= P->data)
		{
			if (L == right_node)
			{
				//L = L->next;
				break;
			}
			L = L->next;
		}
		while (R->data > P->data)
		{
			struct node *tmp = head;
			if (R == left_node)
			{
				while (tmp->next != R)	tmp = tmp->next;
				R = tmp;
				break;
			}
			while (tmp->next != R)	tmp = tmp->next;
			R = tmp;
		}
		if (check_ok(L,R))
		{
			//pivot �������� ���� �Ϸ�
			//R �� pivot ��ġ �ٲٱ�
			struct node *pivot_prev = head;
			struct node *R_prev = head;
			if (P != head)
			{
				while (R_prev->next != R)
				{
					R_prev = R_prev->next;
					R_idx++;
				}
				R_idx++;
			}
			if (P != R) 
			{	
				if (head == P)
				{
					head = head->next;
					R_prev->next = R->next;
					P->next = R_prev->next;
					if (R_prev != P) 
					{
						R_prev->next = P;
						R->next = head;
						head = R;
					}
					else 
					{
						R->next = P;
					}
				}
				else
				{
					while (pivot_prev->next != P)	pivot_prev = pivot_prev->next;
					if (P->next == R)
					{
						pivot_prev->next = R->next;
						R->next = P;
						P->next = pivot_prev->next;
						pivot_prev->next = R;
					}
					else
					{
						pivot_prev->next = P->next;
						R_prev->next = R->next;
						R->next = pivot_prev->next;
						pivot_prev->next = R;
						P->next = R_prev->next;
						R_prev->next = P;
					}
				}
			}
			break;
		}
		else
		{
			//L�� R�� ��ġ �ٲٱ�
			struct node *L_prev = head;
			struct node *R_prev = head;
			while (R_prev->next != R)	R_prev = R_prev->next;
			while (L_prev->next != L)	L_prev = L_prev->next;
			if (L->next != R)
			{
				L_prev->next = L->next;
				R_prev->next = R->next;
				L->next = R_prev->next;
				R_prev->next = L;
				R->next = L_prev->next;
				L_prev->next = R;
			}
			else
			{
				L_prev->next = R->next;
				R->next = L;
				L->next = L_prev->next;
				L_prev->next = R;
			}
			struct node *temp = L;
			if (L == left_node)
			{
				left_node = R;
			}
			L = R;
			if (R == right_node)
			{
				right_node = temp;
			}
			R = temp;
		}
	}
	q_sort(pivot, left, R_idx - 1, cur_level + 1);
	q_sort(R_idx + 1, R_idx + 2, right, cur_level + 1);
	if (cur_level > max_quick)	max_quick = cur_level;
	return;
}
void init_data()
{
	struct node *prev = 0;
	for (int i = 0; i < num; i++)
	{
		struct node *new1 = (struct node*)malloc(sizeof(struct node));
		new1->data = data[i];
		new1->next = 0;
		new1->idx = 0;
		if (prev == 0)
		{
			prev = new1;
			head = prev;
		}
		else
		{
			prev->next = new1;
			prev = new1;
		}
	}
}
int main()
{
	init_data();
	struct node *cur = head;
	std::cout << "before sort" << std::endl;
	for (int i = 0; i < num; i++)
	{
		std::cout << cur->data << ", " << cur << std::endl;
		cur = cur->next;
	}
	std::cout << "----------------" << std::endl;
	#if 0
	mergesort(0, num - 1, 0);
	cur = head;
	std::cout << "after sort " << std::endl;
	while (cur!=0)
	{
		std::cout << cur->data << "," << cur << std::endl;
		cur = cur->next;
	}
	std::cout << "max merge : " << max_merge << std::endl;
	std::cout << "----------------" << std::endl;
	#endif
	#if 1
	q_sort(0, 1, num - 1, 0);
	cur = head;
	std::cout << "after sort" << std::endl;
	for (int i = 0; i < num; i++)
	{
		std::cout << cur->data << ", " << cur << std::endl;
		cur = cur->next;
	}
	std::cout << "max quick : " << max_quick << std::endl;
	#endif
	return 0;
}