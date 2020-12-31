int* merge_sort(int *origin_arr, int *result_arr, int start, int end)
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
		merge_sort(origin_arr, result_arr, start, m);
		merge_sort(origin_arr, result_arr, m + 1, end);

		//�� �ɰ� ���� �ٽ� ��ġ�� ����

		while (i <= m && j <= end)
		{
			if (origin_arr[i] < origin_arr[j])
			{
				result_arr[g] = origin_arr[i];
				i++;
			}
			else
			{
				result_arr[g] = origin_arr[j];
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
				result_arr[g] = origin_arr[i];
				g++;
				i++;
			}
		}
		//���� ��� ���
		else
		{
			for (int k = j; k <= end; k++)
			{
				result_arr[g] = origin_arr[j];
				g++;
				j++;
			}
		}
		//�ΰ��� ��� ��� ��ġ�� �Ϸ��� ���
		memcpy(origin_arr + start, result_arr + start, sizeof(int)*(end - start + 1));
		return result_arr;
	}
}