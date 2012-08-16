#include <stdlib.h>
#include <stdio.h>

struct list {
    int value;
    struct list *next;
};
typedef struct list list;


//problem 14
list* sortedMerge(list* a, list* b) {
    /*
    each new tail is the smaller of a's or b's head
    assume a and b are already sorted
    */
    list* head;
    list** tailRef = &head;

    while (1) {
        if (a == NULL) {
            *tailRef = b;
            break;
        } else if (b == NULL) {
            *tailRef = a;
            break;
        } else {
            if (a->value > b->value) {
                moveHead(tailRef, &b);
            } else {
                moveHead(tailRef, &a);
            }
            tailRef = &((*tailRef)->next);
        }
    }

    return head;
}

//problem 15: mergesort
/*
if we have two one-item lists, sorting is easy with sortedMerge
bahhhhhhhhh i haven't been doing any recursive solutions :'[

*/
mergeSort(list** headRef) {
    list* head = *headRef;
    // just spit back 0- and 1-item lists
    if (head == NULL || head->next == NULL) return;
    list* front = NULL;
    list* back = NULL;
    frontBackSplit(head, &front, &back);

    mergeSort(&front);
    mergeSort(&back);

    *headRef = sortedMerge(front, back);
}

//problem 13
list* shuffleMerge(list* a, list* b) {
    /*
    each new tail link is a's or b's head
    */

    //easy cases :)
    if (a == NULL) return b;
    if (b == NULL) return a;

    list* result = NULL;
    list** tailPtrRef = &result;

    //while we haven't broken out
    while (1) {
        if (a == NULL) {
            *tailPtrRef = b;
            break;
        } else if (b == NULL) {
            *tailPtrRef = a;
            break;
        } else {
            moveHead(tailPtrRef, &a);
            tailPtrRef = &((*tailPtrRef)->next);
            moveHead(tailPtrRef, &b);
            tailPtrRef = &((*tailPtrRef)->next);
        }
    }
    return result;
}

alternatingSplit(list* l, list** aRef, list** bRef) {
    int counter = 0;
    while (l) {
        list* newnode = malloc(sizeof(list));
        newnode->value = l->value;
        if (counter % 2) {
            newnode->next = *aRef;
            *aRef = newnode;
        } else {
            newnode->next = *bRef;
            *bRef = newnode;
        }
        l = l->next;
        counter++;
    }
}
            
moveHead(list** aRef, list** bRef) {
    //bail if b is NULL
    if (*bRef) {
        //stash b's original head node
        list* movehead = *bRef;
        //set b to its next element
        *bRef = movehead->next;
        //prepare the node to become a's head
        movehead->next = *aRef;
        //point aHead at oldhead
        *aRef = movehead;
    }
}

removeDuplicates(list* l) {
    list* prev = NULL;
    while(l && l->next) {
        if (l->next->value == l->value) {
            //remove l->next
            l->next = l->next->next;
        } else {
            l = l->next;
        }
    }
}
 frontBackSplit(list* head, list** front, list** back) {
    //take in a list and spit out an additional one,...
    //split input in half, round into the input list
    // have two pointers, one advances two-at-a-time, t'other: one
    list* slow = head;
    list* fast = head;
    if (fast == NULL || fast->next == NULL) {
        return;
    }
    int counter = 0;
    while(fast->next && fast->next->next) {
        counter++;
        fast = fast->next->next;
        slow = slow->next;
    }

    *back = slow->next;
    //close the front
    slow->next = NULL;
    *front = head;
}
append(list** aRef, list** bRef) {
    if (*aRef == NULL) {
        printf("your a is empty...\n");
        *aRef = *bRef;
        *bRef = NULL;
    } else {
    
        list* aHead = *aRef;
        
        while(aHead->next) {
            aHead = aHead->next;
        }
        aHead->next = *bRef;
        *bRef = NULL;
    }
}

int pop(list** head) {
    list* old = *head;
    int ret = old->value;
    *head = old->next;
    free(old);
    return ret;
}

void push(list** head, int value) {
    list* newnode = malloc(sizeof(list));
    newnode->value = value;
    newnode->next = *head;
    *head = newnode;
}

sortedInsert(list** headRef, list* newNode) {
    //special case for end and begining
    if (*headRef == NULL || (*headRef)->value >= newNode->value) {
        newNode->next = *headRef;
        *headRef = newNode;
    } else {
        //deref and find the place to insert
        list* l = *headRef;
        while (l->next && l->next->value < newNode->value) {
            l = l->next;
        }
        //found it!
        newNode->next = l->next;
        l->next = newNode;
    }
}

insertionSort(list** headRef) {
    /*
    loop through *head and re-insert nodes :)
    at each node, we remove it and re-insert it
    don't bother if we're already where we belong
    */
    list* sorted = NULL;
    list* head = *headRef;
    list* next;
    while (head) {
        next = head->next;
        sortedInsert(&sorted, head);
        head = next;
    }
    *headRef = sorted;
}

insertAt(list** headRef, int index, int value) {
    /*
    insert value into *head at index
    we will need to count up to index, then do some dancing:
    - stash previous
    - set a new node's next to previous-next
    - set previous->next to the new node
    */
    if (index == 0) {
        push(headRef, value);
    } else {
        list* previous;
        int counter = 0;
        list* head = *headRef;

        while(head && counter < index) {
            counter ++;
            head = head->next;
        }
        if (head) push(&(head->next), value);
    }
}

list* reverseList(list* head, list* previous) {
    list* tail;
    //hit the end!
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
        free(l);
    } // otherwise we didn't find it!
}

int count(list* l, int find) {
    int found = 0;
    while(l) {
        if (l->value == find)
            found++;
        l = l->next;
    }
    return found;
}

int nth(list* l, int index) {
    int counter = 0;
    while (l) {
        if (counter == index) return l->value;
        l = l->next;
        counter++;
    }
    return -1;
}

deleteList(list** head) {
    list* current = *head;
    list* next;
    while(current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

//problem 16
list* sortedIntersect(list* a, list* b) {
    if (a == NULL || b == NULL) return NULL;
    list dummy;
    list* tail = &dummy;
    dummy.next = NULL;

    while (1) {
        //if one is done, there's no more intersect
        if (a == NULL || b == NULL) {
            printf("a or b is done, so we're done\n");
            tail->next = NULL;
            break;
        } else {
        //check head of a and b, if they are the same, push and advance both
        // otherwise, advance the smaller one
            if (a->value > b->value) {
                printf("a's %d is greater than b's %d\n", a->value, b->value);
                b = b->next;
            } else if (a->value < b->value) {
                printf("a's %d is less than b's %d\n", a->value, b->value);
                a = a->next;
            } else {
                printf("a's %d is equal to b's %d\n", a->value, b->value);
                push(&(tail->next), a->value);
                tail = tail->next;
                a = a->next;
                b = b->next;
            }
        }
    }
    return dummy.next;
}

int main() {
/*
    printf("Make a list\n");
    list* head = (list*)malloc(sizeof(list));

    printf("Assign a value\n");
    head->value = 0;
    head->next = NULL;
    printList(head);

    printf("push...\n");
    addTail(head, 1);
    addTail(head, 2);
    addTail(head, 3);
    addTail(head, 100);
    printList(head);

    printf("insertAt...\n");
    insertAt(&head, 0, 10);
    insertAt(&head, 1, 100);
    insertAt(&head, 1, 21);
    printList(head);

    printf("insertion sort...\n");
    insertionSort(&head);
    printList(head);


    printf("pop offa head: %d\n", pop(&head));
    printf("pop offa head: %d\n", pop(&head));

    list* reversed = reverseList(head, NULL);
    printList(reversed);

    deleteList(&head);
    deleteList(&reversed);

    //list* a = NULL;
    list* a = malloc(sizeof(list));
    a->value = 1;
    addTail(a, 2);
    addTail(a, 3);

    list* b = malloc(sizeof(list));
    b->value = 4;
    addTail(b, 7);

    printf("list a:\n");
    printList(a);
    printf("list b:\n");
    printList(b);

    //problem 8
    append(&a, &b);
    printf("After append, a is:\n");
    printList(a);
    printf("and b is:\n");
    printList(b);

    //problem 11
    list* a = NULL;
    push(&a, 1);
    push(&a, 2);
    push(&a, 3);

    list* b = NULL;
    push(&b, 1);
    push(&b, 2);
    push(&b, 3);

    moveHead(&a, &b);
    printList(a);
    printList(b);

    //problem 12
    list* source = NULL;
    push(&source, 6);
    push(&source, 5);
    push(&source, 4);
    push(&source, 3);
    push(&source, 2);
    push(&source, 1);
    list* evens = NULL;
    list* odds = NULL;
    alternatingSplit(source, &evens, &odds);
    printf("original: ");
    printList(source);
    printf("evens: ");
    printList(evens);
    printf("odds: ");
    printList(odds);

    //problem 9
    printf("let's try the front/back split\n");
    list* firsthalf = NULL;
    list* lasthalf = NULL;
    frontBackSplit(merged, &firsthalf, &lasthalf);
    printf("front: ");
    printList(firsthalf);
    printf("back: ");
    printList(lasthalf);

    //problem13
    list* a = NULL;
    push(&a, 3);
    push(&a, 2);
    push(&a, 1);
    list* b = NULL;
    push(&b, 6);
    push(&b, 5);
    push(&b, 4);

    printList(a);
    printList(b);
    list* shuffled = shuffleMerge(a, b);
    printList(shuffled);
*/

    //problem 14
    list* one = NULL;
    push(&one, 100);
    push(&one, 100);
    push(&one, 9);
    push(&one, 6);
    push(&one, 3);

    list* two = NULL;
    push(&two, 101);
    push(&two, 100);
    push(&two, 6);
    push(&two, 5);
    push(&two, 3);
    push(&two, 2);
    push(&two, 1);

    printList(one);
    printList(two);
    list* intersect = sortedIntersect(one, two);
    printList(intersect);



    return 0;
}
