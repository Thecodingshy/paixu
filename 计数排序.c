#define _CRT_SECURE_NO_WARNINGS
//计数排序：
//1.统计每个数据出现的次数
//2.排序（按出现的次数回写原数组）

//局限性
//1. 如果是浮点数字符串就不能了
//2.如果数据范围很大，空间复杂度很高，相对不适合

//时间复杂度 O（max(range,N)）
//空间复杂度 O （range）
//从以上来分析可以知道该算法在数据集中，且范围不大的情况下适用

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

	//统计次数
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;	//找到相对映射并且在该位置上进行计数累加count[i]是在该相对位置上存在的个数
	}
	int j = 0;
	for (int i = 0; i < range; i++)	//回写到a数组中
	{
		while (count[i]--)
		{
			a[j--] = i + min;
		}
	}
}