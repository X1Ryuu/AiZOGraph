#include "utils.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>


void generateGraph(GraphIncidence& incidenceGraph, GraphList& listGraph, GraphIncidence& incidenceGraphMST, GraphList& listGraphMST, int numVertices, double density){
    int minimumEdgeNumber = numVertices - 1;
    int edgeNumber = ((density * numVertices * (numVertices - 1))/2 );
    edgeNumber = edgeNumber > minimumEdgeNumber ? edgeNumber : minimumEdgeNumber;
    listGraph = GraphList(numVertices);
    incidenceGraph = GraphIncidence(numVertices, edgeNumber);
    listGraphMST = GraphList(numVertices);
    incidenceGraphMST = GraphIncidence(numVertices, edgeNumber);
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> values(1, 100);
    std::uniform_int_distribution<int> vertices(0, numVertices - 1);
//std::cout << minimumEdgeNumber << ", " << edgeNumber<< std::endl;
    std::vector<std::vector<bool>> existConnection(numVertices, std::vector<bool>(numVertices, false));



    // Create a spanning tree to ensure the graph is connected
    for (int i = 0; i < minimumEdgeNumber; ++i) {
        int weight = values(gen);
        listGraph.addEdge(i, i + 1, weight);
        incidenceGraph.addEdge(i, i + 1, weight);

        listGraphMST.addEdges(i, i + 1, weight);
        incidenceGraphMST.addEdges(i, i + 1, weight);


        existConnection[i][i + 1] = true;
        existConnection[i + 1][i] = true;
    }

    for (int i = minimumEdgeNumber; i < edgeNumber; ++i) {
        int origin = vertices(gen);
        int destination = vertices(gen);

        while (origin == destination || existConnection[origin][destination]) {
            origin = vertices(gen);
            destination = vertices(gen);
        }

        int weight = values(gen);

            listGraph.addEdge(origin, destination, weight);
            incidenceGraph.addEdge(origin, destination, weight);

            listGraphMST.addEdges(origin, destination, weight);
            incidenceGraphMST.addEdges(origin, destination, weight);

        existConnection[origin][destination] = true;
        existConnection[destination][origin] = true;
    }
}



void generateGraph(GraphIncidence& incidenceGraph, GraphList& listGraph, int numVertices, double density, bool directed) {


    int minimumEdgeNumber = numVertices - 1;

    int edgeNumber = density * numVertices * (numVertices - 1);
    if (!directed) {
        edgeNumber/=2;
    }
    edgeNumber = edgeNumber > minimumEdgeNumber ? edgeNumber : minimumEdgeNumber;
    listGraph = GraphList(numVertices);
    incidenceGraph = GraphIncidence(numVertices, edgeNumber);
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<int> values(1, 100);
    std::uniform_int_distribution<int> vertices(0, numVertices - 1);
//std::cout << minimumEdgeNumber << ", " << edgeNumber<< std::endl;
    std::vector<std::vector<bool>> existConnection(numVertices, std::vector<bool>(numVertices, false));



    // Create a spanning tree to ensure the graph is connected
    for (int i = 0; i < minimumEdgeNumber; ++i) {
        int weight = values(gen);
        if (directed){
            listGraph.addEdge(i, i + 1, weight);
            incidenceGraph.addEdge(i, i + 1, weight);
        }else {
            listGraph.addEdges(i, i + 1, weight);
            incidenceGraph.addEdges(i, i + 1, weight);
        }

        existConnection[i][i + 1] = true;
        existConnection[i + 1][i] = true;
    }

    for (int i = minimumEdgeNumber; i < edgeNumber; ++i) {
        int origin = vertices(gen);
        int destination = vertices(gen);

        while (origin == destination || existConnection[origin][destination]) {
            origin = vertices(gen);
            destination = vertices(gen);
        }

        int weight = values(gen);
        if (directed){
            listGraph.addEdge(origin, destination, weight);
            incidenceGraph.addEdge(origin, destination, weight);
        }else {
            listGraph.addEdges(origin, destination, weight);
            incidenceGraph.addEdges(origin, destination, weight);
        }

        existConnection[origin][destination] = true;
        existConnection[destination][origin] = true;
    }
}

bool loadGraphFromFile(const std::string& filename, GraphList& graphList, GraphIncidence& graphIncidence, GraphList& graphListMST, GraphIncidence& graphIncidenceMST) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false; // Zwracamy false w przypadku błędu
    }

    int numVertices, numEdges;
    file >> numEdges >> numVertices; // Pierwsza linia: liczba krawędzi i liczba wierzchołków

    // Inicjalizacja obu struktur grafowych
    graphList = GraphList(numVertices);
    graphIncidence = GraphIncidence(numVertices, numEdges);
    graphListMST = GraphList(numVertices);
    graphIncidenceMST = GraphIncidence(numVertices, numEdges);

    int start, end, weight;
    int edgeIndex = 0;
    while (file >> start >> end >> weight) {
        graphList.addEdge(start, end, weight); // Dodaj krawędź do GraphList
        graphIncidence.addEdge(start, end, weight); // Dodaj krawędź do GraphIncidence
        graphListMST.addEdges(start, end, weight); // Dodaj krawędź do GraphListMST
        graphIncidenceMST.addEdges(start, end, weight);
        edgeIndex++;
    }

    file.close();
    return true;
}




void displayGraph(const GraphList& listGraph, const GraphIncidence& incidenceGraph) {
    std::cout << "\nList representation:" << std::endl;
    for (int i = 0; i < listGraph.getNumVertices(); ++i) {
        std::cout << i << ": ";
        for (const auto& neighbor : listGraph.getEdges(i)) {
            std::cout << neighbor.first << "(" << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }


    std::cout << "\nIncidence Matrix representation:" << std::endl;
    for (int i = 0; i < incidenceGraph.getNumVertices(); ++i) {
        for (int j = 0; j < incidenceGraph.getNumEdges(); ++j) {

            printf(" %3d", incidenceGraph.getEdgeWeight(i, j));
        }
        std::cout << std::endl;
    }

}
