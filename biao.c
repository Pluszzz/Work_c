#include<stdio.h>
struct olnode{
	int i,j;
	double e;
	olnode *right ,*down;
};
struct crosslist{//十字链表
	olnode **rhead,**chead;//行指针，列指针 
	int mu ,nu,tu;// 行数，列数，非零元素数 
};
int creatlist(crosslist &M){
	int m,n,t;
	printf("依次输入行，列，元素数目：");
	scanf("%d,%d,%d",&m,&n,&t);
	if(m<=0||n<=0||(m*n)<t||m>20||n>20){
		printf("error\n");
		return 0;
	}
	else{
	M.mu=m;
	M.nu=n;
	M.tu=t;
	M.rhead= new olnode *[m+1];
	M.chead= new olnode *[n+1];
	for(int i=0;i<=M.mu;i++)
	M.rhead[i]=NULL;
	for(int i=0;i<=M.nu;i++)
	M.chead[i]=NULL;
	return t;
	}
}
void creatlist1(crosslist &M,int a,int b){
	M.mu=a;
	M.nu=b;
	M.tu=0;
	M.rhead= new olnode *[a+1];
	M.chead= new olnode *[b+1];
	for(int i=0;i<=M.mu;i++)
	M.rhead[i]=NULL;
	for(int i=0;i<=M.nu;i++)
	M.chead[i]=NULL;	
}
int check(crosslist M,int a,int b){
	olnode *p=M.rhead[a];
	olnode *q=M.chead[b];
	int l1=0,l2=0;
	if(M.rhead[a]==NULL||M.chead[b]==NULL) return 1;
	if(p->j==b) return 0;
	else{while(p->j!=b&&p->right!=NULL){
		p=p->right;
		if(p->j==b)l1=1;
	}
	if(l1==1)return 0;
	else return 1;
	}
}
int inlist(crosslist &M,int m,int n,double e){
    int f = 0;
    olnode *p = new olnode;
    p->i = m;
    p->j = n;
    p->e = e;
    olnode *q = new olnode;

    if (e == 0);
    else
        if (m > M.mu || n > M.nu||m<1||n<1)
            f = 1;
        else if (check(M, m, n) == 0) f = 1;       
 else {
            if (M.rhead[m] == NULL || M.rhead[m]->j > n)        
 {
                p->right = M.rhead[m];
                M.rhead[m] = p;
            }
            
            else {
                for (q = M.rhead[m]; (q->right) && q->right->j < n; q = q->right);
                p->right = q->right;
                q->right = p;
            }
            if (M.chead[n] == NULL || M.chead[n]->i > m)
            {
                p->down = M.chead[n];
                M.chead[n] = p;
            }
            else {
                for (q = M.chead[n]; (q->down) && q->down->i < m; q = q->down);
                p->down = q->down;
                q->down = p;
            }
        }
    return f;
    }
void printflist(crosslist a){
  int m = a.mu, n = a.nu;
    olnode *p = new olnode;
       for (int i = 1; i <= m; i++) {
        p = a.rhead[i];
        {
            for (int j = 1; j <= n; j++) {
                if (p && p->j == j) {
                    printf("%6.f", p->e);
                    p = p->right;
                }
                else printf(" 0 ");
            }
            printf("\n");
        }
    }
}
void addlist(crosslist a, crosslist b, crosslist &c) {//加法
    int m = a.mu, n = a.nu;
    double xa = 0, xb = 0;
    olnode *p = new olnode;
    olnode *q = new olnode;
    for (int i = 1; i <= m; i++) {
        p = a.rhead[i];
        q = b.rhead[i];
        {
            for (int j = 1; j <= n; j++) {
                if (p && p->j == j) {
                    xa = p->e;
                    p = p->right;
                }
                else xa = 0;
                if (q && q->j == j) {
                    xb = q->e;
                    q = q->right;
                }
                else xb = 0;
                if ((xa + xb) != 0) inlist(c, i, j, xa + xb);
            }
        }
    }
}
void sublist(crosslist a, crosslist b, crosslist &c) {//减法
    int m = a.mu, n = a.nu;
    double xa = 0, xb = 0;
    olnode *p = new olnode;
    olnode *q = new olnode;
    for (int i = 1; i <= m; i++) {
        p = a.rhead[i];
        q = b.rhead[i];
        {
            for (int j = 1; j <= n; j++) {
                if (p && p->j == j) {
                    xa = p->e;
                    p = p->right;
                }
                else xa = 0;
                if (q && q->j == j) {
                    xb = -(q->e);
                    q = q->right;
                }
                else xb = 0;
                if ((xa + xb) != 0) inlist(c, i, j, xa + xb);
            }
        }
    }
}
void mullist(crosslist a, crosslist b, crosslist &c) {//乘法
    double xa = 0, xb = 0, x = 0;
    olnode *p = new olnode;
    olnode *q = new olnode;
    for (int i = 1; i <= a.mu; i++) {
        p = a.rhead[i];
        for (int j = 1; j <= b.nu; j++) {
            q = b.chead[j];
            x = 0;
            for (int k = 1; k <= a.nu; k++) {
                if (p && p->j == k) {
                    xa = p->e;
                    p = p->right;
                }
                else xa = 0;
                if (q && q->i == k) {
                    xb = q->e;
                    q = q->down;
                }
                else xb = 0;
                x = x + xa * xb;
                xa = 0; xb = 0;
            }
            if (x != 0) {
                inlist(c, i, j, x);
                x = 0;
                
            }
            p = a.rhead[i];
        }
        
    }
}
int main(){
	int num1=0;
	int num2=0;
	int num3=0;
	int a,b,ch;
	double e;
	crosslist list1, list2, list3;
    printf( " 请输入要进行的操作\n 1:加法\n 2:减法\n 3:乘法\n");
    scanf("%d",&ch);
    num1 = creatlist(list1);
    num2 = creatlist(list2);
        if (ch == 1) {//加法
            if (list1.mu == list2.mu&&list1.nu == list2.nu) {
        creatlist1(list3, list1.mu, list1.nu);
        for (int i = 0; i < num1; i++) {
            printf("依次输入矩阵1的行，列，元素值" );
            scanf("%d,%d,%lf",&a,&b,&e);
            inlist(list1, a, b, e);
                }
                printflist(list1);
        for (int i = 0; i < num2; i++) {
            printf("依次输入矩阵2的行，列，元素值");
            scanf("%d,%d,%lf",&a,&b,&e);
            inlist(list2, a, b, e);
                }
                printflist(list2);
            }
                addlist(list1, list2, list3);
                printf("相加之后的结果为：\n");
                printflist(list3);
            }
        else
            if (ch == 2) {//减法
                if (list1.mu == list2.mu&&list1.nu == list2.nu) {
        creatlist1(list3, list1.mu, list1.nu);
        for (int i = 0; i < num1; i++) {
            printf("依次输入矩阵1的行，列，元素值" );
            scanf("%d,%d,%lf",&a,&b,&e);
            inlist(list1, a, b, e);
                }
                printflist(list1);
        for (int i = 0; i < num2; i++) {
            printf("依次输入矩阵2的行，列，元素值");
            scanf("%d,%d,%lf",&a,&b,&e);
            inlist(list2, a, b, e);
                }
                printflist(list2);
            }
                    sublist(list1, list2, list3);
                    printf("相减之后的结果为：\n");
                    printflist(list3);
                }
            else
                if (ch == 3) {//乘法
                if (list1.nu == list2.mu) {
                        creatlist1(list3, list1.mu, list2.nu);
        for (int i = 0; i < num1; i++) {
            printf("依次输入矩阵1的行，列，元素值" );
            scanf("%d,%d,%lf",&a,&b,&e);
            inlist(list1, a, b, e);
                }
                printflist(list1);
        for (int i = 0; i < num2; i++) {
            printf("依次输入矩阵2的行，列，元素值");
            scanf("%d,%d,%lf",&a,&b,&e);
            inlist(list2, a, b, e);
                }
                printflist(list2);
            }
                        mullist(list1, list2, list3);
                        printf("相乘之后结果为：\n"); 
                        printflist(list3);
                    }
}
