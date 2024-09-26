#include <stdio.h>
#include <stdlib.h>
#include "LevelTraversal.h"

int main() {

    // 트리 노드 정의 및 초기화
    TreeNode n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15;
    n1.data = 1; n1.left = &n2; n1.right = &n3;
    n2.data = 2; n2.left = &n4; n2.right = &n5;
    n3.data = 3; n3.left = &n6; n3.right = &n7;
    n4.data = 4; n4.left = &n8; n4.right = &n9;
    n5.data = 5; n5.left = &n10; n5.right = &n11;
    n6.data = 6; n6.left = &n12; n6.right = &n13;
    n7.data = 7; n7.left = &n14; n7.right = &n15;
    n8.data = 8; n8.left = NULL; n8.right = NULL;
    n9.data = 9; n9.left = NULL; n9.right = NULL;
    n10.data = 10; n10.left = NULL; n10.right = NULL;
    n11.data = 11; n11.left = NULL; n11.right = NULL;
    n12.data = 12; n12.left = NULL; n12.right = NULL;
    n13.data = 13; n13.left = NULL; n13.right = NULL;
    n14.data = 14; n14.left = NULL; n14.right = NULL;
    n15.data = 15; n15.left = NULL; n15.right = NULL;

    // 각종 트리 데이터 출력
    printf("Sum of nodes: %d\n", sum_of_tree_nodes(&n1));           // 노드 값의 합
    printf("Number of nodes: %d\n", get_node_count(&n1));            // 노드 개수
    printf("Height of Tree: %d\n", get_height(&n1));                 // 트리의 높이
    printf("Number of leaf nodes: %d\n", level_order_x(&n1));        // 단말 노드 개수

    return 0;
}
