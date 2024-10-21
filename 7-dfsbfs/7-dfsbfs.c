#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// 인접 행렬 방식으로 그래프를 표현하는 구조체
typedef struct {
    int n; // 그래프의 정점 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬
} GraphMatType;

// 스택을 정의하는 구조체
typedef struct {
    int items[MAX_VERTICES]; // 스택에 저장되는 아이템 배열
    int top; // 스택의 탑 위치
} Stack;

// 큐를 정의하는 구조체
typedef struct {
    int items[MAX_VERTICES]; // 큐에 저장되는 아이템 배열
    int front; // 큐의 앞부분
    int rear; // 큐의 뒷부분
} Queue;

// 그래프 생성 함수
GraphMatType* create_mat_graph();

// 그래프 메모리 해제 함수
void destroy_mat_graph(GraphMatType* g);

// 그래프 초기화 함수
void init_mat_graph(GraphMatType* g);

// 그래프에 정점 삽입 함수
void insert_vertex_mat_graph(GraphMatType* g, int v);

// 그래프에 간선 삽입 함수
void insert_edge_mat_graph(GraphMatType* g, int s, int e);

// 인접 행렬을 출력하는 함수 (디버깅 용도)
void print_adj_mat(GraphMatType* g);

// 깊이 우선 탐색(DFS) 함수
void DFS_matrix(GraphMatType* g, int start, int target);

// 너비 우선 탐색(BFS) 함수
void BFS_matrix(GraphMatType* g, int start, int target);

// 사용자 인터페이스 함수
void runUserInterface(GraphMatType* root);

// 스택에 값을 넣는 함수
void push(Stack* s, int value);

// 스택에서 값을 꺼내는 함수
int pop(Stack* s);

// 스택이 비어있는지 확인하는 함수
int is_empty_stack(Stack* s);

// 큐에 값을 넣는 함수
void enqueue(Queue* q, int value);

// 큐에서 값을 꺼내는 함수
int dequeue(Queue* q);

// 큐가 비어있는지 확인하는 함수
int is_empty_queue(Queue* q);

int main() {
    // 그래프 생성 및 초기화
    GraphMatType* g = create_mat_graph();
    init_mat_graph(g);

    // 11개의 정점을 그래프에 삽입
    for (int i = 0; i < 11; i++) {
        insert_vertex_mat_graph(g, i);
    }

    // 그래프에 간선 삽입 (인접한 정점 연결)
    insert_edge_mat_graph(g, 0, 5);
    insert_edge_mat_graph(g, 0, 2);
    insert_edge_mat_graph(g, 0, 4);
    insert_edge_mat_graph(g, 0, 6);
    insert_edge_mat_graph(g, 0, 9);

    insert_edge_mat_graph(g, 1, 5);
    insert_edge_mat_graph(g, 1, 4);
    insert_edge_mat_graph(g, 1, 7);
    insert_edge_mat_graph(g, 1, 10);

    insert_edge_mat_graph(g, 2, 3);
    insert_edge_mat_graph(g, 2, 0);
    insert_edge_mat_graph(g, 2, 4);

    insert_edge_mat_graph(g, 3, 2);
    insert_edge_mat_graph(g, 3, 5);
    insert_edge_mat_graph(g, 3, 4);

    insert_edge_mat_graph(g, 4, 2);
    insert_edge_mat_graph(g, 4, 3);
    insert_edge_mat_graph(g, 4, 6);
    insert_edge_mat_graph(g, 4, 7);
    insert_edge_mat_graph(g, 4, 1);
    insert_edge_mat_graph(g, 4, 5);
    insert_edge_mat_graph(g, 4, 0);

    insert_edge_mat_graph(g, 5, 0);
    insert_edge_mat_graph(g, 5, 3);
    insert_edge_mat_graph(g, 5, 1);
    insert_edge_mat_graph(g, 5, 4);

    insert_edge_mat_graph(g, 6, 0);
    insert_edge_mat_graph(g, 6, 4);
    insert_edge_mat_graph(g, 6, 7);
    insert_edge_mat_graph(g, 6, 8);

    insert_edge_mat_graph(g, 7, 1);
    insert_edge_mat_graph(g, 7, 4);
    insert_edge_mat_graph(g, 7, 6);
    insert_edge_mat_graph(g, 7, 10);

    insert_edge_mat_graph(g, 8, 6);
    insert_edge_mat_graph(g, 8, 9);
    insert_edge_mat_graph(g, 8, 10);

    insert_edge_mat_graph(g, 9, 0);
    insert_edge_mat_graph(g, 9, 8);

    insert_edge_mat_graph(g, 10, 1);
    insert_edge_mat_graph(g, 10, 7);
    insert_edge_mat_graph(g, 10, 8);

    // 사용자 인터페이스 실행 (탐색 기능 제공)
    runUserInterface(g);

    // 그래프 메모리 해제
    free(g);
    return 0;
}

// 인접 행렬 방식으로 그래프를 생성하는 함수
GraphMatType* create_mat_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

// 그래프를 초기화하는 함수 (모든 값을 0으로 설정)
void init_mat_graph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}

// 그래프에 정점을 추가하는 함수
void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if ((g->n) >= (MAX_VERTICES - 1)) {
        fprintf(stderr, "정점의 개수가 초과 되었습니다\n");
        return;
    }
    (g->n)++; // 정점 개수 증가
}

// 두 정점 사이에 간선을 추가하는 함수
void insert_edge_mat_graph(GraphMatType* g, int start, int end) {
    if (g->n <= start || g->n <= end) {
        fprintf(stderr, "그래프 정점번호 오류.\n");
        return;
    }
    g->adj_mat[start][end] = 1; // 간선 추가 (양방향)
    g->adj_mat[end][start] = 1;
}

// 인접 행렬을 출력하는 함수 (그래프 상태를 확인하는 용도)
void print_adj_mat(GraphMatType* g) {
    printf("     ");
    for (int i = 0; i < g->n; i++) {
        printf(" %02d ", i);
    }
    printf("\n_____");
    for (int i = 0; i < g->n; i++) {
        printf("_______");
    }
    printf("\n");
    for (int i = 0; i < g->n; i++) {
        printf(" %02d: ", i);
        for (int j = 0; j < g->n; j++)
            printf(" %02d ", g->adj_mat[i][j]);
        printf("\n");
    }
}

// 깊이 우선 탐색(DFS)을 수행하는 함수
void DFS_matrix(GraphMatType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 }; // 각 정점의 방문 여부를 저장하는 배열
    Stack s;
    s.top = -1; // 스택 초기화
    push(&s, start); // 시작 정점을 스택에 추가
    int count = 0; // 방문한 노드의 개수를 기록

    while (!is_empty_stack(&s)) {
        int vertex = pop(&s); // 스택에서 정점을 꺼냄

        if (!visited[vertex]) { // 아직 방문하지 않았다면
            visited[vertex] = 1; // 방문 처리
            count++;
            printf("%d ", vertex); // 방문한 정점 출력

            if (vertex == target) { // 목표 정점에 도달했다면 탐색 종료
                printf("\n탐색 성공: %d\n", target);
                printf("방문한 노드 수: %d\n", count);
                return;
            }

            // 인접한 정점을 스택에 추가
            for (int i = 0; i < g->n; i++) {
                if (g->adj_mat[vertex][i] == 1 && !visited[i]) {
                    push(&s, i);
                }
            }
        }
        else {
            printf("%d ", vertex); // 이미 방문한 정점 출력
        }
    }
    printf("\n%d 발견하지 못함(탐색 실패)\n", target);
    printf("방문한 노드 수: %d\n", count);
}

// 너비 우선 탐색(BFS)을 수행하는 함수
void BFS_matrix(GraphMatType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 }; // 방문 여부를 추적

    Queue q;
    q.front = 0;
    q.rear = -1; // 큐 초기화
    enqueue(&q, start); // 시작 정점을 큐에 삽입
    int count = 0; // 방문한 노드의 개수를 기록

    while (!is_empty_queue(&q)) {
        int vertex = dequeue(&q); // 큐에서 정점을 꺼냄

        if (visited[vertex] == 0) { // 아직 방문하지 않았다면
            visited[vertex] = 1; // 방문 처리
            count++;
            printf("%d ", vertex); // 방문한 정점 출력

            if (vertex == target) { // 목표 정점에 도달했다면 탐색 종료
                printf("\n탐색 성공: %d\n", target);
                printf("방문한 노드 수: %d\n", count);
                return;
            }

            // 인접한 정점을 큐에 추가
            for (int i = 0; i < g->n; i++) {
                if (g->adj_mat[vertex][i] == 1 && !visited[i]) {
                    enqueue(&q, i);
                }
            }
        }
        else {
            printf("%d ", vertex); // 이미 방문한 정점 출력
        }
    }
    printf("\n%d 발견하지 못함(탐색 실패)\n", target);
    printf("방문한 노드 수: %d\n", count);
}

// 사용자 인터페이스를 제공하는 함수
void runUserInterface(GraphMatType* root) {
    int c = 0;
    int start_node = 0;
    int target_node = 0;

    for (;;) {
        printf("------------------------------\n");
        printf("1     : 깊이 우선 탐색        |\n");
        printf("2     : 너비 우선 탐색        |\n");
        printf("3     : 종료                  |\n");
        printf("------------------------------\n");

        printf("메뉴 입력: ");
        scanf_s("%d", &c);

        switch (c) {
        case 1:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d", &start_node);
            scanf_s("%d", &target_node);
            DFS_matrix(root, start_node, target_node); // DFS 탐색 실행
            break;
        case 2:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d", &start_node);
            scanf_s("%d", &target_node);
            BFS_matrix(root, start_node, target_node); // BFS 탐색 실행
            break;
        case 3:
            exit(0); // 프로그램 종료
        default:
            printf("다시입력해주세요.\n");
        }
    }
}

// 스택에 값을 삽입하는 함수
void push(Stack* s, int value) {
    if (s->top < MAX_VERTICES - 1) {
        s->items[++(s->top)] = value; // 스택의 top을 증가시키고 값을 추가
    }
}

// 스택에서 값을 꺼내는 함수
int pop(Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--]; // 스택의 top에서 값을 제거하고 반환
    }
    return -1; // 스택이 비어있으면 -1 반환
}

// 스택이 비어있는지 확인하는 함수
int is_empty_stack(Stack* s) {
    return s->top == -1;
}

// 큐에 값을 삽입하는 함수
void enqueue(Queue* q, int value) {
    if (q->rear < MAX_VERTICES - 1) {
        q->items[++(q->rear)] = value; // 큐의 rear에 값을 추가
    }
}

// 큐에서 값을 꺼내는 함수
int dequeue(Queue* q) {
    if (q->front <= q->rear) {
        return q->items[(q->front)++]; // 큐의 front에서 값을 꺼내고 반환
    }
    return -1; // 큐가 비어있으면 -1 반환
}

// 큐가 비어있는지 확인하는 함수
int is_empty_queue(Queue* q) {
    return q->front > q->rear; // 큐의 front가 rear보다 크면 비어있음
}