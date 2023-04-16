#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
typedef int HPDataType;
typedef struct Heap {
	HPDataType* a;
	int size;
	int capacity;
}HP;
void AdjustUp(HPDataType* a, int child)
{
	assert(a);
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}


void AdjustDown(HPDataType* a, int size, int parent)		//�����д��������
{
	int child = 2 * parent + 1;
	while (child < size)		//��ʼĬ�������ӣ������Һ��Ӳ�һ������
	{
		if (child + 1 < size && a[child + 1] < a[child])
		{
			child++;
		}

		//���Ӹ����ױȽ�
		if (a[child] < a[parent])
		{
			Swap(&a[parent], &a[child]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}


void Swap(HPDataType* p1, HPDataType* p2)
{
	HPDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}


//-------------��һ��-----------------------//

void TextHeapSort1(HPDataType* a,int n)
{
	//ͨ�����ϵ����ķ�ʽ
	for (int i = 1; i < n; i++)						//ʱ�临�Ӷ�ΪO(N*logN)
	{
		AdjustUp(a,i);
	}
}


//---------------�ڶ���---------------------//

void TextHeapSort2(HPDataType* a, int n, int p)		//�ܹ���ʱ�临�Ӷ���O(N*logN)
{
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)		//O(log N)
	{
		AdjustDown(a, n, i);
	}


	int end = n - 1;
	while (end>0)									//O(N)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
}

int main()
{
	int a[] = { 27,15,19,18,28,34,65,49,25,37 };
	int sz = sizeof(a) / sizeof(a[0]);
	TextHeapSort1(&a, sz);
	TextHeapSort2(&a, sz, 0);
	return 0;
}