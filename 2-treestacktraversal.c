#include <stdio.h>
#include <stdlib.h>

typedef TreeNode* element;
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

int main() {
	TreeNode* root = data;
	root->data = 1;

	GenerateLinkTree(root);

	Linkorders(root);

	return 0;
}

void placeNode(TreeNode* node, int direction, int data) {
	if (direction == 0) {  
		node->left;
	}
	else {  
		node->right;
	}
}

void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);
	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);
	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	printf("\n");
	LinkInOrder(root);
	printf("\n");
	LinkPostOrder(root);
	printf("\n");
}

void LinkPreOrder(TreeNode* root) {
	if (root == NULL) return;
	printf("%d ", root->data);
	LinkPreOrder(root->left);
	LinkPreOrder(root->right);
}

void LinkInOrder(TreeNode* root) {
	if (root == NULL) return;
	LinkInOrder(root->left);
	printf("%d ", root->data);
	LinkInOrder(root->right);
}

void LinkPostOrder(TreeNode* root) {
	if (root == NULL) return;
	LinkPostOrder(root->left);
	LinkPostOrder(root->right);
	printf("%d ", root->data);
}
