#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"


//function declare
void dijkstra(graph * g, vertex * src);
void BFS(graph * metro, vertex * src, vertex * des);
void printpath(graph * metro, vertex * desc, int order);

int main(int argc, char *argv[])
{
	
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
	
	graph * metro;
	
	vertex * src;
	vertex * des;
	
	metro = buildgraph();
	
	char s1[20];
	char s2[20];
	scanf("%s", &s1);
	scanf("%s", &s2);
	
	src = findvertexbyname(metro, s1);
    des = findvertexbyname(metro, s2);
	
	printf("in BFS:\n");
	BFS(metro, src, des);
	printpath(metro, des, 0);
	
	cleartags(metro);
	
	printf("indjstl:\n");
	dijkstra(metro, src);
	printpath(metro, des, 1);
	
fclose(stdin);
fclose(stdout);	

	return 0;	
}

void BFS(graph * metro, vertex * src, vertex * des)
{
	vertex * que[300];
	int head, tail;
	head = tail = 0;
	vertex * u, *v;
	edge * arc;
	que[tail++] = src;
	src->isdiscovered = 1;
	while(tail != head) {
		u = que[head];
		head = (head+1) % 300;
		if(u == des) break;
		arc = u->firstedge;
		while (arc) {
			v = arc->adjtex;
			if(v->isdiscovered == 0) {
				v->isdiscovered = 1;
				que[tail] = v;
				tail = (tail + 1) % 300;
				v->prev = u;
			}
			arc = arc->nextedge;
		}
	}
}

void dijkstra(graph * g, vertex * src)
{
	int i, k, alt;
	vertex * u, *v;
	edge * arc;
	for(i=0; i<g->vexnum; ++i) {
		g->vertices[i]->info = 99999;
		g->vertices[i]->prev = 0;
	}
	src->info = 0;
	k = g->vexnum;
	while(k > 0) {
		u = findmininfo(g);
		u->isdiscovered = 1;
		k--;
		arc = u->firstedge;
		while (arc) {
			v = arc->adjtex;
			alt = u->info + arc->weight;
			if (alt < v->info) {
				v->info = alt;
				v->prev = u;
			}
			arc = arc->nextedge;
		}
	}
}

void printpath(graph * metro, vertex * desc, int order)
{
	int i=0;
	vertex * sta[300];
	vertex * v = desc;
	while(v) {
		sta[i++] = v;
		v = v->prev;
	}
	
	for(i--; i>=0; --i){
		if(order) printf("%s %d\n", sta[i]->site, sta[i]->info);
		else  printf("%s \n", sta[i]->site);
	}
}
