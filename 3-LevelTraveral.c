#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "LevelTraversal.h"
#include "Queue.h"

int get_height(TreeNode* root) {

	int height;

	if (root == NULL) return 0;

	height = 1 + ((get_height(root->left) > get_height(root->right))
		? get_height(root->left) : get_height(root->right));
	return height;
}

int get_node_count(TreeNode* root) {
	int count;

	if (root == NULL) return 0;

	count = 1 + get_node_count(root->left)
		+ get_node_count(root->right);
	return count;
}

int sum_of_tree_nodes(TreeNode* root) {
	int sum;

	if (root == NULL) return 0;
	sum = root->data + sum_of_tree_nodes(root->left)
		+ sum_of_tree_nodes(root->right);
	return sum;
}

int level_order_x(TreeNode* root)
{

	int node_sum = 0;
	LinkedQueueType q;
	TreeNode* ptr = root;
	init(&q);	 // 큐 초기화

	if (root == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		node_sum += ptr->data;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
	return node_sum;
}

