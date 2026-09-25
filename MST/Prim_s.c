#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int vertex;
    int weight;
    struct Node *next;
};

// Create a new node
struct Node* createNode(int vertex, int weight) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;

    return newNode;
}

// Add an undirected edge
void addEdge(struct Node *adj[], int src, int dest, int weight) {

    struct Node *newNode = createNode(dest, weight);
    newNode->next = adj[src];
    adj[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

// Prim's Algorithm
void prim(struct Node *adj[], int n, int start) {

    int inMST[n];
    int key[n];
    int parent[n];

    // Initially, no node is in MST
    for (int i = 0; i < n; i++) {
        inMST[i] = 0;
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    // Step 1 & 2:
    // T = {starting node}
    key[start] = 0;

    int totalWeight = 0;

    printf("\nEdges in Minimum Spanning Tree:\n");

    // Repeat n times
    for (int count = 0; count < n; count++) {

        // Find minimum weight vertex not in MST
        int min = INT_MAX;
        int u = -1;

        for (int i = 0; i < n; i++) {

            if (!inMST[i] && key[i] < min) {
                min = key[i];
                u = i;
            }
        }

        // Add vertex u to MST
        inMST[u] = 1;

        // Add its edge to MST
        if (parent[u] != -1) {

            printf("%d -- %d : %d\n",
                   parent[u], u, key[u]);

            totalWeight += key[u];
        }

        // Update adjacent vertices
        struct Node *temp = adj[u];

        while (temp != NULL) {

            int v = temp->vertex;
            int weight = temp->weight;

            if (!inMST[v] && weight < key[v]) {

                key[v] = weight;
                parent[v] = u;
            }

            temp = temp->next;
        }
    }

    printf("\nTotal weight of MST = %d\n", totalWeight);
}

int main() {

    int n, m;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &m);

    struct Node *adj[n];

    // Initialize adjacency list
    for (int i = 0; i < n; i++)
        adj[i] = NULL;

    printf("\nEnter edges (source destination weight):\n");

    for (int i = 0; i < m; i++) {

        int src, dest, weight;

        scanf("%d %d %d", &src, &dest, &weight);

        addEdge(adj, src, dest, weight);
    }

    int start;

    printf("\nEnter starting vertex: ");
    scanf("%d", &start);

    prim(adj, n, start);

    return 0;
}