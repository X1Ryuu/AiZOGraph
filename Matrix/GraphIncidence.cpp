//
// Created by Bart on 17.06.2024.
//

#include "GraphIncidence.h"


GraphIncidence::GraphIncidence(int vertices, int edges)
        : numVertices(vertices), numEdges(edges), incidenceMatrix(vertices, std::vector<int>(edges, 0)) {
  //  int edgesWeight[edges];
}

void GraphIncidence::addEdge(int vertex, int vertex2, int weight) {
    incidenceMatrix[vertex][edges] = weight;
    incidenceMatrix[vertex2][edges] = -1;
 //   edgesWeight[edges] = weight;
    edges++;
}

void GraphIncidence::addEdges(int vertex, int vertex2, int weight) {
    incidenceMatrix[vertex][edges] = weight;
    incidenceMatrix[vertex2][edges] = weight;
    //   edgesWeight[edges] = weight;
    edges++;
}

/*int GraphIncidence::getEdgesWeight(int edge) const {
    return edgesWeight[edge];
}*/

int GraphIncidence::getEdgeWeight(int vertex, int edge) const {
    return incidenceMatrix[vertex][edge];
}



int GraphIncidence::getNumVertices() const {
    return numVertices;
}

int GraphIncidence::getNumEdges() const {
    return numEdges;
}