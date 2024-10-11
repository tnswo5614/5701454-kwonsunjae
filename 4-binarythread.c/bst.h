#pragma once

typedef struct tree_node {
    int data;
    struct tree_node* right, * left;
} TreeNode;

typedef struct thread_node {
    int data;
    struct thread_node* right, * left;
    int rightThread;  // 1이면 스레드임을 나타냄
} ThreadNode;

TreeNode* GenerateBinaryTree(int inputData[], int size);  // 이진 탐색 트리 생성 함수
ThreadNode* GenerateThreadTree(TreeNode* root);           // 스레드 이진 트리 생성 함수
void BinaryTreeInOrder(TreeNode* root);                   // 이진 탐색 트리 중위 순회 함수
void ThreadTreeInOrder(ThreadNode* root);                 // 스레드 이진 트리 중위 순회 함수
