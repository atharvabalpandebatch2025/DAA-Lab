#include <stdio.h>
#include <limits.h>

#define INF 1000000000

struct Edge {
int u, v, w;
};

int main() {
	int n, m;

	scanf("%d", &n);
	scanf("%d", &m);
	struct Edge edges[m];

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d",
			&edges[i].u,
			&edges[i].v,
			&edges[i].w);
	}


	int source;
	scanf("%d", &source);

	int dist[n + 1];
	int parent[n + 1];

	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
		parent[i] = -1;
	}

	dist[source] = 0;

	for (int i = 1; i <= n - 1; i++) {
		int changed = 0;

		for (int j = 0; j < m; j++) {
			int u = edges[j].u;
			int v = edges[j].v;
			int w = edges[j].w;

			if (dist[u] != INF && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				parent[v] = u;
				changed = 1;
			}
		}

		if (!changed)
			break;
	}

for (int i=0;i<m;i++){
	int u = edges[i].u;
	int v = edges[i].v;
	int w = edges[i].w;
	if (dist[u] != INF && dist[u] + w < dist[v]) {
		printf("Negative cycle detected\n");
		return 0;
	}
	}

	for (int v = 1; v <= n; v++) {
		if (v == source)
			continue;
		if (dist[v] == INF) {
			printf("%d INF None\n", v);
			continue;
		}
		int path[n + 1];
		int count = 0;
		int current = v;

		while (current != -1) {
			path[count++] = current;
			current = parent[current];
		}
		printf("%d %d ", v, dist[v]);

		for (int i = count - 1; i >= 0; i--) {
			printf("%d", path[i]);
			if (i != 0)
				printf("->");
		}

		printf("\n");
	}
	return 0;
}