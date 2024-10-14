#pragma once
#define MAX_SIZE 100

// ��Ҹ� ����
typedef struct {
    int key;
} element;

// �� ����ü ����
typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} HeapType;

// �� ���� �Լ� ����
extern HeapType* create_heap();
extern void init_heap(HeapType* h);
extern void destroy_heap(HeapType* h);
extern int is_empty_heap(HeapType* h);
extern int is_full_heap(HeapType* h);
extern void insert_heap(HeapType* h, element item);
extern element delete_heap(HeapType* h);
extern void display_heap(HeapType* h);
extern HeapType* generateMaxHeapTree(int inputData[], int size);
