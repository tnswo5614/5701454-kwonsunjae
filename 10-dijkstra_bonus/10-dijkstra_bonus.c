#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000000

// 그래프 구조체 (인접 행렬 사용)
typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES]; // 가중치 행렬
} GraphType;

// 최소 힙의 노드 구조체
typedef struct HeapNode {
    int vertex; // 정점 번호
    int distance; // 정점까지의 거리
} HeapNode;

// 최소 힙 구조체
typedef struct {
    HeapNode heap[MAX_VERTICES]; // 힙 배열
    int size; // 힙 크기
} Heap;

// 그래프의 간선 구조체 (연결 리스트 사용)
typedef struct Edge {
    int vertex; // 연결된 정점
    int weight; // 간선의 가중치
    struct Edge* next; // 다음 간선 포인터
} Edge;

// 연결 리스트 기반의 그래프 구조체
typedef struct GraphTypeList {
    int n; // 정점의 개수
    Edge* adj_list[MAX_VERTICES]; // 인접 리스트
} GraphTypeList;

// 전역 변수: 각 정점까지의 최단 거리, 방문 여부, 방문 순서 저장
int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int foundorder[MAX_VERTICES];

// 인접 행렬 그래프 초기화 함수
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->weight[i][j] = INF; // 모든 가중치를 무한대로 초기화
        }
    }
}

// 인접 행렬에 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start - 1][end - 1] = weight; // 양방향 간선 추가
    g->weight[end - 1][start - 1] = weight;
}

// 현재 상태 출력 함수: 각 정점의 거리와 방문 여부 출력
void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

// 최소 거리의 정점 선택 함수
int choose(int distance[], int n, int found[]) {
    int min = INF;
    int minpos = -1;
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 다익스트라 최단 경로 알고리즘 (인접 행렬 사용)
void shortest_path(GraphType* g, int start) {
    int visit_count = 0;
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF; // 초기화: 모든 거리 무한대로 설정
        found[i] = FALSE; // 모든 정점 방문 안 함으로 설정
    }
    found[start] = TRUE; // 시작 정점 방문 처리
    distance[start] = 0; // 시작 정점의 거리 0으로 설정
    foundorder[visit_count++] = start + 1; // 방문 순서 저장
    print_status(g);

    // 시작 정점과 연결된 간선 거리 초기화
    for (int w = 0; w < g->n; w++) {
        if (!found[w]) {
            distance[w] = g->weight[start][w];
        }
    }

    // 나머지 정점 탐색
    int u = choose(distance, g->n, found);
    found[u] = TRUE;
    foundorder[visit_count++] = u + 1;
    print_status(g);

    for (int i = 0; i < g->n - 2; i++) {
        for (int w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w]; // 거리 갱신
                }
            }
        }
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        foundorder[visit_count++] = u + 1;
        print_status(g);
    }
}

// 최소 힙 초기화 함수
void init_heap(Heap* h) {
    h->size = 0; // 초기 힙 크기 설정
}

// 최소 힙에 새로운 노드 삽입 함수
void insert_min_heap(Heap* h, int vertex, int key) {
    int i = ++(h->size);
    while (i != 1 && key < h->heap[i / 2].distance) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].distance = key;
}

// 최소 힙에서 최소값 제거 및 반환 함수
HeapNode delete_min_heap(Heap* h) {
    int parent = 1, child = 2;
    HeapNode item = h->heap[1];
    HeapNode temp = h->heap[(h->size)--];
    while (child <= h->size) {
        if (child < h->size && h->heap[child].distance > h->heap[child + 1].distance)
            child++;
        if (temp.distance <= h->heap[child].distance)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 연결 리스트 그래프 초기화 함수
void init_graph_list(GraphTypeList* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++)
        g->adj_list[i] = NULL; // 모든 인접 리스트 초기화
}

// 연결 리스트에 간선 추가 함수
void insert_edge_list(GraphTypeList* g, int start, int end, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge)); // 새로운 간선 생성
    edge->vertex = end - 1;
    edge->weight = weight;
    edge->next = g->adj_list[start - 1];
    g->adj_list[start - 1] = edge;

    edge = (Edge*)malloc(sizeof(Edge)); // 양방향 간선 추가
    edge->vertex = start - 1;
    edge->weight = weight;
    edge->next = g->adj_list[end - 1];
    g->adj_list[end - 1] = edge;
}

// 다익스트라 최단 경로 알고리즘 (연결 리스트와 힙 사용)
void shortest_path_list(GraphTypeList* g, int start) {
    Heap heap;
    init_heap(&heap);
    int visit_count = 0;
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF; // 초기화: 모든 거리 무한대로 설정
        found[i] = FALSE; // 모든 정점 방문 안 함으로 설정
    }
    found[start] = TRUE; // 시작 정점 방문 처리
    distance[start] = 0; // 시작 정점의 거리 0으로 설정
    insert_min_heap(&heap, start, distance[start]); // 시작 정점 힙에 삽입
    foundorder[visit_count++] = start + 1; // 방문 순서 저장
    print_status((GraphType*)g);

    while (heap.size > 0) {
        HeapNode u = delete_min_heap(&heap);
        int current = u.vertex;
        if (found[current] && current != start) continue; // 이미 방문된 정점이면 건너뜀
        if (current != start) {
            found[current] = TRUE; // 현재 정점 방문 처리
            foundorder[visit_count++] = current + 1; // 방문 순서 저장
            print_status((GraphType*)g);
        }
        for (Edge* e = g->adj_list[current]; e != NULL; e = e->next) {
            int next = e->vertex;
            if (!found[next]) {
                if (distance[current] + e->weight < distance[next]) {
                    distance[next] = distance[current] + e->weight; // 거리 갱신
                    insert_min_heap(&heap, next, distance[next]); // 갱신된 거리 힙에 삽입
                }
            }
        }
    }
}

// 그래프 생성 함수
void generate_graph(GraphType* g1, GraphTypeList* g2) {
    struct {
        int start, end, weight;
    } edges[] = {
        {1, 7, 12}, {1, 6, 11}, {1, 2, 3},
        {2, 3, 5},  {2, 4, 4},  {2, 5, 1},
        {2, 6, 7},  {2, 7, 8},  {3, 4, 2},
        {3, 7, 6},  {3, 8, 5},  {4, 5, 13},
        {4, 8, 14}, {4, 10, 16},{5, 6, 9},
        {5, 9, 18}, {5, 10, 17},{7, 8, 13},
        {8, 10, 15},{9, 10, 10}
    };

    init_graph(g1, 10); // 인접 행렬 그래프 초기화
    init_graph_list(g2, 10); // 연결 리스트 그래프 초기화

    for (int i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {
        insert_edge(g1, edges[i].start, edges[i].end, edges[i].weight); // 인접 행렬에 간선 추가
        insert_edge_list(g2, edges[i].start, edges[i].end, edges[i].weight); // 연결 리스트에 간선 추가
    }
}

int main(void) {
    GraphType g1;
    GraphTypeList g2;

    generate_graph(&g1, &g2); // 그래프 생성

    printf("----------인접 행렬을 이용한 구현----------\n");
    shortest_path(&g1, 0); // 인접 행렬 기반 최단 경로 탐색

    printf("\n방문 순서 (인접 행렬): ");
    for (int i = 0; i < g1.n; i++) {
        printf("%d ", foundorder[i]); // 방문 순서 출력
    }
    printf("\n\n");

    // 전역 변수 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF;
        found[i] = FALSE;
        foundorder[i] = 0;
    }

    printf("----------연결리스트와 힙을 이용한 구현 (bonus)----------\n");
    shortest_path_list(&g2, 0); // 연결 리스트 및 힙 기반 최단 경로 탐색

    printf("\n방문 순서 (연결리스트): ");
    for (int i = 0; i < g2.n; i++) {
        printf("%d ", foundorder[i]); // 방문 순서 출력
    }
    printf("\n");

    return 0;
}