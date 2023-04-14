#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//�ȿ���������������һ������
void InserSort1(int* a, int n)
{
	int end;
	int tmp = a[end + 1];
	while (end >= 0)
	{
		if (tmp < a[end])
		{
			a[end + 1] = a[end];
			end--;
		}
		else
		{
			break;
		}
	}
	a[end + 1] = tmp;			//�ߵ���������� 1��end--�ߵ�ͷ���±꡾-1����˵����û�ҵ�����С����ô�Ҿ�����С��ֱ�ӻ�
								//				 2���ҵ���Ӧλ��ֱ���뵱ǰ�±꡾end+1����λ��	
}


//�Ѳ�������������ƣ�Ŀ���ǽ�
void InserSort2(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
			}
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;
	}
}

//˼·�����ݽ�
//1----�Ȱ������۳ɵ��ˣ���ǰ�����򣬰�����end+1���ֵѡ���滻ǰ���λ�ã������൱��end���ƣ���
//2----Ȼ�����ڿ������end,end�Ǵ�0��1��2��3��...n-2��һ��һ�������ȥ

//���������ʱ�临�Ӷȣ�O��n^2��
//�����
//���ţ�˳������/�ӽ�˳������

//----------------------------------------------------------------

//ϣ�����򣺶Բ���������иĽ�
//��һ����Ԥ���򣨽ӽ�˳������
//�ڶ�����ֱ�Ӳ�����������

//�������Ԥ��
//ϣ��������
void ShellSort1(int* a, int n)
{
	int gap;	//�Ȳ�����
	int end;	//�Ȳ�����
	int tmp = a[end + gap];
	while (end>=0)
	{
		if (tmp < a[end])
		{
			a[end + 1] = a[end];
			end-=gap;
		}
		else
		{
			break;
		}
	}
	a[end + gap] = tmp;
}

//������Ҫ����end(�±�)��ʵ��һ��(��gap������)���ݵĲ���

void ShellSort2(int* a, int n)
{
	int gap;		//�Ȳ�����
	for (int i = 0; i < n - gap; i += gap)
	{
		int end = i;
		int tmp = a[end + gap];
		while (end<=0)
		{
			if (tmp < a[end])
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			else 
			{
				break;
			}
		}
		a[end + gap] = tmp;
	}
}

//��Ȼ���Ѿ�������end[0]end[0+gap]....���Ϊgap��һ�飬��ô����ȥ����������ﵽ��������ȫ�����ݵļ�end[1]end[1+gap]....
//����   ��ʱ�����Ǽ���gap����3

void ShellSort2(int* a, int n)
{
	int gap = 3;

	for (int j = 0; j < n - gap; j++)		//Ҳֻ�ǿ�����һ������Ҳ�Ͷ�Ӧa[0]-->a[0+gap]-->a[0+gap*2]
																		//a[0],a[3],a[6]...ֱ������������С��n-gup(n-3)
	{
		for (int i = j; i < n - gap; i += gap)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end - gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}


//���������ǽ���һ���ܽ�
//����������Ҹ���gapԽ�󣬴�����ֿ��Ը���ĵ����棬С�������Ը���ĵ�ǰ�浫�ǲ����ӽ�����
//����������Ҹ���gapԽС��Խ�ӽ�����
//		��gap=1ʱ��Ҳ�����ҿ�ʼ�ᵽ�Ĳ�������

//�Ҿ��������д��ѭ���ǲ���̫����
//�õĽ��������Ƕ������иĽ���gap�����������n���

void ShellSort3(int* a, int n)
{
	int gap = n;
								
	while (gap > 1)
	{
		gap = n / 3 + 1;		//�����ҿ��Կ���ÿ��gap��ֵ�������+1��֤��gap����ȡ��0��
												//for (int i = 0; i < n - gap; i += gap){} ������������ѭ����ȥ���ˣ����
		for (int i = 0; i < n - gap; i++)		//�������ǲ����뵽��ÿ����һ�ˣ��ҵ�gepԽС���ҵ��������и�������
												//�ҵ������˵���ŵĸ��ӿ죬�������仰�Ŀ��Կ���ǰ����ܽ�,gap�����ݽ����������
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + 1] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}
