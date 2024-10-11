#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// 이진 탐색 트리 노드 생성 함수
TreeNode* new_node(int key) {
    TreeNode* temp = malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

// 이진 탐색 트리에 노드 삽입 함수
TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL)
        return new_node(key);

    if (key < root->data)
        root->left = insert_node(root->left, key);
    else if (key > root->data)
        root->right = insert_node(root->right, key);

    return root;
}

// 이진 탐색 트리 중위 순회 (재귀 방식)
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

// 이진 탐색 트리를 생성하는 함수
TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, inputData[i]);
    }
    return root;
}

// 스레드 이진 트리 노드 생성 함수
ThreadNode* new_thread_node(int key) {
    ThreadNode* temp = malloc(sizeof(ThreadNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    temp->rightThread = 0;
    return temp;
}

// 이진 탐색 트리를 스레드 이진 트리로 변환하는 함수
ThreadNode* GenerateThreadTree(TreeNode* root) {
    if (!root) return NULL;

    static ThreadNode* prev = NULL;  // 이전 노드 저장

    ThreadNode* leftThreaded = GenerateThreadTree(root->left);  // 왼쪽 서브트리 변환

    ThreadNode* current = new_thread_node(root->data);  // 현재 노드를 스레드 트리 노드로 변환
    if (prev != NULL) {
        prev->right = current;  // 이전 노드의 오른쪽을 현재 노드로 설정
        prev->rightThread = 1;  // 이전 노드에 스레드 설정
    }
    prev = current;  // 현재 노드를 이전 노드로 갱신

    GenerateThreadTree(root->right);  // 오른쪽 서브트리 변환
    return leftThreaded ? leftThreaded : current;  // 변환된 루트 노드 반환
}

// 스레드 이진 트리 중위 순회 (스택/재귀 없이 반복문 사용)
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
