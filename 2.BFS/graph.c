#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int buildedge(vertex * from, vertex * to, int lineno, int weight);
int isexist(char line[300][20], const char * name, int k);

//---------------------------------public function implements below ----------------------- 
graph * buildgraph()
{
	char  staname[20];
	char line[300][20];
	vertex * station[300];
	int i, k, l, weight;
	int lineno, iscycle;
	
	vertex * pretex, * headtex;
	vertex * v;
	graph * metro;

	k = l  = 0;
	lineno = iscycle = 0;
	pretex = headtex = 0;
	
	metro = (graph *)malloc(sizeof(graph));
	metro->vertices = 0;
	metro->vexnum = metro->edgnum = 0;
	
	while(gets(staname) != NULL) 
	{
		if(atoi(staname)) 
		{
			if (iscycle) {
				weight = rand()%10 + 1;
				buildedge(pretex, headtex, lineno, weight);
				buildedge(headtex, pretex, lineno, weight);
				l += 2;
			}
			
			lineno = atoi(staname);
			if(lineno == -1) break;
			
			pretex = headtex = 0;
			if(lineno % 10 == 0) iscycle = 0;
			else iscycle = 1;
			lineno /= 10;
		}
		else {
			//查找是否站已经存在
			i = isexist(line, staname, k);
			
			if (i > -1) v = station[i];
			else {
				v = (vertex *)malloc(sizeof(vertex));
				v->firstedge = 0;
				v->isdiscovered = v->info = 0;
				v->prev = 0; 
				station[k] = v;
				strcpy(line[k++], staname);
				strcpy(v->site, staname);
			}
			
			if (pretex) {
				weight = rand()%10 + 1;
				buildedge(pretex, v, lineno, weight);
				buildedge(v, pretex, lineno, weight);
				l += 2;
			} 
			if (!pretex && iscycle) headtex = v;
			pretex = v; 
		}
	}
	metro->vexnum = k;
	metro->edgnum = l;
	metro->vertices = (vertex **)malloc(sizeof(vertex *) * k);
	for(i=0; i<k; ++i) metro->vertices[i] = station[i]; 
	return metro;
}

vertex * findvertexbyname(graph * g, const char * name)
{
	int i;
	for(i=0; i<g->vexnum; ++i) {
		if (strcmp(name, g->vertices[i]->site) ==0 ) return g->vertices[i];
	}
}

void cleartags(graph * g)
{
	int i;
	for(i=0; i<g->vexnum; ++i) {
		g->vertices[i]->isdiscovered = 0;
		g->vertices[i]->prev = 0;
		g->vertices[i]->info = 0;
	}
}

vertex * findmininfo(graph * g)
{
	int i;
	int min = 999999;
	int mini;
	for (i=0; i<g->vexnum; ++i) {
		if (g->vertices[i]->isdiscovered == 0) {
		if (g->vertices[i]->info < min) {
				mini = i;
				min = g->vertices[i]->info;
			}
		}
	}
	return g->vertices[mini];
}

//------------------------private function below here------------------------------ 
int isexist(char line[300][20], const char * name, int k)
{
	int i;
	for(i=0; i<k; ++i) if(strcmp(name, line[i]) == 0)  return i;
	return -1;
}

int buildedge(vertex * from, vertex * to, int lineno, int weight)
{
	edge * arc = (edge *)malloc(sizeof(edge));
	arc->nextedge = from->firstedge;
	from->firstedge = arc;
	arc->adjtex = to;
	arc->info = lineno;
	arc->weight = weight;
}

