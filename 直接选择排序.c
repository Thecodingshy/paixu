#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
void Swap(int* a,int* b)
{
	int* tmp = *a;
	*a = *b;
	*b = tmp;
}
void SelectSortUp(int* a, int n)		//������10
{
	assert(a);
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		//ѡ�����ĸ�maxi��ѡ����С�ĸ�mini
		int maxi = end, mini = begin;	//11  0
		for (int i = end; i > begin; i--)
		{
			if (a[i] < a[mini])
				mini = i;
			if (a[i] > a[maxi])
				maxi = i;
		}
		//����
		Swap(&a[begin], &a[mini]);
		//���end��mini�ص���
			if (end == maxi)
			{
				mini = maxi;
			}
		Swap(&a[end], &a[maxi]);
		begin++;
		end--;
	}
}

void SelectSortDown(int* a, int n)
{
	//�±�
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int mini = begin, maxi = end;
		//ѡ�����ĸ�maxi��ѡ����С�ĸ�mini
		for (int i = begin; i <= end; ++i)
		{
			if (a[i] > a[mini])//����
			{
				mini = i;   //������if�ķ��ż���ʵ�����򡢽���ת����
			}
			if (a[i] < a[maxi])
			{
				maxi = i;
			}
		}
		//����
		Swap(&a[begin], &a[mini]);
		if (begin == maxi)
		{
			maxi = mini;
		}
		Swap(&a[end], &a[maxi]);
		++begin;
		--end;
	}
}

int main()
{
	int a[] = { 9 ,1 ,2 ,5 ,7 ,4 ,8 ,6 ,3 ,5 ,1,9};
	int n = sizeof(a) / sizeof(a[0]);
	printf("��������");
	SelectSortUp(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	printf("���ǽ���");
	SelectSortDown(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}