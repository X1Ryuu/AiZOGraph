#ifndef UTILS_H
#define UTILS_H


#include <string>
#include "../Matrix/GraphIncidence.h"
#include "../List/GraphList.h"


void generateGraph(GraphIncidence& matrixGraph, GraphList& listGraph, int numVertices, double density, bool directed);
void displayGraph(const GraphList& listGraph, const GraphIncidence& incidenceGraph);
void generateGraph(GraphIncidence& incidenceGraph, GraphList& listGraph, GraphIncidence& incidenceGraphMST, GraphList& listGraphMST, int numVertices, double density);
bool loadGraphFromFile(const std::string& filename, GraphList& graphList, GraphIncidence& graphIncidence, GraphList& graphListMST, GraphIncidence& graphIncidenceMST);
#endif // UTILS_H
