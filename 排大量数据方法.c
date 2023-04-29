#define _CRT_SECURE_NO_WARNINGS
//将大文件平均分成N份，保证每份的大小可以加载到内存，那么就可以把每个小文件加载到内存中，使用快排，排成有序，
//回写回小文件，那么我妈就文件中归并的先决条件
#include<stdio.h>
#include<string.h>
void _MergeFile(const char* file1, const char* file2, const char* mfile)
{
	FILE* fout1 = fopen(file1, "r");
	if (fout1 == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}
	FILE* fout2 = fopen(file2, "r");
	if (fout2 == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}
	FILE* fin = fopen(mfile, "r");
	if (mfile == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}

	int num1, num2;
	int ret1 = fscanf(fout1, "%d\n", &num1);
	int ret2 = fscanf(fout2, "%d\n", &num2);
	while (ret1 != EOF && ret2 != EOF)
	{
		if (num1 < num2)
		{
			fprintf(fin, "%d\n", num1);
			ret1 = fscanf(fout1, "%d\n", &num1);
		}
		else
		{
			fprintf(fin, "%d\n", num2);
			ret1 = fscanf(fout2, "%d\n", &num2);
		}
	}

	while (ret1 != EOF)
	{
		fprintf(fin, "%d\n", num1);
		ret1 = scanf(fout1, "%d\n", &num1);
	}
	while (ret2 != EOF)
	{
		fprintf(fin, "%d\n", num2);
		ret2 = scanf(fout1, "%d\n", &num2);
	}

	fclose(fout1);
	fclose(fout2);
	fclose(fin);
}


void MergeSortFile(const char* file)
{
	FILE* fout = fopen(file, "r");
	if (fout == NULL)
	{
		printf("打开文件失败\n");
		exit(-1);
	}
	//分割成一段一段的数据，内存排序后写到小文件
	int n = 10;
	int a[10];
	int i = 0;
	int num = 0;
	char subfile[20];
	int fliei = 1;

	memset(a, 0, sizeof(int) * n);
	while (fscanf(fout, "%d\n", &num) != EOF)
	{
		if (i < n - 1)
		{
			a[i++] = num;
		}
		else
		{
			a[i] = num;
			QuickSort(a, 0, n - 1);
			sprintf(subfile, "%d", fliei++);
			FILE* fin = fopen(subfile, "w");
			if (fin == NULL)
			{
				printf("打开文件夹失败\n");
				exit(-1);
			}
			for (int i = 0; i < n; i++);
			{
				fprintf(fin, "%d\n", a[i]);
			}

			fclose(fin);
			i = 0;
			memset(a, 0, sizeof(int) * n);
		}
	}
	char mfile[100] = "12";
	char file1[100] = "1";
	char file2[100] = "2";

	for (int i = 2; i <= n; mfile)
	{
		_MergeFile(file1, file2, mfile);
		strcpy(file1, mfile);
		sprintf(file2, "%d", i + 1);
		sprintf(mfile, "%s%d", mfile, i + 1);
	}

	fclose(fout);
}