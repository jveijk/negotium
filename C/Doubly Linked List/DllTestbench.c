#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"
#include "doublyLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

static MunitResult
test_addNode(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

    DoublyLinkedList *dll = createList();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

	munit_assert_int(*((int*)(dll -> head -> data)), ==, 2);
	munit_assert_int(*((int*)(dll -> head -> next -> data)), ==, 1);
	munit_assert_int(*((int*)(dll -> head -> next -> next -> data)), ==, 2);
    munit_assert_int(*((int*)(dll -> head -> next -> next-> next -> data)), ==, 3);
    munit_assert_int(*((int*)(dll -> head -> next -> next-> next -> next ->data)), ==, 2);

    addBefore(dll, &c);   
    addBefore(dll, &a);    
    addBefore(dll, &b);
    addBefore(dll, &c);
    addBefore(dll, &a);

    munit_assert_int(*((int*)(dll -> head -> data)), ==, 1);
	munit_assert_int(*((int*)(dll -> head -> next -> data)), ==, 3);
	munit_assert_int(*((int*)(dll -> head -> next -> next -> data)), ==, 2);
    munit_assert_int(*((int*)(dll -> head -> next -> next-> next -> data)), ==, 1);
    munit_assert_int(*((int*)(dll -> head -> next -> next-> next -> next ->data)), ==, 3);

    addBeforeNode(dll, dll -> head -> next -> next, &d);
    munit_assert(dll -> head -> next -> next -> data == &d);

    addAfterNode(dll, dll -> head -> next -> next -> next, &d);
    munit_assert(dll -> head -> next -> next -> next -> next -> data == &d);

    disposeList(dll);
	return MUNIT_OK;
}

static MunitResult
test_popNode(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(nodeCount(dll) == 5);

    popNode(dll, dll -> head -> next);

    munit_assert(nodeCount(dll) ==  4);

    popNode(dll, dll -> head -> next);
    popNode(dll, dll -> head -> next); 
    popNode(dll, dll -> head);

    munit_assert((dll -> head -> next) == (dll -> tail -> next));

    popNode(dll, dll -> head ->next);

    munit_assert_null(dll -> tail-> next);
    munit_assert_null(dll -> head -> next);

    popNode(dll, dll -> head -> next);// test for pop without Node
    
    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_findNode(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    addAfter(dll, &a);   
    addAfter(dll, &b);    
    addAfter(dll, &c);
    addAfter(dll, &d);
    addAfter(dll, &e);
    addAfter(dll, &d);
    addAfter(dll, &c);
    addAfter(dll, &b);  
    addAfter(dll, &a);
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &c);   
    addAfter(dll, &b);    
    addAfter(dll, &a);
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &d);
    addAfter(dll, &e);
    addAfter(dll, &d);  
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &a);

    munit_assert(findFirstNode(dll, findInt, &e) == dll -> head -> next -> next -> next -> next);
    munit_assert_ptr(findLastNode(dll, findInt, &b), ==, (dll -> tail -> previous));
    munit_assert_ptr(findFirstNodeAfterNode(dll, findInt, &a, dll -> tail -> previous -> previous -> previous -> previous -> previous), ==, (dll -> tail));
    munit_assert_ptr(findFirstNodeBeforeNode(dll, findInt, &b, dll -> tail -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous -> previous), ==, (dll -> head -> next));

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_nodeCount(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &b);
    addAfter(dll, &a);
    addAfter(dll, &a);  
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(nodeCount(dll) == 11);

    popNode(dll, dll -> head -> next);
    popNode(dll, dll -> head -> next);
    
    munit_assert(nodeCount(dll) ==  9);

    popNode(dll, dll -> head -> next);
    popNode(dll, dll -> head -> next);
    popNode(dll, dll -> head -> next);
    popNode(dll, dll -> head -> next);

    munit_assert(nodeCount(dll) == 5);

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_shortType(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    short a = 1;
    short b = 2;
    short c = 3;
    short d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &b);
    addAfter(dll, &a);
    addAfter(dll, &a);  
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(dll -> head -> data == dll -> head -> next -> next -> data);
    munit_assert(&b == dll -> head -> data);

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_intType(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &b);
    addAfter(dll, &a);
    addAfter(dll, &a);  
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(dll -> head -> data == dll -> head -> next -> next -> data);
    munit_assert(&b == dll -> head -> data);

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_floatType(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    float a = 1;
    float b = 2;
    float c = 3;
    float d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &b);
    addAfter(dll, &a);
    addAfter(dll, &a);  
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(dll -> head -> data == dll -> head -> next -> next -> data);
    munit_assert(&b == dll -> head -> data);

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_doubleType(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    double a = 1;
    double b = 2;
    double c = 3;
    double d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &b);
    addAfter(dll, &a);
    addAfter(dll, &a);  
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(dll -> head -> data == dll -> head -> next -> next -> data);
    munit_assert(&b == dll -> head -> data);

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_charType(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    char a = 1;
    char b = 2;
    char c = 3;
    char d = 4;

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &b);
    addAfter(dll, &a);
    addAfter(dll, &a);  
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(dll -> head -> data == dll -> head -> next -> next -> data);
    munit_assert(&b == dll -> head -> data);

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_stringType(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *dll = createList();

    char a[] = "Hoi";
    char b[] = "Doei";
    char c[] = "Hi";
    char d[] = "Bye";

    addAfter(dll, &b);   
    addAfter(dll, &a);    
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);
    addAfter(dll, &b);
    addAfter(dll, &a);
    addAfter(dll, &a);  
    addAfter(dll, &b);
    addAfter(dll, &c);
    addAfter(dll, &b);

    munit_assert(dll -> head -> data == dll -> head -> next -> next -> data);
    munit_assert(&b == dll -> head -> data);

    disposeList(dll);
    return MUNIT_OK;
}

static MunitResult
test_multipleDll(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    
    DoublyLinkedList *chardll = createList();

    DoublyLinkedList *intdll = createList();


    int a = 1;
    char c = 'c';

    addAfter(intdll, &a);   
    addAfter(chardll, &c);


    munit_assert(intdll -> head -> data == &a); 
    munit_assert(chardll -> head -> data == &c);

    disposeList(chardll);
    disposeList(intdll);
    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    { (char*) "/Add test_addNode", test_addNode, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/Add test_popNode", test_popNode, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/Add test_findNode", test_findNode, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_charType", test_charType, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_shortType", test_shortType, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_floatType", test_floatType, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_doubleType", test_doubleType, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_intType", test_intType, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_stringType", test_stringType, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_nodeCount", test_nodeCount, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_multipleDll", test_multipleDll, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
	(char*) "test",
	test_suite_tests,
	NULL,
	1,
	MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
	return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}