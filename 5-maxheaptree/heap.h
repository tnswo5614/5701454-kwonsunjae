#pragma once
#define MAX_SIZE 100

// 요소를 정의
typedef struct {
    int key;
} element;

// 힙 구조체 정의
typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} HeapType;

// 힙 관련 함수 선언
extern HeapType* create_heap();
extern void init_heap(HeapType* h);
extern void destroy_heap(HeapType* h);
extern int is_empty_heap(HeapType* h);
extern int is_full_heap(HeapType* h);
extern void insert_heap(HeapType* h, element item);
extern element delete_heap(HeapType* h);
extern void display_heap(HeapType* h);
extern HeapType* generateMaxHeapTree(int inputData[], int size);
