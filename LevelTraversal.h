#pragma once

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

extern int level_order_x(TreeNode* root);
extern int sum_of_tree_nodes(TreeNode* root);
extern int get_node_count(TreeNode* root);
extern int get_height(TreeNode* root);
