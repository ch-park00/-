#include <stdio.h>
#include <stdlib.h>

int main()
{
	//              ���ϸ�		 read���,text�� ����ִ�(������ ���̴� ���� text.�ƴ� ���� ��� binary->�����̳� ���� ��)
	FILE *f = fopen("seoul.txt", "rt"); //file�� �� ���� file������ �̿�.���� �ּ� ��ȯ

	char buf[100] = { 0 };
	/* fgets(buf, 99, f); //buf�� f���� 99���� char��(string)�� �о��.1�ٸ�*/

	while(1)
	{
		if (feof(f)) //������ ���� �˷���
		{
			break;
		}
		fgets(buf, 99, f);
		printf("%s", buf);
		buf[0] = '\0';
	}
	fclose(f); //file �ݱ�
	return 0;
}