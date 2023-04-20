#define _CRT_SECURE_NO_WARNINGS
#include"Stack.h"
void Swap(int* a, int* b)
{
	int* tmp = *a;
	*a = *b;
	*b = tmp;
}
//�����д���ǵ���Hoareԭ����д����Ҳ���������ȽϾ����д��
//ֻҪ��ס�����key�ұ����������С��key,�ұ��Ҵ���key
//��֤����λ�õ�ֵ��key��ֵС�����߾���key��λ��
void QuickSort1(int* a, int begin, int end)
{
	if (begin >= end)	//  �����>����Ϊ�õݹ������Ϊ�գ������=����Ϊ�ݹ鵽ֻ��һ������ʱ��
	{
		return;			//����ֱ�ӷ��ص�����ջ֡����һ��
	}
	int left = begin;
	int right = end;
	int keyi = left;

	//����򵥷���һ��ΪʲôҪ�ұ�����
	//�޷Ƿ��������
	//1��R���ߣ�Rͣ������Lȥ����R��
	//	����λ�þ���Rͣ��λ��Rλ�þ��Ǳ�keyiҪС��λ�ã�
	//2��R���ߣ�Rû���ҵ���keyҪС��ֵRȥ������L��
	//	 ����λ�þ���L��һ��ͣ�µ�λ�ã�����key��λ��Ҫô��keyС

	while (left<right)								//һ����������������left<right,
	{
		while (left < right && a[right] >= a[keyi])	//���������С���ҵ���ͣ��
		{
			right--;
		}
		while (left < right && a[left] <= a[keyi])	//��ȥ�ұ��Ҵ��ҵ���ͣ��
		{
			left++;
		}	
		Swap(&a[left], &a[right]);					//�����ո��ҵ���λ�õ�ֵ
	}
	Swap(&a[keyi], &a[left]);
	keyi = left;

	//�����ҿ��Ƶ��Ǳ�������������д		
	//[begin,keyi-1] keyi [keyi+1,end]

	QuickSort(a, begin, keyi-1);				//�ݹ���������
	QuickSort(a, keyi + 1, end);
}



//��������Ƚ��鷳������һ���ڿӷ������ַ����Ƚ�ͨ���׶�
int PartSort2(int* a, int begin, int end)
{
	int key = a[begin];
	int piti = begin;
	while (begin < end)
	{
		//�ұ���С���ҵ�������ߵĿ�����λ���γ��µĿ�
		while (begin < end && a[end] >= key)  
		{
			end--;
		}

		a[piti] = a[end];	//��ֵ
		piti = end;			//���±�
		//����Ҵ��ҵ������ұߵĿ�����λ���γ��µĿ�
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}

		a[piti] = a[begin];	//��ֵ
		piti = begin;		//���±�
	}
}



//����ǰ���ַ�����û�дӱ����϶����������е���
//������Ҫ���ܵ���ǰ��ָ�뷨
void QuickSort3(int* a, int begin, int end)
{
	int prev = begin;
	int cur = begin + 1;
	int keyi = begin;
	while(cur <= end)
	{
		if (a[cur] < a[keyi] && ++prev != cur)		//&&����Ҳ��һ���жϣ���ǰ����ж���ȷ��prevֱ��++
			Swap(&a[prev], &a[cur]);				//��cur==prev ʡȥ���Լ����Լ�����
		cur++;										//������ĩ�䣬��curҪһֱ��ǰ��
	}
	///while (cur <= end)
	//{
	//	if (a[cur] < a[keyi])
	//		{
	//		  prev++;								//��ͷ����ո�����д������
	//		  Swap(&a[prev],&a[cur]);	
	//		}
	//	cur++;
	//}
	Swap(&a[prev], &a[keyi]);
	return keyi;
}
//��������һ������Ͼ����������д������Ĭ��ȡ�����һ��ֵΪkey������һ������
//�����ԭ����������߽ӽ�������ʱ������Ч�����
//N+(N-1)+(N-2)+(N-3)+....+3+2+1
//O(N^2)
//������һ������������������ܴ�����ջ�������ʹ��release�汾���ܳŵ�ס����Ϊ�����治�ŵ�����Ϣ������һ�����ֻ�����һ���Ӵ�Ͳ����ˣ�

//�������Ǿ�������������key��ѡȡ�����ֽ�
//��һ�ַ���:ѡȡ���������������Ϊkey��������λ�ú�keyλ�õ���������ȱ���ǲ��ȶ�
//�ڶ��ַ���:������ȡ�С�
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
	else     //�൱��a[begin] >= a[midi]
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


//�Ƿ���Խ�һ���Ż������㷨�أ������������ѷ��ֺ��涼��ͨ��QuickSort(a,begin,key-1);QuickSort(a,key+1,end)�ݹ���ʵ��
//���ǡ��ݹ����Ѩ��----�ݹ�̫���ʱ���ջ���
//ջ��һ���СΪ8MB����
//�෴����һ��ܴ�

//��ʱ�����ǵ�˼·��
//ֱ�Ӹ�ѭ��----����쳲���ϵ���У��鲢����
//�����ݽṹջ��ģ��ʵ�ֵݹ�Ĺ���
void QuickSortNonR(int* a, int begin, int end)
{
	ST st;
	StackInit(&st);
	StackPush(&st, end);	//�����ұ�
	StackPush(&st, begin);	//�������
	while (!StackEmpty)
	{
		int left = StackTop(&st);	
		StackPop(&st);

		int right = StackTop(&st);	
		StackPop(&st);

		int keyi = PartSort2(a, left, right);	//������ķ�����һ�˵�key

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