#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

LinkedList *LinkedListNew() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = NULL;
    return list;
}

void LinkedListAddElement(LinkedList *list, void *elt) {
    LinkedElement *currentElement = list->head;
    while (currentElement != NULL && currentElement->next != NULL) {
        currentElement = currentElement->next;
    }
    LinkedElement *newElement = malloc(sizeof(LinkedElement));
    newElement->elt = elt;
    newElement->next = NULL;
    if (list->head == NULL) {
        list->head = newElement;
    } else {
        currentElement->next = newElement;
    }
    list->size++;
}

void *LinkedListGetFirstElement(LinkedList *list) {
    if (list->head != NULL) {
        return list->head->elt;
    }
    return NULL;
}

void LinkedListCreateFromTwoLast(LinkedList *list, ApplyFunction func) {
    LinkedElement *currentElement = list->head;
    LinkedElement *previousElement = NULL;
    while (currentElement != NULL && currentElement->next != NULL) {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    if (currentElement != NULL && previousElement != NULL) {
        LinkedElement *newElement = malloc(sizeof(LinkedElement));
        newElement->elt = func(currentElement, previousElement);
        newElement->next = NULL;
        currentElement->next = newElement;
        list->size++;
    }
}

int LinkedListFoundAndFree(LinkedList *list, void *elt, EqualsFunction func) {
    if (list != NULL) {
        LinkedElement *currentElement = list->head;
        LinkedElement *previousElement = NULL;
        while(currentElement != NULL) {
            if (func(elt, currentElement->elt)) {
                if (previousElement == NULL) {
                    list->head = currentElement->next;
                } else {
                    previousElement->next = currentElement->next;
                }
                free(currentElement->elt);
                free(currentElement);
                list->size--;
                printf("REMOVED !!!\n");
                return (1);
            }
            previousElement = currentElement;
            currentElement = currentElement->next;
        }
    }
    return(0);
}

int LinkedListHeadEqualsOthers(LinkedList *list, EqualsFunction func) {
     LinkedElement *head = list->head;
     if (head != NULL) {
        LinkedElement *currentElement = head->next;
        while(currentElement != NULL) {
            if (func(head->elt, currentElement->elt)) {
                return (1);
            }
            currentElement = currentElement->next;
        }
     }
     return (0);
}

void LinkedListApply(LinkedList *list, ApplyFunction func) {
    LinkedElement *currentElement = list->head;
    LinkedElement *previousElement = NULL;
    while (currentElement != NULL) {
        currentElement->elt = func(currentElement->elt, previousElement);
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
}

void LinkedListApplyAndFill(LinkedList *list, void **array, ApplyAnFillFunction func) {
    LinkedElement *currentElement = list->head;
    int i = 0;
    while (currentElement != NULL) {
        func(currentElement->elt, array);
        currentElement = currentElement->next;
        i++;
    }
}

void LinkedListPrint(LinkedList *list, DisplayFunction display) {
    LinkedElement *currentElement = list->head;
    while(currentElement != NULL) {
        display(currentElement->elt);
        currentElement = currentElement->next;
    }
}

void recurseDestroy(LinkedElement *elt) {
    if (elt != NULL) {
        recurseDestroy(elt->next);
        free(elt);
    }
}

void LinkedListDestroy(LinkedList *list) {
    recurseDestroy(list->head);
    free(list);
}