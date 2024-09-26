#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "LevelTraversal.h"
#include "Stack.h"  // ������ ����Ͽ� �ݺ��� ��ȸ�� ����

// ���� ����� ���� �߰����� ��� �ʿ�
typedef struct QueueNode {
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

// ť ����ü�� ����Ͽ� �ݺ��� ���� ��ȸ�� ����
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


// Ʈ���� ��� ��� �� �ջ�
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

// Ʈ���� ��ü ��� ���� ���ϱ�
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

// Ʈ���� ���� ���ϱ�
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

// �ܸ� ����� ���� ���ϴ� �Լ� (�ݺ��� ���)
int level_order_x(TreeNode* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);

        // �ܸ� ����� ��� ī��Ʈ ����
        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }

        // �ڽ� ��尡 ������ ť�� �߰�
        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    return leafCount;
}
