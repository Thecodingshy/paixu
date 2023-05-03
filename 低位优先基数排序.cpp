#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<queue>

using namespace std;
#define K 3
#define RADIX 10

//定义基数
queue<int> Q[RADIX];
int GetKey(int value, int k)
{
	int key = 0;
	while (k >= 0)
	{
		key = value % 10;
		value = value / 10;
		k--;
	}
	return key;
}

void Distribute(int arr[], int left, int right, int k)
{
	for (int i = left; i < right; i++)
	{
		int key = GetKey(arr[i], k);
		Q[key].push(arr[i]);
	}
}

void Collect(int arr[])
{
	int k = 0;
	for (int i = 0; i < RADIX; i++)
	{
		while (!Q[i].empty())
		{
			arr[k++] = Q[i].front();
			Q[i].pop();
		}
	}
}

void RadixSort(int arr[],int left,int right)
{
	for (int i = 0; i < K; i++)
	{
		Distribute(arr, left, right, i);

		Collect(arr);
	}
}

int main()
{

	int arr[] = { 278,109,63,930,589,184,550,269,8,83 };
	int n = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < n; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

	RadixSort(arr, 0, n);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
