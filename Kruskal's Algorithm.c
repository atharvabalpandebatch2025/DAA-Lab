#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
int u, v, cost;
} Edge;

int find(int parent[], int x) {
	if (parent[x] != x)
		parent[x] = find(parent, parent[x]);
	return parent[x];
}
void unionSet(int parent[], int rank[], int x, int y) {
	x = find(parent, x);
	y = find(parent, y);
	if (x == y)
		return;
	if (rank[x] < rank[y])
		parent[x] = y;
	else if (rank[x] > rank[y])
		parent[y] = x;
	else {
		parent[y] = x;
		rank[x]++;
	}
}

int compareEdges(const void *a, const void *b) {
	Edge *e1 = (Edge *)a;
	Edge *e2 = (Edge *)b;
	if (e1->cost != e2->cost)
		return e1->cost - e2->cost;
	if (e1->u != e2->u)
		return e1->u - e2->u;
	return e1->v - e2->v;
}
void kruskalMST(int **cost, int V) {
	Edge *edges = malloc(V * V * sizeof(Edge));
	int edgeCount = 0;
	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++) {
			if (cost[i][j] != 9999) {
				edges[edgeCount].u = i;
				edges[edgeCount].v = j;
				edges[edgeCount].cost = cost[i][j];
				edgeCount++;
			}
		}
	}
	qsort(edges, edgeCount, sizeof(Edge), compareEdges);
	int *parent = malloc(V * sizeof(int));
	int *rank = calloc(V, sizeof(int));
	for (int i = 0; i < V; i++)
		parent[i] = i;
	int totalCost = 0;
	int selected = 0;
	for (int i = 0; i < edgeCount && selected < V - 1; i++) {
		int u = edges[i].u;
		int v = edges[i].v;
		if (find(parent, u) != find(parent, v)) {
			unionSet(parent, rank, u, v);
			printf("Edge %d:(%d, %d) cost:%d\n",
				selected, u, v, edges[i].cost);
			totalCost += edges[i].cost;
			selected++;
		}
	}
	printf("Minimum cost= %d\n", totalCost);
	free(edges);
	free(parent);
	free(rank);
}

int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        cost[i] = (int *)malloc(V * sizeof(int));

    printf("Adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, V);

    for (int i = 0; i < V; i++)
        free(cost[i]);
    free(cost);

    return 0;
}