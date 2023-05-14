#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<malloc.h>
#define  MAXN   1000000 + 7
int arr[MAXN];
int size;
int getdigit(int x, int d) 
{
	int a[] = { 1,1,10,100,1e3,1e4,1e5,1e6,1e7,1e8,1e9,1e10,1e11 }; //因为待排数据最⼤数据位数  
	return ((x / a[d]) % 10);
}
void msdradix_sort(int begin, int end, int d)
{
	const int radix = 10; //进制数
	int count[radix], i, j; //count表⽰每个桶中元素个数 count[8]=2
	//置零
	for (i = 0; i < 10; ++i)count[i] = 0;
	//给桶分配空间
	int* bucket = (int*)malloc((end - begin + 1) * sizeof(int));
	//统计各桶需要装的元素的个数
	for (i = begin; i <= end; ++i) 
	{
		count[getdigit(arr[i], d)]++;
	}
	//求出桶的边界索引，count[i]值为第i个桶的右边界索引+1
	for (i = 1; i < radix; ++i) 
	{
		count[i] += count[i - 1];				//每个桶的边界，便于下步将arr重新放⼊bucket⾥
	}
	//这⾥要从右向左扫描，保证排序稳定性
	for (i = end; i >= begin; --i)
	{
		j = getdigit(arr[i], d);				//求出关键码的第d位的数字，例如：576的第3位是5
		bucket[count[j] - 1] = arr[i];		    //放⼊对应的桶中，count[j]-1是第j个桶的右边界索引 
		--count[j];							   //第j个桶放下⼀个元素的位置(右边界索引+1)
	}
	//注意：此时count[i]为第i个桶左边界
	//从各个桶中收集数据
	for (i = begin, j = 0; i <= end; ++i, ++j)
	{
		arr[i] = bucket[j];
	}
	//释放存储空间
	free(bucket);
	//对每个桶再次排序
	for (i = 0; i < radix; i++) {
		int p1 = begin + count[i];			 //第一个桶的左边界
		int p2 = begin + count[i + 1] - 1;	 //第i个桶的右边界
		if (p1 < p2 && d>1) {
			msdradix_sort(p1, p2, d - 1);	 //对第i个桶递归调⽤，进⾏基数排序，数位降 1 
		}
	}
}
int main() {

	int len = 10;

	// 从文件中读取数据
	FILE* input_file = fopen("input.txt", "r");

	if (!input_file)
	{
		puts("input.txt Error");
		exit(-1);
	}

	while (fscanf(input_file, "%d", &arr[size]) != EOF) 
	{
		printf("%d ", arr[size]);
		size++;
	}
	puts("");
	fclose(input_file);
	 
	//for (int i = 0; i < size; i++) printf("%d ", arr[i]);
	puts("");
	msdradix_sort(0, size - 1, len); 

	// 将排序后的结果写入文件
	FILE* output_file = fopen("output.txt", "w");
	for (int i = 0; i < size; i++) 
	{
		printf("%d ", arr[i]);
		fprintf(output_file, "%d\n", arr[i]);
	}
	puts("");
	fclose(output_file);

}
