#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
	int weight;
	int info;
	struct edge * nextedge;
	struct vertex * adjtex;
} edge;

typedef struct vertex {
	char site[20];
	struct edge * firstedge;
	struct vertex * prev;
	int info;
	int isdiscovered;
} vertex;

typedef struct {
	vertex ** vertices;
	int vexnum, edgnum;
}graph;


//function declare
graph * buildgraph(); 
vertex * findvertexbyname(graph * g, const char * name);
void cleartags(graph * g);
vertex * findmininfo(graph * g);

#endif
