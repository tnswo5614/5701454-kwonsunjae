#include <stdio.h>
#include <stdlib.h>

// 허프만 트리의 노드 구조체 정의
typedef struct Node {
    char character; // 문자를 저장하는 필드
    int frequency;  // 빈도수 필드
    struct Node* left, * right; // 왼쪽, 오른쪽 자식 노드
} Node;

// 힙에서 최소 빈도수를 가진 노드를 추출하는 함수
Node* extractMin(Node** heap, int* heapSize) {
    Node* minNode = heap[0]; // 루트 노드가 최소값
    heap[0] = heap[--(*heapSize)]; // 마지막 노드를 루트로 이동

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

// 힙에 새로운 노드를 삽입하는 함수
void insertHeap(Node** heap, int* heapSize, Node* newNode) {
    heap[(*heapSize)++] = newNode;  // 새로운 노드를 힙에 삽입

    int i = *heapSize - 1;
    while (i && heap[(i - 1) / 2]->frequency > heap[i]->frequency) {
        Node* temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// 새로운 노드를 생성하는 함수
Node* newNode(char character, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;  // 초기 자식 노드 없음
    return node;
}

// 힙의 상태를 출력하는 함수
void printHeap(Node** heap, int heapSize) {
    for (int i = 0; i < heapSize; i++) {
        printf("%d ", heap[i]->frequency);
    }
    printf("\n");
}

// 허프만 트리를 빌드하는 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* heap[100];
    int heapSize = 0;

    // 문자를 힙에 삽입하고 상태 출력
    for (int i = 0; i < size; i++) {
        insertHeap(heap, &heapSize, newNode(characters[i], frequencies[i]));
        printHeap(heap, heapSize);  // 현재 힙 상태 출력
    }

    // 허프만 트리 빌드
    while (heapSize > 1) {
        Node* left = extractMin(heap, &heapSize);  // 최소값 추출
        Node* right = extractMin(heap, &heapSize);  // 두 번째 최소값 추출

        // 두 노드의 빈도수를 더하고 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, left->frequency + right->frequency);

        // 새로운 합쳐진 노드 생성
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->character = '-';
        newNode->frequency = left->frequency + right->frequency;
        newNode->left = left;
        newNode->right = right;

        insertHeap(heap, &heapSize, newNode);  // 힙에 삽입
        printHeap(heap, heapSize);  // 힙 상태 출력
    }

    return heap[0];  // 루트 노드 반환
}

// 허프만 코드를 출력하는 함수
void printCodes(Node* root, int arr[], int top) {
    // 왼쪽 자식이 있을 경우 1 추가
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    // 오른쪽 자식이 있을 경우 0 추가
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    // 리프 노드일 경우 코드 출력
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// 허프만 코드를 생성하는 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);  // 허프만 트리 생성
    int arr[100], top = 0;
    printCodes(root, arr, top);  // 허프만 코드 출력
}

int main() {
    // 허프만 코딩을 위한 데이터
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int huffSize = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, huffSize);  // 허프만 코드 생성

    return 0;
}
