#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int compareCount = 0;  // 탐색 시 비교 횟수
int searchCount = 0;   // 탐색 횟수

// 새로운 노드 생성
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// 노드의 높이 반환
int getHeight(Node* node) {
    if (node == (Node*)NULL) return 0;
    else return node->height;
}

// 균형 인수 계산
int getBalance(Node* node) {
    return getHeight(node->left) - getHeight(node->right);
}

// 오른쪽 회전
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// 왼쪽 회전
Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;
    x->left = y;
    y->right = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// 트리에서 최소값 노드 찾기
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

// 노드 삭제
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    // 일반 이진 탐색 트리 삭제
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // 노드 삭제
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// 삽입 연산
Node* insertNode(Node* root, int key) {
    if (root == NULL) return createNode(key);

    if (key < root->key) {
        root->left = insertNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertNode(root->right, key);
    }
    else {
        return root;
    }

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// 탐색 연산
Node* searchNode(Node* root, int key) {
    if (root == NULL) return NULL;

    compareCount++;  // 첫 번째 비교
    if (key == root->key) {
        return root;
    }
    else if (key < root->key) {
        return searchNode(root->left, key);  // 왼쪽 서브트리 탐색
    }
    else {
        return searchNode(root->right, key);  // 오른쪽 서브트리 탐색
    }
}

// 트리 메모리 해제
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// AVL 트리에서 배치 작업 수행
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;

        if (A == 0) {
            *root = insertNode(*root, B);  // 삽입
        }
        else if (A == 1) {
            *root = deleteNode(*root, B);  // 삭제
        }
        else if (A == 2) {
            searchCount++;  // A == 2일 때 탐색 횟수 증가
            searchNode(*root, B);  // 탐색 실행
        }
    }
}

void doBinaryBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;

        if (A == 0) {
            *root = insertNode(*root, B);
        }
        else if (A == 1) {
            *root = deleteNode(*root, B);
        }
        else if (A == 2) {
            searchCount++;
            Node* result = searchNode(*root, B);  // 탐색을 실행하면서 비교 횟수도 증가
            // 만약 추가적인 처리가 필요하면 여기에 추가
        }
    }
}

// main 함수
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // AVL 트리에서 배치 작업 수행
    doAVLBatch(&root); // root 포인터를 참조하여 수정된 값을 반영
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;

    // 이진 탐색 트리에서 배치 작업 수행
    doBinaryBatch(&root); // root 포인터를 참조하여 수정된 값을 반영
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}
