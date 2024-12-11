#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "graph.h"

int** Matrix_Allocate(int dimension){
	int** matrix = (int**)calloc(dimension, sizeof(int*));;

	for(int i = 0; i < dimension; i++){
		matrix[i] = (int*)calloc(dimension, sizeof(int));
	}

	return matrix;
}

_graph* Graph_Allocate(){
	return (_graph*)calloc(1, sizeof(_graph));
}

_graph* Graph_Init(int vert_quantity){
	_graph* new_graph = Graph_Allocate();

	new_graph->vert_quantity = vert_quantity;
	new_graph->edges = Matrix_Allocate(vert_quantity);

	return new_graph;
}

void Graph_Delete(_graph* graph){
	for(int i = 0; i < graph->vert_quantity; i++){
		free(graph->edges[i]);
	}
	free(graph->edges);
	free(graph);
}

void Graph_Matrix_Print(_graph* graph){
	for(int i = 0; i < graph->vert_quantity; i++){
		for(int j = 0; j < graph->vert_quantity; j++){
			printf("%d ", graph->edges[i][j]);
		}
		printf("\n");
	}
}

void Graph_Define_Connection(_graph* graph, int vert_a, int vert_b, int weight){
	if(graph == NULL){
		printf("graph is NULL!\n");
		return;
	}
	if(graph->edges == NULL){
		printf("graph has no matrix!\n");
		return;
	}
	graph->edges[vert_a - 1][vert_b - 1] = weight;
	graph->edges[vert_b - 1][vert_a - 1] = weight;
}

void Graph_Define_Connection_OneWay(_graph* graph, int source, int destination, int weight){
	if(graph == NULL){
		printf("graph is NULL!\n");
		return;
	}
	if(graph->edges == NULL){
		printf("graph has no matrix!\n");
		return;
	}
	graph->edges[source - 1][destination - 1] = weight;
}

int Minimum_Distance(int* distance, bool* shortest_path_tree, int vert_quantity){
    // Initialize min value
    int minimum = INT_MAX;
    int minimum_index;

    for (int i = 0; i < vert_quantity; i++){
        if (shortest_path_tree[i] == false && distance[i] <= minimum){
            minimum = distance[i];
	    minimum_index = i;
	}
    }

    return minimum_index;
}

void Shortest_Path(_graph* graph, int vertex){
    int source = vertex - 1;
    int distance[graph->vert_quantity]; 
    // The output array.  dist[i] will hold the
    // shortest
    // distance from src to i

    bool shortest_path_tree[graph->vert_quantity]; 
    // shortest_path_tree[i] will be true if vertex i is
    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized

    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < graph->vert_quantity; i++){
        distance[i] = INT_MAX;
	shortest_path_tree[i] = false;
    }

    // Distance of source vertex from itself is always 0
    distance[source] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < graph->vert_quantity - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int vertex = Minimum_Distance(distance, shortest_path_tree, graph->vert_quantity);

        // Mark the picked vertex as processed
        shortest_path_tree[vertex] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int i = 0; i < graph->vert_quantity; i++){
            // Update distance[i] only if is not in shortest_path_tree,
            // there is an edge from vertex to i, and total
            // weight of path from source to i through vertex is
            // smaller than current value of dist[v]
            if (!shortest_path_tree[i] && graph->edges[vertex][i] && distance[vertex] != INT_MAX && distance[vertex] + graph->edges[vertex][i] < distance[i]){
                distance[i] = distance[vertex] + graph->edges[vertex][i];
	    }
	}
    }
    
    for(int i = 0; i < graph->vert_quantity; i++){
	printf("distance %d: %d\n", i + 1, distance[i]);
    }
}
