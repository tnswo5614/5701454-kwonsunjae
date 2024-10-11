#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
    int inputData[] = {4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // ���� Ž�� Ʈ�� ����
    TreeNode* root = GenerateBinaryTree(inputData, size);

    // ���� Ž�� Ʈ�� ���� ��ȸ ���
    printf("���� Ž�� Ʈ�� ���� ��ȸ: ");
    BinaryTreeInOrder(root);
    printf("\n");

    // ������ ���� Ʈ�� ����
    ThreadNode* troot = GenerateThreadTree(root);

    // ������ ���� Ʈ�� ���� ��ȸ ��� (����/��� ����)
    printf("������ ���� Ʈ�� ���� ��ȸ: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    return 0;
}
