#include <stdio.h>
#include <stdlib.h>
int scanN();
int scan(int*, int);
int print(int*, int);
int print2(int**, int, int);
int scan2(int**, int, int);
int** create2(int**, int, int);
void free2(int**, int);
void delete_line(int**, int, int);
int delete_lines(int**, int, int, int);
int sum_line(int*, int);

int main()
{
    int **a, **b, z, i, n1=scanN(),m1=scanN(),n2=scanN(),m2=scanN();
    a = create2(a, n1, m1);
    b = create2(b, n2, m2);
    scan2(a, n1, m1);
    scan2(b, n2, m2);
    print2(a, n1, m1);
    printf("\n");
    print2(b, n2, m2);
    printf("\n");
    z=delete_lines(a, n1, m1, 0);
    printf("%d line(s) was deleted\n\na\n",z);
    n1-=z;
    print2(a, n1, m1);
    z=delete_lines(b, n2, m2, 1);
    printf("\n%d line(s) was deleted\n\nb\n",z);
    n2-=z;
    print2(b, n2, m2);
    printf("\n");
    free2(a, n1);
    printf("\n");
    free2(b, n2);
    return 0;
}

int scanN()
{
    int n;
    do
        scanf("%d",&n);
    while (n<1);
    return n;
}

int scan(int* a, int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i] = rand()%100;
    return 0;
}

int print(int*a, int n)
{
    int i;
    if (n<1)
        return 0;
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
    if (n<1)
        return 0;
    for(i=0; i<n; i++)
        print(a[i], m);
    return 0;
}

int** create2(int**a, int n, int m)
{
    int i,j;
    a = malloc(n*sizeof(int*));
    if (a==NULL)
        return 0;
    for(i=0; i<n; i++)
    {
        a[i] = malloc(m*sizeof(int));
        if (a[i]==NULL)
        {
            for(j=0;j<i;j++)
                free(a[j]);
            free(a);
            return 0;
        };
    };
    return a;
}

void free2(int**a, int n)
{
    int i;
    for(i=0;i<n;i++)
        free(a[i]);
    free(a);
}

void delete_line(int**a, int n, int m)
{
    int i;
    free(a[n]);
    for(i=n; i<m-1; i++)
        a[i] = a[i+1];
}
int sum_line(int* a, int n)
{
    int i,s=0;
    for (i=0;i<n;i++)
        s+=a[i];
    return s;
}

int delete_lines(int**a, int n, int m, int p)
{
    int i,s,c=0;
    for(i=0; i<n; i++)
    {
        s=sum_line(a[i],m);
        if (s%2==p)
        {
            delete_line(a,i,n);
            c++;
            i--;
            n--;
        };
    };
    return c;
}


