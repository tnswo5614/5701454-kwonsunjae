#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// 사용자 입력 인터페이스 함수
void runUserInterface(HeapType* heap) {
    char command;
    int value;

    printf("i: 노드 추가 | d: 노드 삭제 | p: 레벨별 출력 | c: 종료\n");

    while (1) {
        printf("메뉴 입력: ");
        scanf(" %c", &command);

        switch (command) {
        case 'i':  // 입력
            printf("추가할 값 입력: ");
            scanf("%d", &value);
            insert_heap(heap, (element) { value });
            break;
        case 'd':  // 삭제
            if (!is_empty_heap(heap)) {
                printf("\n메뉴 입력: d\n");
                delete_heap(heap);
            }
            else {
                printf("힙이 비어 있습니다.\n");
            }
            break;
        case 'p':  // 출력
            printf("\n메뉴 입력: p\n");
            display_heap(heap);
            break;
        case 'c':  // 종료
            destroy_heap(heap);
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("올바른 명령을 입력하세요.\n");
        }
    }
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63,65, 21, 18, 15 };  // 트리 데이터
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 트리 생성, 초기 값 출력하지 않음
    HeapType* root = generateMaxHeapTree(inputData, size);

    // 사용자 입력 인터페이스 실행
    runUserInterface(root);

    // 힙 메모리 해제
    destroy_heap(root);

    return 0;
}
