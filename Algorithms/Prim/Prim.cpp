#include <climits>
#include <vector>
#include <queue>
#include <cstdio>
#include <iostream>
#include "Prim.h"

using namespace std;

void primMST(GraphList& graph) {
    int V = graph.getNumVertices();
    std::vector<int> key(V, INT_MAX); // Key values used to pick minimum weight edge in cut
    std::vector<int> parent(V, -1); // Array to store constructed MST
    std::vector<bool> inMST(V, false); // To represent set of vertices not yet included in MST

    // Priority queue to store vertices that are being preprocessed.
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int src = 0; // Starting from the first vertex
    key[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true; // Include u in MST

        // Traverse all adjacent vertices of u
        for (auto& edge : graph.getEdges(u)) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }
    std::cout << "Prim for List: \n";
    std::cout << "Edge \tWeight\n";
    for (int i = 1; i < V; ++i) {
        std::cout << parent[i] << " - " << i << " \t" << key[i] << " \n";
    }
}



void primMST(GraphIncidence& graph) {
    int V = graph.getNumVertices();
    int E = graph.getNumEdges();
    std::vector<int> key(V, INT_MAX);
    std::vector<int> parent(V, -1);
    std::vector<bool> inMST(V, false);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int src = 0; // Start from vertex 0
    key[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        // Traverse all edges (columns) incident on vertex u
        for (int edge = 0; edge < E; ++edge) {
            if (graph.getEdgeWeight(u, edge) != 0) { // Check if there is an edge
                // Find the other end of the edge (vertex v)
                int v = -1;
                for (int vertex = 0; vertex < V; ++vertex) {
                    if (vertex != u && graph.getEdgeWeight(vertex, edge) != 0) {
                        v = vertex;
                        break;
                    }
                }

                // If v is not yet in MST and weight of u-v is less than key[v]
                if (v != -1 && !inMST[v] && graph.getEdgeWeight(u, edge) < key[v]) {
                    key[v] = graph.getEdgeWeight(u, edge);
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }
    }

    // Print the MST edges and weights
    std::cout << "Prim for Incidence Matrix: \n";
    std::cout << "Edge \tWeight\n";
    for (int i = 1; i < V; ++i) {
        std::cout << parent[i] << " - " << i << " \t" << key[i] << " \n";
    }
}
