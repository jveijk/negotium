#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "doublyLinkedList.h"

int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    int t = 99;

    DoublyLinkedList *dll = createList();
    addAfter(dll, &a);
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &a);
    
    DllNode *node = findLastNode(dll, findInt, &b);
    addBeforeNode(dll, node, &t);

    disposeList(dll);
    
    return 0;
}