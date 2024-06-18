#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <vector>
#include <utility>

class GraphList {
public:
    GraphList(int vertices);
    void addEdge(int u, int v, int weight);
    void addEdges(int u, int v, int weight);
    bool hasEdge(int u, int v);
    int getNumVertices() const;
    int getNumEdges() const;
    const std::vector<std::pair<int, int>>& getEdges(int vertex) const;

private:
    int numVertices;
    int edges;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;
};

#endif // GRAPH_LIST_H
