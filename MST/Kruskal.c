#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    int weight;
    struct Node *next;
};

struct Edge {
    int src;
    int dest;
    int weight;
};

// Create a new node
struct Node* createNode(int vertex, int weight) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;

    return newNode;
}

// Add edge to adjacency list
void addEdge(struct Node *adj[], int src, int dest, int weight) {

    // src -> dest
    struct Node *newNode = createNode(dest, weight);
    newNode->next = adj[src];
    adj[src] = newNode;

    // dest -> src (undirected graph)
    newNode = createNode(src, weight);
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

// Find parent of a vertex
int find(int parent[], int x) {

    if (parent[x] == x)
        return x;

    return parent[x] = find(parent, parent[x]);
}

// Union two sets
void unionSet(int parent[], int rank[], int x, int y) {

    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;

        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;

        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Sort edges according to weight
int compare(const void *a, const void *b) {

    struct Edge *e1 = (struct Edge*)a;
    struct Edge *e2 = (struct Edge*)b;

    return e1->weight - e2->weight;
}

// Kruskal's Algorithm
void kruskal(struct Edge edges[], int n, int m) {

    int parent[n];
    int rank[n];

    // Initially, every vertex is a separate set
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // 1. Sort the m edges in increasing weight order
    qsort(edges, m, sizeof(struct Edge), compare);

    // 2. E = {} -> MST initially empty
    struct Edge MST[n - 1];

    // 3. i = 0 -> counter for edges
    int i = 0;
    int count = 0;

    // 4. While |E| < n-1
    while (count < n - 1 && i < m) {

        // Check whether adding edges[i] creates a cycle
        int src = edges[i].src;
        int dest = edges[i].dest;

        if (find(parent, src) != find(parent, dest)) {

            // No cycle, so add edge to MST
            MST[count] = edges[i];

            unionSet(parent, rank, src, dest);

            count++;
        }

        // i = i + 1
        i++;
    }

    // 5. Return E
    printf("\nMinimum Spanning Tree:\n");

    int totalWeight = 0;

    for (i = 0; i < count; i++) {

        printf("%d -- %d : %d\n",
               MST[i].src,
               MST[i].dest,
               MST[i].weight);

        totalWeight += MST[i].weight;
    }

    printf("\nTotal weight = %d\n", totalWeight);
}

int main() {

    int n, m;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &m);

    // Adjacency list
    struct Node *adj[n];

    for (int i = 0; i < n; i++)
        adj[i] = NULL;

    printf("\nEnter edges (source destination weight):\n");

    for (int i = 0; i < m; i++) {

        int src, dest, weight;

        scanf("%d %d %d", &src, &dest, &weight);

        addEdge(adj, src, dest, weight);
    }

    // Extract edges from adjacency list
    struct Edge edges[m];
    int edgeCount = 0;

    for (int i = 0; i < n; i++) {

        struct Node *temp = adj[i];

        while (temp != NULL) {

            // Since graph is undirected,
            // store each edge only once
            if (i < temp->vertex) {

                edges[edgeCount].src = i;
                edges[edgeCount].dest = temp->vertex;
                edges[edgeCount].weight = temp->weight;

                edgeCount++;
            }

            temp = temp->next;
        }
    }

    // Apply Kruskal
    kruskal(edges, n, edgeCount);

    return 0;
}