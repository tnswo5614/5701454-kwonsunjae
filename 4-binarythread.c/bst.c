#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// ���� Ž�� Ʈ�� ��� ���� �Լ�
TreeNode* new_node(int key) {
    TreeNode* temp = malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

// ���� Ž�� Ʈ���� ��� ���� �Լ�
TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL)
        return new_node(key);

    if (key < root->data)
        root->left = insert_node(root->left, key);
    else if (key > root->data)
        root->right = insert_node(root->right, key);

    return root;
}

// ���� Ž�� Ʈ�� ���� ��ȸ (��� ���)
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

// ���� Ž�� Ʈ���� �����ϴ� �Լ�
TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

// ������ ���� Ʈ�� ��� ���� �Լ�
ThreadNode* new_thread_node(int key) {
    ThreadNode* temp = malloc(sizeof(ThreadNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    temp->rightThread = 0;
    return temp;
}

// ���� Ž�� Ʈ���� ������ ���� Ʈ���� ��ȯ�ϴ� �Լ�
ThreadNode* GenerateThreadTree(TreeNode* root) {
    if (!root) return NULL;

    static ThreadNode* prev = NULL;  // ���� ��� ����

    ThreadNode* leftThreaded = GenerateThreadTree(root->left);  // ���� ����Ʈ�� ��ȯ

    ThreadNode* current = new_thread_node(root->data);  // ���� ��带 ������ Ʈ�� ���� ��ȯ
    if (prev != NULL) {
        prev->right = current;  // ���� ����� �������� ���� ���� ����
        prev->rightThread = 1;  // ���� ��忡 ������ ����
    }
    prev = current;  // ���� ��带 ���� ���� ����

    GenerateThreadTree(root->right);  // ������ ����Ʈ�� ��ȯ
    return leftThreaded ? leftThreaded : current;  // ��ȯ�� ��Ʈ ��� ��ȯ
}

// ������ ���� Ʈ�� ���� ��ȸ (����/��� ���� �ݺ��� ���)
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    while (current) {
        while (current->left)
            current = current->left;

        printf("%d ", current->data);

        while (current->rightThread) {
            current = current->right;
            printf("%d ", current->data);
        }

        current = current->right;
    }
}
