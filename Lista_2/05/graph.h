#pragma once

typedef struct _graph{
	int vert_quantity;
	int** edges;
}_graph;

_graph* Graph_Init(int vert_quantity);
void Graph_Delete(_graph* graph);

void Graph_Matrix_Print(_graph* graph);

void Graph_Define_Connection(_graph* graph, int vert_a, int vert_b, int weight);
void Graph_Define_Connection_OneWay(_graph* graph, int vert_a, int vert_b, int weight);

void Shortest_Path(_graph* graph, int source);
