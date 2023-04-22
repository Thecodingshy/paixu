#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBERS  10000
int arr[MAX_NUMBERS];

int size = 0;
struct Node 
{
    int value;
    struct Node* next;
};
void radix_sort(int* A, int n) 
{
    int max = A[0];
    for (int i = 1; i < n; i++) 
    {
        if (max < A[i])
            max = A[i];
    }
    int maxL = (int)log10(max) + 1; //获取最大数字中的位数

    int k = pow(10, maxL - 1);
    struct Node* t[10]; // 桶
    int num[10] = { 0 };

    for (int i = 0; i < 10; i++) 
    {
        t[i] = NULL; // 将每个bucket初始化为空
    }

    for (int i = 0; i < n; i++) { // 将元素分配到桶中
        int m = (A[i] / k) % 10;
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->value = A[i];
        node->next = t[m];
        t[m] = node;
        num[m]++;
    }

    int c = 0;
    for (int i = 0; i < 10; i++) 
    { // 递归地对每个bucket进行排序
        struct Node* node = t[i];
        if (num[i] == 1) 
        { // 如果bucket只有一个元素，就把它取出来
            A[c++] = node->value;
            free(node);
        }
        else if (num[i] > 1) 
        { // 如果bucket有多个元素，则递归排序
            int* B = (int*)malloc(num[i] * sizeof(int));
            int j = 0;
            while (node != NULL) 
            {
                B[j++] = node->value;
                struct Node* temp = node;
                node = node->next;
                free(temp);
            }
            radix_sort(B, num[i]);
            for (int k = 0; k < num[i]; k++) 
            {
                A[c++] = B[k];
            }
            free(B);
        }
    }
}


int main() 
{
    // 从文件中读取数据
    FILE* input_file = fopen("input.txt", "r");

    if (!input_file)
    {
        puts("input.txt error");
        exit(-1);
    }


    while (fscanf(input_file, "%d", &arr[size]) != EOF) 
    {
        printf("%d ", arr[size]);
        size++;
    }
    puts("");
    fclose(input_file);

    radix_sort(arr, size);
    // 将排序后的结果写入文件
    FILE* output_file = fopen("output.txt", "w");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
        fprintf(output_file, "%d\n", arr[i]);
    }
    fclose(output_file);

    return 0;
}
