#include<iostream> 
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
using namespace std;
 
/* 构造完成标志 */
bool sign = false;
 
/* 创建数独矩阵 */
int num[9][9];
 
/* 函数声明 */
void Input(int a,char *q);
void Output(int b,char *w);
bool Check(int n, int key,int c);
int DFS(int n,int d);
 
/*文件流*/ 
   ifstream file1;
   ofstream file2;
/* 主函数 */
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
 
/* 读入数独矩阵 */
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
 
/* 输出数独矩阵 */
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
 
/* 判断key填入n时是否满足条件 */
bool Check(int n, int key,int c)
{
    /* 判断n所在横列是否合法 */
    for (int i = 0; i < c; i++)
    {
        /* j为n竖坐标 */
        int j = n / c;
        if (num[j][i] == key) return false;
    }
 
    /* 判断n所在竖列是否合法 */
    for (int i = 0; i < c; i++)
    {
        /* j为n横坐标 */
        int j = n % c;
        if (num[i][j] == key) return false;
    }
 
    /* x为n所在的小九宫格左顶点竖坐标 */
    int x = n / 9 / 3 * 3;
 
    /* y为n所在的小九宫格左顶点横坐标 */
    int y = n % 9 / 3 * 3;
 
    /* 判断n所在的小九宫格是否合法 */
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (num[i][j] == key) return false;
        }
    }
 
    /* 全部合法，返回正确 */
    return true;
}
 
/* 深搜构造数独 */
int DFS(int n,int d)
{
    /* 所有的都符合，退出递归 */
    if (n > 80)
    {
        sign = true;
        return 0;
    }
    /* 当前位不为空时跳过 */
    if (num[n/d][n%d] != 0)
    {
        DFS(n+1,d);
    }
    else
    {
        /* 否则对当前位进行枚举测试 */
        for (int i = 1; i <= d; i++)
        {
            /* 满足条件时填入数字 */
            if (Check(n, i,d) == true)
            {
                num[n/d][n%d] = i;
                /* 继续搜索 */
                DFS(n+1,d);
                /* 返回时如果构造成功，则直接退出 */
                if (sign == true) return 0;
                /* 如果构造不成功，还原当前位 */
                num[n/d][n%d] = 0;
            }
        }
    }
}
