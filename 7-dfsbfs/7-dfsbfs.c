#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 11  // 정점의 수

typedef struct Node {
    int vertex;          // 정점 번호
    struct Node* next;   // 다음 노드 포인터
} Node;

typedef struct Graph {
    Node* adjList[MAX_VERTICES]; // 인접 리스트 배열
    int visited[MAX_VERTICES];     // 방문 여부 배열
    int vertexCount;               // 정점의 수
} Graph;

// 그래프 생성 함수
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->vertexCount = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;  // 인접 리스트 초기화
        graph->visited[i] = 0;      // 방문 배열 초기화
    }

    return graph;
}

// 엣지 추가 함수 (양방향)
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = dest;       // 목적지 정점
    newNode->next = graph->adjList[src]; // 현재 출발 정점의 리스트 앞에 추가
    graph->adjList[src] = newNode;

    newNode = malloc(sizeof(Node));
    newNode->vertex = src;        // 반대 방향 정점
    newNode->next = graph->adjList[dest]; // 목적지 정점의 리스트 앞에 추가
    graph->adjList[dest] = newNode;
}

// 깊이 우선 탐색 함수
void dfs(Graph* graph, int start, int target) {
    int stack[MAX_VERTICES];
    int top = -1;                // 스택의 탑 초기화
    int count = 0;               // 방문한 노드 수

    stack[++top] = start;        // 시작 정점을 스택에 푸시

    while (top != -1) {
        int current = stack[top--]; // 스택에서 정점 팝

        if (!graph->visited[current]) {
            graph->visited[current] = 1; // 방문 표시
            printf("%d ", current);
            count++;

            if (current == target) { // 목표 정점 찾기
                printf("\n탐색 성공: %d\n", target);
                printf("방문한 노드의 수: %d\n", count);
                return; // 목표 발견
            }

            Node* adjList = graph->adjList[current];
            while (adjList != NULL) {
                if (!graph->visited[adjList->vertex]) {
                    if (top < MAX_VERTICES - 1) { // 스택 범위 체크
                        stack[++top] = adjList->vertex; // 인접 정점을 스택에 푸시
                    }
                }
                adjList = adjList->next;
            }
        }
    }
    printf("\n탐색 실패: %d\n", target);
}

// 너비 우선 탐색 함수
void bfs(Graph* graph, int start, int target) {
    int queue[MAX_VERTICES], front = 0, rear = -1; // 큐 초기화
    graph->visited[start] = 1; // 시작 정점 방문 표시
    queue[++rear] = start;      // 시작 정점을 큐에 추가
    int count = 0;              // 방문한 노드 수

    while (front <= rear) {
        int current = queue[front++]; // 큐에서 정점 팝
        printf("%d ", current);
        count++;

        if (current == target) { // 목표 정점 찾기
            printf("\n탐색 성공: %d\n", target);
            printf("방문한 노드의 수: %d\n", count);
            return; // 목표 발견
        }

        Node* adjList = graph->adjList[current];
        while (adjList != NULL) {
            if (!graph->visited[adjList->vertex]) {
                graph->visited[adjList->vertex] = 1; // 방문 표시
                queue[++rear] = adjList->vertex; // 인접 정점을 큐에 추가
            }
            adjList = adjList->next;
        }
    }
    printf("\n탐색 실패: %d\n", target);
}

// 방문 배열 초기화 함수
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->vertexCount; i++) {
        graph->visited[i] = 0; // 모든 정점 방문 배열을 0으로 초기화
    }
}

int main() {
    Graph* graph = createGraph(MAX_VERTICES); // 그래프 생성

    // 그래프에 엣지 추가
    addEdge(graph, 0, 5);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 4);
    addEdge(graph, 0, 6);
    addEdge(graph, 0, 9);
    addEdge(graph, 1, 5);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 7);
    addEdge(graph, 1, 10);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 6);
    addEdge(graph, 4, 5);
    addEdge(graph, 4, 7);
    addEdge(graph, 6, 8);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 10);
    addEdge(graph, 8, 9);
    addEdge(graph, 8, 10);

    printf("-------------------------\n");
    printf("1    : 깊이 우선 탐색    |\n");
    printf("2    : 너비 우선 탐색    |\n");
    printf("3    : 종료              |\n");
    printf("-------------------------\n");

    while (1) {
        int choice;

        printf("\n메뉴 입력: ");

        if (scanf_s("%d", &choice) != 1) {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
            continue;
        }

        if (choice == 1 || choice == 2) {
            int startnode, targetnode;
            printf("시작 번호와 탐색할 값 입력: ");
            if (scanf_s("%d %d", &startnode, &targetnode) != 2) {
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
                while (getchar() != '\n'); // 입력 버퍼 비우기
                continue;
            }

            if (startnode >= MAX_VERTICES || targetnode >= MAX_VERTICES) {
                printf("탐색에 실패하였습니다. 존재하지 않는 데이터입니다.\n");
                continue;
            }

            if (choice == 1) {
                dfs(graph, startnode, targetnode); // 깊이 우선 탐색 실행
            }
            else if (choice == 2) {
                bfs(graph, startnode, targetnode); // 너비 우선 탐색 실행
            }

            resetVisited(graph); // 방문 배열 초기화
        }
        else if (choice == 3) {
            printf("프로그램을 종료합니다.\n");
            break; // 프로그램 종료
        }
        else {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
        }
    }

    // 메모리 해제
    for (int i = 0; i < MAX_VERTICES; i++) {
        Node* temp;
        while (graph->adjList[i] != NULL) {
            temp = graph->adjList[i];
            graph->adjList[i] = graph->adjList[i]->next;
            free(temp); // 노드 메모리 해제
        }
    }
    free(graph); // 그래프 메모리 해제

    return 0;
}
