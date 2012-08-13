#include <stdlib.h>
#include <stdio.h>

struct list {
    int value;
    struct list *next;
};
typedef struct list list;

addTail(list* l, int value) {
    while (l->next != NULL) {
        printf("Find the tail\n");
        l = l->next;
    }
    list* tail = (list*)malloc(sizeof(list));
    tail->value = value;
    l->next = tail;
}

printList(list* l) {
    while (l->next != NULL) {
        printf("%d ->", l->value);
        l = l->next;
    }
    printf(" %d\n", l->value);
}
main() {
    printf("Make a list\n");
    list* head = (list*)malloc(sizeof(list));
    printf("Assign a value\n");
    head->value = 0;
    head->next = NULL;
    printList(head);
    printf("Call add a tail...\n");
    addTail(head, 10);
    printList(head);
    addTail(head, 20);
    printList(head);
}
