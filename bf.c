#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a structure for an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Define a structure for a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to run the Bellman-Ford algorithm
void bellmanFord(struct Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int distance[V];
    int parent[V];

    // Initialize distances from source to all other vertices as INFINITE
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    distance[source] = 0;

    printf("Step\tVertex\tDistance\n");

    // Relax all edges |V| - 1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].source;
            int v = graph->edges[j].destination;
            int w = graph->edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                parent[v] = u;
            }
        }
        // Print the current state of distances after relaxation in this iteration
        for (int j = 0; j < V; j++) {
            printf("%d\t%d\t", i + 1, j);
            if (distance[j] == INT_MAX)
                printf("INF\n");
            else
                printf("%d\n", distance[j]);
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].source;
        int v = graph->edges[j].destination;
        int w = graph->edges[j].weight;
        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d%d", &V, &E);

    struct Graph* graph = createGraph(V, E);

    printf("Enter source, destination, and weight for each edge:\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d:\n", i + 1);
        printf("Source: ");
        scanf("%d", &graph->edges[i].source);
        printf("Destination: ");
        scanf("%d", &graph->edges[i].destination);
        printf("Weight: ");
        scanf("%d", &graph->edges[i].weight);
    }

    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);

    bellmanFord(graph, source);

    // Free dynamically allocated memory
    free(graph->edges);
    free(graph);

    return 0;
}