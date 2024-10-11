#include <stdio.h>
#include <stdlib.h>

typedef struct Tree_node {
    int data;
    struct Tree_node* left;
    struct Tree_node* right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    int isThreaded;
} ThreadNode;


TreeNode* createTreeNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}


TreeNode* insertBST(TreeNode* root, int data) {
    if (root == NULL) return createTreeNode(data);
    if (data < root->data)
        root->left = insertBST(root->left, data);
    else
        root->right = insertBST(root->right, data);
    return root;
}


TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insertBST(root, inputData[i]);
    }
    return root;
}


void BinaryTreeInOrder(TreeNode* root) {
    if (root) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}


ThreadNode* createThreadNode(int data) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}


void convertToThreaded(TreeNode* root, ThreadNode** prev) {
    if (root) {
        convertToThreaded(root->left, prev);

        ThreadNode* newNode = createThreadNode(root->data);
        if (*prev) {
            newNode->left = *prev;
            if ((*prev)->right == NULL) {
                (*prev)->right = newNode;
                (*prev)->isThreaded = 1;
            }
        }
        *prev = newNode;

        convertToThreaded(root->right, prev);
    }
}


ThreadNode* GenerateThreadTree(TreeNode* bstRoot) {
    ThreadNode* tRoot = NULL;
    ThreadNode* prev = NULL;
    convertToThreaded(bstRoot, &prev);
    return tRoot;
}


void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;
    while (current) {

        while (current->left) {
            current = current->left;
        }
        printf("%d ", current->data);

        if (current->isThreaded) {
            current = current->right;
        }
        else {
            current = current->right;
        }
    }
}


ThreadNode* initializeThreadTree(TreeNode* bstRoot) {
    if (!bstRoot) return NULL;

    ThreadNode* root = createThreadNode(bstRoot->data);
    ThreadNode* prev = NULL;

    convertToThreaded(bstRoot, &prev);


    return root;
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);


    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = initializeThreadTree(root);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");


    free(root);
    free(troot);

    return 0;
}

