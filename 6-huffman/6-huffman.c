#include <stdio.h>
#include <stdlib.h>

// ������ Ʈ���� ��� ����ü ����
typedef struct Node {
    char character; // ���ڸ� �����ϴ� �ʵ�
    int frequency;  // �󵵼� �ʵ�
    struct Node* left, * right; // ����, ������ �ڽ� ���
} Node;

// ������ �ּ� �󵵼��� ���� ��带 �����ϴ� �Լ�
Node* extractMin(Node** heap, int* heapSize) {
    Node* minNode = heap[0]; // ��Ʈ ��尡 �ּҰ�
    heap[0] = heap[--(*heapSize)]; // ������ ��带 ��Ʈ�� �̵�

    int i = 0;
    while (2 * i + 1 < *heapSize) {
        int left = 2 * i + 1, right = 2 * i + 2;
        int smallest = left;
        if (right < *heapSize && heap[right]->frequency < heap[left]->frequency)
            smallest = right;
        if (heap[i]->frequency <= heap[smallest]->frequency)
            break;
        Node* temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }

    return minNode;
}

// ���� ���ο� ��带 �����ϴ� �Լ�
void insertHeap(Node** heap, int* heapSize, Node* newNode) {
    heap[(*heapSize)++] = newNode;  // ���ο� ��带 ���� ����

    int i = *heapSize - 1;
    while (i && heap[(i - 1) / 2]->frequency > heap[i]->frequency) {
        Node* temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// ���ο� ��带 �����ϴ� �Լ�
Node* newNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;  // �ʱ� �ڽ� ��� ����
    return node;
}

// ���� ���¸� ����ϴ� �Լ�
void printHeap(Node** heap, int heapSize) {
    for (int i = 0; i < heapSize; i++) {
        printf("%d ", heap[i]->frequency);
    }
    printf("\n");
}

// ������ Ʈ���� �����ϴ� �Լ�
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* heap[100];
    int heapSize = 0;

    // ���ڸ� ���� �����ϰ� ���� ���
    for (int i = 0; i < size; i++) {
        insertHeap(heap, &heapSize, newNode(characters[i], frequencies[i]));
        printHeap(heap, heapSize);  // ���� �� ���� ���
    }

    // ������ Ʈ�� ����
    while (heapSize > 1) {
        Node* left = extractMin(heap, &heapSize);  // �ּҰ� ����
        Node* right = extractMin(heap, &heapSize);  // �� ��° �ּҰ� ����

        // �� ����� �󵵼��� ���ϰ� ���
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, left->frequency + right->frequency);

        // ���ο� ������ ��� ����
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->character = '-';
        newNode->frequency = left->frequency + right->frequency;
        newNode->left = left;
        newNode->right = right;

        insertHeap(heap, &heapSize, newNode);  // ���� ����
        printHeap(heap, heapSize);  // �� ���� ���
    }

    return heap[0];  // ��Ʈ ��� ��ȯ
}

// ������ �ڵ带 ����ϴ� �Լ�
void printCodes(Node* root, int arr[], int top) {
    // ���� �ڽ��� ���� ��� 1 �߰�
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    // ������ �ڽ��� ���� ��� 0 �߰�
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    // ���� ����� ��� �ڵ� ���
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// ������ �ڵ带 �����ϴ� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);  // ������ Ʈ�� ����
    int arr[100], top = 0;
    printCodes(root, arr, top);  // ������ �ڵ� ���
}

int main() {
    // ������ �ڵ��� ���� ������
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int huffSize = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, huffSize);  // ������ �ڵ� ����

    return 0;
}
