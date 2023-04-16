#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
void Swap(int* a,int* b)
{
	int* tmp = *a;
	*a = *b;
	*b = tmp;
}
void SelectSortUp(int* a, int n)		//排升序10
{
	assert(a);
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		//选出最大的给maxi，选出最小的给mini
		int maxi = end, mini = begin;	//11  0
		for (int i = end; i > begin; i--)
		{
			if (a[i] < a[mini])
				mini = i;
			if (a[i] > a[maxi])
				maxi = i;
		}
		//交换
		Swap(&a[begin], &a[mini]);
		//如果end和mini重叠了
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
	//下标
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int mini = begin, maxi = end;
		//选出最大的给maxi，选出最小的给mini
		for (int i = begin; i <= end; ++i)
		{
			if (a[i] > a[mini])//升序
			{
				mini = i;   //改两个if的符号即可实现升序、降序转换。
			}
			if (a[i] < a[maxi])
			{
				maxi = i;
			}
		}
		//交换
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
	printf("这是升序：");
	SelectSortUp(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	printf("这是降序：");
	SelectSortDown(a, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}