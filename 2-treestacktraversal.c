#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
typedef int value;
struct tree_node {
    value data;
    struct tree_node* left, * right;
};
typedef struct tree_node TreeNode;

// 스택 요소 타입 정의
typedef TreeNode* element;
typedef struct StackNode {
    element data;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

// 스택 관련 함수들 정의
void init(LinkedStackType* s) {
    s->top = NULL;
}

int is_empty(LinkedStackType* s) {
    return (s->top == NULL);
}

int is_full(LinkedStackType* s) {
    return 0;
}

void push(LinkedStackType* s, element item) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
    printf("push(%d) ", item->data);
}

element pop(LinkedStackType* s) {
    StackNode* temp = s->top;
    element data = temp->data;
    s->top = temp->link;
    free(temp);
    printf("pop(%d) ", data->data);
    return data;
}

void print_stack(LinkedStackType* s) {
    for (StackNode* p = s->top; p != NULL; p = p->link)
        printf("%d->", p->data->data);
    printf("NULL \n");
}

// 전위 순회 함수
void itr_preorder_traversal(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    printf("전위 순회의 출력 예\n");
    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            printf("visit(%d) ", nptr->data);
            push(&s, nptr);
            nptr = nptr->left;
        }
        nptr = pop(&s);
        nptr = nptr->right;
    }
    printf("\n");
}

// 중위 순회 함수
void itr_inorder_traversal(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    printf("중위 순회의 출력 예\n");
    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }
        nptr = pop(&s);
        printf("visit(%d) ", nptr->data);
        nptr = nptr->right;
    }
    printf("\n");
}

// 후위 순회 함수
void itr_postorder_traversal(TreeNode* root) {
    LinkedStackType s1, s2;
    TreeNode* nptr = root;
    printf("후위 순회의 출력 예\n");
    init(&s1);
    init(&s2);

    if (nptr == NULL) return;

    push(&s1, nptr);

    while (!is_empty(&s1)) {
        nptr = pop(&s1);
        push(&s2, nptr);

        if (nptr->left)
            push(&s1, nptr->left);
        if (nptr->right)
            push(&s1, nptr->right);
    }

    while (!is_empty(&s2)) {
        nptr = pop(&s2);
        printf("visit(%d) ", nptr->data);
    }
}

// 메인 함수
int main() {
    // 트리 생성
    TreeNode n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15;
    n1.data = 1, n1.left = &n2, n1.right = &n3;
    n2.data = 2, n2.left = &n4, n2.right = &n5;
    n3.data = 9, n3.left = &n6, n3.right = &n7;
    n4.data = 3, n4.left = &n8, n4.right = &n9;
    n5.data = 5, n5.left = &n10, n5.right = &n11;
    n6.data = 10, n6.left = &n12, n6.right = &n13;
    n7.data = 13, n7.left = &n14, n7.right = &n15;
    n8.data = 4, n8.left = NULL, n8.right = NULL;
    n9.data = 6, n9.left = NULL, n9.right = NULL;
    n10.data = 7, n10.left = NULL, n10.right = NULL;
    n11.data = 8, n11.left = NULL, n11.right = NULL;
    n12.data = 11, n12.left = NULL, n12.right = NULL;
    n13.data = 12, n13.left = NULL, n13.right = NULL;
    n14.data = 14, n14.left = NULL, n14.right = NULL;
    n15.data = 15, n15.left = NULL, n15.right = NULL;

    printf("출력결과:\n\n");
    // 전위, 중위, 후위 순회 호출
    itr_preorder_traversal(&n1);
    printf("\n\n");
    itr_inorder_traversal(&n1);
    printf("\n\n");
    itr_postorder_traversal(&n1);

    return 0;
}
