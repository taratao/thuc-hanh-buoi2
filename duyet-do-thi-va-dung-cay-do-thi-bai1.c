#include <stdio.h>


#define MAX_N 100
int mark[MAX_N];
int parent[MAX_N];

typedef struct{
	int font, rear;
	int data[MAX_N];
}Queue;

void make_null_queue(Queue *Q){
	Q->rear = -1;
	Q->font = 0;
}

void push(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear] = x;
}

void pop(Queue *Q){
	Q->font++;
}

int top(Queue *Q){
	return Q->data[Q->font];
}

int empty(Queue *Q){
	return Q->font > Q->rear;
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
	G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y){
	return G->A[x][y] == 1 || G->A[y][x] == 1;
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


void bfs(Graph *G, int s){
	Queue frontier;
	
	make_null_queue(&frontier);
	
	push(&frontier, s);
	mark[s] = 1;
	
	while(!empty(&frontier)){
		int x = top(&frontier); pop(&frontier);
		
		List L = neighbours(G, x);
		
		int j;
		for(j = 1; j <= L.size; j++){
			int y = element_at(&L, j);
			if(mark[y] == 0){
				push(&frontier, y);
				mark[y] = 1;
				parent[y] = x;
			}
		}
	}
}


int main(){
	//freopen("dt.txt", "r", stdin);
	int x, y, n, m;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	int i;
	for(i = 1; i <= m; i++){
		scanf("%d%d", &x, &y); 
		add_edge(&G, x, y);
	}
	
	for(i = 1; i <= n; i++){
		mark[i] = 0;
		parent[i] = 0;
	}
	
	for(i = 1; i <= n; i++){
		if(mark[i] == 0){
			bfs(&G, i);
		}
	}
	
	for(i = 1; i <= n; i++){
		printf("%d %d\n", i, parent[i]);
	}
	return 0;
}
