#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000000

// �׷��� ����ü (���� ��� ���)
typedef struct GraphType {
    int n; // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES]; // ����ġ ���
} GraphType;

// �ּ� ���� ��� ����ü
typedef struct HeapNode {
    int vertex; // ���� ��ȣ
    int distance; // ���������� �Ÿ�
} HeapNode;

// �ּ� �� ����ü
typedef struct {
    HeapNode heap[MAX_VERTICES]; // �� �迭
    int size; // �� ũ��
} Heap;

// �׷����� ���� ����ü (���� ����Ʈ ���)
typedef struct Edge {
    int vertex; // ����� ����
    int weight; // ������ ����ġ
    struct Edge* next; // ���� ���� ������
} Edge;

// ���� ����Ʈ ����� �׷��� ����ü
typedef struct GraphTypeList {
    int n; // ������ ����
    Edge* adj_list[MAX_VERTICES]; // ���� ����Ʈ
} GraphTypeList;

// ���� ����: �� ���������� �ִ� �Ÿ�, �湮 ����, �湮 ���� ����
int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int foundorder[MAX_VERTICES];

// ���� ��� �׷��� �ʱ�ȭ �Լ�
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->weight[i][j] = INF; // ��� ����ġ�� ���Ѵ�� �ʱ�ȭ
        }
    }
}

// ���� ��Ŀ� ���� �߰� �Լ�
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start - 1][end - 1] = weight; // ����� ���� �߰�
    g->weight[end - 1][start - 1] = weight;
}

// ���� ���� ��� �Լ�: �� ������ �Ÿ��� �湮 ���� ���
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

// �ּ� �Ÿ��� ���� ���� �Լ�
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

// ���ͽ�Ʈ�� �ִ� ��� �˰��� (���� ��� ���)
void shortest_path(GraphType* g, int start) {
    int visit_count = 0;
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF; // �ʱ�ȭ: ��� �Ÿ� ���Ѵ�� ����
        found[i] = FALSE; // ��� ���� �湮 �� ������ ����
    }
    found[start] = TRUE; // ���� ���� �湮 ó��
    distance[start] = 0; // ���� ������ �Ÿ� 0���� ����
    foundorder[visit_count++] = start + 1; // �湮 ���� ����
    print_status(g);

    // ���� ������ ����� ���� �Ÿ� �ʱ�ȭ
    for (int w = 0; w < g->n; w++) {
        if (!found[w]) {
            distance[w] = g->weight[start][w];
        }
    }

    // ������ ���� Ž��
    int u = choose(distance, g->n, found);
    found[u] = TRUE;
    foundorder[visit_count++] = u + 1;
    print_status(g);

    for (int i = 0; i < g->n - 2; i++) {
        for (int w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w]; // �Ÿ� ����
                }
            }
        }
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        foundorder[visit_count++] = u + 1;
        print_status(g);
    }
}

// �ּ� �� �ʱ�ȭ �Լ�
void init_heap(Heap* h) {
    h->size = 0; // �ʱ� �� ũ�� ����
}

// �ּ� ���� ���ο� ��� ���� �Լ�
void insert_min_heap(Heap* h, int vertex, int key) {
    int i = ++(h->size);
    while (i != 1 && key < h->heap[i / 2].distance) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].distance = key;
}

// �ּ� ������ �ּҰ� ���� �� ��ȯ �Լ�
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

// ���� ����Ʈ �׷��� �ʱ�ȭ �Լ�
void init_graph_list(GraphTypeList* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++)
        g->adj_list[i] = NULL; // ��� ���� ����Ʈ �ʱ�ȭ
}

// ���� ����Ʈ�� ���� �߰� �Լ�
void insert_edge_list(GraphTypeList* g, int start, int end, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge)); // ���ο� ���� ����
    edge->vertex = end - 1;
    edge->weight = weight;
    edge->next = g->adj_list[start - 1];
    g->adj_list[start - 1] = edge;

    edge = (Edge*)malloc(sizeof(Edge)); // ����� ���� �߰�
    edge->vertex = start - 1;
    edge->weight = weight;
    edge->next = g->adj_list[end - 1];
    g->adj_list[end - 1] = edge;
}

// ���ͽ�Ʈ�� �ִ� ��� �˰��� (���� ����Ʈ�� �� ���)
void shortest_path_list(GraphTypeList* g, int start) {
    Heap heap;
    init_heap(&heap);
    int visit_count = 0;
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF; // �ʱ�ȭ: ��� �Ÿ� ���Ѵ�� ����
        found[i] = FALSE; // ��� ���� �湮 �� ������ ����
    }
    found[start] = TRUE; // ���� ���� �湮 ó��
    distance[start] = 0; // ���� ������ �Ÿ� 0���� ����
    insert_min_heap(&heap, start, distance[start]); // ���� ���� ���� ����
    foundorder[visit_count++] = start + 1; // �湮 ���� ����
    print_status((GraphType*)g);

    while (heap.size > 0) {
        HeapNode u = delete_min_heap(&heap);
        int current = u.vertex;
        if (found[current] && current != start) continue; // �̹� �湮�� �����̸� �ǳʶ�
        if (current != start) {
            found[current] = TRUE; // ���� ���� �湮 ó��
            foundorder[visit_count++] = current + 1; // �湮 ���� ����
            print_status((GraphType*)g);
        }
        for (Edge* e = g->adj_list[current]; e != NULL; e = e->next) {
            int next = e->vertex;
            if (!found[next]) {
                if (distance[current] + e->weight < distance[next]) {
                    distance[next] = distance[current] + e->weight; // �Ÿ� ����
                    insert_min_heap(&heap, next, distance[next]); // ���ŵ� �Ÿ� ���� ����
                }
            }
        }
    }
}

// �׷��� ���� �Լ�
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

    init_graph(g1, 10); // ���� ��� �׷��� �ʱ�ȭ
    init_graph_list(g2, 10); // ���� ����Ʈ �׷��� �ʱ�ȭ

    for (int i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {
        insert_edge(g1, edges[i].start, edges[i].end, edges[i].weight); // ���� ��Ŀ� ���� �߰�
        insert_edge_list(g2, edges[i].start, edges[i].end, edges[i].weight); // ���� ����Ʈ�� ���� �߰�
    }
}

int main(void) {
    GraphType g1;
    GraphTypeList g2;

    generate_graph(&g1, &g2); // �׷��� ����

    printf("----------���� ����� �̿��� ����----------\n");
    shortest_path(&g1, 0); // ���� ��� ��� �ִ� ��� Ž��

    printf("\n�湮 ���� (���� ���): ");
    for (int i = 0; i < g1.n; i++) {
        printf("%d ", foundorder[i]); // �湮 ���� ���
    }
    printf("\n\n");

    // ���� ���� �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF;
        found[i] = FALSE;
        foundorder[i] = 0;
    }

    printf("----------���Ḯ��Ʈ�� ���� �̿��� ���� (bonus)----------\n");
    shortest_path_list(&g2, 0); // ���� ����Ʈ �� �� ��� �ִ� ��� Ž��

    printf("\n�湮 ���� (���Ḯ��Ʈ): ");
    for (int i = 0; i < g2.n; i++) {
        printf("%d ", foundorder[i]); // �湮 ���� ���
    }
    printf("\n");

    return 0;
}