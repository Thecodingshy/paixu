#define _CRT_SECURE_NO_WARNINGS
#include"Stack.h"

void Swap(int* pa, int* pb)
{
	int* tmp = 0;
	tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

int PartSort3(int* a, int begin, int end)
{
	int prev = begin;
	int cur = begin + 1;
	int keyi = begin;

	while(cur<=end)								//ǰ��ָ�뷨
	{
		if (a[cur < a[keyi] && ++prev != cur])
			Swap(&a[prev], &a[cur]);
		cur++;
	}
	Swap(&a[prev], &a[cur]);
	return keyi;
}

void QuickSort(int* a, int begin, int end)		//�ݹ�
{
	if (begin >= end)
	{
		return;
	}
	int keyi = PartSort3(a, begin, end);

	QuickSort(a, begin, keyi-1);
	QuickSort(a, keyi+1, end);
}

void QuickSortNonR(int* a, int begin, int end)
{
	ST st;
	StackInit(&st);
	StackPush(&st,end);		//�����ұ�
	StackPush(&st, begin);	//�������

	while (!StackEmpty(&st))	//ջ�ڼ�¼���±����ֿ��˾Ͳ�����
	{
		int left = StackTop(&st);	//��ȡ���ұ�
		StackPop(&st);

		int right = StackTop(&st);	//��ȡ�����
		StackPop(&st);

		int keyi = PartSort3(a, left, right);	//�����֮ǰѡ������left �� right ���е�������

		if (left < keyi - 1)		//����keyi��ߵ�������ǲ�����
		{
			StackPush(&st, keyi - 1);
			StackPush(&st, left);
		}

		if (keyi + 1 < right)		//����keyi�ұߵ�������ǲ�����
		{
			StackPush(&st, right);
			StackPush(&st, keyi + 1);
		}
	}
	StackDestory(&st);				//��ֹ�ڴ�й¶
}
/*
	�ǵݹ��д������ĵݹ����̫�ջ�ռ������

	���ͣ�
					��ʼ���������䣬�����ţ��ų����������䣬�����������´�ȡ��ȡ�����ǣ���ջ��������ұ��������ߣ�������
			��������keyi���룬��������䱻ѹ�������棬�ٽ�һ����������---����---����---���ٴ������������䴦������
			��ȥȡ�����䣬������ָ����룬�ָ����봦��
					����������һ��ֵ���߲����ڣ��Ͳ�������
					���Ը���������ģ�left,right�����ж���ջ
					if(left<keyi-1)
					����
					if(keyi-1<right)
					����
				ģ���˵ݹ�Ĺ���

*/