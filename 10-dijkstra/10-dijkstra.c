#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 11
#define INF INT_MAX

// 그래프 출력 함수
void printState(int distance[], int found[], int vertices) {
    printf("Distance: ");
    for (int i = 1; i < vertices; i++) {
        if (distance[i] == INF) {
            printf("* ");
        }
        else {
            printf("%d ", distance[i]);
        }
    }
    printf("\nFound: ");
    for (int i = 1; i < vertices; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

// 최소 거리 정점 찾기
int getMinVertex(int distance[], int found[], int vertices) {
    int minDistance = INF;
    int minVertex = -1;
    for (int i = 1; i < vertices; i++) {
        if (!found[i] && distance[i] < minDistance) {
            minDistance = distance[i];
            minVertex = i;
        }
    }
    return minVertex;
}

// Dijkstra 알고리즘
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int startVertex, int vertices) {
    int distance[MAX_VERTICES];
    int found[MAX_VERTICES] = { 0 };

    for (int i = 0; i < vertices; i++) {
        distance[i] = INF;
    }
    distance[startVertex] = 0;

    for (int i = 0; i < vertices - 1; i++) {
        int u = getMinVertex(distance, found, vertices);
        if (u == -1) break;
        found[u] = 1;

        for (int v = 1; v < vertices; v++) {
            if (graph[u][v] && !found[v] && distance[u] != INF &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
        printState(distance, found, vertices);
    }
}

// 메인 함수
int main() {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    // 간선 추가 (인접 행렬 초기화)
    graph[1][2] = 3; graph[2][1] = 3;
    graph[2][5] = 1; graph[5][2] = 1;
    graph[3][4] = 2; graph[4][3] = 2;
    graph[2][4] = 4; graph[4][2] = 4;
    graph[3][8] = 5; graph[8][3] = 5;
    graph[3][7] = 6; graph[7][3] = 6;
    graph[2][6] = 7; graph[6][2] = 7;
    graph[9][10] = 10; graph[10][9] = 10;
    graph[8][10] = 15; graph[10][8] = 15;
    graph[1][7] = 12; graph[7][1] = 12;
    graph[1][6] = 11; graph[6][1] = 11;
    graph[6][5] = 9; graph[5][6] = 9;
    graph[7][2] = 8; graph[2][7] = 8;
    graph[2][3] = 5; graph[3][2] = 5;
    graph[8][7] = 13; graph[7][8] = 13;
    graph[8][4] = 14; graph[4][8] = 14;
    graph[4][10] = 16; graph[10][4] = 16;
    graph[4][5] = 13; graph[5][4] = 13;
    graph[5][10] = 17; graph[10][5] = 17;
    graph[5][9] = 18; graph[9][5] = 18;

    dijkstra(graph, 1, MAX_VERTICES);

    return 0;
}
