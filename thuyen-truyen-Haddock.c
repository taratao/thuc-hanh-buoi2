#include <stdio.h>

#define white 0
#define gray 2
#define black 1

#define MAX_N 100

int cycle;
int color[MAX_N];

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


void dfs(Graph *G, int s){
	color[s] = gray;
	
	List L = neighbours(G, s);
	int j;
	for(j = 1; j <= L.size; j++){
		int y = element_at(&L, j);
		
		if(color[y] == gray){
			cycle = 1;
			return;
		}
		
		if(color[y] == white){
			dfs(G, y);
		}
	}
	
	color[s] = black;
}

int check_contains_cycle(Graph *G){
	int j;
	for(j = 1; j <= G->n; j++){
		color[j] = white;
	}
	
	cycle = 0;
	for(j = 1; j <= G->n; j++){
		if(color[j] == white){
			dfs(G, j);
		}
	}
	return cycle;
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
	
	if(check_contains_cycle(&G)){
		printf("NO");
	}
	else{
		printf("YES");
	}
	
	return 0;
}
