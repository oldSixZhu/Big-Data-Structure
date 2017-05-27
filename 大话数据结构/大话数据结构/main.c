//
//  main.c
//  数据结构
//
//  Created by Mac on 2017/5/23.
//  Copyright © 2017年 oldSix. All rights reserved.
//


typedef int ELemType;

#include <stdio.h>

//函数声明
int ListLength(int L);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    ELemType a = 1;
    int b = ListLength(a);
    printf("%d\n",b);
    
    printf("Hello, World!\n");
    return 0;
}



int ListLength(int L){
    return L;
}
