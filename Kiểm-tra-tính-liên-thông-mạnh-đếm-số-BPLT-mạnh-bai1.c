#include <stdio.h>


#define MAX_N 100
int on_stack[MAX_N];
int min_num[MAX_N];
int num[MAX_N];
int k = 1;
int dem = 0;



typedef struct{
	int size;
	int data[MAX_N];
}Stack;
Stack S;

void make_null_stack(Stack *S){
	S->size = 0;
}

int top(Stack *S){
	return S->data[S->size-1];
}
void push(Stack *S, int X){
	S->data[S->size] = X;
	S->size++;
}

void pop(Stack *S){
	S->size--;
}

int empty(Stack *S){
	return S->size == 0;
}

typedef struct{
	int size;
	int data[MAX_N];
}List;


void make_null_list(List* L){
	L->size = 0;
}

void push_back(List* L, int X){
	L->data[L->size] = X;
	L->size++;
}

int element_at(List* L, int P){
	return L->data[P-1];
}


typedef struct{
	int n;
	int A[MAX_N][MAX_N];
}Graph;


void init_graph(Graph *G, int n){
	G->n = n;
	int i, j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			G->A[i][j] = 0;
		}
	}
}


void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
}

int adjacent(Graph *G, int x, int y){
	return G->A[x][y] == 1;
}


List neighbours(Graph *G, int x){
	int y;
	List L;
	make_null_list(&L);
	for(y = 1; y <= G->n; y++){
		if(x == y) continue;
		if(adjacent(G, x, y)){
			push_back(&L, y);
		}
	}
	return L;
}
int min(int a, int b){
	return a > b ? b : a;
}
void strong_connect(Graph *G, int x){
	num[x] = min_num[x] = k; k++;
	push(&S, x);
	on_stack[x] = 1;
	
	List L = neighbours(G, x);
	int j;
	
	for(j = 1; j <= L.size; j++){
		int y = element_at(&L, j);
		
		if(num[y] < 0){
			strong_connect(G, y);
			min_num[x] = min(min_num[x], min_num[y]);
		}else if(on_stack[y]){
			min_num[x] = min(min_num[x], num[y]);
		}
	}
	
	if(min_num[x] == num[x]){
		int w;
		dem++;
		do{
			w = top(&S); pop(&S);
			on_stack[w] = 0;
		}while(w != x);
	}
}


int main(){
	//freopen("dt.txt", "r", stdin);
	int x, y, n, m, p;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	int i;
	for(i = 1; i <= m; i++){
		scanf("%d%d", &x, &y);
		add_edge(&G, x, y);
   }
	make_null_stack(&S);
	for(i = 1; i <= n; i++){
		on_stack[i] = 0;
		num[i] = -1;
	}

   for(i=1; i<=n;i++){
   	   if(num[i] == -1){
   	   	strong_connect(&G, i);
	   }
   }
     
     if(dem == 1){
     	printf("strong connected\n");
	 }else if(dem > 1){
	 	printf("unconnected\n");
	 }
	 
	return 0;
}
