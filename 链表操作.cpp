
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct Slist
{
	int data;
	struct Slist *next;
}SLIST;

SLIST *InitList_Sq()
{
	int a;
	SLIST *h, *s, *r;
	printf("输入-1以结束链表创建\n");
	h = (SLIST*)malloc(sizeof(SLIST));/*建立头指针*/
	r = h; 
	if(!h)
	{
		printf("分配失败");
		exit(0);
	}
	scanf("%d", &a);
	for( ; a != -1; )
	{
		s = (SLIST*)malloc(sizeof(SLIST));/*每次都开辟一个结点空间并赋值*/
		s->data = a;
		r->next = s;
		r = s;
		scanf("%d", &a);
	}
	r->next = '\0';
	return h;
}

void print_list(SLIST *finder)/*打印函数*/
{
	printf("head");
	while(finder)
	{
		printf("->%d",	finder->data);
		finder = finder->next;
	}
	printf("->end\n");
}

int DeleteNode(SLIST *killer)//删除节点函数
{
	int i, j = 0;
	SLIST *p, *q;
	int x;
	p = killer;
	q = killer->next;	
	printf("请输入您要删除的节点序号：");
	scanf("%d", &i);
	while((p->next) && (j < i - 1))
	{
		p = p->next;
		j ++;
		q = p->next;
	}
	if(p->next == '\0' || j > i - 1)
    {
		printf("\n error");
		return -1;
	}
	else
	{
		p->next = q->next;
		x = q->data;
		free(q);
		return x;
	}
}

void Insert_Node(SLIST *jumper)//插入函数，本算法为前插结点法
{
	int t, e, j = 0;
	SLIST *p, *q;
	p = jumper;
	printf("请输入要插入位置的序号：");
	scanf("%d", &t);
	printf("请输入要插入的元素：");
	scanf("%d", &e);
	while(p->next && j < t - 1)
	{
		j ++;
		p = p->next;
	}
	if(p == '\0' || j > t - 1) printf("插入的目的位置不存在\n");
	else
	{
		q = (SLIST*)malloc(sizeof(SLIST));
		q->data = e;
		q->next = p->next;
		p->next = q;
	}
}

void Locate_List(SLIST *reader)//查找值为e的元素
{
	int e, i = 0;
	SLIST *p;
	p = reader;
	printf("请输入要查找的元素：");
	scanf("%d", &e);
	while(p->next && p->data != e)
	{
		i ++;
		p = p->next;
	}
	if(p->data == e) printf("此元素在%d号位置\n", i);
	else printf("无此元素！\n");
}

void Menu();

void solve(int s)
{
	int o, y;
	SLIST *head;
	switch(s)
    {
		case 1:
		{
			head = InitList_Sq();
			print_list(head->next);
			printf("输入1以继续,输入0结束程序:");
			scanf("%d", &o);
			if(o){
				system("cls");
				Menu();
			}
			else return;
		}break;
        case 2:
		{
			head = InitList_Sq();
			print_list(head->next);
			Insert_Node(head);
			print_list(head->next);
			printf("输入1以继续,输入0结束程序:");
			scanf("%d", &o);
			if(o){
				system("cls");
				Menu();
			}
			else return;
		}break;
		case 3:
		{
			head = InitList_Sq();
			print_list(head->next);
			y = DeleteNode(head);
			print_list(head->next);
			if(y != -1)
			printf("被删除元素为：%d\n", y);
			printf("输入1以继续,输入0结束程序:");
			scanf("%d", &o);
			if(o){
				system("cls");
				Menu();
			}
			else return;
		}break;//头结点不算，从有数据的开始算第一个
		case 4:
		{
			head = InitList_Sq();
			print_list(head->next);
			Locate_List(head);
			printf("输入1以继续,输入0结束程序:");
			scanf("%d", &o);
			if(o){
				system("cls");
				Menu();
			}
			else return;
		}break;
	}
	return;
}

int main()
{
	system("COLOR f0");
	Menu();
	return 0;
}
void Menu()
{
    int k;
	printf("\n1.建立线性表");
	printf("\n2.在i位置插入元素e");
	printf("\n3.删除第i个元素，返回其值");
	printf("\n4.查找值为e的元素");
	printf("\n5.结束程序运行");
	printf("\n===================================================\n");
	printf("请输入您的选择：");
	scanf("%d", &k);
	return solve(k);
}

