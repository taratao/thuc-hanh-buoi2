#include <stdio.h>



#define MAX_N 100

int color[MAX_N];
int fail;

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

void colorize(Graph* G, int x, int c){
	if(color[x] == -1){
		color[x] = c;
		List L = neighbours(G, x);
		int j;
		
		for(j = 1; j <= L.size; j++){
			int y = element_at(&L, j);
			colorize(G, y, !c);
		}
	}else{
		if(color[x] != c){
			fail = 1;
		}
	}
}

int is_bigraph(Graph *G){
	int j;
	
	for(j = 1; j <= G->n; j++){
		color[j] = -1;
	}
	
	fail = 0;
	colorize(G, 1, 0);
	return !fail;
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
	
	if(is_bigraph(&G)){
		for(i = 1; i <= n; i++){
			if(color[i] == 0) printf("%d ", i);
		}
		printf("\n");
		for(i = 1; i <= n; i++){
			if(color[i] == 1) printf("%d ", i);
		}
	}else{
		printf("IMPOSSIBLE");
	}
	
	return 0;
}
