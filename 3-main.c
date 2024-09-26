#include <stdio.h>
#include <stdlib.h>
#include "LevelTraversal.h"

main() {

	TreeNode n1, n2, n3, n4, n5, n6;
	n1.data = 10, n1.left = &n2; n1.right = &n3;
	n2.data = 5, n2.left = &n4; n2.right = &n5;
	n3.data = 9, n3.left = NULL; n3.right = &n6;
	n4.data = 6, n4.left = NULL; n4.right = NULL;
	n5.data = 3, n5.left = NULL; n5.right = NULL;
	n6.data = 7, n6.left = NULL; n6.right = NULL;

	printf(" Total sum of tree node(R) = %d\n",sum_of_tree_nodes(&n1));
	printf(" Total sum of tree node(I) = %d\n",level_order_x(&n1));

	printf(" Node Count = %d\n", get_node_count(&n1));
	printf(" Height = %d\n", get_height(&n1));

}