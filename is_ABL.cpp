#include <iostream>
typedef struct bin {
	int data = 0;
	bin* left = NULL;
	bin* right = NULL;
} bin, *pbin;
bool is_abl(pbin root) {
	if (root == NULL)
		return true;
	if (root->left == NULL) {
		if (root->right == NULL)
			return true;
		else {
			return root->data <= root->right->data ? is_abl(root->right)* balance_height(root->right) : false;
		}
	}
	else {
		if (root->right == NULL)
			return root->data >= root->left->data ? is_abl(root->left)* balance_height(root->left) : false;
		else
			return root->data >= root->left->data && root->data <= root->right->data ? is_abl(root->left) * is_abl(root->right)*balance_height(root->left)* balance_height(root->right) : false;
	}
}
bool balance_height(pbin root){
	if (root == NULL)
		return true;
	else {
		int a = find_height(root->left);
		int b = find_height(root->right);
		if (a - b > -2 && a - b < 2) {
			return balance_height(root->left) * balance_height(root->right);
		}
		else
			return false;
	}
}
int find_height(pbin root) {
	if (root == NULL)
		return 0;
	else {
		int a = find_height(root->left);
		int b = find_height(root->right);
		if (a > b)
			return a + 1;
		else
			return b + 1;
	}
}