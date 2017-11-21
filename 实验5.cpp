#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>
#include<math.h>
#define MAX 30

//����������ʽ����������ṹ��
typedef struct term{  
    float coef;  
    int expn;  
    struct term *next;  
}term, *LinkList;  
  
typedef LinkList polynomial;

//˳���������ʽ����ṹ��
typedef struct {  
    float coef; //ϵ��  
    int expn;  //ָ��  
}ElemType, Term;  
  
typedef struct {  
    Term *elem;  //�洢�ռ��ַ  
    int length;  //����  
}Poly;   

//ջ��������
typedef struct{
    char data[MAX];
    int top;
}operator_stack, *operator_stackptr;

typedef struct{
    int data[MAX];
    int top;
}num_stack, *num_stackptr;

//��������
typedef struct { 
    int row,col;//����Ԫ�����±�����±�  
    int data;//Ԫ�ص�ֵ  
}Triple;  

typedef struct {  
    Triple dataArray[MAX+1];//����Ԫ���dataArray[0]δ��  
    int rpos[MAX+1];//���е�һ������Ԫ��λ��(��Ŀ������еĴ洢λ��)��  
    int row_count,col_count,data_count;//����������������ͷ���Ԫ����  
}*TSMatrix,Matrix;//����Triple Sequence Matrix ��Ԫ����� 

void Vector(){//�������� 
	int vec1[MAX];
	int vec2[MAX];
	int ans[MAX];
    int m; 
    printf("1.�����ӷ�\n");
    printf("2.��������\n");
    printf("3.�������н�");
    printf("\n===================================================================\n");
	printf("����������ѡ��");
	int choice;
	scanf("%d", &choice);
	printf("��������ά��: ");
    scanf("%d", &m);  
    printf("��������һ����:"); 
    for(int i = 0; i < m; i++){
    	scanf("%d", &vec1[i]);
    }  
    printf("��������������:"); 
    for(int i = 0; i < m; i++){
    	scanf("%d", &vec2[i]);
    }  
	switch(choice){
		case 1 :{
			for (int i = 0; i < m; ++i)
			{
				ans[i] = vec1[i] + vec2[i];
			}
			printf("����֮��Ϊ:(");
			for (int i = 0; i < m; ++i)
			{
				printf("%d ", ans[i]);
			}
			printf(")\n");
		}break;
		case 2:{
			for (int i = 0; i < m; ++i)
			{
				ans[i] = vec1[i] - vec2[i];
			}
			printf("����֮��Ϊ:(");
			for (int i = 0; i < m; ++i)
			{
				printf("%d ", ans[i]);
			}
			printf(")\n");
		}break;
		case 3:{
			int sum = 0;
			for (int i = 0; i < m; ++i)
			{
				sum += (vec1[i] * vec2[i]);
			}
			int sum1 = 0;
			int sum2 = 0;
			for (int i = 0; i < m; ++i)
			{
				sum1 += vec1[i] * vec1[i];
				sum2 += vec2[i] * vec2[i];
			}
			float out = sum / (sqrt(sum1) * sqrt(sum2));
			printf("�������ɽǵ�����ֵΪ:%.3f", out);
		}break;
	}
}

int CreatePoly(Poly &P, Term e[], int n) {//˳�����һԪϡ�����ʽ  
    int i;  
    P.elem = (Term*)malloc(sizeof(Term)*n);  
    if (NULL == P.elem) return -1;  
    for (i = 0; i < n; i++) P.elem[i] = e[i];  
    P.length = n;  
    return 1;  
}  

int PrintPoly(Poly P) {//˳����ӡ���� 
    int i;  
    printf("�������Ϊ:");  
    for (i = 0; i < P.length; i++) {  
        if (i == P.length - 1)  
            printf("%4.2fx^%d\n", P.elem[i].coef, P.elem[i].expn);  
        else  
            printf("%4.2fx^%d + ", P.elem[i].coef, P.elem[i].expn);  
          
    }  
    return 1;  
}

int AddPoly(Poly pa, Poly pb, Poly &pc) {//˳�������һԪϡ�����ʽ���ӷ�
    int i = 0, j = 0, k = 0;  
    float c;  
    pc.elem = (Term*)malloc((pa.length + pb.length) * sizeof(Term));  
    if (NULL == pc.elem) return -1;  
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
            return -1;  
    pc.length = k;  
}  

int SubPoly(Poly pa, Poly pb, Poly &pc) {//˳�������һԪϡ�����ʽ������
    int i = 0, j = 0, k = 0;  
    float c;  
    pc.elem = (Term*)malloc((pa.length + pb.length) * sizeof(Term));  
    if (NULL == pc.elem) return -1;  
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
            return -1;  
    pc.length = k;  
}  

int MulPoly(Poly pa, Poly pb, Poly &pc) {//˳�������һԪϡ�����ʽ���˷�  
    int i = 0, j = 0, k = 0, m = 0;  
    int flag;  
    float c;  
    Poly temp;  
    temp.elem = (Term*)malloc((pa.length*pb.length) * sizeof(Term));  
    pc.elem = (Term*)malloc((pa.length*pb.length) * sizeof(Term));  
    if (NULL == pc.elem || NULL == temp.elem)  
        return -1;  
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
            return -1;  
    pc.length = m;  
    free(temp.elem);  
    return 1;  
} 

void PolyMenu2() {//˳���˵�   
    printf("1.һԪ����ʽ�ӷ�\n");  
    printf("2.һԪ����ʽ����\n");  
    printf("3.һԪ����ʽ�˷�");     
	printf("\n===================================================================\n");
}  

int SolvePoly() {//˳���һԪ����������� 
    ElemType *e,*e2;  
    Poly pa,pb,pc;  
    int i;  
    int n,length,order;
	printf("������������������ʽ\n");
    //����pa  
    printf("���������ʽa������\n");  
    scanf("%d", &n);  
    printf("����ϵ��,ָ��,����(coef,expn):\n");  
    e= (Term*)malloc(n*sizeof(Term));  
    for (i = 0; i < n; i++) {  
        scanf("%f,%d", &e[i].coef, &e[i].expn);  
    }  
    CreatePoly(pa, e, n);  
    PrintPoly(pa);  
  
    //����pb  
    printf("���������ʽb������\n");  
    scanf("%d", &n);  
    printf("����ϵ��,ָ��,����(coef,expn):\n");  
    e2 = (Term*)malloc(n * sizeof(Term));  
    for (i = 0; i < n; i++) {  
        scanf("%f,%d", &e2[i].coef, &e2[i].expn);  
    }  
    CreatePoly(pb, e2, n);  
    PrintPoly(pb);  
  
    while (1) {  
        printf("\n��������Ҫ��������ţ�\n");  
        scanf("%d", &order);  
        switch (order)  
        {  
        	case 1 : AddPoly(pa, pb, pc);  
                     PrintPoly(pc); 
				 	 break;  
        	case 2 : SubPoly(pa, pb, pc);  
                 	 PrintPoly(pc); 
				 	 break;  
        	case 3 : MulPoly(pa, pb, pc);
        	default: printf("�����������!����������:\n");  
                	 break;  
        }  
    }  
      
    return 0;  
}  

void PrintPolyn(polynomial &P){//��ӡһԪ����ʽ
	LinkList q = P->next;  
    printf("��ӡ����ʽ��");
    printf("%.2fx^%d", q->coef, q->expn);
    q = q->next;
    while(q){
	    printf("+%.2fx^%d", q->coef, q->expn);  
        q = q->next;  
    }
    printf("\n");  
}

bool LocateElem(LinkList L, LinkList t, LinkList &q){//����
    LinkList p1 = L->next;  
    LinkList p2 = L;//p2��ָ��p1��ǰ��  
    while(p1){  
        if(t->expn > p1->expn){  
            p1 = p1->next;  
            p2 = p2->next;  
        }
		else if(t->expn == p1->expn){  
            q = p1;   
            return true;  
        }
		else{//p1->expn > t->expn,��ΪL�������������������ߵ�����һ����˵��û�ҵ�����t��ָ����ȵĽڵ�Ԫ���򷵻�q��ǰ�����  
            q = p2;  
            return false;  
        }  
    }  
    if(!p1){//t->expn�ȵ�ǰ�б�����Ԫ�ص�ָ�������������whileѭ������Ϊp2������β�ڵ㣬p1=NULL������  
        q = p2;  
        return false;  
    }  
}  

void InitPoly(polynomial &P){//��������ʽ
	P = (polynomial)malloc(sizeof(term));  //�Ƚ���һ������ͷ�ڵ�Ŀ���������ʼ�� 
    if(!P){
		printf("����ʧ��");
		exit(0);
	}
	P->next = NULL;  
    int m; 
	printf("�������ʽ������\n");
    scanf("%d", &m);  
    printf("����ϵ��,ָ��,����(coef,expn):\n");//���ذ���������  
    for(int i = 0; i < m; i++){//��������m��������  
        LinkList t = (LinkList)malloc(sizeof(term));  
        t->next = NULL;  
        LinkList q;  
        scanf("%f,%d", &t->coef, &t->expn);  
        if(!LocateElem(P, t, q)){//��ǰ�����в����ڸ�ָ�������룬��ʱqΪ�����е�һ��ָ������t->expn�Ľڵ��ǰ�����  
            t->next = q->next;  
            q->next = t;  
        }
		else{//��ǰ�б����Ѿ������нڵ�Ԫ�ص�ָ���뱾����������ָ����ͬ�����Ա���������Ч��Ӧ��������  
            i--;  
        }  
    }  
}

int cmp(LinkList qa, LinkList qb){//�Ƚ�ָ����С 
    if(qa->expn > qb->expn)  
        return 1;  
    else if(qa->expn == qb->expn)  
        return 0;  
    else  
        return -1;  
} 

void AddPolyn(polynomial &Pa, polynomial &Pb){//һԪ����ʽ���
	LinkList qa = Pa->next;  
    LinkList qb = Pb->next;  
    LinkList qc = Pa;//pc����ָ��"�Ͷ���ʽ����"�����һ���ڵ�  
  
    float SumOfCoef;  
    while(qa && qb){  
        switch(cmp(qa, qb)){  
            case 1:  
                qc->next = qb;  
                qc = qb;  
                qb = qb->next;  
                break;  
            case 0://��ǰ�Ƚϵ������ָ����ͬ  
                SumOfCoef = qa->coef + qb->coef;  
                if(SumOfCoef != 0.0){//ϵ��֮�Ͳ�Ϊ0,���޸�qa��ָ�ڵ��ϵ����ͬʱ�ͷ�gb��ָ�ڵ�  
                    LinkList s = qb;//s������free��  
                    qa->coef = SumOfCoef;    
                    qc->next = qa;  
                    qc = qa;  
                    qa = qa->next;  
                    qb = qb->next;    
                    free(s);  
                }
				else{//ϵ��֮��Ϊ0����Ӷ���ʽ����A��ɾ��qa��ָ�ڵ㣬��free��qa��qb��ָ�ڵ�  
                    LinkList s1 = qa;  
                    LinkList s2 = qb;    
                    qc->next = qa ->next;  //qc��λ�ò���,qa��qb����ƶ�  
                    qa = qa->next;  
                    qb = qb->next;    
                    free(s1);  
                    free(s2);                        
                }  
                break;  
            case -1:  
                qc->next = qa;  
                qc = qa;  
                qa = qa->next;  
                break;  
        }  
    }
    qc->next = qa ? qa : qb;//����ʣ���  
    free(Pb);//�ͷ�Pb��ͷ�ڵ�  
}

void DerPoly(polynomial &P){//һԪ����ʽ��
	LinkList q = P->next;  
    printf("�������󵼴�����");
    int n;
	scanf("%d", &n);  
    for(int i = 0; i < n; i ++){
    	while(q){
	    	q->coef = (q->coef) * (q->expn);
			(q->expn) --;  
        	q = q->next;  
    	} 
	}
	PrintPolyn(P);
}

LinkList MultiPolyn(polynomial &Pa, polynomial &Pb){//һԪ����ʽ��� 
	LinkList pa = Pa->next;
	LinkList r = (polynomial)malloc(sizeof(term));
	LinkList n = r;
	LinkList t, s, ss, sss;
	n->next = NULL;
	while(pa != NULL){
		s = (polynomial)malloc(sizeof(term));
		ss = s;
		ss->next = NULL;
		for(sss = Pb->next; sss; sss = sss->next){
			t = (polynomial)malloc(sizeof(term));
			t->coef = pa->coef * sss->coef;
			t->expn = pa->expn + sss->expn;
			ss->next = t;
			ss = t;
			ss->next = NULL;
		}
		pa = pa->next;
		AddPolyn(n, s);
	}
	return (n);
}

void Polynomial(int flag){//����ʽ��������
	polynomial Pa, Pb, Pc;
	InitPoly(Pa);
	switch(flag){
		case 1: {
			InitPoly(Pb);
			Pc = MultiPolyn(Pa, Pb);
			PrintPolyn(Pc);
		}break;
		case 2: {
			InitPoly(Pb);
			AddPolyn(Pa, Pb);
			PrintPolyn(Pa);
		}break;
		case 3: {
			DerPoly(Pa);
			PrintPolyn(Pa);
		}break;
	}
}

void PolyMenu(){//����ʽ�����˵�
    int k;
   	printf("1.һԪ����ʽ�˷�\n");
	printf("2.һԪ����ʽ���\n");
	printf("3.һԪ����ʽ��");
	printf("\n===================================================================\n");
	printf("����������ѡ��");
	scanf("%d", &k);
	Polynomial(k);
}

int prior(char x){//�������ȼ� 
    switch(x)
    {
        case '+':
        case '-': return 3;
        case '*':
        case '/': return 4;
        default:  exit(0);
    }
}

int calcu_two_num(char operat,int x,int y){//��ֵ 
    switch(operat)
    {
        case '*': return x * y;
        case '/': return x / y;
        case '-': return x - y;
        case '+': return x + y;

    }
}

int calcu_by_stack(char *x){//��׺���ʽ��ֵ 
    int num_1, num_2, result, i = 0;
    char operator_1;
    operator_stack stack_op;
    num_stack stack_num;
    stack_op.top = -1;
    stack_num.top = -1;

    if(x[i] == '('){
        stack_op.data[++ stack_op.top] = '(';
        i ++;
    }
    else{
        stack_num.data[++ stack_num.top] = atoi(x);
        while(isdigit(x[++ i]));
    }

    while(x[i]!='\0'){
        if(isdigit(x[i])){
            stack_num.data[++ stack_num.top] = atoi(&x[i]);
            while(isdigit(x[++ i]));
        }

        else{
            if(x[i] == '(')
               stack_op.data[++ stack_op.top] = '(';
            else if(x[i] != ')'){
                if(stack_op.top == -1)
                    stack_op.data[++ stack_op.top] = x[i];
                else if(stack_op.data[stack_op.top] == '(')
                    stack_op.data[++stack_op.top] = x[i];
                else{
                    while(prior(x[i]) < prior(stack_op.data[stack_op.top])){
                        num_1 = stack_num.data[stack_num.top --];
                        num_2 = stack_num.data[stack_num.top --];
                        result = calcu_two_num(stack_op.data[stack_op.top--], num_2, num_1);
                        stack_num.data[++ stack_num.top] = result;
                        if(stack_op.top == -1)
                            break;
                    }
                    stack_op.data[++ stack_op.top] = x[i];
                }
            }
            else{
                while((operator_1 = stack_op.data[stack_op.top --]) != '('){
                    num_1 = stack_num.data[stack_num.top --];
                    num_2 = stack_num.data[stack_num.top --];
                    stack_num.data[++ stack_num.top] = calcu_two_num(operator_1, num_2, num_1);
                }

            }
            i ++;
        }
    }
    while(stack_op.top != -1 && stack_num.top != 0)
                {
                    operator_1 = stack_op.data[stack_op.top --];
                    num_1 = stack_num.data[stack_num.top --];
                    num_2 = stack_num.data[stack_num.top --];
                    stack_num.data[++ stack_num.top] = calcu_two_num(operator_1, num_2, num_1);

                }
    return stack_num.data[stack_num.top --];

}

int Mypow(int x, int y, int out){//��ֵ����ָ������ *
	if(y > 1){
		out *= x;
		Mypow(x, y - 1, out);
	}
	else{
		return out;
	}
}

void Arithmetic(){//���������������
	int ans;
    char expression[MAX];
    printf("��������Ҫ�����ʽ��(�˺Ų���ʡ��): ");
    scanf("%s", expression);
    ans = calcu_by_stack(expression);
    printf("��������: %d\n", ans);
}

void Equation(){//���ʽ����
	char equation[MAX];
	int elem;
	int temp = 0;
	printf("��������ʽ: ");
	scanf("%s", equation);
	printf("�����������ֵ: ");
	scanf("%d", &elem);
	for (int i = 0; equation[i] != '\0'; ++ i){
		if(equation[i] == 'x'){
			equation[i] = elem + '0';
		}
	}
	int j;
	for (j = 0; equation[j] != '\0'; ++ j){
		if(equation[j] == '*' || equation[j] == '^' || equation[j] == '+'){
			equation[j - 1]  = equation[j - 1] - '0';
		}
	}
	equation[j - 1]  = equation[j - 1] - '0';
	for (int i = 0; equation[i] != '\0'; i ++){
		if(equation[i] == '*'){
			temp += equation[i - 1] * Mypow(equation[i + 1], equation[i + 3], equation[i + 1]);
		}
	}
	for (int i = 0; equation[i] != '\0'; i ++){
		if(equation[i] == '+'){
			if(equation[i + 2] != '*'){
				temp += Mypow(equation[i + 1], equation[i + 3], equation[i + 1]);
			}
		}
	}
	printf("���ʽ������Ϊ: %d\n", temp);
}

void DefFunction(){//���庯�� 
	char func[MAX];
	printf("�����붨��ĺ���: ");
	scanf("%s", func);
	int out;
	int ans = 0;
	printf("�����������ֵ: ");
	scanf("%d", &out);
		for (int i = 0; func[i] != '\0'; ++ i){
			if(func[i] == 'x'){
				func[i] = out + '0';
			}
		}
		int j;
		for (j = 0; func[j] != '\0'; ++ j){
			if(func[j] == '*' || func[j] == '^' || func[j] == '+'){
				func[j - 1]  = func[j - 1] - '0';
			}
		}
		func[j - 1]  = func[j - 1] - '0';
		for (int i = 0; func[i] != '\0'; i ++){
			if(func[i] == '*'){
				ans += func[i - 1] * Mypow(func[i + 1], func[i + 3], func[i + 1]);
			}
		}
		for (int i = 0; func[i] != '\0'; i ++){
			if(func[i] == '+'){
				if(func[i + 2] != '*'){
					ans += Mypow(func[i + 1], func[i + 3], func[i + 1]);
				}
			}
		}
 	printf("��������:f(%d)=%d\n", out, ans);
}

void HisFunction(){//��ʷ������ֵ                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	FILE*fp2 = fopen("in.txt","r");
	char func[5][MAX];
	char find[MAX];
	printf("������Ҫ���ҵ���ʷ����: ");
	scanf("%s", find);
	int out;
	int ans = 0;
	int i = 0;
	if(fp2 == NULL)
 	{
 		perror("fail to read");
 		exit (1) ;
 	}
 	else{
 		while(fgets(func[i], MAX, fp2) != NULL){
 			printf("%s",func[i]);
			if(func[i][0] == find[0]){
				printf("�����������ֵ: ");
				scanf("%d", &out);
				for (int k = 0; func[i][k] != '\0'; ++ k){
					if(func[i][k] == 'x'){
						func[i][k] = out + '0';
					}
				}
				int j;
				for (j = 0; func[i][j] != '\0'; ++ j){
					if(func[i][j] == '*' || func[i][j] == '^' || func[i][j] == '+'){
						func[i][j - 1]  = func[i][j - 1] - '0';
					}
				}
				func[i][j - 2]  = func[i][j - 2] - '0';
				for (int k = 0; func[i][k] != '\0'; k ++){
					if(func[i][k] == '*'){
						ans += func[i][k - 1] * Mypow(func[i][k + 1], func[i][k + 3], func[i][k + 1]);
					}
				}
				for (int k = 0; func[i][k] != '\0'; k ++){
					if(func[i][k] == '+'){
						if(func[i][k + 2] != '*'){
							ans += Mypow(func[i][k + 1], func[i][k + 3], func[i][k + 1]);
						}
					}
				}
				printf("��������:f(%d)=%d\n", out, ans);
				fclose(fp2); 
				return;
			}
		i ++;
 		}
	}	
 	printf("δ�ҵ��ú�����\n");
 	return;
}
 
int CreateTSMatrix(TSMatrix &M){ //����һ������
    M = (TSMatrix)malloc(sizeof(Matrix));  
    if(!M){  
        exit(0);  
    }  
    printf("������Ԫ��������������ͷ���Ԫ������");  
    int rc, cc, dc;  
    scanf("%d%d%d", &rc, &cc, &dc);  
    M->row_count = rc;  
    M->col_count = cc;  
    M->data_count = dc;  
    int i = 0;  
    printf("��ʼ�������\n");  
    int r, c, d;
    while(i < dc){  
        printf("�����%d������Ԫ���кţ��кź�ֵ��", i + 1);  
        scanf("%d%d%d", &r, &c, &d);  
        if(r > rc || c > cc){ //�к��в���Խ��  
            printf("�������ݲ��Ϸ�������������\n");  
            continue;  
        }else{
            M->dataArray[i + 1].row = r;  
            M->dataArray[i + 1].col = c;  
            M->dataArray[i + 1].data = d;  
            i ++;  
        }  
    }
    //����rpos[]��ֵ
    for(i = 1; i <= M->row_count; i ++){  
        M->rpos[i] = 0;//����ֵΪ0  
    }  
    for(i = 1; i <= M->data_count; i ++){  
        M->rpos[M->dataArray[i].row] ++;//����ÿһ�з���Ԫ����
    }//����rpos[]��ֵ 
    for(i = M->row_count; i >= 1; i --){  
        M->rpos[i] = 1;  
        for(int j = i - 1; j >= 1; j --){  
            M->rpos[i] += M->rpos[j];  
        }  
    }  
    printf("�������ɹ�\n");  
    return 1;  
}  

int PrintTSMatrix(TSMatrix M){//��ӡ��Ԫ�����
    //����������  
    for(int i = 1; i <= M->data_count; i ++){  
        printf("�к� �к� ֵ��%d %d %d",M->dataArray[i].row,M->dataArray[i].col, M->dataArray[i].data);  
        printf("\n");  
    }  
    return 1;  
}  

int MultTSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q){//ʵ�־���ĳ˷�: Q = M * N
    int arow, brow, p, q, ccol, ctemp[MAX+1], t, tp;  
    if(M->col_count != N->row_count){//�������  
        return 0;  
    }  
    if(M->data_count * N->data_count == 0){//��һ���������  
        return 0;  
    }  
    //Q��ʼ��  
    Q->row_count = M->row_count;  
    Q->col_count = N->col_count;  
    Q->data_count = 0;  
    //��M�ĵ�һ�п�ʼ�����һ�У�arow��M�ĵ�ǰ��  
    for(arow = 1; arow <= M->row_count; arow++){  
        for(ccol = 1; ccol <= Q->col_count; ccol++){  
            ctemp[ccol] = 0;//Q�ĵ�ǰ�еĸ���Ԫ������  
        }  
        Q->rpos[arow] = Q->data_count + 1;//��ʼʱ�ӵ�һ���洢λ�ÿ�ʼ�� 
        if(arow < M->row_count){  
            tp = M->rpos[arow + 1];//��һ�е���ʼλ��  
        }
        else{  
            tp = M->data_count + 1;//���һ�еı߽�  
        }  
        for(p = M->rpos[arow]; p < tp; p ++){  
            //��M��ǰ�е�ÿһ������Ԫ  
            //�ҵ���ӦԪ����N�е��кţ���M�е�ǰԪ���к�  
            brow = M->dataArray[p].col;   
            if(brow < N->row_count){  
                t = N->rpos[brow + 1];  
            }
            else{  
                t = N->data_count + 1;  
            }  
            for(q = N->rpos[brow]; q < t; q ++){  
                ccol = N->dataArray[q].col;//�˻�Ԫ����Q���е�λ��  
                ctemp[ccol] += M->dataArray[p].data * N->dataArray[q].data;  
            }  
        } 
        for(ccol = 1; ccol <= Q->col_count; ccol ++){  
            if(ctemp[ccol] != 0){  
                if(++ Q->data_count > MAX){  
                    return 0;  
                }  
                Q->dataArray[Q->data_count].row = arow;  
                Q->dataArray[Q->data_count].col = ccol;  
                Q->dataArray[Q->data_count].data = ctemp[ccol];  
            }  
        }  
    }//for_arow  
    return 1;  
}  

void MatrixMenu(){//��������˵�
    int k;
   	printf("1.����ӷ�\n");
	printf("2.����˷�\n");
	printf("3.������ʽ");
	printf("\n===================================================================\n");
	printf("����������ѡ��");
	scanf("%d", &k);
	switch(k){
		case 1:
		case 2:{  
    		TSMatrix M, N, Q;  
    		Q = (TSMatrix)malloc(sizeof(TSMatrix));  
    		CreateTSMatrix(M);  
    		printf("����M��\n");  
    		PrintTSMatrix(M);  
    		CreateTSMatrix(N);  
    		printf("����N��\n");  
    		PrintTSMatrix(N);  
    		MultTSMatrix(M,N,Q);  
    		printf("����Q��\n");  
    		PrintTSMatrix(Q);
		}  
		case 3:;
	}
}

void MainMenu(){//���˵�
	int k;
	printf("=========================ʵ��05-�ɱ�̼�����==========================\n");
	printf("1.ͬά����������\n");
	printf("2.һԪ����ʽ����(����洢)\n");
	printf("3.����������ʽ��ֵ\n");
	printf("4.���������ʽ��ֵ\n");
	printf("5.���岢���к���\n");
	printf("6.������ʷ����\n");
	printf("7.��������\n"); 
	printf("8.һԪ����ʽ����(˳���洢)");
	printf("\n===================================================================\n");
	printf("����������ѡ��");
	scanf("%d", &k);
	switch(k){
		case 1: Vector();
				break;
		case 2: PolyMenu();
				break;
		case 3: Arithmetic();
		        break;
		case 4: Equation();
		        break;
		case 5: DefFunction();
		        break;
		case 6: HisFunction();
		        break;
		case 7: MatrixMenu();
				break;
		case 8: PolyMenu2();
				SolvePoly();
				break; 
	}
}

int main(int argc, char const *argv[]){
	system("COLOR f0");
	MainMenu();
	return 0;
}
