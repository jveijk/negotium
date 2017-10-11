#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"
#include "graph.h"
#include "doublyLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

static MunitResult
test_addGraph(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;
    Graph* graph = createGraph();
    munit_assert_ptr(graph, !=, NULL);

    disposeGraph(graph);
	return MUNIT_OK;
}

static MunitResult
test_createVertex(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;
    Graph* graph = createGraph();

    munit_assert_ptr(createVertex("karel"), !=, NULL);
    munit_assert_string_equal(createVertex("tester") -> name, "tester");

    disposeGraph(graph);
	return MUNIT_OK;
}


static MunitResult
test_findVertexByName(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;
    
    char* name = "Karel";
    char* name2 = "Joost";

    Graph* graph = createGraph();
    Vertex* v1 = createVertex(name);
    Vertex* v2 = createVertex(name2);
    Edge* e1 = createWeightedEdge(v1, 12);

    addVertex(graph, v1);
    addVertex(graph, v2);

    addDirectedEdge(v1, e1);

    Vertex *fv = getVertex(findFirstNode(graph->vertices, &findVertexByName, name));

    munit_assert_ptr(fv, ==, v1);

	return MUNIT_OK;
}

static MunitResult
test_findVertexByData(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

    char* name = "Karel";
    char* name2 = "Joost";
    int a = 4;

    Graph* graph = createGraph();
    Vertex* v1 = createVertex(name);
    Vertex* v2 = createVertex(name2);
    Edge* e1 = createWeightedEdge(v1, 12);

    v1->data = &a;

    addVertex(graph, v1);
    addVertex(graph, v2);

    addDirectedEdge(v1, e1);

    Vertex *fp = getVertex(findFirstNode(graph->vertices, &findDataPointer, &a));

    munit_assert_ptr(fp, ==, v1);

	return MUNIT_OK;
}

static MunitResult
test_edgeCreationDirected(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

    Graph* graph = createGraph();
    Vertex* v1 = createVertex("Karel");
    Vertex* v2 = createVertex("Joost");
    Edge* e1 = createWeightedEdge(v1, 12);

    addVertex(graph, v1);
    addVertex(graph, v2);

    addDirectedEdge(v1, e1);

    Vertex* vcompare = (Vertex*)(graph -> vertices -> head -> data);
    munit_assert(vcompare == v1);

    Edge* ecompare = (Edge*)(vcompare -> edges -> head -> data);
    munit_assert(ecompare == e1);

    double dcompare = 12;
    munit_assert((e1 -> weight) == dcompare);

    Vertex* vcompare2 = (Vertex*)(graph -> vertices -> head -> next -> data);
    munit_assert_null(vcompare2 -> edges -> head);
    //Directed because there is no pointer in the counter-specified direction

    disposeGraph(graph);
	return MUNIT_OK;
}

static MunitResult
test_edgeCreationUndirected(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

    Graph* graph = createGraph();
    Vertex* v1 = createVertex("Karel");
    Vertex* v2 = createVertex("Joost");
    Edge* e1 = createWeightedEdge(v1, 12);

    addVertex(graph, v1);
    addVertex(graph, v2);

    addUndirectedEdge(v2, e1);

    Vertex* vcompare = (Vertex*)(graph -> vertices -> head -> data);
    munit_assert(vcompare == v1);

    Edge* ecompare = (Edge*)(vcompare -> edges -> head -> data);
    munit_assert(ecompare != e1);

    double dcompare = 12;
    munit_assert((e1 -> weight) == dcompare);

    Vertex* vcompare2 = (Vertex*)(graph -> vertices -> head -> next -> data);
    munit_assert(vcompare2 == v2);

    Edge* ecompare2 = (Edge*)(vcompare2 -> edges -> head -> data);
    munit_assert((ecompare2) == e1);
    munit_assert((ecompare2 -> destination) == vcompare);
    //Undirected because there is no pointer in the counter-specified direction

    disposeGraph(graph);
	return MUNIT_OK;
}

static MunitResult
test_vertexPop(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

    Graph* graph = createGraph();
    Vertex* v1 = createVertex("Karel");
    Vertex* v2 = createVertex("Joost");
    Edge* e1 = createWeightedEdge(v1, 12);

    addVertex(graph, v1);
    addVertex(graph, v2);

    addUndirectedEdge(v2, e1);
    
    Vertex* vcompare = (Vertex*)(graph -> vertices -> head -> data);
    munit_assert(vcompare == v1);

    Edge* ecompare = (Edge*)(vcompare -> edges -> head -> data);
    munit_assert(ecompare != e1);

    double dcompare = 12;
    munit_assert((e1 -> weight) == dcompare);

    Vertex* vcompare2 = (Vertex*)(graph -> vertices -> head -> next -> data);
    munit_assert(vcompare2 == v2);

    Edge* ecompare2 = (Edge*)(vcompare2 -> edges -> head -> data);
    munit_assert((ecompare2) == e1);
    munit_assert((ecompare2 -> destination) == vcompare);

    popVertex(graph, v1);
    munit_assert((Vertex*)(graph -> vertices -> head -> data) != vcompare);

    disposeGraph(graph);
	return MUNIT_OK;
}

static MunitResult
test_edgePop(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

    Graph* graph = createGraph();
    Vertex* v1 = createVertex("Karel");
    Vertex* v2 = createVertex("Joost");
    Edge* e1 = createWeightedEdge(v1, 12);

    addVertex(graph, v1);
    addVertex(graph, v2);

    addUndirectedEdge(v2, e1);
    
    Vertex* vcompare = (Vertex*)(graph -> vertices -> head -> data);
    munit_assert(vcompare == v1);

    Edge* ecompare = (Edge*)(vcompare -> edges -> head -> data);
    munit_assert(ecompare != e1);

    double dcompare = 12;
    munit_assert((e1 -> weight) == dcompare);

    Vertex* vcompare2 = (Vertex*)(graph -> vertices -> head -> next -> data);
    munit_assert(vcompare2 == v2);

    Edge* ecompare2 = (Edge*)(vcompare2 -> edges -> head -> data);
    munit_assert((ecompare2) == e1);
    munit_assert((ecompare2 -> destination) == vcompare);

    popEdge(v1, e1);
    ecompare = (Edge*)(vcompare -> edges -> head -> data);

    munit_assert_false(ecompare == e1);

    disposeGraph(graph);
	return MUNIT_OK;
}

static MunitResult
test_freeAllEdges(const MunitParameter params[], void* user_data) {
	(void) params;
	(void) user_data;

    Graph* graph = createGraph();
    Vertex* v1 = createVertex("Karel");
    Vertex* v2 = createVertex("Joost");
    Vertex* v3 = createVertex("Joost");
    Edge* e1 = createWeightedEdge(v1, 12);
    Edge* e2 = createUnweightedEdge(v2);
    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);

    addDirectedEdge(v2, e1);
    addDirectedEdge(v1, e2);

    
    Vertex* vcompare = (Vertex*)(graph -> vertices -> head -> data);
    munit_assert(vcompare == v1);

    Edge* ecompare = (Edge*)(vcompare -> edges -> head -> data);
    munit_assert(ecompare != e1);

    double dcompare = 12;
    munit_assert((e1 -> weight) == dcompare);

    Vertex* vcompare2 = (Vertex*)(graph -> vertices -> head -> next -> data);
    munit_assert(vcompare2 == v2);

    Edge* ecompare2 = (Edge*)(vcompare2 -> edges -> head -> data);
    munit_assert((ecompare2) == e1);
    munit_assert((ecompare2 -> destination) == vcompare);

    freeEdge(v2, v1);
    ecompare = (Edge*)(vcompare -> edges -> head -> data);
    ecompare2 = (Edge*)(vcompare2 -> edges -> head -> data);

    munit_assert_true(ecompare != e1);
    munit_assert_true(ecompare2 != e2);

    disposeGraph(graph);
    
	return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    { (char*) "/Add test_addGraph", test_addGraph, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/Add test_createVertex", test_createVertex, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/Add test_findVertexByName", test_findVertexByName, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/Add test_findVertexByData", test_findVertexByData, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_edgeCreationDirected", test_edgeCreationDirected, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_edgeCreationUndirected", test_edgeCreationUndirected, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_edgePop", test_edgePop, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_freeAllEdges", test_freeAllEdges, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/add test_vertexPop", test_vertexPop, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

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