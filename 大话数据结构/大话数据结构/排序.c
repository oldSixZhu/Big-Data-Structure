////
////  排序.c
//  大话数据结构
//
//  Created by Mac on 2017/6/15.
//  Copyright © 2017年 oldSix. All rights reserved.
//
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_LENGTH_INSERT_SORT 7 /* 用于快速排序时判断是否选用插入排序阙值 */

typedef int Status;


#define MAXSIZE 10000  /* 用于要排序数组个数最大值，可根据需要修改 */
typedef struct
{
    int r[MAXSIZE+1];	/* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
    int length;			/* 用于记录顺序表的长度 */
}SqList;

#include <stdio.h>

//冒泡排序,两两比较相邻的数据,如果反序则交换,直到没有反序的记录
//改进冒泡排序
//在性能上有一些提升,避免因已经有序的情况下的无意义循环判断
void maoPao(SqList *L){
    Status flag = TRUE;
    //若flag为true则退出循环
    for (int i = 1; i < L->length && flag; i++)
    {
        flag = FALSE;
        for (int j = L->length - 1; j >= 1; j--)
        {
            if (L->r[j] > L->r[j+1])
            {
                int temp = L->r[i];
                L->r[i] = L->r[j];
                L->r[j] = temp;
                flag = TRUE;
            }
        }
    }
}

//选择排序
//通过n-i次关键字间的比较,从n-i+1个数据中选出关键字最小的数据,并和第i(1<=i<=n)个数据交换
void xuanZe(SqList *L){
    int min;
    for (int i = 1; i < L->length; i++)
    {
        //将当前下标定义为最小值下标
        min = i;
        //循环当前下标之后的所有数据
        for (int j = i+1; j <= L->length; j++)
        {
            //j=2 L[1]>L[2] 9>1
            //min=2
            //j=3 L[2]>L[3] 1>5
            //min不变,还是2
            if (L->r[min] > L->r[j])
            {
                min = j;
            }
        }
        //全比较过后,交换值
        if (i != min)
        {
            int temp=L->r[i];
            L->r[i]=L->r[min];
            L->r[min]=temp;
        }
    }
}


//直接插入排序
//将一个数据插入到已经排好序的有序表中,得到一个新的有序表
//r[6] = {0,5,3,4,6,2}
void chaRu(SqList *L){
    int i,j;
    for (i = 2; i < L->length; i++)
    {
        //i=2,053462,3<5
        //i=3,035462,4<5接着执行
        if (L->r[i] < L->r[i-1])
        {
            //设置哨兵
            //r0 = 3
            L->r[0] = L->r[i];
            //j=1 5>3成立,走循环体
            //j=0 3>3不成立,出循环,此时j为0
            for (j=i-1; L->r[j] > L->r[0]; j--)
            {
                //r2=5
                L->r[j+1] = L->r[j];
            }
            //r1=3
            L->r[j+1] = L->r[0];
        }
    }
}

//希尔排序
//实际上是优化的直接插入排序,采取跳跃分割的策略,将相距某个"增量"的记录组成一个子序列,保证子序列内分别进行直接插入排序结果基本有序(大的基本在后面)
//时间复杂度为O(n³/2),比O(n²)要好点
void xiEr(SqList *L){
    int i,j;
    int zeng = L->length;
    do{
        //增量序列
        zeng = zeng/3 + 1;
        //分段排序,与直接插入排序相同
        for (i = zeng+1; i <= L->length; i++)
        {
            //判断是否交换
            if (L->r[i] < L->r[i-zeng])
            {
                L->r[0] = L->r[i];
                for (j = i-zeng; j>0 && L->r[j] > L->r[0]; j-=zeng)
                {
                    L->r[j+zeng] = L->r[j];
                }
                L->r[j+zeng] = L->r[0];
            }
        }
    //增量为1时,停止循环
    } while (zeng > 1);
}


//堆排序
//对简单选择排序进行的一种改造,时间复杂度为O(nlogn),比冒泡,选择,插入的O(n²)好很多
//堆是一种近似完全二叉树:利用完全二叉树的深度是(log2n)+1的特性
//每个结点的值都大于或等于左右孩子结点的值,为大顶堆
//每个结点的值都小于或等于左右孩子结点的值,为小顶堆
//将待排序的序列构造成一个大顶堆,整个序列的最大值就是堆顶的根结点,将它移走,然后将剩余的n-1个序列重新构造成一个大顶堆,反复执行
//就是将堆数组的根结点与末尾元素交换,末尾元素就变成最大值了

//将数组调整为大顶堆
void daDingDui(SqList *L,int s,int m);
void dui(SqList *L){
    int i;
    //把有子节点的结点调整成大顶堆
    for (i = L->length/2 ; i>0 ; i--)
    {
        daDingDui(L, i, L->length);
    }
    for (i = L->length; i>1 ; i--)
    {
        //将堆顶数据和当前未经排序子序列的最后一个数据交换
        //把最大值换到尾巴处
        int temp=L->r[i];
        L->r[i]=L->r[1];
        L->r[1]=temp;
        //排除最后一个最大数据,再重新调整成大顶堆
        daDingDui(L, 1, i-1);
    }
}

void daDingDui(SqList *L,int s,int m){
    int temp,j;
    temp= L->r[s];
    //沿关键字较大的孩子结点向下筛选
    //根据完全二叉树的按层序递增排列特点
    //从j=2s开始,j=m结束
    for (j=2*s ; j<=m ; j*=2)
    {
        //j为左孩子下标,j+1为右孩子下标,找出最大的
        if (j<m && L->r[j] < L->r[j+1])
        {
            ++j;
        }
        //比较根结点大小
        if (temp >= L->r[j])
        {
            break;
        }
        //把最大值给根结点
        L->r[s] = L->r[j];
        s = j;
    }
    //把刚开始保存的较小值给子结点
    L->r[s] = temp;
}


//归并排序
//归并--将两个或两个以上的有序表组合成一个新的有序表
//2路归并排序:n个数据,两两归并,直到得到一个长度为n的有序序列
void guiBing(SqList *L){
    
}

























