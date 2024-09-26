#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "LevelTraversal.h"
#include "Stack.h"  // 스택을 사용하여 반복적 순회를 구현

// 스택 사용을 위해 추가적인 헤더 필요
typedef struct QueueNode {
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

// 큐 구조체를 사용하여 반복적 레벨 순회를 구현
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, TreeNode* node) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;
    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

TreeNode* dequeue(Queue* q) {
    if (isQueueEmpty(q)) return NULL;
    QueueNode* temp = q->front;
    TreeNode* node = temp->node;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return node;
}


// 트리의 모든 노드 값 합산
int sum_of_tree_nodes(TreeNode* root) {
    if (root == NULL) return 0;

    int sum = 0;
    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);
        sum += current->data;

        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    return sum;
}

// 트리의 전체 노드 개수 구하기
int get_node_count(TreeNode* root) {
    if (root == NULL) return 0;

    int count = 0;
    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);
        count++;

        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    return count;
}

// 트리의 높이 구하기
int get_height(TreeNode* root) {
    if (root == NULL) return 0;

    Queue* queue = createQueue();
    enqueue(queue, root);
    int height = 0;

    while (!isQueueEmpty(queue)) {
        int level_size = 0;
        Queue* tempQueue = createQueue();

        while (!isQueueEmpty(queue)) {
            TreeNode* current = dequeue(queue);
            level_size++;

            if (current->left) enqueue(tempQueue, current->left);
            if (current->right) enqueue(tempQueue, current->right);
        }

        if (level_size > 0) height++;
        queue = tempQueue;
    }

    return height;
}

// 단말 노드의 수를 구하는 함수 (반복적 방식)
int level_order_x(TreeNode* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);

        // 단말 노드일 경우 카운트 증가
        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }

        // 자식 노드가 있으면 큐에 추가
        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    return leafCount;
}
