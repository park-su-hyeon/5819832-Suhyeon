#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
    h->heap_size = 0;
}

void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
            child++;
        if (temp.key < h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    node->weight = (left ? left->weight : 0) + (right ? right->weight : 0);
    return node;
}

void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

void print_heap(HeapType* heap) {
    for (int i = 1; i <= heap->heap_size; i++) {
        printf("%d ", heap->heap[i].key);
    }
    printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top + 1);
    }
    if (!root->left && !root->right) { // Leaf node
        printf("%c: ", root->ch);
        for (int i = 0; i < top; i++) {
            printf("%d", codes[i]);
        }
        printf("\n");
    }
}

void huffman_tree(int freq[], char ch_list[], int n) {
    int i;
    TreeNode* node, * x;
    HeapType* heap = create();
    init(heap);
    element e, e1, e2;

    // 힙에 주파수 추가
    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        node->ch = ch_list[i];
        node->weight = freq[i];
        e.ptree = node;
        e.ch = node->ch;
        e.key = node->weight;
        insert_min_heap(heap, e);

        // 현재 힙 상태 출력

        print_heap(heap);
    }

    // 허프만 트리 생성
    for (i = 1; i < n; i++) {
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_tree(e1.ptree, e2.ptree);
        e.ptree = x;
        e.key = x->weight;

        printf("///%d + %d -> %d\n", e1.key, e2.key, e.key);

        // 새로운 노드를 힙에 추가
        insert_min_heap(heap, e);

        // 힙 상태 출력
        print_heap(heap);
    }

    e = delete_min_heap(heap);
    int codes[MAX_ELEMENT];
    print_codes(e.ptree, codes, 0);
    destroy_tree(e.ptree);
    free(heap);
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    huffman_tree(frequencies, characters, size);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
