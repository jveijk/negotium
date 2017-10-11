#include "doublyLinkedList.h"
#ifndef graph_Chi_
#define graph_Chi_


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

Vertex* createVertex(char *name);

Graph* createGraph();

Edge* createWeightedEdge(Vertex *vertex, double weight);

Edge* createUnweightedEdge(Vertex *vertex);

void addVertex(Graph *graph, Vertex *vertex);

bool findVertexByName(void *node, void *condition);

bool findDataPointer(void *node, void *condition);

bool findEdge(void *node, void *condition);

void addDirectedEdge(Vertex *vertex, Edge *edge);

void addUndirectedEdge(Vertex *vertex, Edge *edge);

void popEdge(void *vertex, void *destination);

void freeEdge(void *edge, void *condition);

void popVertex(Graph *graph, Vertex *vertex);

void disposeGraph(Graph *graph);

void printEdge(void *edge, void *condition);

void printGraph(Graph *graph);

Vertex* getVertex(DllNode *node);

#endif