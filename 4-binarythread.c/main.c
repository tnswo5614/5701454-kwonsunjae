#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
    int inputData[] = {4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 이진 탐색 트리 생성
    TreeNode* root = GenerateBinaryTree(inputData, size);

    // 이진 탐색 트리 중위 순회 출력
    printf("이진 탐색 트리 중위 순회: ");
    BinaryTreeInOrder(root);
    printf("\n");

    // 스레드 이진 트리 생성
    ThreadNode* troot = GenerateThreadTree(root);

    // 스레드 이진 트리 중위 순회 출력 (스택/재귀 없이)
    printf("스레드 이진 트리 중위 순회: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    return 0;
}
