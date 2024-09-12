#include <stdio.h>
#include <stdlib.h>

typedef TreeNode* element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

int main() {
	TreeNode* root = ;
	root->data = 1;

	GenerateLinkTree(root);

	Linkorders(root);

	return 0;
}

void PlaceNode(TreeNode* node, int direction, int data) {
	if (&direction == 0) {
		pop(&s, );
		 = ->left;
	}
}

void GenerateLinkTree(TreeNode* root, int direction, int data) {
	PlaceNode(root, 0, 2);
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	LinkInOrder(root);
	LinkPostOrder(root);
}

void LinkPreOrder(TreeNode* root) {

}

void LinkInOrder(TreeNode* root) {

}

void LinkPostOrder(TreeNode* root) {

}