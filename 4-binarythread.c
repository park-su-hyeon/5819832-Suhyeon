#include <stdio.h>
#include <stdlib.h>


typedef struct Tree_node {
	int data;
	struct tree_node* right, * left;
} TreeNode;

typedef struct ThreadNodee {
	int data;
	struct ThreadNode* right, * left;
} ThreadNode;

TreeNode* GenerateBinaryTree(int inputData[]) {
	TreeNode* root =, , , ;
	return root;
}
ThreadNode* GenerateThreadTree(int inputData[]) {
	ThreadNode* root =, , , ;
		return root;
}

TreeNode* BinaryTreeInOrder(TreeNode* root) {}
ThreadNode * ThreadTreeInOrder(ThreadNode *root) {}


int main() {
	int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,7 };
	
	TreeNode* root = GenerateBinaryTree(inputData);
	BinaryTreeInOrder(root);
	ThreadTree* troot = GenerateThreadTree(inputData);
	ThreadTreeInOrder(troot);
	free(root);
	free(troot);
	return 0;
}
