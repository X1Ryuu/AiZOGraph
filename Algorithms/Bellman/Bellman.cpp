//
// Created by Bart on 17.06.2024.
//

#include <limits>
#include <iostream>
#include "Bellman.h"



struct Edge {
    int src, dest, weight;
};



void bellmanFord(GraphList& graph, int source) {
    int V = graph.getNumVertices();

    std::vector<Edge> edges;
    int l=0;
    // Zbieranie wszystkich krawędzi do wektora
    for (int u = 0; u < V; ++u) {
        for (const auto& neighbor : graph.getEdges(u)) {
            int v = neighbor.first;
            int weight = neighbor.second;
            edges.push_back({u, v, weight});
            l++;
        }
    }
 //   std::cout << l << "\n";

    for(int i=0;i<edges.size();i++)printf("%d %d %d\n", edges[i].src, edges[i].dest, edges[i].weight);

    // Inicjalizacja odległości i poprzedników
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> prev(V, -1);
    dist[source] = 0;

    // Wykonujemy relaksację V-1 razy
    for (int i = 1; i < V; ++i) {
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
   //         printf("%d > %d + %d (%d)\n", dist[v], dist[u], weight, dist[u] + weight);
            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {

                dist[v] = dist[u] + weight;
                prev[v] = u;


            }
        }
    }

    // Sprawdzamy obecność ujemnego cyklu
    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
            std::cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    // Wypisujemy wyniki
    std::cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == std::numeric_limits<int>::max()) {
            std::cout << "Vertex " << i << ": " << "INF\n";
        } else {
            std::cout << "Vertex " << i << ": " << dist[i] <<", prev: "<< prev[i] << "\n";
        }
    }
}

void bellmanFord(GraphIncidence& graph, int source) {
    int V = graph.getNumVertices();
    int E = graph.getNumEdges();

    std::vector<Edge> edges;
    int l=0;
    // Zbieramy wszystkie dodatnie krawędzie z macierzy incydencji
    int v1=0, v2=0, licz=0, weight;
    for (int edge = 0; edge < E; ++edge) {
        licz=0;
        for (int vertex = 0; vertex < V; ++vertex) {
            if (graph.getEdgeWeight(vertex, edge) != 0 && licz<2) {
                if (graph.getEdgeWeight(vertex, edge)>0) {
                    v1 = vertex;
                    licz++;
                    if(graph.getEdgeWeight(vertex, edge)>0)weight= graph.getEdgeWeight(vertex, edge);
                    if(licz==2) {
                        edges.push_back({v1, v2, weight});
                        break;
                    }
                }else {
                    v2=vertex;
                    licz++;
                    if(graph.getEdgeWeight(vertex, edge)>0)weight= graph.getEdgeWeight(vertex, edge);
                    if(licz==2){
                        edges.push_back({v1, v2, weight});
                        break;
                    }
                }

            }
        }
    }
    for(int i=0;i<edges.size();i++)printf("%d %d %d\n", edges[i].src, edges[i].dest, edges[i].weight);
//    std::cout << l << "\n";
    // Inicjalizacja odległości i poprzedników
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> p(V, -1);
    dist[source] = 0;

    // Relaksacja krawędzi V-1 razy
    for (int i = 1; i < V; ++i) {
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            weight = edge.weight;
            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {

                dist[v] = dist[u] + weight;
                p[v] = u;


            }
        }
    }

    // Sprawdzamy obecność ujemnego cyklu
    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
            std::cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    // Wypisujemy wyniki
    std::cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == std::numeric_limits<int>::max()) {
            std::cout << "Vertex " << i << ": " << "INF\n";
        } else {
            std::cout << "Vertex " << i << ": " << dist[i] <<", prev: "<< p[i] << "\n";
        }
    }
}
