#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>
#include<math.h>
#define MAX 30

//链表计算多项式、函数所需结构体
typedef struct term{  
    float coef;  
    int expn;  
    struct term *next;  
}term, *LinkList;  
  
typedef LinkList polynomial;

//顺序表计算多项式所需结构体
typedef struct {  
    float coef; //系数  
    int expn;  //指数  
}ElemType, Term;  
  
typedef struct {  
    Term *elem;  //存储空间基址  
    int length;  //长度  
}Poly;   

//栈四则运算
typedef struct{
    char data[MAX];
    int top;
}operator_stack, *operator_stackptr;

typedef struct{
    int data[MAX];
    int top;
}num_stack, *num_stackptr;

//矩阵运算
typedef struct { 
    int row,col;//非零元的行下标和列下标  
    int data;//元素的值  
}Triple;  

typedef struct {  
    Triple dataArray[MAX+1];//非零元组表，dataArray[0]未用  
    int rpos[MAX+1];//各行第一个非零元的位置(在目标矩阵中的存储位置)表  
    int row_count,col_count,data_count;//矩阵的行数，列数和非零元个数  
}*TSMatrix,Matrix;//代表Triple Sequence Matrix 三元组矩阵 

void Vector(){//向量运算 
	int vec1[MAX];
	int vec2[MAX];
	int ans[MAX];
    int m; 
    printf("1.向量加法\n");
    printf("2.向量减法\n");
    printf("3.求向量夹角");
    printf("\n===================================================================\n");
	printf("请输入您的选择：");
	int choice;
	scanf("%d", &choice);
	printf("输入向量维数: ");
    scanf("%d", &m);  
    printf("输入向量一坐标:"); 
    for(int i = 0; i < m; i++){
    	scanf("%d", &vec1[i]);
    }  
    printf("输入向量二坐标:"); 
    for(int i = 0; i < m; i++){
    	scanf("%d", &vec2[i]);
    }  
	switch(choice){
		case 1 :{
			for (int i = 0; i < m; ++i)
			{
				ans[i] = vec1[i] + vec2[i];
			}
			printf("向量之和为:(");
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
			printf("向量之差为:(");
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
			printf("向量所成角的余弦值为:%.3f", out);
		}break;
	}
}

int CreatePoly(Poly &P, Term e[], int n) {//顺序表构建一元稀疏多项式  
    int i;  
    P.elem = (Term*)malloc(sizeof(Term)*n);  
    if (NULL == P.elem) return -1;  
    for (i = 0; i < n; i++) P.elem[i] = e[i];  
    P.length = n;  
    return 1;  
}  

int PrintPoly(Poly P) {//顺序表打印函数 
    int i;  
    printf("操作结果为:");  
    for (i = 0; i < P.length; i++) {  
        if (i == P.length - 1)  
            printf("%4.2fx^%d\n", P.elem[i].coef, P.elem[i].expn);  
        else  
            printf("%4.2fx^%d + ", P.elem[i].coef, P.elem[i].expn);  
          
    }  
    return 1;  
}

int AddPoly(Poly pa, Poly pb, Poly &pc) {//顺序表两个一元稀疏多项式做加法
    int i = 0, j = 0, k = 0;  
    float c;  
    pc.elem = (Term*)malloc((pa.length + pb.length) * sizeof(Term));  
    if (NULL == pc.elem) return -1;  
    while (i < pa.length&&j < pb.length) {//两个多项式均未处理结束  
        if (pa.elem[i].expn < pb.elem[j].expn)//pa项的指数较小，添加pc  
            pc.elem[k++] = pa.elem[i++];  
        else if (pa.elem[i].expn > pb.elem[j].expn)//pb项的指数较小，添加到pc  
            pc.elem[k++] = pb.elem[j++];  
        else {//pa，pb指数相等  
            c = pa.elem[i].coef + pb.elem[j].coef;//系数相加  
            if (c != 0) {//系数和不为0，构建和项，并添加到pc  
                pc.elem[k].expn = pa.elem[i].expn;  
                pc.elem[k].coef = c;  
                k++;  
            }  
            i++;  
            j++;//pa和pb均取下一项  
        }  
    }  
    if (i == pa.length)//pa已处理完，将pb剩余部分添加到pc  
        while (j < pb.length)  
            pc.elem[k++] = pb.elem[j++];  
    if (j == pb.length)//pb已处理完，将pa剩余部分加到pc  
        while (i < pa.length)  
            pc.elem[k++] = pa.elem[i++];  
    if (k < pa.length + pb.length)  
        if (NULL == (pc.elem = (Term*)realloc(pc.elem, k * sizeof(Term))))  
            return -1;  
    pc.length = k;  
}  

int SubPoly(Poly pa, Poly pb, Poly &pc) {//顺序表两个一元稀疏多项式做减法
    int i = 0, j = 0, k = 0;  
    float c;  
    pc.elem = (Term*)malloc((pa.length + pb.length) * sizeof(Term));  
    if (NULL == pc.elem) return -1;  
    while (i < pa.length&&j < pb.length) {//两个多项式均未处理结束  
        if (pa.elem[i].expn < pb.elem[j].expn)//pa项的指数较小，添加pc  
            pc.elem[k++] = pa.elem[i++];  
        else if (pa.elem[i].expn > pb.elem[j].expn)//pb项的指数较小，添加到pc  
            pc.elem[k++] = pb.elem[j++];  
        else {//pa，pb指数相等  
            c = pa.elem[i].coef - pb.elem[j].coef;//系数相减  
            if (c != 0) {//系数和不为0，构建和项，并添加到pc  
                pc.elem[k].expn = pa.elem[i].expn;  
                pc.elem[k].coef = c;  
                k++;  
            }  
            i++;  
            j++;//pa和pb均取下一项  
        }  
    }  
    if (i == pa.length)//pa已处理完，将pb剩余部分添加到pc  
        while (j < pb.length)  
            pc.elem[k++] = pb.elem[j++];  
    if (j == pb.length)//pb已处理完，将pa剩余部分加到pc  
        while (i < pa.length)  
            pc.elem[k++] = pa.elem[i++];  
    if (k < pa.length + pb.length)  
        if (NULL == (pc.elem = (Term*)realloc(pc.elem, k * sizeof(Term))))  
            return -1;  
    pc.length = k;  
}  

int MulPoly(Poly pa, Poly pb, Poly &pc) {//顺序表两个一元稀疏多项式做乘法  
    int i = 0, j = 0, k = 0, m = 0;  
    int flag;  
    float c;  
    Poly temp;  
    temp.elem = (Term*)malloc((pa.length*pb.length) * sizeof(Term));  
    pc.elem = (Term*)malloc((pa.length*pb.length) * sizeof(Term));  
    if (NULL == pc.elem || NULL == temp.elem)  
        return -1;  
    while (i < pa.length) {  
        while (j < pb.length) {//pa中的每一项去乘于pb中的每一项  
            temp.elem[k].coef = (pa.elem[i].coef) * (pb.elem[j].coef);//系数相乘  
            temp.elem[k].expn = (pa.elem[i].expn) + (pb.elem[j].expn);//指数相加  
            k++;  
            j++;//指向下一项  
        }  
        i++;  
        j = 0;//将j重新赋值为0  
    }  
    while (j < k) {//将一元稀疏多项式temp中可合并的项合并赋给pc  
        flag = 1;  
        if (temp.elem[j].coef == 0) {  
            j++;  
            continue;  
        }  
        i = j + 1;//i指向j的下一项  
        while (i < k) {  
            if (temp.elem[j].expn == temp.elem[i].expn) {//如果指数相同，则将系数相加  
                c = temp.elem[j].coef + temp.elem[i].coef;  
                if (c != 0) {//如果系数和不为0，则构建和项，并添加到pc  
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

void PolyMenu2() {//顺序表菜单   
    printf("1.一元多项式加法\n");  
    printf("2.一元多项式减法\n");  
    printf("3.一元多项式乘法");     
	printf("\n===================================================================\n");
}  

int SolvePoly() {//顺序表一元多项操作函数 
    ElemType *e,*e2;  
    Poly pa,pb,pc;  
    int i;  
    int n,length,order;
	printf("首先请输入两个多项式\n");
    //建立pa  
    printf("请输入多项式a的项数\n");  
    scanf("%d", &n);  
    printf("输入系数,指数,形如(coef,expn):\n");  
    e= (Term*)malloc(n*sizeof(Term));  
    for (i = 0; i < n; i++) {  
        scanf("%f,%d", &e[i].coef, &e[i].expn);  
    }  
    CreatePoly(pa, e, n);  
    PrintPoly(pa);  
  
    //建立pb  
    printf("请输入多项式b的项数\n");  
    scanf("%d", &n);  
    printf("输入系数,指数,形如(coef,expn):\n");  
    e2 = (Term*)malloc(n * sizeof(Term));  
    for (i = 0; i < n; i++) {  
        scanf("%f,%d", &e2[i].coef, &e2[i].expn);  
    }  
    CreatePoly(pb, e2, n);  
    PrintPoly(pb);  
  
    while (1) {  
        printf("\n请输入你要操作的序号：\n");  
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
        	default: printf("输入命令错误!请重新输入:\n");  
                	 break;  
        }  
    }  
      
    return 0;  
}  

void PrintPolyn(polynomial &P){//打印一元多项式
	LinkList q = P->next;  
    printf("打印多项式：");
    printf("%.2fx^%d", q->coef, q->expn);
    q = q->next;
    while(q){
	    printf("+%.2fx^%d", q->coef, q->expn);  
        q = q->next;  
    }
    printf("\n");  
}

bool LocateElem(LinkList L, LinkList t, LinkList &q){//查找
    LinkList p1 = L->next;  
    LinkList p2 = L;//p2总指向p1的前驱  
    while(p1){  
        if(t->expn > p1->expn){  
            p1 = p1->next;  
            p2 = p2->next;  
        }
		else if(t->expn == p1->expn){  
            q = p1;   
            return true;  
        }
		else{//p1->expn > t->expn,因为L是有序表，所以如果程序走到了这一步，说明没找到与项t的指数相等的节点元素则返回q的前驱结点  
            q = p2;  
            return false;  
        }  
    }  
    if(!p1){//t->expn比当前列表所有元素的指数都大，则上面的while循环会因为p2到达了尾节点，p1=NULL而跳出  
        q = p2;  
        return false;  
    }  
}  

void InitPoly(polynomial &P){//建立多项式
	P = (polynomial)malloc(sizeof(term));  //先建立一个带有头节点的空链表，即初始化 
    if(!P){
		printf("分配失败");
		exit(0);
	}
	P->next = NULL;  
    int m; 
	printf("输入多项式项数：\n");
    scanf("%d", &m);  
    printf("输入系数,指数,形如(coef,expn):\n");//不必按升幂输入  
    for(int i = 0; i < m; i++){//依次输入m个非零项  
        LinkList t = (LinkList)malloc(sizeof(term));  
        t->next = NULL;  
        LinkList q;  
        scanf("%f,%d", &t->coef, &t->expn);  
        if(!LocateElem(P, t, q)){//当前链表中不存在该指数项，则插入，此时q为链表中第一个指数大于t->expn的节点的前驱结点  
            t->next = q->next;  
            q->next = t;  
        }
		else{//当前列表中已经存在有节点元素的指数与本次输入的项的指数相同，所以本次输入无效，应重新输入  
            i--;  
        }  
    }  
}

int cmp(LinkList qa, LinkList qb){//比较指数大小 
    if(qa->expn > qb->expn)  
        return 1;  
    else if(qa->expn == qb->expn)  
        return 0;  
    else  
        return -1;  
} 

void AddPolyn(polynomial &Pa, polynomial &Pb){//一元多项式相加
	LinkList qa = Pa->next;  
    LinkList qb = Pb->next;  
    LinkList qc = Pa;//pc总是指向"和多项式链表"的最后一个节点  
  
    float SumOfCoef;  
    while(qa && qb){  
        switch(cmp(qa, qb)){  
            case 1:  
                qc->next = qb;  
                qc = qb;  
                qb = qb->next;  
                break;  
            case 0://当前比较的两项的指数相同  
                SumOfCoef = qa->coef + qb->coef;  
                if(SumOfCoef != 0.0){//系数之和不为0,则修改qa所指节点的系数，同时释放gb所指节点  
                    LinkList s = qb;//s即将被free掉  
                    qa->coef = SumOfCoef;    
                    qc->next = qa;  
                    qc = qa;  
                    qa = qa->next;  
                    qb = qb->next;    
                    free(s);  
                }
				else{//系数之和为0，则从多项式链表A中删除qa所指节点，并free掉qa、qb所指节点  
                    LinkList s1 = qa;  
                    LinkList s2 = qb;    
                    qc->next = qa ->next;  //qc的位置不变,qa、qb向后移动  
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
    qc->next = qa ? qa : qb;//插入剩余段  
    free(Pb);//释放Pb的头节点  
}

void DerPoly(polynomial &P){//一元多项式求导
	LinkList q = P->next;  
    printf("请输入求导次数：");
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

LinkList MultiPolyn(polynomial &Pa, polynomial &Pb){//一元多项式相乘 
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

void Polynomial(int flag){//多项式操作函数
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

void PolyMenu(){//多项式操作菜单
    int k;
   	printf("1.一元多项式乘法\n");
	printf("2.一元多项式求和\n");
	printf("3.一元多项式求导");
	printf("\n===================================================================\n");
	printf("请输入您的选择：");
	scanf("%d", &k);
	Polynomial(k);
}

int prior(char x){//运算优先级 
    switch(x)
    {
        case '+':
        case '-': return 3;
        case '*':
        case '/': return 4;
        default:  exit(0);
    }
}

int calcu_two_num(char operat,int x,int y){//求值 
    switch(operat)
    {
        case '*': return x * y;
        case '/': return x / y;
        case '-': return x - y;
        case '+': return x + y;

    }
}

int calcu_by_stack(char *x){//后缀表达式求值 
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

int Mypow(int x, int y, int out){//求值所用指数函数 *
	if(y > 1){
		out *= x;
		Mypow(x, y - 1, out);
	}
	else{
		return out;
	}
}

void Arithmetic(){//四则运算操作函数
	int ans;
    char expression[MAX];
    printf("请输入需要计算的式子(乘号不可省略): ");
    scanf("%s", expression);
    ans = calcu_by_stack(expression);
    printf("计算结果是: %d\n", ans);
}

void Equation(){//表达式计算
	char equation[MAX];
	int elem;
	int temp = 0;
	printf("请输入表达式: ");
	scanf("%s", equation);
	printf("请输入变量赋值: ");
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
	printf("表达式计算结果为: %d\n", temp);
}

void DefFunction(){//定义函数 
	char func[MAX];
	printf("请输入定义的函数: ");
	scanf("%s", func);
	int out;
	int ans = 0;
	printf("请输入变量赋值: ");
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
 	printf("计算结果是:f(%d)=%d\n", out, ans);
}

void HisFunction(){//历史函数求值                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	FILE*fp2 = fopen("in.txt","r");
	char func[5][MAX];
	char find[MAX];
	printf("请输入要查找的历史函数: ");
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
				printf("请输入变量赋值: ");
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
				printf("计算结果是:f(%d)=%d\n", out, ans);
				fclose(fp2); 
				return;
			}
		i ++;
 		}
	}	
 	printf("未找到该函数！\n");
 	return;
}
 
int CreateTSMatrix(TSMatrix &M){ //创建一个矩阵
    M = (TSMatrix)malloc(sizeof(Matrix));  
    if(!M){  
        exit(0);  
    }  
    printf("输入三元组的行数，列数和非零元个数：");  
    int rc, cc, dc;  
    scanf("%d%d%d", &rc, &cc, &dc);  
    M->row_count = rc;  
    M->col_count = cc;  
    M->data_count = dc;  
    int i = 0;  
    printf("开始构造矩阵\n");  
    int r, c, d;
    while(i < dc){  
        printf("输入第%d个非零元的行号，列号和值：", i + 1);  
        scanf("%d%d%d", &r, &c, &d);  
        if(r > rc || c > cc){ //行和列不能越界  
            printf("此组数据不合法，请重新输入\n");  
            continue;  
        }else{
            M->dataArray[i + 1].row = r;  
            M->dataArray[i + 1].col = c;  
            M->dataArray[i + 1].data = d;  
            i ++;  
        }  
    }
    //构造rpos[]的值
    for(i = 1; i <= M->row_count; i ++){  
        M->rpos[i] = 0;//赋初值为0  
    }  
    for(i = 1; i <= M->data_count; i ++){  
        M->rpos[M->dataArray[i].row] ++;//计算每一行非零元个数
    }//计算rpos[]的值 
    for(i = M->row_count; i >= 1; i --){  
        M->rpos[i] = 1;  
        for(int j = i - 1; j >= 1; j --){  
            M->rpos[i] += M->rpos[j];  
        }  
    }  
    printf("构造矩阵成功\n");  
    return 1;  
}  

int PrintTSMatrix(TSMatrix M){//打印三元组矩阵
    //用描述法吧  
    for(int i = 1; i <= M->data_count; i ++){  
        printf("行号 列号 值：%d %d %d",M->dataArray[i].row,M->dataArray[i].col, M->dataArray[i].data);  
        printf("\n");  
    }  
    return 1;  
}  

int MultTSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q){//实现矩阵的乘法: Q = M * N
    int arow, brow, p, q, ccol, ctemp[MAX+1], t, tp;  
    if(M->col_count != N->row_count){//不能相乘  
        return 0;  
    }  
    if(M->data_count * N->data_count == 0){//有一个是零矩阵  
        return 0;  
    }  
    //Q初始化  
    Q->row_count = M->row_count;  
    Q->col_count = N->col_count;  
    Q->data_count = 0;  
    //从M的第一行开始到最后一行，arow是M的当前行  
    for(arow = 1; arow <= M->row_count; arow++){  
        for(ccol = 1; ccol <= Q->col_count; ccol++){  
            ctemp[ccol] = 0;//Q的当前行的各列元素清零  
        }  
        Q->rpos[arow] = Q->data_count + 1;//开始时从第一个存储位置开始存 
        if(arow < M->row_count){  
            tp = M->rpos[arow + 1];//下一行的起始位置  
        }
        else{  
            tp = M->data_count + 1;//最后一行的边界  
        }  
        for(p = M->rpos[arow]; p < tp; p ++){  
            //对M当前行的每一个非零元  
            //找到对应元素在N中的行号，即M中当前元的列号  
            brow = M->dataArray[p].col;   
            if(brow < N->row_count){  
                t = N->rpos[brow + 1];  
            }
            else{  
                t = N->data_count + 1;  
            }  
            for(q = N->rpos[brow]; q < t; q ++){  
                ccol = N->dataArray[q].col;//乘积元素在Q中列的位置  
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

void MatrixMenu(){//矩阵操作菜单
    int k;
   	printf("1.矩阵加法\n");
	printf("2.矩阵乘法\n");
	printf("3.求行列式");
	printf("\n===================================================================\n");
	printf("请输入您的选择：");
	scanf("%d", &k);
	switch(k){
		case 1:
		case 2:{  
    		TSMatrix M, N, Q;  
    		Q = (TSMatrix)malloc(sizeof(TSMatrix));  
    		CreateTSMatrix(M);  
    		printf("矩阵M：\n");  
    		PrintTSMatrix(M);  
    		CreateTSMatrix(N);  
    		printf("矩阵N：\n");  
    		PrintTSMatrix(N);  
    		MultTSMatrix(M,N,Q);  
    		printf("矩阵Q：\n");  
    		PrintTSMatrix(Q);
		}  
		case 3:;
	}
}

void MainMenu(){//主菜单
	int k;
	printf("=========================实验05-可编程计算器==========================\n");
	printf("1.同维度向量计算\n");
	printf("2.一元多项式计算(链表存储)\n");
	printf("3.四则运算表达式求值\n");
	printf("4.含变量表达式求值\n");
	printf("5.定义并运行函数\n");
	printf("6.运行历史函数\n");
	printf("7.矩阵运算\n"); 
	printf("8.一元多项式计算(顺序表存储)");
	printf("\n===================================================================\n");
	printf("请输入您的选择：");
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
