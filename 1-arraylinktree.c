#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNde {
	int data;
	int* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {
	int list[16] = {-1, 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}

	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(int tree) {
	if (tree != -1) {
		printf("%d", tree);
		ArrayPreOrder(tree * 2);
		ArrayPreOrder(tree * 2 + 1);
	}
}

void ArrayInOrder(int tree) {

}

void ArrayPostOrder(int tree) {

}

void ArrayOrders(int tree) {
	ArrayPreOrder(tree);
	ArrayInOrder(tree);
	ArrayPostOrder(tree);
}



void PlaceNode(TreeNode* node, int direction, int data) {

}

void GenerateLinkTree(TreeNode *root) {
	PlaceNode(root, 0, 2);

}

void LinkPreOrder(TreeNode* root) {
	if (root != NULL) {
		printf("%d", root->data);
		LinkPreOrder(root->left);
		LinkPreOrder(root->right);
	}
}

void LinkInOrder(TreeNode* root) {

}

void LinkPostOrder(TreeNode* root) {

}

void LinkOrders(TreeNode *root) {
	LinkPreOrder(root);
	LinkInOrder(root);
	LinkPostOrder(root);
}

int main {
	int arr[];
TreeNode* root = ;
n1->data = 1;

GenerateArrayTree(arr);
GenerateLinkTree(root);

ArrayOrders(arr);
LinkOrders(root);

return 0;

}