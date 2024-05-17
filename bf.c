#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF_SYMBOL 'x'

struct Edge {
    int source, destination, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

void printTable(int dist[], int parent[], int V, int iteration) {
    printf("Iteration %d:\n", iteration);
    printf("Vertex   Distance from Source   Parent\n");
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t %c \t\t\t\t %d\n", i, INF_SYMBOL, parent[i]);
        else
            printf("%d \t\t %d \t\t\t\t %d\n", i, dist[i], parent[i]);
    }
    printf("\n");
}

void BellmanFord(struct Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];

    for (int i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[source] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                printTable(dist, parent, V, i + 1); // Print table after each iteration
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < E; ++j) {
        int u = graph->edge[j].source;
        int v = graph->edge[j].destination;
        int weight = graph->edge[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle.\n");
            return;
        }
    }

    printf("Final Result:\n");
    printTable(dist, parent, V, V - 1);
}

int main() {
    int V, E, source;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter source vertex: ");
    scanf("%d", &source);

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; ++i) {
        scanf("%d %d %d", &graph->edge[i].source, &graph->edge[i].destination, &graph->edge[i].weight);
    }

    BellmanFord(graph, source);

    return 0;
}
