#ifndef doublyLinkedList_Chi_
#define doublyLinkedList_Chi_


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

void addAfter(DoublyLinkedList *dll, void *data);

void addBefore(DoublyLinkedList *dll, void *data);

void addBeforeNode(DoublyLinkedList *dll, DllNode *node, void *data);

void addAfterNode(DoublyLinkedList *dll, DllNode *node, void *data);

void forEachNode(void *dll, void (*predicate)(void *node, void *condition), void *condition);

void* findFirstNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition);

void* findLastNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition);

void* findFirstNodeAfterNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition, void *conditionNode);

void* findFirstNodeBeforeNode(void *dll, bool (*predicate)(void *node, void *condition), void *condition, void *conditionNode);

bool findInt(void *node, void *condition);

int nodeCount(DoublyLinkedList *dll);

void popNode(DoublyLinkedList *dll, DllNode *node);

void disposeList(DoublyLinkedList *dll);

DoublyLinkedList* createList();

#endif
