#include<stdio.h>  
#include<stdlib.h>  
#include<malloc.h>  
#define OK 1  
#define FLASE 0  
#define OVERFLOW -1  
typedef int Status;   
  
typedef struct {  
    float coef; //ϵ��  
    int expn;  //ָ��  
}ElemType, Term;  
  
typedef struct {  
    Term *elem;  //�洢�ռ��ַ  
    int length;  //����  
}Poly;  
  
//����һԪϡ�����ʽ  
Status CreatePoly(Poly &P, Term e[], int n) {  
    int i;  
    P.elem = (Term*)malloc(sizeof(Term)*n);  
    if (NULL == P.elem) return OVERFLOW;  
    for (i = 0; i < n; i++) P.elem[i] = e[i];  
    P.length = n;  
    return OK;  
}  
  
  
//����һԪϡ�����ʽP  
Status DestroyPoly(Poly &P) {  
    if (P.elem == NULL)  
        return OVERFLOW;  
    else  
        free(P.elem);  
    printf("\n���ٳɹ�\n");  
    return OK;  
}  
  
//��ӡ���һԪϡ�����ʽP  
Status PrintPoly(Poly P) {  
    int i;  
    printf("����ʽ:");  
    for (i = 0; i < P.length; i++) {  
        if (i == P.length - 1)  
            printf("%4.2fx^%d\n", P.elem[i].coef, P.elem[i].expn);  
        else  
            printf("%4.2fx^%d + ", P.elem[i].coef, P.elem[i].expn);  
          
    }  
    return OK;  
}  
  
//һԪϡ�����ʽP���ڣ��򷵻�P�е�����  
int PolyLength(Poly P) {  
    return P.length;  
}  
  
//ʵ��һԪϡ�����ʽ�ӷ�  
Status AddPoly(Poly pa, Poly pb, Poly &pc) {//����һԪϡ�����ʽ���ӷ�����pc=pa+pb  
    int i = 0, j = 0, k = 0;  
    float c;  
    pc.elem = (Term*)malloc((pa.length + pb.length) * sizeof(Term));  
    if (NULL == pc.elem) return OVERFLOW;  
    while (i < pa.length&&j < pb.length) {//��������ʽ��δ�������  
        if (pa.elem[i].expn < pb.elem[j].expn)//pa���ָ����С�����pc  
            pc.elem[k++] = pa.elem[i++];  
        else if (pa.elem[i].expn > pb.elem[j].expn)//pb���ָ����С����ӵ�pc  
            pc.elem[k++] = pb.elem[j++];  
        else {//pa��pbָ�����  
            c = pa.elem[i].coef + pb.elem[j].coef;//ϵ�����  
            if (c != 0) {//ϵ���Ͳ�Ϊ0�������������ӵ�pc  
                pc.elem[k].expn = pa.elem[i].expn;  
                pc.elem[k].coef = c;  
                k++;  
            }  
            i++;  
            j++;//pa��pb��ȡ��һ��  
        }  
    }  
    if (i == pa.length)//pa�Ѵ����꣬��pbʣ�ಿ����ӵ�pc  
        while (j < pb.length)  
            pc.elem[k++] = pb.elem[j++];  
    if (j == pb.length)//pb�Ѵ����꣬��paʣ�ಿ�ּӵ�pc  
        while (i < pa.length)  
            pc.elem[k++] = pa.elem[i++];  
    if (k < pa.length + pb.length)  
        if (NULL == (pc.elem = (Term*)realloc(pc.elem, k * sizeof(Term))))  
            return OVERFLOW;  
    pc.length = k;  
}  
  
//����һԪϡ�����ʽ����������pc = pa - pb  
Status SubPoly(Poly pa, Poly pb, Poly &pc) {//����һԪϡ�����ʽ����������pc=pa-pb  
    int i = 0, j = 0, k = 0;  
    float c;  
    pc.elem = (Term*)malloc((pa.length + pb.length) * sizeof(Term));  
    if (NULL == pc.elem) return OVERFLOW;  
    while (i < pa.length&&j < pb.length) {//��������ʽ��δ�������  
        if (pa.elem[i].expn < pb.elem[j].expn)//pa���ָ����С�����pc  
            pc.elem[k++] = pa.elem[i++];  
        else if (pa.elem[i].expn > pb.elem[j].expn)//pb���ָ����С����ӵ�pc  
            pc.elem[k++] = pb.elem[j++];  
        else {//pa��pbָ�����  
            c = pa.elem[i].coef - pb.elem[j].coef;//ϵ�����  
            if (c != 0) {//ϵ���Ͳ�Ϊ0�������������ӵ�pc  
                pc.elem[k].expn = pa.elem[i].expn;  
                pc.elem[k].coef = c;  
                k++;  
            }  
            i++;  
            j++;//pa��pb��ȡ��һ��  
        }  
    }  
    if (i == pa.length)//pa�Ѵ����꣬��pbʣ�ಿ����ӵ�pc  
        while (j < pb.length)  
            pc.elem[k++] = pb.elem[j++];  
    if (j == pb.length)//pb�Ѵ����꣬��paʣ�ಿ�ּӵ�pc  
        while (i < pa.length)  
            pc.elem[k++] = pa.elem[i++];  
    if (k < pa.length + pb.length)  
        if (NULL == (pc.elem = (Term*)realloc(pc.elem, k * sizeof(Term))))  
            return OVERFLOW;  
    pc.length = k;  
}  
  
//����һԪϡ�����ʽ���˷�����pc = pa * pb  
Status MulPoly(Poly pa, Poly pb, Poly &pc) {//����һԪϡ�����ʽ���˷�����pc=pa*pb  
    int i = 0, j = 0, k = 0, m = 0;  
    int flag;  
    float c;  
    Poly temp;  
    temp.elem = (Term*)malloc((pa.length*pb.length) * sizeof(Term));  
    pc.elem = (Term*)malloc((pa.length*pb.length) * sizeof(Term));  
    if (NULL == pc.elem || NULL == temp.elem)  
        return OVERFLOW;  
    while (i < pa.length) {  
        while (j < pb.length) {//pa�е�ÿһ��ȥ����pb�е�ÿһ��  
            temp.elem[k].coef = (pa.elem[i].coef) * (pb.elem[j].coef);//ϵ�����  
            temp.elem[k].expn = (pa.elem[i].expn) + (pb.elem[j].expn);//ָ�����  
            k++;  
            j++;//ָ����һ��  
        }  
        i++;  
        j = 0;//��j���¸�ֵΪ0  
    }  
    while (j < k) {//��һԪϡ�����ʽtemp�пɺϲ�����ϲ�����pc  
        flag = 1;  
        if (temp.elem[j].coef == 0) {  
            j++;  
            continue;  
        }  
        i = j + 1;//iָ��j����һ��  
        while (i < k) {  
            if (temp.elem[j].expn == temp.elem[i].expn) {//���ָ����ͬ����ϵ�����  
                c = temp.elem[j].coef + temp.elem[i].coef;  
                if (c != 0) {//���ϵ���Ͳ�Ϊ0���򹹽��������ӵ�pc  
                    pc.elem[m].expn = temp.elem[j].expn;  
                    pc.elem[m].coef = c;  
                    temp.elem[i].coef = 0;  
                    m++;  
                    flag = 0;  
                }  
            }  
            i++;  
        }  
        if (flag)   
            pc.elem[m++] = temp.elem[j];  
            j++;      
    }  
    if (m < pa.length*pb.length)  
        if (NULL == (pc.elem = (Term*)realloc(pc.elem, m * sizeof(Term))))  
            return OVERFLOW;  
    pc.length = m;  
    free(temp.elem);  
    return OK;  
}  
  
  
//����һԪϡ�����ʽ����������pc = pa / pb  
Status DivPoly(Poly pa, Poly pb, Poly &pc) {//����һԪϡ�����ʽ����������pc=pa/pb  
    int i = 0, j = 0, k = 0, m = 0;  
    float c = 0;  
    int flag;  
    Poly temp;  
    temp.elem = pc.elem = (Term*)malloc((pa.length*pb.length) * sizeof(Term));  
    if (NULL == pc.elem || NULL == temp.elem)  
        return OVERFLOW;  
    while (i < pa.length) {  
        while (j < pb.length) {//pa�е�ÿһ��ȥ����pb�е�ÿһ��  
            temp.elem[k].coef = pa.elem[i].coef / pb.elem[j].coef;//ϵ�����  
            temp.elem[k].expn = pa.elem[i].expn - pb.elem[j].expn;//ָ�����  
            k++;  
            j++;//ָ����һ��  
        }  
        i++;  
        j = 0;//��j���¸�ֵΪ0  
    }  
    while (j < k) {//��һԪϡ�����ʽtemp�пɺϲ�����ϲ�����pc  
        flag = 1;  
        if (temp.elem[j].coef == 0) {  
            j++;  
            continue;  
        }  
        i = j + 1;//iָ��j����һ��  
        while (i<k) {  
            if (temp.elem[j].expn == temp.elem[i].expn) {//���ָ����ͬ����ϵ�����  
                c = temp.elem[j].coef + temp.elem[i].coef;  
                if (c != 0) {//���ϵ���Ͳ�Ϊ0���򹹽��������ӵ�pc  
                    pc.elem[m].expn = temp.elem[j].expn;  
                    pc.elem[m].coef = c;  
                    m++;  
                    flag = 0;  
                }  
            }  
            i++;  
        }  
        if(flag)  
        pc.elem[m++] = temp.elem[j];  
        j++;  
    }  
    if (m < pa.length*pb.length)  
        if (NULL == (pc.elem = (Term*)realloc(pc.elem, m * sizeof(Term))))  
            return OVERFLOW;  
    pc.length = m;  
    return OK;  
}  
  
void menu()  //�˵�   
{    
    printf("1 ����һԪϡ�����ʽ!                       \n");  
    printf("2 ��ӡ���һԪϡ�����ʽ                    \n");  
    printf("3 ����һԪϡ�����ʽP�е�����               \n");  
    printf("4 ����һԪϡ�����ʽ���ӷ�                  \n");  
    printf("5 ����һԪϡ�����ʽ������                  \n");  
    printf("6 ����һԪϡ�����ʽ���˷�                  \n");  
    printf("7 ����һԪϡ�����ʽ������                  \n");  
    printf("8 ����һԪϡ�����ʽ!                       \n");  
    printf("0 �˳�!                                     \n");  
    printf("********************************************\n");  
}  

int main() {  
    ElemType *e,*e2;  
    Poly pa,pb,pc;  
    int i;  
    int n,length,order;  
    //����pa  
    printf("\n���������ʽ������\n");  
    scanf("%d", &n);  
    printf("������%d���������ϵ����������˳��\n", n);  
    e= (Term*)malloc(n*sizeof(Term));  
    for (i = 0; i < n; i++) {  
        scanf("%f %d", &e[i].coef, &e[i].expn);  
    }  
    CreatePoly(pa, e, n);  
    PrintPoly(pa);  
  
    //����pb  
    printf("\n���������ʽ������\n");  
    scanf("%d", &n);  
    printf("������%d���������ϵ����������˳��\n", n);  
    e2 = (Term*)malloc(n * sizeof(Term));  
    for (i = 0; i < n; i++) {  
        scanf("%f %d", &e2[i].coef, &e2[i].expn);  
    }  
    CreatePoly(pb, e2, n);  
    PrintPoly(pb);  
  
    menu();//����˵�  
    while (1) {  
        printf("\n��������Ҫ��������ţ�\n");  
        scanf("%d", &order);  
        switch (order)  
        {  
        case 1:CreatePoly(pa, e, n); break;  
        case 2:PrintPoly(pc); break;  
        case 3:length = PolyLength(pa);  
                printf("\nP������Ϊ:%d\n", length); break;  
        case 4:AddPoly(pa, pb, pc);  
                PrintPoly(pc); break;  
        case 5:SubPoly(pa, pb, pc);  
                PrintPoly(pc); break;  
        case 6:MulPoly(pa, pb, pc);  
                PrintPoly(pc); break;  
        case 7:DivPoly(pa, pb, pc);   
                PrintPoly(pc); break;  
        case 8:DestroyPoly(pc); break;  
        case 0:exit(1); break;  
        default:printf("�����������!����������:\n");  
            break;  
        }  
    }  
      
    return 0;  
}  

