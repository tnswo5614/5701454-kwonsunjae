#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

// Edge 구조체: 그래프의 간선 정보를 저장
typedef struct {
    int start, end, weight;
} Edge;

// GraphType 구조체: 그래프 정보를 저장
typedef struct {
    int n;  // 간선 수
    Edge edges[MAX_VERTICES];
} GraphType;

// MinHeap 구조체: 최소 힙을 위한 구조체
typedef struct {
    Edge heap[MAX_VERTICES];
    int size;
} MinHeap;

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0;
}

// 간선 삽입 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

// 그래프 데이터 생성 함수
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 2, 7, 8);
}

// 간선 가중치 비교 함수 (QuickSort에 사용)
int compare(const void* a, const void* b) {
    Edge* x = (Edge*)a;
    Edge* y = (Edge*)b;
    return x->weight - y->weight;
}

// 부모 노드
int parent[MAX_VERTICES];

// 초기화 함수
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// 특정 요소의 루트 찾기 
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    return parent[curr] = set_find(parent[curr]);
}

// 두 집합을 합치는 함수
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

// QuickSort 기반의 Kruskal 알고리즘
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0;  // 선택된 간선의 수
    int uset, vset;

    qsort(g->edges, g->n, sizeof(Edge), compare);  // 간선 가중치 기준 정렬

    printf("QuickSort Based Kruskal\n");
    set_init(MAX_VERTICES);

    // 간선을 하나씩 선택하면서 MST 구성
    for (int i = 0; i < g->n; i++) {
        uset = set_find(g->edges[i].start);
        vset = set_find(g->edges[i].end);
        if (uset != vset) {
            printf("Edge (%d, %d) select %d\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight);
            set_union(uset, vset);
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1)
            break;
    }

    printf("\n");
}

// 최소 힙 초기화 함수
void minHeapInit(MinHeap* h) {
    h->size = 0;
}

// 최소 힙에 삽입하는 함수
void minHeapInsert(MinHeap* h, Edge e) {
    int i = h->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->heap[parent].weight <= e.weight)
            break;
        h->heap[i] = h->heap[parent];
        i = parent;
    }
    h->heap[i] = e;
}

// 최소 힙에서 최소 가중치 간선 삭제
Edge minHeapDelete(MinHeap* h) {
    Edge minEdge = h->heap[0];
    Edge lastEdge = h->heap[--h->size];

    int parent = 0;
    int child = 1;
    while (child < h->size) {
        if (child + 1 < h->size && h->heap[child + 1].weight < h->heap[child].weight)
            child++;
        if (lastEdge.weight <= h->heap[child].weight)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = 2 * parent + 1;
    }
    h->heap[parent] = lastEdge;
    return minEdge;
}

// MinHeap 기반의 Kruskal 알고리즘
void MinHeapKruskal(GraphType* g) {
    MinHeap heap;
    minHeapInit(&heap);
    int edge_accepted = 0;
    int uset, vset;

    // 모든 간선을 힙에 삽입
    for (int i = 0; i < g->n; i++) {
        minHeapInsert(&heap, g->edges[i]);
    }

    printf("MinHeap Based Kruskal\n");
    set_init(MAX_VERTICES);

    // 힙에서 최소 가중치 간선을 하나씩 선택하여 MST 구성
    while (heap.size > 0) {
        Edge edge = minHeapDelete(&heap);
        uset = set_find(edge.start);
        vset = set_find(edge.end);

        if (uset != vset) {
            printf("Edge (%d, %d) select %d\n", edge.start, edge.end, edge.weight);
            set_union(uset, vset);
            edge_accepted++;
        }
        if (edge_accepted == g->n - 1)
            break;
    }
}

// 메인 함수: 그래프 초기화 및 Kruskal 알고리즘 실행
int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    QuickKruskal(g);
    MinHeapKruskal(g);

    free(g);
    return 0;
}
