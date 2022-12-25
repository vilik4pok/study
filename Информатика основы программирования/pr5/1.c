#include <stdio.h>
#include <stdlib.h>
#define L 10
#define N 3
#define C 4
int main()
{
    int scan(int*, int);
    int print(int*, int);
    int print2(int**, int, int);
    int scan2(int**, int, int);
    int** create2(int**, int, int);
    void sort(int*, int);
    void sort2(int**, int, int);
    void free2(int**, int);
    int M[L], **b;
    b=create2(b,N,C);
    scan(M,L);
    scan2(b,N,C);
    sort(M,L);
    sort2(b,N,C);
    print(M,L);
    print2(b,N,C);
    free2(b,N);
    return 0;
}

int scan(int* a, int n)
{
    int i;
    for(i=0; i<n; i++)
        scanf("%d", &a[i]);
    return 0;
}

int print(int*a, int n)
{
    int i;
    for(i=0; i<n; i++)
        printf("%3d ", a[i]);
    printf("\n");
    return 0;
}

int scan2(int** a, int n, int m)
{
    int i;
    for(i=0; i<n; i++)
        scan(a[i], m);
    return 0;
}

int print2(int**a, int n, int m)
{
    int i;
    for(i=0; i<n; i++)
        print(a[i], m);
    return 0;
}

int** create2(int**a, int n, int m)
{
    int i;
    a = malloc(n*sizeof(int*));
    if (a==NULL)
        return 0;
    for(i=0; i<n; i++)
    {
        a[i] = malloc(m*sizeof(int));
        if (a[i]==NULL)
        {
            for(;i>=0;i--)
                free(a[i]);
            free(a);
            return 0;
        };
    };
    return a;
}

void sort(int*a, int n)
{
    int i,j, tmp;
    for(i=n-1; i>0; i--)
        for(j=0; j<i; j++)
            if(a[j]<a[j+1])
            {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            };
}

void sort2(int**a, int n, int m)
{
    int i;
    for(i=0; i<n; i++)
        sort(a[i], m);
}

void free2(int**a, int n)
{
    int i;
    for(i=0;i<n;i++)
        free(a[i]);
    free(a);
}
