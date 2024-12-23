#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

void testCreateAndDelete(bool* errorCode) {
    VertexValue value1 = { .key = 0};
    VertexValue value2 = { .key = 1};

    Graph* testGraph = createGraph(5, errorCode);
    addVertex(testGraph, value1, errorCode);
    addVertex(testGraph, value2, errorCode);
    deleteGraph(&testGraph, errorCode);
}

void testConnectVertices(bool* errorCode) {
    VertexValue value1 = { .key = 0};
    VertexValue value2 = { .key = 1};
    VertexValue value3 = { .key = 5};

    Graph* testGraph1 = createGraph(2, errorCode);
    addVertex(testGraph1, value1, errorCode);
    addVertex(testGraph1, value2, errorCode);
    addVertex(testGraph1, value3, errorCode);

    testGraph1 = connectVertices(testGraph1, 0, 5, errorCode);
    testGraph1 = connectVertices(testGraph1, 0, 1, errorCode);

    deleteGraph(&testGraph1, errorCode);
    if (*errorCode) {
        return;
    }
    VertexValue value4 = { .key = 5};
    VertexValue value5 = { .key = 1};
    VertexValue value6 = { .key = 0};

    Graph* testGraph2 = createGraph(3, errorCode);
    addVertex(testGraph2, value4, errorCode);
    addVertex(testGraph2, value4, errorCode);
    addVertex(testGraph2, value5, errorCode);
    addVertex(testGraph2, value6, errorCode);

    testGraph2 = connectVertices(testGraph2, 0, 1, errorCode);
    testGraph2 = connectVertices(testGraph2, 0, 5, errorCode);
    deleteGraph(&testGraph2, errorCode);
}

void testGraph(bool* errorCode) {
    testCreateAndDelete(errorCode);
    testConnectVertices(errorCode);
}