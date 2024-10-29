#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];  // 부모 노드

void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

struct Edge {
    int start, end, weight;
};

typedef struct GraphType {
    int n;  // 간선의 개수
    struct Edge edges[2 * MAX_VERTICES];  // 간선 배열
} GraphType;

void graph_init(GraphType* g) {
    g->n = 0;
    // 간선 배열의 모든 필드 초기화
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = -1;  // -1로 초기화하여 유효하지 않은 간선 표시
        g->edges[i].end = -1;
        g->edges[i].weight = INF;
    }
}

void insert_edge(GraphType* g, int start, int end, int w) {
    if (g->n < 2 * MAX_VERTICES) {  // 배열 크기 체크
        g->edges[g->n].start = start;
        g->edges[g->n].end = end;
        g->edges[g->n].weight = w;
        g->n++;
    }
    else {
        printf("Error: Exceeded maximum number of edges.\n");
    }
}

void GenerateGraph(GraphType* g) {
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 9, 10, 10);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 6, 5, 9);
    insert_edge(g, 7, 2, 8);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 8, 7, 13);
    insert_edge(g, 8, 4, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);
}

int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

void QuickKruskal(GraphType* g) {  // 함수 이름 변경
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(g->n);
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->n - 1) && i < g->n) {  // i의 범위 체크 추가
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }

    // QuickKruskal과 MinHeapKruskal 사이에 줄 띄우기
    printf("\n");  // 줄 띄우기
}

typedef struct MinHeap {
    struct Edge* edges;
    int capacity;
    int size;
} MinHeap;

MinHeap* create_minheap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->edges = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    return minHeap;
}

void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
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

struct Edge extract_min(MinHeap* heap) {
    if (heap->size == 0) return (struct Edge) { -1, -1, INF };

    struct Edge root = heap->edges[0];
    if (heap->size > 1) {
        heap->edges[0] = heap->edges[heap->size - 1];
        min_heapify(heap, 0);
    }
    heap->size--;
    return root;
}

void insert_min_heap(MinHeap* heap, struct Edge edge) {
    if (heap->size == heap->capacity) return;

    int i = heap->size++;
    while (i && edge.weight < heap->edges[(i - 1) / 2].weight) {
        heap->edges[i] = heap->edges[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->edges[i] = edge;
}

void MinHeapKruskal(GraphType* g) {  // 함수 이름 변경
    int edge_accepted = 0;
    int uset, vset;

    set_init(g->n);

    MinHeap* heap = create_minheap(g->n);
    for (int i = 0; i < g->n; i++) {
        insert_min_heap(heap, g->edges[i]);
    }

    printf("MinHeap Based Kruskal\n");
    while (edge_accepted < (g->n - 1) && heap->size > 0) {
        struct Edge e = extract_min(heap);
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }

    free(heap->edges);
    free(heap);
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    // 그래프를 생성하는 함수
    GenerateGraph(g);

    // QuickSort 기반 Kruskal
    QuickKruskal(g);  // 함수 호출 변경

    // MinHeap 기반 Kruskal
    MinHeapKruskal(g);  // 함수 호출 변경

    free(g);
    return 0;
}
