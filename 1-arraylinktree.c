#include <stdio.h>
#include <stdlib.h>

// 트리 노드 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// 배열로 트리 순회를 위한 함수 선언
void Pre_Order_Array(int index, int size);
void In_Order_Array(int index, int size);
void Post_Order_Array(int index, int size);

// 링크드 리스트로 트리 순회를 위한 함수 선언
void Pre_Order_By_Pointer(TreeNode* np);
void In_Order_By_Pointer(TreeNode* np);
void Post_Order_By_Pointer(TreeNode* np);

int arrayTree[16] = { 0, 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

int main() {
    // 배열 트리 순회
    printf("배열 트리 순서대로 출력\n");
    printf("전위순회: ");
    Pre_Order_Array(1, 15);
    printf("\n중위순회: ");
    In_Order_Array(1, 15);
    printf("\n후위순회: ");
    Post_Order_Array(1, 15);

    // 링크드 리스트 기반 트리 구성
    TreeNode n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15;

    n1.data = 1; n1.left = &n2; n1.right = &n9;
    n2.data = 2; n2.left = &n3; n2.right = &n5;
    n3.data = 3; n3.left = &n4; n3.right = &n6;
    n4.data = 4; n4.left = NULL; n4.right = NULL;
    n5.data = 5; n5.left = &n7; n5.right = &n8;
    n6.data = 6; n6.left = NULL; n6.right = NULL;
    n7.data = 7; n7.left = NULL; n7.right = NULL;
    n8.data = 8; n8.left = NULL; n8.right = NULL;
    n9.data = 9; n9.left = &n10; n9.right = &n13;
    n10.data = 10; n10.left = &n11; n10.right = &n12;
    n11.data = 11; n11.left = NULL; n11.right = NULL;
    n12.data = 12; n12.left = NULL; n12.right = NULL;
    n13.data = 13; n13.left = &n14; n13.right = &n15;
    n14.data = 14; n14.left = NULL; n14.right = NULL;
    n15.data = 15; n15.left = NULL; n15.right = NULL;

    // 링크드 리스트 트리 순회
    printf("\n\n링크드 리스트 트리 순서대로 출력\n");
    printf("전위순회: ");
    Pre_Order_By_Pointer(&n1);
    printf("\n중위순회: ");
    In_Order_By_Pointer(&n1);
    printf("\n후위순회: ");
    Post_Order_By_Pointer(&n1);

    return 0;
}

// 배열 기반 트리 전위 순회 (Pre-order)
void Pre_Order_Array(int index, int size) {
    if (index <= size && arrayTree[index] != -1) {
        printf("%d ", arrayTree[index]);
        Pre_Order_Array(2 * index, size);
        Pre_Order_Array(2 * index + 1, size);
    }
}

// 배열 기반 트리 중위 순회 (In-order)
void In_Order_Array(int index, int size) {
    if (index <= size && arrayTree[index] != -1) {
        In_Order_Array(2 * index, size);
        printf("%d ", arrayTree[index]);
        In_Order_Array(2 * index + 1, size);
    }
}

// 배열 기반 트리 후위 순회 (Post-order)
void Post_Order_Array(int index, int size) {
    if (index <= size && arrayTree[index] != -1) {
        Post_Order_Array(2 * index, size);
        Post_Order_Array(2 * index + 1, size);
        printf("%d ", arrayTree[index]);
    }
}

// 링크드 리스트 기반 트리 전위 순회 (Pre-order)
void Pre_Order_By_Pointer(TreeNode* np) {
    if (np != NULL) {
        printf("%d ", np->data);
        Pre_Order_By_Pointer(np->left);
        Pre_Order_By_Pointer(np->right);
    }
}

// 링크드 리스트 기반 트리 중위 순회 (In-order)
void In_Order_By_Pointer(TreeNode* np) {
    if (np != NULL) {
        In_Order_By_Pointer(np->left);
        printf("%d ", np->data);
        In_Order_By_Pointer(np->right);
    }
}

// 링크드 리스트 기반 트리 후위 순회 (Post-order)
void Post_Order_By_Pointer(TreeNode* np) {
    if (np != NULL) {
        Post_Order_By_Pointer(np->left);
        Post_Order_By_Pointer(np->right);
        printf("%d ", np->data);
    }
}
