#include<stdio.h>
#include<stdlib.h>
#include<ctype.h> 
#define TRUE 1
#define FALSE 0
#define MAXLENGTH 30
//#define DEBUG

typedef struct{
    char data[MAXLENGTH];
    int top;
}operator_stack,*operator_stackptr;

typedef struct{
    int data[MAXLENGTH];
    int top;
}num_stack,*num_stackptr;

//This function is to return the priority of operator
int prior(char x)
{
    switch(x)
    {
        case '+':
        case '-': return 3;
        case '*':
        case '/': return 4;
        default:  exit(0);
    }
}

//this function is to calculate two num by a operator
int calcu_two_num(char operat,int x,int y)
{
    switch(operat)
    {
        case '*':
            return x*y;
        case '/':
            return x/y;
        case '-':
            return x-y;
        case '+':
            return x+y;

    }
}

void print_two_stack(operator_stackptr x,num_stackptr y)
{
        int i=0;
        if(x->top==-1)
            printf("The operator_stack is empty\n");
        else
        {
            printf("The operator stack is :\n");
            for(i=0;i<=x->top;i++)
                printf("%c-->",x->data[i]);
            printf("top\n");
        }
        if(y->top==-1)
            printf("The num stack is empty\n");
        else
        {
            printf("The num stack is :\n");
            for(i=0;i<=y->top;i++)
                printf("%d-->",y->data[i]);
            printf("top\n\n");
        }
}
int calcu_by_stack(char *x)
{
    //two operation number
    int num_1=0,num_2=0,result=0,i=0;
    char operator_1;
    //Create two stack
    operator_stack stack_op;
    num_stack stack_num;
    //Init the top pointer of these two stack
    stack_op.top=-1;
    stack_num.top=-1;

    if(x[i]=='(')
    {
        stack_op.data[++stack_op.top]='(';
        i++;
    }
    else
    {
        stack_num.data[++stack_num.top]=atoi(x);
        while(isdigit(x[++i]));
    }

    while(x[i]!='\0')
    {
        if(isdigit(x[i]))
        {
            stack_num.data[++stack_num.top]=atoi(&x[i]);
            while(isdigit(x[++i]));
        }

        else
        {
            if(x[i]=='(')
               stack_op.data[++stack_op.top]='(';
            else if(x[i]!=')')//When the operator is '+''-''*''/'
            {
                if(stack_op.top==-1)
                    stack_op.data[++stack_op.top]=x[i];
                else if(stack_op.data[stack_op.top]=='(')
                    stack_op.data[++stack_op.top]=x[i];
                else
                {
                    while(prior(x[i])<prior(stack_op.data[stack_op.top]))
                    {
                        num_1=stack_num.data[stack_num.top--];
                        num_2=stack_num.data[stack_num.top--];
                        result=calcu_two_num(stack_op.data[stack_op.top--],num_2,num_1);
                        stack_num.data[++stack_num.top]=result;
                        if(stack_op.top==-1)
                            break;
                    }
                    stack_op.data[++stack_op.top]=x[i];
                }
            }
            else//When the operator is ')'
            {
                while((operator_1=stack_op.data[stack_op.top--])!='(')
                {
                    num_1=stack_num.data[stack_num.top--];
                    num_2=stack_num.data[stack_num.top--];
                    stack_num.data[++stack_num.top]=calcu_two_num(operator_1,num_2,num_1);

                }

            }
            i++;
        }

	printf("the two stack is :\n");
  	print_two_stack(&stack_op,&stack_num);

    }

    while(stack_op.top!=-1&&stack_num.top!=0)
                {
                    operator_1=stack_op.data[stack_op.top--];
                    num_1=stack_num.data[stack_num.top--];
                    num_2=stack_num.data[stack_num.top--];
                    stack_num.data[++stack_num.top]=calcu_two_num(operator_1,num_2,num_1);

                }
	printf("The stack_num's top is %d\n\n",stack_num.top);

    return stack_num.data[stack_num.top--];

}


int main(void)
{
    char expression[MAXLENGTH];
    int i;

    printf("Enter a string:\n");
    scanf("%s",expression);

    i=calcu_by_stack(expression);
    printf("The i is %d\n\n",i);

    return 0;
}
