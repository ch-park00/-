#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define max 50
//������ ��
int serving = 0;
//���� �Ĵ� �ȿ� ����� �ִ��� Ȯ��
int cur = 0;
//�Ĵ翡 �� ��ȣ
int cnt = 0;
//�Ļ� �� �ϰ� ���� ��� ��
int cnt1 = 0;
//������� ��� ��
int wait = 0;
//���� ���ϰ� �ִ� ������ ��
int serve = 0;
//�Ļ縦 ��ġ�� ���̺��� ġ��� �ִ��� �Ǻ�.
//1�� �� ġ��� ������ �ǹ�.
int wait1[50] = { 0 };
HANDLE hMutex;
HANDLE hMutex1;
LPCWSTR res;
LPCWSTR res1;

// ������
DWORD WINAPI MYThread_2(LPVOID arg)
{
	wait1[(int)arg] = 1;
	// ��� �������� ���ϰ� ���� ��
	if (serve >= serving)
	{
		printf("�������� #%d �Ļ��� ���̺� ġ���ֱ� ��ٸ�����\n", (int)arg);
	}
	WaitForSingleObject(hMutex1, INFINITE);
	//���ݺ��� ġ��� ����
	serve++;
	printf("#%d���̺� ġ�����\n", (int)arg);
	Sleep(200);
	printf("#%d���̺� clear\n", (int)arg);
	serve--;
	cnt1++;
	//200ms���� �� ġ��� �Ӱ迵�� Ż��
	ReleaseSemaphore(hMutex1, 1, NULL);
	wait1[(int)arg] = 0;
	return 0;
}
// �Ĵ� ����
DWORD WINAPI MYThread_1(LPVOID arg)
{
	WaitForSingleObject(hMutex, INFINITE);
	// ������̴� ����� ������ ���
	if (wait > 0)
	{
		//����ο� 1�� ����
		wait--;
	}
	cnt++;
	int me = cnt;
	cur++;
	printf("#%d enter, �ð�:%d, ���� �Ĵ� �ȿ� ��� �� : %d\n", me, (int)arg,cur);
	Sleep((int)arg*100);
	printf("#%d ����\n", me);
	//
	CreateThread(NULL, 0, MYThread_2, (LPVOID)me, 0, NULL);
	Sleep(1);
	while (wait1[me]);
	cur--;
	ReleaseSemaphore(hMutex, 1, NULL);
	return 0;
}
int main(int argc, char *argv[])
{
	int p;
	printf("Ȯ�� �Է�(1/n), n���� �Է�:");
	scanf("%d", &p);
	printf("������ �� �Է�:");
	scanf("%d", &serving);
	srand(time(NULL));
	int c = 0;
	HANDLE hThread[max];
	DWORD THreadid[max];
	hMutex = CreateSemaphore(NULL, 10, 10, res);
	hMutex1 = CreateSemaphore(NULL, serving, serving, res1);
	time_t time1, time2;
	time1 = time(NULL);
	while (1)
	{
		// �Ĵ翡 �� 50���� ����
		if (cnt+wait >= max)
		{
			//��� ����� ������ �� ġ�ﶧ���� ���
			while (cnt1 < max);
			CloseHandle(hMutex);
			CloseHandle(hMutex1);
			break;
		}
		//�Ļ�ð��� ���� Ȯ�� ���
		int t = (rand() % 21) + 10;
		int c = (rand() % p);

		//�ƹ��� ���� ���� ���
		if (c)
		{
			Sleep(100);
			continue;
		}
		//������ ���� ���
		else
		{
			//���� �Ĵ�ȿ� 10�� �̻��� ���
			if (cur == 10)
			{
				wait++;
				printf("%d �����\n",cnt+wait);
			}
			// �������� �ȿ� ������ ����
			hThread[c] = CreateThread(NULL, 0, MYThread_1, (LPVOID)t, 0, &THreadid[c]);
			Sleep(100);
		}
	}
	time2 = time(NULL);
	printf("50���� �Ļ��ϰ� �����µ� �ɸ��ð�:%lld\n", (time2 - time1) );
	return 0;
}