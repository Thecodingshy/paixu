#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct pai 
{
    int huase;
    int manzhi;

} pai_t;

char HS[4][8] = { "梅花", "方块", "红心", "黑心" };
char MZ[13][3] = { "2", "3",  "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

void swap(pai_t* a, pai_t* b) 
{
    pai_t t = *a;
    *a = *b;
    *b = t;
}

void init(pai_t pai[]) 
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            pai[i * 13 + j].huase = i;
            pai[i * 13 + j].manzhi = j;
        }
    }
}

void upset(pai_t pai[]) 
{
    int r;
    srand(time(0));
    for (int i = 0; i < 51; i++) {
        int ii = i + 1;
        r = rand() % (51 - ii + 1) + ii;
        swap(&pai[i], &pai[r]);
    }
}

void print(pai_t pai[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        if (i == n - 1)
            printf("%s%s", HS[pai[i].huase], MZ[pai[i].manzhi]);
        else
            printf("%s%s->", HS[pai[i].huase], MZ[pai[i].manzhi]);
    }
    puts("");
}

void sort(pai_t pai[], int n) 
{
    int i, j, k, l;
    for (i = 0; i < n - 1; i++) 
    {
        k = i;
        for (j = i + 1; j < n; j++) 
        {
            if (pai[k].huase > pai[j].huase) 
            {
                k = j;
            }
        }
        if (k != i) 
        {
            swap(&pai[i], &pai[k]);
        }
    }

    int nums[4] = { 0 };

    for (i = 0; i < n; i++) 
    {
        nums[pai[i].huase]++;
    }
    print(pai, 15);


    pai_t* p = pai;
    for (l = 0; l < 4; l++) 
    {
        for (i = 0; i < nums[l] - 1; i++) 
        {
            k = i;
            for (j = i + 1; j < nums[l]; j++) 
            {
                if (p[k].manzhi > p[j].manzhi)
                {
                    k = j;
                }
            }
            if (k != i)
            {
                swap(&p[i], &p[k]);
            }
        }
        p += nums[l];
    }
}


int main() 
{
    pai_t pai[52];
    init(pai);
    upset(pai);
    print(pai, 15);

    sort(pai, 15);

    print(pai, 15);
}
