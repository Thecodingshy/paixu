#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void _MergeSort(int* a, int begin, int end, int* tmp)
{
	if (begin >= end)
		return;
	//[begin,mid][mid+1,end]  分治递归让子区间有序
	int mid = (begin + end) / 2;
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid+1, end, tmp);

	//归并[begin,mid][mid+1,end]

	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin1;  


	while (begin1 <= end1 && begin2 <= end2)	//谁给过去谁++//参考数组融合
	{
		if (a[begin1] < a[begin2])
		{
			tmp[i] = a[begin1];
			i++, begin1++;
		}
		else
		{
			tmp[i] = a[begin2];
			i++, begin2++;
		}
	}


	while (begin1 <= end)
	{
		tmp[i++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}

	memcpy(a + begin, tmp + begin, (end - begin + 1) * sizeof(int));
}

void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail");
		exit(-1);
	}
	_MergeSort(a, 0, n - 1, tmp);
}

//用栈来模拟非递归过程
void mergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		printf("malloc fail");
		exit(-1);
	}
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + gap * 2 - 1;

																//if(end1>=n || begin2>=n)	//或者将下面的带进行这样的改写
																//	break;
																//else if(end2>=n)
																//	end2=n-1;
			if (end1 >= n)			//全处理
				{
					end1 = n - 1;
					begin2 = n;
					end2 = n - 1;
				}
			else if (begin2 >= n)
				{
					begin2 = n;
					end2 = n - 1;
				}
			else if (end2 >= n)	//最后处理end2越界
				{
					end2 = n - 1;		
				}


																//int m=end2-begin1+1;	//或者处理归并的个数

			int j = begin1;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					tmp[j++] = a[begin1++];
				}
				else
				{
					tmp[j++] = a[begin2++];
				}

					while (begin1 <= end1)
					{
						tmp[j++] = a[end1++];
					}
					while (begin2 <= end2)
					{
						tmp[j++] = a[begin2++];
					}
			}
		}
		memcpy(a, tmp, sizeof(int) * n);						//memcpy(a+i,tmp+i,sizeof(int)*m)	防止memcpy越界出去
		gap = gap * 2;
	}
	free(tmp);
}