#include <stdio.h>
#include "graph.h"

int main(){
	_graph* graph = Graph_Init(6);
	Graph_Define_Connection(graph, 1, 2, 6);
	Graph_Define_Connection(graph, 1, 3, 3);
	Graph_Define_Connection(graph, 2, 3, 2);
	Graph_Define_Connection(graph, 2, 4, 5);
	Graph_Define_Connection(graph, 3, 4, 3);
	Graph_Define_Connection(graph, 3, 5, 4);
	Graph_Define_Connection(graph, 4, 5, 2);
	Graph_Define_Connection(graph, 4, 6, 3);
	Graph_Define_Connection(graph, 5, 6, 5);

	for(int i = 0; i < graph->vert_quantity; i++){
		for(int j = 0; j < graph->vert_quantity; j++){
			printf("%d ", graph->edges[i][j]);
		}
		printf("\n");
	}

	Shortest_Path(graph, 1);
	Graph_Delete(graph);
}
