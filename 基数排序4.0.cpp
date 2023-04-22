#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include <fstream> 
#include<algorithm>
#include<string>
#include<malloc.h>
using namespace std;
int len;//最大字符串的长度
const int maxn = 1000;
string  arr[maxn];
int length;
void msdradix_sort(int begin, int end, int d) {
	const int radix = 127; //进制数
	int count[radix], i, j; //count表⽰每个桶中元素个数
	//置零
	for (i = 0; i < radix; ++i)count[i] = 0;
	//给桶分配空间
	string* bucket = new string[end - begin + 1];
	//统计各桶需要装的元素的个数
	for (i = begin; i <= end; ++i) {
		count[arr[i][d]]++;
	}
	//求出桶的边界索引，count[i]值为第i个桶的右边界索引+1
	for (i = 1; i < radix; ++i) {
		count[i] += count[i - 1]; //每个桶的边界，便于下步将arr重新放⼊bucket⾥
	}
	//这⾥要从右向左扫描，保证排序稳定性
	for (i = end; i >= begin; --i) {
		j = arr[i][d];    //求出关键码的第d位的数字第i个字符串第d位
		bucket[count[j] - 1] = arr[i];   //放⼊对应的桶中，count[j]-1是第j个桶的右边界索引  
		--count[j];     //第j个桶放下⼀个元素的位置(右边界索引+1)
	}
	//注意：此时count[i]为第i个桶左边界
	//从各个桶中收集数据
	for (i = begin, j = 0; i <= end; ++i, ++j) {
		arr[i] = bucket[j];
	}
	//释放存储空间
	delete[] bucket;
	//对每个桶再次排序
	for (i = 0; i < radix; i++) {
		int p1 = begin + count[i]; //第I个桶的左边界
		int p2 = begin + count[i + 1] - 1; //第i个桶的右边界
		if (p1 < p2 && d < len) {	//p1<p2 1 个字符停止'a'
			msdradix_sort(p1, p2, d + 1);  //对第i个桶递归调⽤，进⾏基数排序，数位降 1  
		}
	}
}
int main() {
	// 从文件中读取数据
	char buf[50];
	FILE* input_file = fopen("input.txt", "r");

	while (fscanf(input_file, "%s", buf) != EOF) {
		printf("%s\n", buf);
		arr[length] = buf;
		if (len < arr[length].size())
			len = arr[length].size();
		length++;	//取了多少字符串
	}
	puts("");
	fclose(input_file);
	//for (int i = 0; i < size; i++) printf("%d ", arr[i]);
	puts("");
	msdradix_sort(0, length - 1, 0); // len表⽰最⾼位数	
				// 起始下标   下标	最左边开始

	// 将排序后的结果写入文件
	FILE* output_file = fopen("output.txt", "w");
	for (int i = 0; i < length; i++) {
		printf("%s\n", arr[i].c_str());
		fprintf(output_file, "%s\n", arr[i].c_str());
	}
	puts("");
	fclose(output_file);

}