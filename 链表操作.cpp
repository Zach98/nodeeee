
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
	printf("����-1�Խ���������\n");
	h = (SLIST*)malloc(sizeof(SLIST));/*����ͷָ��*/
	r = h; 
	if(!h)
	{
		printf("����ʧ��");
		exit(0);
	}
	scanf("%d", &a);
	for( ; a != -1; )
	{
		s = (SLIST*)malloc(sizeof(SLIST));/*ÿ�ζ�����һ�����ռ䲢��ֵ*/
		s->data = a;
		r->next = s;
		r = s;
		scanf("%d", &a);
	}
	r->next = '\0';
	return h;
}

void print_list(SLIST *finder)/*��ӡ����*/
{
	printf("head");
	while(finder)
	{
		printf("->%d",	finder->data);
		finder = finder->next;
	}
	printf("->end\n");
}

int DeleteNode(SLIST *killer)//ɾ���ڵ㺯��
{
	int i, j = 0;
	SLIST *p, *q;
	int x;
	p = killer;
	q = killer->next;	
	printf("��������Ҫɾ���Ľڵ���ţ�");
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

void Insert_Node(SLIST *jumper)//���뺯�������㷨Ϊǰ���㷨
{
	int t, e, j = 0;
	SLIST *p, *q;
	p = jumper;
	printf("������Ҫ����λ�õ���ţ�");
	scanf("%d", &t);
	printf("������Ҫ�����Ԫ�أ�");
	scanf("%d", &e);
	while(p->next && j < t - 1)
	{
		j ++;
		p = p->next;
	}
	if(p == '\0' || j > t - 1) printf("�����Ŀ��λ�ò�����\n");
	else
	{
		q = (SLIST*)malloc(sizeof(SLIST));
		q->data = e;
		q->next = p->next;
		p->next = q;
	}
}

void Locate_List(SLIST *reader)//����ֵΪe��Ԫ��
{
	int e, i = 0;
	SLIST *p;
	p = reader;
	printf("������Ҫ���ҵ�Ԫ�أ�");
	scanf("%d", &e);
	while(p->next && p->data != e)
	{
		i ++;
		p = p->next;
	}
	if(p->data == e) printf("��Ԫ����%d��λ��\n", i);
	else printf("�޴�Ԫ�أ�\n");
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
			printf("����1�Լ���,����0��������:");
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
			printf("����1�Լ���,����0��������:");
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
			printf("��ɾ��Ԫ��Ϊ��%d\n", y);
			printf("����1�Լ���,����0��������:");
			scanf("%d", &o);
			if(o){
				system("cls");
				Menu();
			}
			else return;
		}break;//ͷ��㲻�㣬�������ݵĿ�ʼ���һ��
		case 4:
		{
			head = InitList_Sq();
			print_list(head->next);
			Locate_List(head);
			printf("����1�Լ���,����0��������:");
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
	printf("\n1.�������Ա�");
	printf("\n2.��iλ�ò���Ԫ��e");
	printf("\n3.ɾ����i��Ԫ�أ�������ֵ");
	printf("\n4.����ֵΪe��Ԫ��");
	printf("\n5.������������");
	printf("\n===================================================\n");
	printf("����������ѡ��");
	scanf("%d", &k);
	return solve(k);
}

