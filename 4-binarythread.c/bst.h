#pragma once

typedef struct tree_node {
    int data;
    struct tree_node* right, * left;
} TreeNode;

typedef struct thread_node {
    int data;
    struct thread_node* right, * left;
    int rightThread;  // 1�̸� ���������� ��Ÿ��
} ThreadNode;

TreeNode* GenerateBinaryTree(int inputData[], int size);  // ���� Ž�� Ʈ�� ���� �Լ�
ThreadNode* GenerateThreadTree(TreeNode* root);           // ������ ���� Ʈ�� ���� �Լ�
void BinaryTreeInOrder(TreeNode* root);                   // ���� Ž�� Ʈ�� ���� ��ȸ �Լ�
void ThreadTreeInOrder(ThreadNode* root);                 // ������ ���� Ʈ�� ���� ��ȸ �Լ�
