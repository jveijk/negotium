#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

int main()
{
    //Create vertices
    Vertex *v1 = createVertex("Henk");
    Vertex *v2 = createVertex("Jan");
    Vertex *v3 = createVertex("Nick");

    //Assign data to v1
    int a = 3;
    v1->data = &a;
    
    //Create graph
    Graph *graph = createGraph();

    //Add vertices to graph
    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);

    //Find for vertex
    // Vertex *fv = getVertex(findFirstNode(graph->vertices, &findVertexByName, "Henk"));
    
    //Find pointer
    Vertex *fp = getVertex(findFirstNode(graph->vertices, &findDataPointer, &a));
    printf("Data of found pointer: %d", *(int*)fp->data);

    //Create edge and append edge to vertex
    addUndirectedEdge(v2, createWeightedEdge(v1, 2.34));
    addDirectedEdge(v2, createWeightedEdge(v3, 1.11));
    addUndirectedEdge(v3, createUnweightedEdge(v2));
    addDirectedEdge(v3, createWeightedEdge(v3, 5.67));

    //Print names of graph vertices
    printGraph(graph);
    
    //Pop vertex
    popVertex(graph, v3);
    printGraph(graph);
    
    //Pop edge
    popEdge(v2, v1);
    printGraph(graph);

    //Dispose graph
    disposeGraph(graph);
    
    return 0;
}