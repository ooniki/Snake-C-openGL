#ifndef _LinkedList_
#define _LinkedList_

typedef int (EqualsFunction)(void *data1, void *data2);
typedef void *(ApplyFunction)(void *data, void *previousData);
typedef void (ApplyAnFillFunction)(void *data, void **array);
typedef void (DisplayFunction)(void *data);

typedef struct sLinkedElement {
    void *elt;
    struct sLinkedElement *next;
} LinkedElement;

typedef struct sLinkedList {
    LinkedElement *head;
    int size;
} LinkedList;


LinkedList *LinkedListNew();

void LinkedListAddElement(LinkedList *list, void *elt);

void *LinkedListGetFirstElement(LinkedList *list);

void LinkedListCreateFromTwoLast(LinkedList *list, ApplyFunction func);

void LinkedListDestroy(LinkedList *list);

int LinkedListFoundAndFree(LinkedList *list, void *elt, EqualsFunction func);

int LinkedListHeadEqualsOthers(LinkedList *list, EqualsFunction func);

void LinkedListApply(LinkedList *list, ApplyFunction func);

void LinkedListApplyAndFill(LinkedList *list, void **array, ApplyAnFillFunction func);

void LinkedListPrint(LinkedList *list, DisplayFunction display);

#endif