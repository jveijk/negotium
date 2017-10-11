#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct DllNodeTag
{
    void *data;
    struct DllNodeTag *next;
    struct DllNodeTag *previous;
} DllNode;

typedef struct
{
    DllNode *head;
    DllNode *tail;
} DoublyLinkedList;

void printList(DoublyLinkedList *dll)
{
    DllNode *node = dll->head;
    while(node != NULL)
    {
        printf("%d\n", *(int*)node->data);
        node = node->next;
    }
}

void addAfter(DoublyLinkedList *dll, void *data)
{
    DllNode *newNode = malloc(sizeof(DllNode));
    if (newNode == NULL){
        printf("Memory limit exceeded");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;

    if(dll->head == NULL)
        dll->head = dll->tail = newNode;
    else
    {
        DllNode *tmp = dll->head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        newNode->previous = tmp;
        tmp->next = newNode;
        dll->tail = newNode;
    }
}

void addBefore(DoublyLinkedList *dll, void *data)
{
    DllNode *newNode = malloc(sizeof(DllNode));
    if (newNode == NULL){
        printf("Memory limit exceeded");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;


    if(dll->head == NULL)
        dll->head = dll->tail = newNode;
    else
    {
        newNode->next = dll->head;
        dll->head->previous = newNode;
        dll->head = newNode;
    }
}

void addBeforeNode(DoublyLinkedList *dll, DllNode *node, void *data)
{
    if(node==NULL)
        return;
    
    DllNode *newNode = malloc(sizeof(DllNode));
    if (newNode == NULL)
    {
        printf("Memory limit exceeded");
        exit(1);
    }
    newNode->data = data;
    newNode->next = node;
    newNode->previous = node->previous;

    if(node->previous != NULL)
        node->previous->next = newNode;
    else
        dll->head = newNode;
    node->previous = newNode;
}

void addAfterNode(DoublyLinkedList *dll, DllNode *node, void *data)
{
    if(node==NULL)
        return;

    DllNode *newNode = malloc(sizeof(DllNode));
    if (newNode == NULL){
        printf("Memory limit exceeded");
        exit(1);
    }
    newNode->data = data;
    newNode->next = node->next;
    newNode->previous = node;

    if(node->next != NULL)
        node->next->previous = newNode;
    else
        dll->tail = newNode;
    node->next = newNode;
}

void forEachNode(void *dll, void (*predicate)(void *node, void *condition), void *condition)
{
    DllNode *node = ((DoublyLinkedList*)dll)->head;
    while(node != NULL)
    {
        (*predicate)(node->data, condition);
        node = node->next;
    }
}

void* findFirstNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition)
{
    DllNode *node = ((DoublyLinkedList*)dll)->head;
    while(node != NULL)
    {
        if((*predicate)(node->data, condition))
            return node;
        node = node->next;
    }   
    return node;
}   

void* findLastNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition)
{
    DllNode *node = ((DoublyLinkedList*)dll)->tail;
    while(node != NULL)
    {
        if((*predicate)(node->data, condition))
            return node;
        node = node->previous;
    }   
    return node;
}   

void* findFirstNodeAfterNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition, void *conditionNode)
{
    DllNode *node = ((DllNode*)conditionNode)->next;
    while(node != NULL)
    {
        if((*predicate)(node->data, condition))
        return node;
        node = node->next;
    }   
    return node;    
}

void* findFirstNodeBeforeNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition, void *conditionNode)
{
    DllNode *node = ((DllNode*)conditionNode)->previous;
    while(node != NULL)
    {
        if((*predicate)(node->data, condition))
        return node;
        node = node->previous;
    }   
    return node;    
}

bool findInt(void *node, void *condition)
{
    return (*(int*)node == *(int*)condition);
}

int nodeCount(DoublyLinkedList *dll)
{
    int count = 0;
    DllNode *node = dll->head;
    while(node!=NULL)
    {
        node = node->next;
        count++;
    }
    return count;
}

void popNode(DoublyLinkedList *dll, DllNode *node)
{
    if(dll == NULL || node==NULL)
        return;

    if(node->previous != NULL)
        node->previous->next = node->next;
    else
        dll->head = node->next;

    if(node->next != NULL)
        node->next->previous = node->previous;
    else
        dll->tail = node->previous;

    if(node->next==NULL && node->previous==NULL)
        dll->head = dll->tail = NULL;
    free(node);
}

void disposeList(DoublyLinkedList *dll)
{
    if(dll!=NULL)
    {
        DllNode *node = dll->head;
        while(node != NULL)
        {
            DllNode *tmp = node;
            node = node->next;
            free(tmp);
        }
        free(dll);
    }
}

DoublyLinkedList* createList()
{
    DoublyLinkedList *dll = malloc(sizeof(DoublyLinkedList));
    if(dll==NULL)
        exit(1);
    dll->head = NULL;
    dll->tail = NULL;
    return dll;
}