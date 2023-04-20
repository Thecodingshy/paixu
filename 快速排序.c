#define _CRT_SECURE_NO_WARNINGS
#include"Stack.h"
void Swap(int* a, int* b)
{
	int* tmp = *a;
	*a = *b;
	*b = tmp;
}
//下面的写法是当年Hoare原创的写法，也是再排序界比较经典的写法
//只要记住左边作key右边先走左边找小于key,右边找大于key
//保证相遇位置的值比key的值小，或者就是key的位置
void QuickSort1(int* a, int begin, int end)
{
	if (begin >= end)	//  这里的>解释为该递归的区间为空，这里的=解释为递归到只有一个数字时候
	{
		return;			//所以直接返回到函数栈帧的上一层
	}
	int left = begin;
	int right = end;
	int keyi = left;

	//这里简单分析一下为什么要右边先走
	//无非分两种情况
	//1：R先走，R停下来，L去遇到R，
	//	相遇位置就是R停下位置R位置就是比keyi要小的位置；
	//2：R先走，R没有找到比key要小的值R去遇到了L；
	//	 相遇位置就是L上一轮停下的位置，就是key的位置要么比key小

	while (left<right)								//一定最终相遇所以是left<right,
	{
		while (left < right && a[right] >= a[keyi])	//先走左边找小，找到就停留
		{
			right--;
		}
		while (left < right && a[left] <= a[keyi])	//再去右边找大，找到就停留
		{
			left++;
		}	
		Swap(&a[left], &a[right]);					//交换刚刚找到的位置的值
	}
	Swap(&a[keyi], &a[left]);
	keyi = left;

	//这里我控制的是闭区间所以这样写		
	//[begin,keyi-1] keyi [keyi+1,end]

	QuickSort(a, begin, keyi-1);				//递归左右区间
	QuickSort(a, keyi + 1, end);
}



//这个方法比较麻烦，考虑一下挖坑法，这种方法比较通俗易懂
int PartSort2(int* a, int begin, int end)
{
	int key = a[begin];
	int piti = begin;
	while (begin < end)
	{
		//右边找小，找到填在左边的坑里，这个位置形成新的坑
		while (begin < end && a[end] >= key)  
		{
			end--;
		}

		a[piti] = a[end];	//换值
		piti = end;			//换下标
		//左边找大，找到填在右边的坑里，这个位置形成新的坑
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}

		a[piti] = a[begin];	//换值
		piti = begin;		//换下标
	}
}



//但是前两种方法并没有从本质上对这个排序进行调整
//接下来要介绍的是前后指针法
void QuickSort3(int* a, int begin, int end)
{
	int prev = begin;
	int cur = begin + 1;
	int keyi = begin;
	while(cur <= end)
	{
		if (a[cur] < a[keyi] && ++prev != cur)		//&&本身也是一种判断，它前面的判断正确则prev直接++
			Swap(&a[prev], &a[cur]);				//若cur==prev 省去了自己跟自己交换
		cur++;										//无论怎末变，我cur要一直往前走
	}
	///while (cur <= end)
	//{
	//	if (a[cur] < a[keyi])
	//		{
	//		  prev++;								//回头想想刚刚这种写法多妙
	//		  Swap(&a[prev],&a[cur]);	
	//		}
	//	cur++;
	//}
	Swap(&a[prev], &a[keyi]);
	return keyi;
}
//但是又有一个问题毕竟上面的三种写法都是默认取数组第一个值为key，存在一个问题
//如果我原数组有序或者接近有序，这时候排序效果最差
//N+(N-1)+(N-2)+(N-3)+....+3+2+1
//O(N^2)
//还存在一个问题如果我数据量很大会出现栈溢出（即使在release版本可能撑得住，因为它里面不放调试信息，但是一旦数字基数进一步加大就不行了）

//所以我们经过分析可以在key的选取上做手脚
//第一种方法:选取数组内随机的数作为key，交换该位置和key位置的数，但是缺点是不稳定
//第二种方法:《三数取中》
int GetMidIndex(int* a, int begin, int end)
{
	int midi = (begin + end) / 2;
	if (a[begin] < a[midi])
	{
		if (a[begin] < a[midi])
			return midi;
		else if (a[begin] < a[end])
			return end;
		else
			return begin;
	}
	else     //相当于a[begin] >= a[midi]
	{
		if (a[midi] > a[midi])
		{
			if (a[midi] > a[end])
				return midi;
			else if (a[begin] > a[end])
				return begin;
			else
				return end;
		}
	}
}


//是否可以进一步优化以上算法呢，经过分析不难发现后面都是通过QuickSort(a,begin,key-1);QuickSort(a,key+1,end)递归来实现
//但是《递归的死穴》----递归太深，这时候会栈溢出
//栈区一般大小为8MB左右
//相反堆区一般很大

//这时候我们的思路是
//直接改循环----比如斐波拉系数列，归并排序
//用数据结构栈来模拟实现递归的过程
void QuickSortNonR(int* a, int begin, int end)
{
	ST st;
	StackInit(&st);
	StackPush(&st, end);	//先入右边
	StackPush(&st, begin);	//再入左边
	while (!StackEmpty)
	{
		int left = StackTop(&st);	
		StackPop(&st);

		int right = StackTop(&st);	
		StackPop(&st);

		int keyi = PartSort2(a, left, right);	//按上面的方法找一趟的key

		if (left < keyi + 1)
		{
			StackPush(&st, keyi - 1);
			StackPush(&st, left);
		}
		if (keyi + 1 < right)
		{
			StackPush(&st, right);
			StackPush(&st, keyi+1);
		}
	}
	StackDestory(&st);
}


void QuickSort(int* a, int begin, int end)
{
	if (begin >= end)
	{
		return;
	}
	int keyi = PartSort(a, begin, end);
	QuickSort(a, begin, keyi -1);
	QuickSort(a, keyi+1, end);
}