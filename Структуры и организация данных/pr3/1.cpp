//Порядок:  по  возрастанию  элементов.  Методы: выбора,  пузырька,
//пирамидальная сортировка, быстрая  сортировка.
//N1=10000, N2=30000, N3=70000, N4=100000.
//Критерий – количество присваиваний.
#include <iostream>
#include <math.h>
#include <fstream>
#include <locale.h>
#include <chrono>
#include <cstring>
#define N1 10000
#define N2 30000
#define N3 70000
#define N4 100000

using namespace std;
using namespace chrono;

void StraightSelection (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3);
void BubbleSort (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3);
void HeapSort (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3);
int sift (int *a, int L, int R);
void NonRecursiveQuickSort (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3);
void (*f[4])(int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3) = {StraightSelection, BubbleSort, HeapSort, NonRecursiveQuickSort};
void Sort4(int **a, int n, const char* arrtype)
{
    unsigned long long k1, k2;
    int memory;
    high_resolution_clock time = high_resolution_clock();
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    duration<double> time_span;
    char c[4][30] = {"Метод выбора", "Пузырек", "Пирамидальная сортировка", "Быстрая сортировка"};
    for(int i=0; i<4; i++)
    {
        k1 = k2 = memory = 0;
        t1 = time.now();
        f[i](a[i], n, &k1, &k2, &memory);
        t2 = time.now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        printf("%-20s|%6d|%-30s|%-11llu + %-11llu = %-11llu|%10d|%10lf|\n", arrtype, n, c[i], k1, k2, k1+k2, memory, time_span.count());
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
}


int main(int argc, char* files[])
{
    int i,j, num, tmp;
    int ***a = new int**[4];
    char filename[80];
    setlocale(LC_ALL, "rus");
    if(argc<2)
    {
        cout << "Имя файла:";
        cin.getline(filename, 80);
    }
    else
        strcpy(filename,files[1]);
    fstream f(filename);
    if(!f.is_open())
    {
        cout<<"Не удалось открыть файл";
        return -1;
    };

    for(i = 0; i<4; i++)
        a[i] = new int*[4];
    for(i = 0; i<4; i++)
    {
        a[0][i] = new int[N1];
        a[1][i] = new int[N2];
        a[2][i] = new int[N3];
        a[3][i] = new int[N4];
    };

    for(i=0; i<N4; i++)
    {
        f>>num;
        for(j=0; j<4; j++)
        {
            if(i<N1)
                a[0][j][i] = num;
            if(i<N2)
                a[1][j][i] = num;
            if(i<N3)
                a[2][j][i] = num;
            a[3][j][i] = num;
        };
    };
    f.close();
    printf("%-20s|%-6s|%-30s|%-33s|%-10s|%-10s|\n", "Массив", "N", "Сортировка", "Кол-во основых присв. + вспомогательных", "Память", "Время");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    Sort4(a[0], N1, "Неупорядоченный");
    Sort4(a[1], N2, "Неупорядоченный");
    Sort4(a[2], N3, "Неупорядоченный");
    Sort4(a[3], N4, "Неупорядоченный");

    Sort4(a[0], N1, "Упорядоченный");
    Sort4(a[1], N2, "Упорядоченный");
    Sort4(a[2], N3, "Упорядоченный");
    Sort4(a[3], N4, "Упорядоченный");

    for(i=0; i<N4/2; i++)
    {
        tmp = a[3][0][i];
        for(j=0; j<4; j++)
        {
            if(i<N1/2)
                a[0][j][i] = a[0][j][N1-i-1], a[0][j][N1-i-1] = tmp;
            if(i<N2/2)
                a[1][j][i] = a[1][j][N2-i-1], a[1][j][N2-i-1] = tmp;
            if(i<N3/2)
                a[2][j][i] = a[2][j][N3-i-1], a[2][j][N3-i-1] = tmp;
            a[3][j][i] = a[3][j][N4-i-1], a[3][j][N4-i-1] = tmp;
        }
    };

    Sort4(a[0], N1, "В обратном порядке");
    Sort4(a[1], N2, "В обратном порядке");
    Sort4(a[2], N3, "В обратном порядке");
    Sort4(a[3], N4, "В обратном порядке");
    for(i =0; i<4; i++)
    {
        for(j=0; j<4; j++)
            delete [] a[i][j];
        delete[] a[i];
    };
    delete[] a;

    return 0;
}


void StraightSelection (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3)
{
	int i, j, tmp, *min;
    *p3 = 3*sizeof(int)+sizeof(int*);
	*p2 = 1;
	for (i=0; i<n-1; i++)
	{
		min = a+i;
		for (j=i+1; j<n; j++)
			if (a[j]<*min)
            {
                min = a+j;
                *p2+=1;
            };
		tmp = *min;
        *min = a[i];
		a[i] = tmp;
		*p1 += 3;
		*p2 +=3+n-1-i;
	}
}


void BubbleSort (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3)
{
	int i, j, x;
    *p3 += 3*sizeof(int);
	*p2 += 1;
	for (i=1; i<n; i++)
	{
		for (j=n-1; j>=i; j--)
        {
            if (a[j-1]>a[j])
			{
				x = a[j-1];
				a[j-1] = a[j];
				a[j] = x;
				*p1+=3;
			}
        }
        *p2+=2+n-i;
    }
}

void sift (int *a, int L, int R, unsigned long long *p1, unsigned long long *p2, int *p3)
{
	int i = L, j = 2*L+1, x = a[L];
    *p1+=1;
    *p2+=2;
    *p3+=3*sizeof(int);
	if (j<R && a[j+1]>a[j])
        j++,*p2+=1;
	while (j<=R && a[j]>x)
	{
		a[i] = a[j];
		i = j;
		j = 2*j + 1;
		*p1+=1;
		*p2+=2;
		if (j<R && a[j+1]>a[j])
            j++,*p2+=1;
	}
	a[i] = x;
	*p1+=1;
}


void HeapSort (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3)
{
	int L = n/2, R=n-1, x;
    *p3 += 3*sizeof(int);
	*p2 += 2;
	while (L>0)
    {
        sift (a, --L, R, p1, p2, p3);
        *p2+=1;
    }
	while (R>0)
	{
		x = a[0];
		a[0] = a[R];
		a[R] = x;
        sift (a, L, --R, p1, p2, p3);
        *p2+=1;
		*p1+=3;
	}
}

void NonRecursiveQuickSort (int *a, int n, unsigned long long *p1, unsigned long long *p2, int *p3)
{
	const int M=log(n)/log(2)+1;
	int i, j, left, right, s, x, w;
    *p3 += 8*sizeof(int);
	*p2 += 1;
	struct stack {int left, right;} *stack;
	stack = new struct stack[M];
	*p3+=sizeof(int*)+M*sizeof(struct stack);
	s = 0;
	stack[0].left = 0;
	stack[0].right = n-1;
	*p2+=4;
	do
	{
		left = stack[s].left;
		right = stack[s].right;
		s--;
		*p2+=3;
		do
		{
			i = left; j = right;
			x = a[(left+right)/2];
			*p1+=1;
			*p2+=2;
			do
			{
				while (a[i]<x) i++,*p2+=1;
				while (x<a[j]) j--,*p2+=1;
				if (i<=j)
				{
					w = a[i]; a[i] = a[j]; a[j] = w;
					i++; j--;
					*p1+=3;
					*p2+=2;
				}
			}
			while (i<j);
			if (i<right && right-i>=j-left)
			{
				s++;
				stack[s].left = i;
				stack[s].right = right;
				right = j;
				*p2+=4;
			}
			else if (j>left && j-left>right-i)
			{
				s++;
				stack[s].left = left;
				stack[s].right = j;
				left = i;
				*p2+=4;
			}
			else left = right, *p2+=1;
		}
		while (left<right);
	}
	while (s>-1);
	delete [] stack;
}
