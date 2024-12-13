#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int compareCount = 0;  // Ž�� �� �� Ƚ��
int searchCount = 0;   // Ž�� Ƚ��

// ���ο� ��� ����
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// ����� ���� ��ȯ
int getHeight(Node* node) {
    if (node == (Node*)NULL) return 0;
    else return node->height;
}

// ���� �μ� ���
int getBalance(Node* node) {
    return getHeight(node->left) - getHeight(node->right);
}

// ������ ȸ��
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// ���� ȸ��
Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;
    x->left = y;
    y->right = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// Ʈ������ �ּҰ� ��� ã��
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

// ��� ����
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    // �Ϲ� ���� Ž�� Ʈ�� ����
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // ��� ����
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

// ���� ����
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

// Ž�� ����
Node* searchNode(Node* root, int key) {
    if (root == NULL) return NULL;

    compareCount++;  // ù ��° ��
    if (key == root->key) {
        return root;
    }
    else if (key < root->key) {
        return searchNode(root->left, key);  // ���� ����Ʈ�� Ž��
    }
    else {
        return searchNode(root->right, key);  // ������ ����Ʈ�� Ž��
    }
}

// Ʈ�� �޸� ����
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// AVL Ʈ������ ��ġ �۾� ����
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;

        if (A == 0) {
            *root = insertNode(*root, B);  // ����
        }
        else if (A == 1) {
            *root = deleteNode(*root, B);  // ����
        }
        else if (A == 2) {
            searchCount++;  // A == 2�� �� Ž�� Ƚ�� ����
            searchNode(*root, B);  // Ž�� ����
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
            Node* result = searchNode(*root, B);  // Ž���� �����ϸ鼭 �� Ƚ���� ����
            // ���� �߰����� ó���� �ʿ��ϸ� ���⿡ �߰�
        }
    }
}

// main �Լ�
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // AVL Ʈ������ ��ġ �۾� ����
    doAVLBatch(&root); // root �����͸� �����Ͽ� ������ ���� �ݿ�
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;

    // ���� Ž�� Ʈ������ ��ġ �۾� ����
    doBinaryBatch(&root); // root �����͸� �����Ͽ� ������ ���� �ݿ�
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}
