#include <stdio.h>
#include <stdlib.h>

typedef TreeNode* element;
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = root->right = NULL;

	GenerateLinkTree(root);

	Linkorders(root);

	return 0;
}
void init(LinkedStackType* s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

int is_full(LinkedStackType* s)
{
	return 0;
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	StackNode* temp = s->top;
	element data = temp->data;
	s->top = temp->link;
	free(temp);
	return data;
}

void print_stack(LinkedStackType* s)
{
	for (StackNode* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data->data);  // implementation specific
	printf("NULL \n");
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
	LinkedStackType s;
	TreeNode* nptr = root;

	init(&s);

	while (nptr != NULL || !is_empty(&s)) {
		while (nptr != NULL) {
			push(&s, nptr);
			nptr = nptr->left;
		}

		nptr = pop(&s);
		printf("[%2d]", nptr->data);

		nptr = nptr->right;
	}
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
