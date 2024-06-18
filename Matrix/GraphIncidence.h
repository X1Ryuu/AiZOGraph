#ifndef GRAPHINCIDENCE_H
#define GRAPHINCIDENCE_H

#include <vector>
class GraphIncidence {
public:
    GraphIncidence(int numVertices, int numEdges);
    int edges = 0;

    void addEdge(int vertex, int vertex2, int weight);
    int getEdgeWeight(int vertex, int edge) const;
    int getNumVertices() const;
    int getNumEdges() const;
    void addEdges(int vertex, int vertex2, int weight);
  //  int getEdgesWeight(int edge) const;

private:
    int numVertices;
    int numEdges;
    std::vector<std::vector<int>> incidenceMatrix;
  //  int edgesWeight[];
};
#endif // GRAPHINCIDENCE_H
