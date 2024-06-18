//
// Created by Bart on 17.06.2024.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include "Kruskal.h"



struct Subset {
    int parent;
    int rank;
};

// Funkcja pomocnicza do znajdowania zbioru (komponentu) elementu u
int find(std::vector<Subset>& subsets, int u) {
    if (subsets[u].parent != u) {
        subsets[u].parent = find(subsets, subsets[u].parent); // Path compression
    }
    return subsets[u].parent;
}

// Funkcja łącząca dwa zbiory (komponenty) w strukturze Find-Union
void unionSets(std::vector<Subset>& subsets, int u, int v) {
    int rootU = find(subsets, u);
    int rootV = find(subsets, v);

    if (subsets[rootU].rank < subsets[rootV].rank) {
        subsets[rootU].parent = rootV;
    } else if (subsets[rootU].rank > subsets[rootV].rank) {
        subsets[rootV].parent = rootU;
    } else {
        subsets[rootV].parent = rootU;
        subsets[rootU].rank++;
    }
}

// Implementacja algorytmu Kruskala dla grafu w postaci listy sąsiedztwa
void kruskalMST(GraphList& graph) {
    int V = graph.getNumVertices();
    int E = graph.getNumEdges();

    // Kolekcja krawędzi (u, v, weight)
    std::vector<std::pair<int, std::pair<int, int>>> edges;

    // Przechodzenie po wszystkich wierzchołkach
    for (int u = 0; u < V; ++u) {
        for (auto& edge : graph.getEdges(u)) {
            int v = edge.first;
            int weight = edge.second;
            if (u < v) { // Unikamy dodawania krawędzi dwukrotnie
                edges.push_back({weight, {u, v}});
            }
        }
    }

    // Sortowanie krawędzi względem wagi
    std::sort(edges.begin(), edges.end());

    std::vector<std::pair<int, int>> result; // Inicjalizacja wyniku (MST)

    std::vector<Subset> subsets(V);
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int edgeCount = 0; // Licznik dodanych krawędzi do MST
    int index = 0; // Indeks w posortowanych krawędziach

    // Budowanie MST
    while (edgeCount < V - 1 && index < edges.size()) {
        int u = edges[index].second.first;
        int v = edges[index].second.second;
        int weight = edges[index].first;
        index++;

        int rootU = find(subsets, u);
        int rootV = find(subsets, v);

        // Sprawdzenie, czy dodanie krawędzi u-v nie stworzy cyklu
        if (rootU != rootV) {
            result.push_back({u, v});
            unionSets(subsets, rootU, rootV);
            edgeCount++;
        }
    }

    // Wyświetlenie MST
    std::cout << "Kruskal for List: \n";
    std::cout << "Edges in MST:\n";
    for (auto& edge : result) {
        std::cout << edge.first << " - " << edge.second << "   " <<"\n";
    }
}








struct Edge {
    int src, dest, weight;
};

bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

struct UnionFind {
    std::vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};



void kruskalMST(GraphIncidence& graph) {
    int V = graph.getNumVertices();
    int E = graph.getNumEdges();

    // Kolekcja krawędzi (u, v, weight)
    std::vector<Edge> edges;

    // Przechodzenie po wszystkich krawędziach w macierzy incydencji
    for (int edge = 0; edge < E; ++edge) {
        int v1 = -1, v2, weight;
        for (int vertex = 0; vertex < V; ++vertex) {
            int edgeWeight = graph.getEdgeWeight(vertex, edge);
            if (edgeWeight != 0) {
                if (v1 == -1) {
                    v1 = vertex;
                    weight = edgeWeight;
                } else {
                    v2 = vertex;
                    edges.push_back({v1, v2, edgeWeight});
                    break;
                }
            }
        }
    }

    // Sortowanie krawędzi względem wagi
    std::sort(edges.begin(), edges.end(), compareEdges);

    std::vector<Edge> result;
    UnionFind uf(V);
    int edgeCount = 0;
    int index = 0;

    // Budowanie MST za pomocą algorytmu Kruskala
    while (edgeCount < V - 1 && index < edges.size()) {
        int u = edges[index].src;
        int v = edges[index].dest;
        int weight = edges[index].weight;
        index++;

        int rootU = uf.find(u);
        int rootV = uf.find(v);

        // Sprawdzenie, czy dodanie krawędzi u-v nie stworzy cyklu
        if (rootU != rootV) {
            result.push_back({u, v, weight});
            uf.unionSets(rootU, rootV);
            edgeCount++;
        }
    }

    // Wyświetlenie MST
    std::cout << "Kruskal for Incidence matrix:\n";
    std::cout << "Edges in MST:\n";
    for (auto& edge : result) {
        std::cout << edge.src << " - " << edge.dest << " with weight " << edge.weight << "\n";
    }
}



