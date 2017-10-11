#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "doublyLinkedList.h"

//Graph contains: vertices
typedef struct
{
    DoublyLinkedList *vertices;
} Graph;

//Vertex contains: name of vertex, generic data pointer, a set of edges
typedef struct 
{
    char *name;
    void *data;
    DoublyLinkedList *edges;
} Vertex;

//Edge contains: weight of the edge, vertex it's connected to
typedef struct
{
    double weight;
    Vertex *destination;
} Edge;

Vertex* createVertex(char *name)
{
    Vertex *vertex = malloc(sizeof(Vertex));
    if(vertex==NULL)
        exit(1);
    vertex->name = name;
    vertex->edges = createList();
    return vertex;
}

Graph* createGraph()
{
    Graph *graph = malloc(sizeof(Graph));
    if(graph==NULL)
        exit(1);
    graph->vertices = createList();
    return graph;
}

Edge* createWeightedEdge(Vertex *vertex, double weight)
{
    Edge *edge = malloc(sizeof(Edge));
    if(edge==NULL)
        exit(1);
    edge->destination = vertex;
    edge->weight = weight;
    return edge;
}

Edge* createUnweightedEdge(Vertex *vertex)
{
    Edge *edge = malloc(sizeof(Edge));
    if(edge==NULL)
        exit(1);
    edge->destination = vertex;
    edge->weight = 0;
    return edge;
}

void addVertex(Graph *graph, Vertex *vertex)
{
    addAfter(graph->vertices, vertex);
}

bool findVertexByName(void *node, void *condition)
{
    return (((Vertex*)node)->name == (char*)condition);
}

bool findDataPointer(void *node, void *condition)
{
    return (((Vertex*)node)->data == condition);
}

bool findEdge(void *node, void *condition)
{
    return (((Edge*)node)->destination == (Vertex*)condition);
}

void addDirectedEdge(Vertex *vertex, Edge *edge)
{
    if(findFirstNode(vertex->edges, &findEdge, edge->destination)==NULL)
        addAfter(vertex->edges, edge);
}

void addUndirectedEdge(Vertex *vertex, Edge *edge)
{
    if(findFirstNode(vertex->edges, &findEdge, edge->destination)==NULL)
        addAfter(vertex->edges, edge);
    if(findFirstNode(edge->destination->edges, &findEdge, vertex)==NULL)
        addAfter(edge->destination->edges, createWeightedEdge(vertex, edge->weight));   
}

void freeEdge(void *edge, void *condition)
{
    free((Edge*)edge);
}

void popEdge(void *vertex, void *destination)
{
    Vertex *v = (Vertex*)vertex;
    DllNode *n = findFirstNode(v->edges, &findEdge, destination);
    if(n != NULL)
    {
        free((Edge*)n->data);
        popNode(v->edges, n);
    }
}

void popVertex(Graph *graph, Vertex *vertex)
{
    if(vertex == NULL)
        return;
    forEachNode(graph->vertices, &popEdge, vertex);
    forEachNode(vertex->edges, &freeEdge, NULL);
    disposeList(vertex->edges);
    popNode(graph->vertices, findFirstNode(graph->vertices, &findVertexByName, vertex->name));
    free(vertex);
}

void disposeGraph(Graph *graph)
{
    DllNode *graphNode = graph->vertices->head;
    while(graphNode != NULL)
    {
        forEachNode(((Vertex*)graphNode->data)->edges, &freeEdge, NULL);   
        disposeList(((Vertex*)graphNode->data)->edges);
        free((Vertex*)graphNode->data);
        graphNode = graphNode -> next;
    }
    disposeList(graph->vertices);
    free(graph);
}

void printEdge(void *edge, void *condition)
{
    printf(" -> (%f)%s",((Edge*)edge)->weight, ((Edge*)edge)->destination->name);
}

void printGraph(Graph *graph)
{
    DllNode *graphNode = graph->vertices->head;
    while(graphNode != NULL)
    {
        printf("\n%s", ((Vertex*)graphNode->data)->name);        
        forEachNode(((Vertex*)graphNode->data)->edges, &printEdge, NULL);   
        graphNode = graphNode -> next;
        graphNode!=NULL ? printf("\n|") : printf("\n");     
    }
}

Vertex* getVertex(DllNode *node)
{
    return (Vertex*)((DllNode*)node->data);
}
