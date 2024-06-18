//
// Created by Bart on 17.06.2024.
//

#ifndef GRAPH_BELLMAN_H
#define GRAPH_BELLMAN_H


#include "../../List/GraphList.h"
#include "../../Matrix/GraphIncidence.h"

void bellmanFord(GraphIncidence& graph, int source);
void bellmanFord(GraphList& graph, int source);

#endif //GRAPH_BELLMAN_H
