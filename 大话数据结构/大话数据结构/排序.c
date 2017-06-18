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
//总的时间复杂度为O(nlogn),空间复杂度为O(n+logn)
//比较占用内存,但是稳定,效率高

//归并函数
void realGuiBing(int SR[],int TR1[],int s,int t);
//排序函数
void Merge(int SR[],int TR[],int s,int m,int t);

//调用归并函数
void guiBing(SqList *L){
    realGuiBing(L->r,L->r,1,L->length);
}

//递归函数,将 SR[s...t] 归并排序为 TR1[s...t]
void realGuiBing(int SR[],int TR1[],int s,int t){
    int m;
    int TR2[MAXSIZE +1];
    //相等就不用排序了
    if (s == t)
    {
        TR1[s] = SR[s];
    }
    else
    {
        //将SR[s...t]平分为SR[s...m]和SR[m+1...t]
        m = (s+t)/2;
        //递归将SR[s...m]归并为有序的TR2[s...m]
        realGuiBing(SR,TR2,s,m);
        //递归将SR[m+1...t]归并为有序的TR2[m+1...t]
        realGuiBing(SR,TR2,m+1,t);
        //将TR2[s...m]和TR2[m+1...t]归并到TR1[s...t]
        Merge(TR2,TR1,s,m,t);
    }
}

//关键函数,排序并合并
//将有序的SR[i...m] 和 SR[m+1...n]归并为有序的TR[i...n]
void Merge(int SR[],int TR[],int s,int m,int t){
    int j,k,l;
    //将SR中数据由小到大归并入TR
    for (j = m+1, k = s; s <= m && j <= t; k++)
    {
        if (SR[s] < SR[j])
        {
            TR[k] = SR[s++];
        }
        else
        {
            TR[k] = SR[j++];
        }
    }
    //将剩余的SR[s...m]复制到TR
    if (s <= m)
    {
        for (l = 0; l <= m-s; l++)
        {
            TR[k+1] = SR[s+1];
        }
    }
    //将剩余的SR[j...t]复制到TR
    if (j <= t)
    {
        for (l = 0; l < t-j; l++)
        {
            TR[k+1] = SR[j+1];
        }
    }
}

//----------------------
//优化归并排序,非递归实现
//非递归增加的函数
void MergeAdd(int SR[], int TR[],int s,int n);
//归并排序
void guiBing2(SqList *L){
    //申请内存空间
    int *TR = (int *)malloc(L->length *sizeof(int));
    int k = 1;
    while (k < L->length)
    {
        MergeAdd(L->r, TR, k, L->length);
        //子序列长度加倍
        k = 2*k;
        MergeAdd(TR, L->r, k, L->length);
        //加倍
        k = 2*k;
    }
}

void MergeAdd(int SR[], int TR[],int s,int n){
    int i = 1;
    int j;
    while (i <= n - 2 * s + 1)
    {
        //两两归并
        Merge(SR, TR, i, i + s - 1, i + 2 *s -1);
        i = i +2 *s;
    }
    //归并最后两个序列
    if (i < n-s+1)
    {
        Merge(SR, TR, i, i+s-1, n);
    }
    //剩下的单数直接并入
    else
    {
        for (j = i; j <= n; j++)
        {
            TR[j] = SR[j];
        }
    }
}

//希尔排序为直接插入排序的升级,属于插入排序类
//堆排序为简单选择排序的升级,属于选择排序类
//快速排序为冒泡排序的升级,属于交换排序类

//快速排序
//通过一趟排序将待排数据分割成独立的两部分,其中一部分key均比另一部分key小,分别对这两部分记录继续排序,最终完成排序
//时间复杂度平均为O(nlogn)

//快速排序
void realKuaiSu(SqList *L,int low,int high);
//找到枢轴值
int fenKai(SqList *L ,int low,int high);
//调用快速排序
void kuaiSu(SqList *L){
    realKuaiSu(L,1,L->length);
}
//快速排序
void realKuaiSu(SqList *L,int low,int high){
    int pivot;
    if (low < high)
    {
        //将L->r[low...high]一分为二,算出枢轴值pivot
        pivot = fenKai(L,low,high);
        //对低子表递归排序
        realKuaiSu(L,low,pivot-1);
        //对高子表递归排序
        realKuaiSu(L,pivot+1,high);
    }
}

//找到枢轴值,交换顺序表L中子表的数据
//将选取的枢轴值不断变换,将比它小的换到它的左边,比它大的换到它的右边,它也在交换中不断更改自己的位置,直到完全满足这个要求为止
int fenKai(SqList *L ,int low,int high){
    int pivotkey;
    //用子表的第一个数据做枢轴数据
    pivotkey = L -> r[low];
    //从表的两端交替向中间扫描
    while (low < high)
    {
        //比枢轴数据小的数据交换到低端
        while (low < high && L->r[high] >= pivotkey)
        {
            high--;
            int temp=L->r[low];
            L->r[low]=L->r[high];
            L->r[high]=temp;
        }
        //将比枢轴大的数据交换到高端
        while (low < high && L->r[low] <= pivotkey)
        {
            low++;
            int temp=L->r[low];
            L->r[low]=L->r[high];
            L->r[high]=temp;
        }
    }
    return low;
}

//快速排序优化
//1.选取枢轴pivotkey的优化
//三数取中法:取左,中,右三个数据先排序,将中间数作为枢轴
//九数取中法
int getPivotkey(SqList *L,int high,int low){
    int pivotkey;
    //计算数组中间元素的下标
    int m = low + (high - low)/2;
    //交换左右端数据,保证左端较小
    if (L->r[low] > L->r[high])
    {
        int temp=L->r[low];
        L->r[low]=L->r[high];
        L->r[high]=temp;
    }
    //交换中间与右端数据,保证中间较小
    if (L->r[m] > L->r[high])
    {
        int temp=L->r[m];
        L->r[m]=L->r[high];
        L->r[high]=temp;
    }
    //交换中间与左端数据,保证左端较小
    if (L->r[m] > L->r[low])
    {
        int temp=L->r[m];
        L->r[m]=L->r[low];
        L->r[low]=temp;
    }
    //L.r[row]为三个关键字中间值
    pivotkey = L->r[low];
    return pivotkey;
}

//2.优化不必要的交换
int youHuaKuaiSu(SqList *L,int low,int high){
    //取到枢轴
    int pivotkey = getPivotkey(L, high, low);
    //将枢轴备份
    L->r[0] = pivotkey;
    //从表的两端交替向中间扫描
    while (low < high)
    {
        //比枢轴数据小的数据交换到低端
        while (low < high && L->r[high] >= pivotkey)
        {
            high--;
            //采用替换不是交换
            L->r[low] = L->r[high];
        }
        //将比枢轴大的数据交换到高端
        while (low < high && L->r[low] <= pivotkey)
        {
            low++;
            //采用替换不是交换
            L->r[high] = L->r[low];
        }
    }
    //将枢轴数值替换回L.r[low]
    L->r[low] = L->r[0];
    //返回枢轴所在位置
    return low;
}

//因为递归的使用,非常大的数组用快速排序,直接插入排序是简单排序中性能最好的



























