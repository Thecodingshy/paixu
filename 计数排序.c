#define _CRT_SECURE_NO_WARNINGS
//��������
//1.ͳ��ÿ�����ݳ��ֵĴ���
//2.���򣨰����ֵĴ�����дԭ���飩

//������
//1. ����Ǹ������ַ����Ͳ�����
//2.������ݷ�Χ�ܴ󣬿ռ临�ӶȺܸߣ���Բ��ʺ�

//ʱ�临�Ӷ� O��max(range,N)��
//�ռ临�Ӷ� O ��range��
//����������������֪�����㷨�����ݼ��У��ҷ�Χ��������������

#include<stdio.h>
#include<string.h>
void CountSort(int* a, int n)
{
	int min = a[0], max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}
	int range = max - min + 1;
	int* count = (int*)malloc(sizeof(int) * range);
	if (count == NULL)
	{
		printf("malloc fail");
		exit(-1);
	}
	memset(count, 0, sizeof(int)*range);

	//ͳ�ƴ���
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;	//�ҵ����ӳ�䲢���ڸ�λ���Ͻ��м����ۼ�count[i]���ڸ����λ���ϴ��ڵĸ���
	}
	int j = 0;
	for (int i = 0; i < range; i++)	//��д��a������
	{
		while (count[i]--)
		{
			a[j--] = i + min;
		}
	}
}