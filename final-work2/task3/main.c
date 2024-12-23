#define _CRT_SECURE_NO_WARNINGS

#include "graphsTests.h"
#include "graph.h"
#include "stacksTests.h"

#include <stdbool.h>
#include <stdio.h>

bool areArraysEqual(bool array1[], bool array2[], int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

Graph* buildGraphUsingMatrix(const char* fileName, bool* errorCode) {
    FILE* file = fopen(fileName, "r");

    int graphSize = -1;
    fscanf(file, "%d\t", &graphSize);
    Graph* graph = createGraph(graphSize, errorCode);
    if (*errorCode) {
        fclose(file);
        return;
    }

    for (int key = 0; key < graphSize; ++key) {
        VertexValue value = { .key = key };
        addVertex(graph, value, errorCode);
        if (*errorCode) {
            fclose(file);
            deleteGraph(&graph, errorCode);
            return;
        }
    }

    int line = 0;
    int column = 0;
    int isEdge = false;
    while (fscanf(file, "%d\t", &isEdge) == 1) {
        if (isEdge) {
            graph = connectVertices(graph, column, line, errorCode);
            if (*errorCode) {
                fclose(file);
                deleteGraph(&graph, errorCode);
                return;
            }
        }
        column = (column + 1) % graphSize;
        if (column == 0) {
            ++line;
        }
    }
    fclose(file);
    return graph;
}

bool testTask3(void) {
    bool errorCode = false;
    bool resultTest1[6] = {false};
    resultTest1[0] = true;
    Graph* graph1 = buildGraphUsingMatrix("matrix.txt", &errorCode);
    if (errorCode) {
        deleteGraph(&graph1, errorCode);
        return false;
    }
    bool test1 = areArraysEqual(findGoodVertex(graph1, &errorCode), resultTest1, 6);
    if (errorCode) {
        deleteGraph(&graph1, errorCode);
        return false;
    }
    deleteGraph(&graph1, errorCode);

    bool resultTest2[1] = { true };
    Graph* graph2 = buildGraphUsingMatrix("test2.txt", &errorCode);
    if (errorCode) {
        deleteGraph(&graph2, errorCode);
        return false;
    }
    bool test2 = areArraysEqual(findGoodVertex(graph2, &errorCode), resultTest2, 1);
    if (errorCode) {
        deleteGraph(&graph2, errorCode);
        return false;
    }
    deleteGraph(&graph2, errorCode);

    return test1 && test2;
}

int main(void) {
    bool errorCode = false;
    runStackTest(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    testGraph(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    errorCode = !testTask3();
    return errorCode;
}