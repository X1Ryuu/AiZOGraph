#include <iostream>
#include <limits>
#include <queue>
#include "Dijkstra.h"

void dijkstra(GraphIncidence& graph, int source) {
    int V = graph.getNumVertices();
    std::vector<int> dist(V, std::numeric_limits<int>::max()); // Tablica odległości od źródła do pozostałych wierzchołków
    std::vector<bool> visited(V, false); // Tablica odwiedzonych wierzchołków

    dist[source] = 0; // Odległość od źródła do źródła wynosi 0

    // Priorytetowa kolejka do przechowywania wierzchołków do przetworzenia
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source}); // Para (odległość, wierzchołek)

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Jeśli wierzchołek został już odwiedzony, kontynuuj
        if (visited[u]) continue;

        visited[u] = true;

        // Przejście po wszystkich krawędziach wychodzących z wierzchołka u w macierzy incydencji
        for (int edge = 0; edge < graph.getNumEdges(); ++edge) {
            if (graph.getEdgeWeight(u, edge) > 0) { // Sprawdź czy istnieje krawędź (u, v) o dodatniej wadze
                int v = -1;
                for (int vertex = 0; vertex < V; ++vertex) {
                    if (graph.getEdgeWeight(vertex, edge) < 0) { // Znajdź wierzchołek docelowy v dla dodatniej krawędzi
                        v = vertex;
                        break;
                    }
                }

                int weight = graph.getEdgeWeight(u, edge);

                // Relaksacja krawędzi (u, v)
                if (dist[u] != std::numeric_limits<int>::max() && dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // Wyświetlenie wyników
    std::cout << "Shortest distances from vertex " << source << ":\n";
   // printf("%d", V);
    for (int i = 0; i < V; ++i) {
        std::cout << "Vertex " << i << ": ";
        if (dist[i] == std::numeric_limits<int>::max()) {
            std::cout << "INF\n";
        } else {
            std::cout << dist[i] << "\n";
        }
    }
}


void dijkstra(GraphList& graph, int source) {
    int V = graph.getNumVertices();
    std::vector<int> dist(V, std::numeric_limits<int>::max()); // Tablica odległości od źródła do pozostałych wierzchołków
    std::vector<bool> visited(V, false); // Tablica odwiedzonych wierzchołków

    dist[source] = 0; // Odległość od źródła do źródła wynosi 0

    // Priorytetowa kolejka do przechowywania wierzchołków do przetworzenia
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source}); // Para (odległość, wierzchołek)

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Jeśli wierzchołek został już odwiedzony, kontynuuj
        if (visited[u]) continue;

        visited[u] = true;

        // Przejście po wszystkich sąsiadach wierzchołka u
        for (auto& edge : graph.getEdges(u)) {
            int v = edge.first;
            int weight = edge.second;

            // Relaksacja krawędzi (u, v)
            if (dist[u] != std::numeric_limits<int>::max() && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Wyświetlenie wyników
    std::cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        std::cout << "Vertex " << i << ": ";
        if (dist[i] == std::numeric_limits<int>::max()) {
            std::cout << "INF\n";
        } else {
            std::cout << dist[i] << "\n";
        }
    }

}