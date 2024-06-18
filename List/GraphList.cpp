#include "GraphList.h"

GraphList::GraphList(int vertices) : numVertices(vertices), edges(0) {
    adjacencyList.resize(numVertices);
}

void GraphList::addEdges(int u, int v, int weight) {
    if (!hasEdge(u, v)) {
        edges++;
    }
    adjacencyList[u].emplace_back(v, weight);
    adjacencyList[v].emplace_back(u, weight); // for undirected graph
}

void GraphList::addEdge(int u, int v, int weight) {
    if (!hasEdge(u, v)) {
        edges++;
    }
    adjacencyList[u].emplace_back(v, weight);
}

bool GraphList::hasEdge(int u, int v) {
    for (const auto& neighbor : adjacencyList[u]) {
        if (neighbor.first == v) {
            return true;
        }
    }
    return false;
}

int GraphList::getNumVertices() const {
    return numVertices;
}

int GraphList::getNumEdges() const {
    return edges;
}

const std::vector<std::pair<int, int>>& GraphList::getEdges(int vertex) const {
    return adjacencyList[vertex];
}
