#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// �� ����
HeapType* create_heap() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// �� �ʱ�ȭ
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

// �� ����
void destroy_heap(HeapType* h) {
    free(h);
}

// ���� ������� Ȯ��
int is_empty_heap(HeapType* h) {
    return (h->heap_size == 0);
}

// ���� ���� á���� Ȯ��
int is_full_heap(HeapType* h) {
    return (h->heap_size == (MAX_SIZE - 1));
}

// �� ����, ��� �̵� ������ ������� �ʵ��� ����
void insert_heap_silent(HeapType* h, element item) {
    int i = h->heap_size + 1;

    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];
        i = i / 2;
    }
    h->heap[i] = item;
    h->heap_size++;
}

// �� ����, ��� �̵� ������ ���
void insert_heap(HeapType* h, element item) {
    int i = h->heap_size + 1;
    int move_count = 0;

    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];
        i = i / 2;
        move_count++;
    }
    h->heap[i] = item;
    h->heap_size++;

    printf("�߰��� �� �Է�: %d\n", item.key);
    display_heap(h);
    printf("��尡 �̵��� Ƚ��: %d\n", move_count);
}

// ��Ʈ ��带 �����ϰ� �� ����, ��� �̵� ���� ���
element delete_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    int move_count = 0;

    item = h->heap[1];  // ��Ʈ ��� ����
    temp = h->heap[h->heap_size];
    h->heap_size--;

    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            child++;
        }
        if (temp.key >= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
        move_count++;
    }
    h->heap[parent] = temp;

    display_heap(h);
    printf("��尡 �̵��� Ƚ��: %d\n", move_count);
    return item;
}

// ���� �������� ���
void display_heap(HeapType* h) {
    printf("\n�� ����: ");
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");

    int level = 1;
    int count = 1;
    printf("Ʈ�� ������ ���\n");
    while (count <= h->heap_size) {
        printf("[%d] ", level);
        int nodes_in_level = 1 << (level - 1);  // �ش� ������ �ִ� ��� ���� (2^(level-1))
        for (int i = 0; i < nodes_in_level && count <= h->heap_size; i++) {
            printf("%d ", h->heap[count]);
            count++;
        }
        printf("\n");
        level++;
    }
}

// �� ���� �Լ�
HeapType* generateMaxHeapTree(int inputData[], int size) {
    HeapType* h = create_heap();
    init_heap(h);

    // �־��� ������ �迭�� ���� ���� (���� �� ��� ����)
    for (int i = 0; i < size; i++) {
        insert_heap_silent(h, (element){ inputData[i] });
    }

    return h;
}
