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

	while(cur<=end)								//前后指针法
	{
		if (a[cur < a[keyi] && ++prev != cur])
			Swap(&a[prev], &a[cur]);
		cur++;
	}
	Swap(&a[prev], &a[cur]);
	return keyi;
}

void QuickSort(int* a, int begin, int end)		//递归
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
	StackPush(&st,end);		//先入右边
	StackPush(&st, begin);	//再入左边

	while (!StackEmpty(&st))	//栈内记录的下标数字空了就不排了
	{
		int left = StackTop(&st);	//先取得右边
		StackPop(&st);

		int right = StackTop(&st);	//再取得左边
		StackPop(&st);

		int keyi = PartSort3(a, left, right);	//这里对之前选出来的left 和 right 进行单趟排序

		if (left < keyi - 1)		//先入keyi左边的区间除非不存在
		{
			StackPush(&st, keyi - 1);
			StackPush(&st, left);
		}

		if (keyi + 1 < right)		//再入keyi右边的区间除非不存在
		{
			StackPush(&st, right);
			StackPush(&st, keyi + 1);
		}
	}
	StackDestory(&st);				//防止内存泄露
}
/*
	非递归的写法避免的递归深度太深，栈空间溢出；

	解释：
					开始传入大的区间，单趟排，排出两个子区间，两个子区间下次取，取到的是（在栈上先入的右边在入的左边）左区间
			在左区间keyi再入，这个右区间被压在最下面，再进一步处理，再入---处理---再入---在再处理，当我左区间处理完了
			再去取右区间，右区间分割再入，分割再入处理
					当子区间是一个值或者不存在，就不再入了
					所以根据子区间的（left,right）来判断入栈
					if(left<keyi-1)
					入入
					if(keyi-1<right)
					入入
				模拟了递归的过程

*/