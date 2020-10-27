#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
	int weight;
	int info; //线路名称 
	struct edge * nextedge;
	struct vertex * adjtex;
} edge;

typedef struct vertex {
	char site[20];
	struct edge * firstedge;
	struct vertex * prev; //用来存储结果路径上的上一个节点 
	int info; //用来存储多余的数据 
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
