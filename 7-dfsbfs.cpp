#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

typedef struct {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

GraphMatType* create_mat_graph() {
	return (GraphMatType*)malloc(sizeof(GraphMatType));
}

void destroy_mat_graph(GraphMatType* g) {
	free(g);
}

void init_mat_graph(GraphMatType* g) {
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			g->adj_mat[i][j] = 0;
}

void insert_vertex_mat_graph(GraphMatType* g, int v) {
	if ((g->n) >= (MAX_VERTICES - 1)) {
		fprintf(stderr, "Over number of vertex\n");
		return;
	}
	(g->n)++;
}

void insert_edge_mat_graph(GraphMatType* g, int s, int e) {
	if (g->n <= s || g->n <= e) {
		fprintf(stderr, "vertex number error\n");
		return;
	}
	g->adj_mat[s][e] = 1;
	g->adj_mat[e][s] = 1;
}

void print_adj_mat(GraphMatType* g) {
	printf("     ");
	for (int i = 0; i < g->n; i++) {
		printf(" %02d ", i);
	}
	printf("\n_____");
	for (int i = 0; i < g->n; i++) {
		printf("_______", i);
	}
	printf("\n");
	for (int i = 0; i < g->n; i++) {
		printf(" %02d: ", i);
		for (int j = 0; j < g->n; j++)
			printf(" %02d ", g->adj_mat[i][j]);
		printf("\n");
	}
}

	int main() {

		GraphMatType* g;

		g = create_mat_graph();
		init_mat_graph(g);

		while (1) {
			int choice;

			printf("-------------------------\n");
			printf("1    : 깊이 우선 탐색    |\n");
			printf("2    : 너비 우선 탐색    |\n");
			printf("3    : 종료              |\n");
			printf("-------------------------\n");


			printf("메뉴 입력: ");
			scanf("%d\n", &choice);

			if (choice == 1 || choice == 2) {
				int startnode, targetnode;
				printf("시작 번호와 탐색할 값 입력: ");
				scanf("%d %d", &startnode, &targetnode);
			}

			if (choice == 1) {

				printf("탐색 성공: ");
				printf("방문한 노드의 수: ");
			}

			else if (choice == 2) {

				printf("탐색 성공: ");
				printf("방문한 노드의 수: ");
			}
			else if (choice == 3) {
				printf("프로그램을 종료합니다.\n");
				break;
			}
			else {
				printf("잘못된 입력입니다. 다시 시도하세요.\n");
			}
		}
		return 0;
	}




#include <stdio.h>
#include <stdlib.h>

#define MAX 100

    typedef struct Graph {
        int adj[MAX][MAX];
        int numVertices;
    } Graph;

    void initGraph(Graph* g, int vertices) {
        g->numVertices = vertices;
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                g->adj[i][j] = 0;
            }
        }
    }

    void addEdge(Graph* g, int u, int v) {
        g->adj[u][v] = 1;
        g->adj[v][u] = 1; // 무향 그래프
    }

    int dfs(Graph* g, int vertex, int target, int visited[], int* visitCount) {
        visited[vertex] = 1;
        printf("%d ", vertex);
        (*visitCount)++;

        if (vertex == target) {
            return 1; // 목표 노드를 찾음
        }

        for (int i = 0; i < g->numVertices; i++) {
            if (g->adj[vertex][i] && !visited[i]) {
                if (dfs(g, i, target, visited, visitCount)) {
                    return 1; // 목표 노드를 찾음
                }
            }
        }
        return 0; // 목표 노드를 찾지 못함
    }

    int bfs(Graph* g, int start, int target, int* visitCount) {
        int visited[MAX] = { 0 };
        int queue[MAX], front = -1, rear = -1;

        visited[start] = 1;
        queue[++rear] = start;

        while (front < rear) {
            int vertex = queue[++front];
            printf("%d ", vertex);
            (*visitCount)++;

            if (vertex == target) {
                return 1; // 목표 노드를 찾음
            }

            for (int i = 0; i < g->numVertices; i++) {
                if (g->adj[vertex][i] && !visited[i]) {
                    visited[i] = 1;
                    queue[++rear] = i;
                }
            }
        }
        return 0; // 목표 노드를 찾지 못함
    }

    int main() {
        Graph g;
        initGraph(&g, 10); // 노드 수 설정 (0~9)

        // 간선 추가
        addEdge(&g, 1, 2);
        addEdge(&g, 1, 3);
        addEdge(&g, 2, 4);
        addEdge(&g, 2, 5);
        addEdge(&g, 3, 6);
        addEdge(&g, 4, 0);
        addEdge(&g, 5, 3);
        addEdge(&g, 6, 7);
        addEdge(&g, 7, 10);
        addEdge(&g, 10, 8);
        addEdge(&g, 8, 9);

        while (1) {
            int choice;
            printf("\n메뉴:\n");
            printf("1) 깊이 우선 탐색 (DFS)\n");
            printf("2) 너비 우선 탐색 (BFS)\n");
            printf("3) 프로그램 종료\n");

            printf("메뉴 입력: ");
            scanf("%d", &choice);

            if (choice == 1 || choice == 2) {
                int startNode, targetNode;
                printf("시작 번호와 탐색할 값 입력: ");
                scanf("%d %d", &startNode, &targetNode);

                int visitCount = 0;
                int visited[MAX] = { 0 };
                int found = 0;

                if (choice == 1) {
                    printf("DFS 탐색 결과: ");
                    found = dfs(&g, startNode, targetNode, visited, &visitCount);
                }
                else if (choice == 2) {
                    printf("BFS 탐색 결과: ");
                    found = bfs(&g, startNode, targetNode, &visitCount);
                }

                printf("\n");
                if (found) {
                    printf("탐색 성공: %d\n", targetNode);
                }
                else {
                    printf("탐색 실패: %d\n", targetNode);
                }
                printf("방문한 노드의 수: %d\n", visitCount);
            }
            else if (choice == 3) {
                printf("프로그램을 종료합니다.\n");
                break;
            }
            else {
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
            }
        }

        return 0;
    }
