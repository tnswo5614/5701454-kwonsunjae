#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// ����� �Է� �������̽� �Լ�
void runUserInterface(HeapType* heap) {
    char command;
    int value;

    printf("i: ��� �߰� | d: ��� ���� | p: ������ ��� | c: ����\n");

    while (1) {
        printf("�޴� �Է�: ");
        scanf(" %c", &command);

        switch (command) {
        case 'i':  // �Է�
            printf("�߰��� �� �Է�: ");
            scanf("%d", &value);
            insert_heap(heap, (element) { value });
            break;
        case 'd':  // ����
            if (!is_empty_heap(heap)) {
                printf("\n�޴� �Է�: d\n");
                delete_heap(heap);
            }
            else {
                printf("���� ��� �ֽ��ϴ�.\n");
            }
            break;
        case 'p':  // ���
            printf("\n�޴� �Է�: p\n");
            display_heap(heap);
            break;
        case 'c':  // ����
            destroy_heap(heap);
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�ùٸ� ����� �Է��ϼ���.\n");
        }
    }
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63,65, 21, 18, 15 };  // Ʈ�� ������
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // Ʈ�� ����, �ʱ� �� ������� ����
    HeapType* root = generateMaxHeapTree(inputData, size);

    // ����� �Է� �������̽� ����
    runUserInterface(root);

    // �� �޸� ����
    destroy_heap(root);

    return 0;
}
