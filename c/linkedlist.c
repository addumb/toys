#include <stdlib.h>
#include <stdio.h>

struct list {
    int value;
    struct list *next;
};
typedef struct list list;

list* reverseList(list* head, list* previous) {
    list* tail;
    if (head->next == NULL) {
        head->next = previous;
        return head;
    } else {
        tail = reverseList(head->next, head);
        head->next = previous;
        return tail;
    }
}

int length(list* l) {
    int num = 0;
    while (l) {
        num++;
        l = l->next;
    }
    return num;
}
    
addTail(list* l, int value) {
    while (l->next != NULL) {
        printf("Find the tail\n");
        l = l->next;
    }
    list* tail = (list*)malloc(sizeof(list));
    tail->value = value;
    tail->next = NULL;
    l->next = tail;
}

printList(list* l) {
    while (l) {
        printf("%d ->", l->value);
        l = l->next;
    }
    printf(" END\n");
}

removeValue(list* l, int begone) {
    /*
    remove a node with a value
    keep a trailing reference to tie the gap together

    at each node, if value != begone, update previous
    if it is begone, set previous' next to current's next
    and free the unlinked node

    what about the HEAD?
    */
    list* previous = (list*)malloc(sizeof(list));
    while (l->next) {
        if (l->value == begone) break;
        previous = l;
        l = l->next;
    }
    if (l->value == begone) {
        previous->next = l->next;
    } // otherwise we didn't find it!
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
    addTail(head, 21);
    printList(head);


    printf("Remove something!\n");
    removeValue(head, 0);
    printList(head);

    printf("length: %d\n", length(head));

    list* reversed = reverseList(head, NULL);
    printList(reversed);
}
