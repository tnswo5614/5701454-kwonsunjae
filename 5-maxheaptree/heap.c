#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// 힙 생성
HeapType* create_heap() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 힙 초기화
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

// 힙 삭제
void destroy_heap(HeapType* h) {
    free(h);
}

// 힙이 비었는지 확인
int is_empty_heap(HeapType* h) {
    return (h->heap_size == 0);
}

// 힙이 가득 찼는지 확인
int is_full_heap(HeapType* h) {
    return (h->heap_size == (MAX_SIZE - 1));
}

// 힙 삽입, 노드 이동 과정을 출력하지 않도록 수정
void insert_heap_silent(HeapType* h, element item) {
    int i = h->heap_size + 1;

    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];
        i = i / 2;
    }
    h->heap[i] = item;
    h->heap_size++;
}

// 힙 삽입, 노드 이동 과정을 출력
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

    printf("추가할 값 입력: %d\n", item.key);
    display_heap(h);
    printf("노드가 이동된 횟수: %d\n", move_count);
}

// 루트 노드를 삭제하고 힙 유지, 노드 이동 과정 출력
element delete_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    int move_count = 0;

    item = h->heap[1];  // 루트 노드 삭제
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
    printf("노드가 이동된 횟수: %d\n", move_count);
    return item;
}

// 힙을 레벨별로 출력
void display_heap(HeapType* h) {
    printf("\n힙 상태: ");
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");

    int level = 1;
    int count = 1;
    printf("트리 레벨별 출력\n");
    while (count <= h->heap_size) {
        printf("[%d] ", level);
        int nodes_in_level = 1 << (level - 1);  // 해당 레벨에 있는 노드 개수 (2^(level-1))
        for (int i = 0; i < nodes_in_level && count <= h->heap_size; i++) {
            printf("%d ", h->heap[count]);
            count++;
        }
        printf("\n");
        level++;
    }
}

// 힙 생성 함수
HeapType* generateMaxHeapTree(int inputData[], int size) {
    HeapType* h = create_heap();
    init_heap(h);

    // 주어진 데이터 배열로 힙을 구성 (삽입 시 출력 없음)
    for (int i = 0; i < size; i++) {
        insert_heap_silent(h, (element){ inputData[i] });
    }

    return h;
}
