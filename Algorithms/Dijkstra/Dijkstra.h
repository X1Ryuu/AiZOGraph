//
// Created by Bart on 17.06.2024.
//

#ifndef GRAPH_DIJKSTRA_H
#define GRAPH_DIJKSTRA_H


#include "../../Matrix/GraphIncidence.h"
#include "../../List/GraphList.h"

void dijkstra(GraphIncidence& graph, int source);
void dijkstra(GraphList& graph, int source);


#endif //GRAPH_DIJKSTRA_H
