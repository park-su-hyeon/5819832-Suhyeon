#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

typedef struct {
    int start;
    int end;
    int weight;
} EdgeType;

typedef struct {
    int numVertices;
    int numEdges;
    EdgeType edges[MAX_EDGES];
} GraphType;

// Disjoint Set for union-find
int parent[MAX_VERTICES];

void graph_init(GraphType* g) {
    g->numEdges = 0;
    g->numVertices = 0;
}

void add_edge(GraphType* g, int start, int end, int weight) {
    g->edges[g->numEdges].start = start;
    g->edges[g->numEdges].end = end;
    g->edges[g->numEdges].weight = weight;
    g->numEdges++;
}

// Find function for disjoint set
int find(int v) {
    if (parent[v] != v) {
        parent[v] = find(parent[v]);
    }
    return parent[v];
}

// Union function for disjoint set
void union_sets(int u, int v) {
    parent[find(u)] = find(v);
}

// Comparator function for qsort
int compare(const void* a, const void* b) {
    EdgeType* edgeA = (EdgeType*)a;
    EdgeType* edgeB = (EdgeType*)b;
    return edgeA->weight - edgeB->weight;
}

// Qsort-based Kruskal
void QsortKruskal(GraphType* g) {
    // Initialize the disjoint set
    for (int i = 0; i < g->numVertices; i++) {
        parent[i] = i;
    }

    // Sort edges by weight
    qsort(g->edges, g->numEdges, sizeof(EdgeType), compare);

    printf("Using Qsort-based Kruskal Algorithm:\n");
    int select_count = 1; // To track selection index
    for (int i = 0; i < g->numEdges; i++) {
        int u = g->edges[i].start;
        int v = g->edges[i].end;
        if (find(u) != find(v)) {
            union_sets(u, v);
            printf("Edge (%d, %d) select %d\n", u, v, select_count++);
        }
    }
}

// MinHeap Structure
typedef struct {
    EdgeType* edges;
    int size;
    int capacity;
} MinHeap;

MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->edges = (EdgeType*)malloc(capacity * sizeof(EdgeType));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(EdgeType* a, EdgeType* b) {
    EdgeType temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->edges[left].weight < heap->edges[smallest].weight)
        smallest = left;

    if (right < heap->size && heap->edges[right].weight < heap->edges[smallest].weight)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->edges[idx], &heap->edges[smallest]);
        min_heapify(heap, smallest);
    }
}

EdgeType extract_min(MinHeap* heap) {
    if (heap->size == 0) {
        EdgeType edge = { -1, -1, -1 }; // Return an invalid edge
        return edge;
    }
    EdgeType minEdge = heap->edges[0];
    heap->edges[0] = heap->edges[--heap->size];
    min_heapify(heap, 0);
    return minEdge;
}

void insert_min_heap(MinHeap* heap, EdgeType edge) {
    if (heap->size == heap->capacity) {
        printf("MinHeap capacity reached!\n");
        return;
    }
    heap->edges[heap->size++] = edge;
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        min_heapify(heap, i);
    }
}

// MinHeap-based Kruskal
void MinHeapKruskal(GraphType* g) {
    // Initialize the disjoint set
    for (int i = 0; i < g->numVertices; i++) {
        parent[i] = i;
    }

    MinHeap* heap = create_min_heap(g->numEdges);
    for (int i = 0; i < g->numEdges; i++) {
        insert_min_heap(heap, g->edges[i]);
    }

    printf("Using MinHeap-based Kruskal Algorithm:\n");
    int select_count = 1; // To track selection index
    for (int i = 0; i < g->numEdges; i++) {
        EdgeType edge = extract_min(heap);
        if (find(edge.start) != find(edge.end)) {
            union_sets(edge.start, edge.end);
            printf("Edge (%d, %d) select %d\n", edge.start, edge.end, select_count++);
        }
    }

    free(heap->edges);
    free(heap);
}

// Function to generate a sample graph
void GenerateGraph(GraphType* g) {
    g->numVertices = 10; // Number of vertices
    add_edge(g, 2, 5, 1);
    add_edge(g, 3, 4, 2);
    add_edge(g, 1, 2, 3);
    add_edge(g, 2, 4, 4);
    add_edge(g, 3, 8, 5);
    add_edge(g, 3, 7, 6);
    add_edge(g, 2, 6, 7);
    add_edge(g, 9, 10, 10);
    add_edge(g, 8, 10, 15);
    add_edge(g, 1, 7, 12);
    add_edge(g, 1, 6, 11);
    add_edge(g, 6, 5, 9);
    add_edge(g, 7, 2, 8);
    add_edge(g, 2, 3, 5);
    add_edge(g, 8, 7, 13);
    add_edge(g, 8, 4, 14);
    add_edge(g, 4, 10, 16);
    add_edge(g, 4, 5, 13);
    add_edge(g, 5, 10, 17);
    add_edge(g, 5, 9, 18);
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    GenerateGraph(g);
    QsortKruskal(g);
    printf("\n");
    MinHeapKruskal(g);
    free(g);
    return 0;
}

