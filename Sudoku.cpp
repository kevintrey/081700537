#include<iostream> 
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
using namespace std;
 
/* ������ɱ�־ */
bool sign = false;
 
/* ������������ */
int num[9][9];
 
/* �������� */
void Input(int a,char *q);
void Output(int b,char *w);
bool Check(int n, int key,int c);
int DFS(int n,int d);
 
/*�ļ���*/ 
   ifstream file1;
   ofstream file2;
/* ������ */
int main(int argc, char * argv[])
{
    char *a;
    a=argv[6];
    char *b;
    b=argv[8];
	int m=atoi(argv[2]);
    Input(m,a);
    DFS(0,m);
    Output(m,b);
    system("pause");
}
 
/* ������������ */
void Input(int a,char *q)
{
	file1.open(q);
    char temp[a][a];
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            file1 >> temp[i][j];
            num[i][j] = temp[i][j] - '0';
        }
    }
}
 
/* ����������� */
void Output(int b,char *w)
{
	file2.open(w);
    cout << endl;
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < b; j++)
        {
            file2 << num[i][j] << " ";
        }
        file2<< endl;
    }
}
 
/* �ж�key����nʱ�Ƿ��������� */
bool Check(int n, int key,int c)
{
    /* �ж�n���ں����Ƿ�Ϸ� */
    for (int i = 0; i < c; i++)
    {
        /* jΪn������ */
        int j = n / c;
        if (num[j][i] == key) return false;
    }
 
    /* �ж�n���������Ƿ�Ϸ� */
    for (int i = 0; i < c; i++)
    {
        /* jΪn������ */
        int j = n % c;
        if (num[i][j] == key) return false;
    }
 
    /* xΪn���ڵ�С�Ź����󶥵������� */
    int x = n / 9 / 3 * 3;
 
    /* yΪn���ڵ�С�Ź����󶥵������ */
    int y = n % 9 / 3 * 3;
 
    /* �ж�n���ڵ�С�Ź����Ƿ�Ϸ� */
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (num[i][j] == key) return false;
        }
    }
 
    /* ȫ���Ϸ���������ȷ */
    return true;
}
 
/* ���ѹ������� */
int DFS(int n,int d)
{
    /* ���еĶ����ϣ��˳��ݹ� */
    if (n > 80)
    {
        sign = true;
        return 0;
    }
    /* ��ǰλ��Ϊ��ʱ���� */
    if (num[n/d][n%d] != 0)
    {
        DFS(n+1,d);
    }
    else
    {
        /* ����Ե�ǰλ����ö�ٲ��� */
        for (int i = 1; i <= d; i++)
        {
            /* ��������ʱ�������� */
            if (Check(n, i,d) == true)
            {
                num[n/d][n%d] = i;
                /* �������� */
                DFS(n+1,d);
                /* ����ʱ�������ɹ�����ֱ���˳� */
                if (sign == true) return 0;
                /* ������첻�ɹ�����ԭ��ǰλ */
                num[n/d][n%d] = 0;
            }
        }
    }
}
