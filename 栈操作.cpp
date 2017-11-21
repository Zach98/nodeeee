#include<malloc.h>  
#include<string.h>  
#include<stdio.h>  
  
#define OVERFLOW        -1  
#define STACK_INIT_SIZE 10  
#define STACKINCREMENT   2  
#define OK               1  
#define ERROR            0  
#define TRUE             1  
#define FALSE            0  
  
typedef int SElemType;  
typedef int Status;   
  
  
  
struct SqStack  
{  
    SElemType *base;  
    SElemType *top;  
    int stacksize;  
};  
  
Status InitStack(SqStack &S);  
Status DestoryStack(SqStack &S);  
Status ClearStack(SqStack &S);  
Status StackEmpty(SqStack S);  
int StackLength(SqStack S);  
Status GetTop(SqStack S, SElemType &e);  
Status Push(SqStack &S, SElemType e);  
Status Pop(SqStack &S, SElemType &e);  
Status StackTraverse(SqStack S, Status(*visit)());  
  
Status InitStack(SqStack &S)  
{  
    S.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));  
    if(!S.base) return OVERFLOW;  
    S.top = S.base;  
    S.stacksize = STACK_INIT_SIZE;  
    return OK;  
}  
  
Status DestoryStack(SqStack &S)  
{  
    free(S.base);  
    S.base = NULL;  
    S.top = NULL;  
    S.stacksize = 0;  
    return OK;  
}  
  
Status ClearStack(SqStack &S)  
{  
    S.top = S.base;  
    return OK;  
}  
  
Status StackEmpty(SqStack S)  
{  
    if(S.top == S.base)  
        return TRUE;  
    else  
        return FALSE;  
}  
  
int StackLength(SqStack S)  
{  
    return S.top - S.base;  
}  
  
Status GetTop(SqStack S,SElemType &e)  
{  
    if(S.top == S.base) return ERROR;  
    e = *(S.top -1);  
    return OK;  
}  
  
Status Push(SqStack &S, SElemType e)  
{  
    if(S.top - S.base >= S.stacksize)  
    {  
        S.base = (SElemType *)realloc(S.base,(S.stacksize + STACKINCREMENT)*sizeof(SElemType));  
        if(!S.base) return OVERFLOW;  
        S.top = S.base + S.stacksize;  
        S.stacksize += STACKINCREMENT;   
    }  
    *S.top++ = e;  
    return OK;  
}  
  
Status Pop(SqStack &S, SElemType &e)  
{  
    if(S.top == S.base) return ERROR;  
    e = * --S.top;  
    return OK;  
}  
  
Status StackTraverse(SqStack S, Status(* visit)(SElemType))  
{  
    while(S.top > S.base)  
        visit(*S.base++);  
    printf("\n");  
    return OK;  
}  
  
Status visit(SElemType e)  
{  
    printf("%d ", e);  
    return OK;  
}  
  
int main()  
{  
    SElemType j;  
    SqStack s;  
    SElemType e;  
  
    if(InitStack(s) == OK)  
        for(j = 1; j <= 12; j++)  
        {  
            Push(s,j);  
        }  
    printf("栈中的元素依次为：");  
    StackTraverse(s,visit);  
    Pop(s, e);  
    printf("弹出的栈顶元素 e=%d\n", e);  
    printf("栈空否：%d(1：是 0：否)\n", StackEmpty(s));  
    GetTop(s, e);  
    printf("栈顶元素 e=%d 栈的长度为%d\n", e, StackLength(s));  
    ClearStack(s);  
    printf("清栈后，栈空否：%d(1：空 0：否)\n",StackEmpty(s));  
    DestoryStack(s);  
    printf("销毁栈后，s.top = %u s.base= %u s.stacksize=%d\n",s.top,s.base,s.stacksize);  
    return 0;  
} 
