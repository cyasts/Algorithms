#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
	int lineno;
	int weight;
	struct edge * nextedge;
	struct vertex * adjtex;
} edge;

typedef struct vertex {
	char site[20];
	struct edge * firstedge;
	struct vertex * prev;
	int dist;
	int isdiscovered;
} vertex;

typedef struct {
	vertex * vertices;
	int vexnum, edgnum;
}graph;

//global var
char  line[300][20];		//station name 
vertex * station[300]; 	 	//station pointer 

//function declare
graph * input(); 
void BFS(graph * g, vertex * src, vertex * desc);
void dijkstra(graph * g, vertex * src);
void cleartags(graph * g);
int isexist(const char * sta, int k);
vertex * findvertexbyname(graph * g, const char * name);
vertex * findmindist(graph * g);
int buildedge(vertex * from, vertex * to, int lineno);
void printpath(graph * metro, vertex * desc);

int main(int argc, char *argv[])
{
	
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
	
	graph * metro;
	
	vertex * src;
	vertex * des;
	
	metro = input();
	
	char s1[20];
	char s2[20];
	scanf("%s", &s1);
	scanf("%s", &s2);
	
	src = findvertexbyname(metro, s1);
    des = findvertexbyname(metro, s2);
	
	dijkstra(metro, src);
	printpath(metro, des);
	cleartags(metro);
	
fclose(stdin);
fclose(stdout);	

	return 0;	
}


void dijkstra(graph * g, vertex * src)
{
	int i, k, alt;
	vertex * u, *v;
	edge * arc;
	for(i=0; i<g->vexnum; ++i) {
		station[i]->dist = 999999999;
		station[i]->prev = 0;
	}
	src->dist = 0;
	while(k > 0) {
		u = findmindist(g);
		u->isdiscovered = 1;
		arc = u->firstedge;
		while (arc) {
			v = arc->adjtex;
			if (v->isdiscovered) continue;
			alt = u->dist + arc->weight;
			if (alt < v->dist) {
				v->dist = alt;
				v->prev = u;
			}
			arc = arc->nextedge;
		}
	}
}

graph * input()
{
	char  staname[20];
	int i, k, l;
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
		if(atoi(staname)) //先接受一条地铁线的线路号，规定为输入的数据为 线路号*10+是否为环线，比如 1号线对应输入10，7号线有环线对应输入为71 
		{
			lineno = atoi(staname); 
			if(lineno == -1) break;
			
			if (iscycle) {
				buildedge(pretex, headtex, lineno);
				buildedge(headtex, pretex, lineno);
				l += 2;
			}
			metro->vertices = pretex;
			
			pretex = headtex = 0;
			if(lineno % 10 == 0) iscycle = 0;
			else iscycle = 1;
			lineno /= 10;
		}
		else {
			//查找是否站已经存在
			i = isexist(staname, k);
			
			if (i > -1) {
				v = station[i];
			}else {
				v = (vertex *)malloc(sizeof(vertex));
				v->firstedge = v->isdiscovered = v->prev = 0;
				station[k] = v;
				strcpy(line[k++], staname);
				strcpy(v->site, staname);
			}
			
			if (pretex) {
				buildedge(pretex, v, lineno);
				buildedge(v, pretex, lineno);
				l += 2;
			} 
			if (!pretex && iscycle) headtex = v;
			pretex = v; 
		}
	}
	metro->vexnum = k;
	metro->edgnum = l;
	return metro;
}
//查找站台是否存在，存在返回对应的全局数组的下标，不存在则返回-1 
int isexist(const char * sta, int k)
{
	int i;
	for(i=0; i<k; ++i) if(strcmp(sta, line[i]) == 0)  return i;
	return -1;
	
}
 
int buildedge(vertex * from, vertex * to, int lineno)
{
	edge * arc = (edge *)malloc(sizeof(edge));
	arc->nextedge = from->firstedge;
	from->firstedge = arc;
	arc->adjtex = to;
	arc->lineno = lineno;
	arc->weight = rand()%10+1;
}

vertex * findvertexbyname(graph * g, const char * name)
{
	int i;
	for(i=0; i<g->vexnum; ++i) {
		if (strcmp(name, line[i]) ==0 ) return station[i];
	}
}

vertex * findmindist(graph * g)
{
	int i;
	int min = 999999;
	int mini;
	for (i=0; i<g->vexnum; ++i) {
		if (station[i]->isdiscovered == 0) {
			if (station[i]->dist < min) {
				mini = i;
				min = station[i]->dist;
			}
		}
	}
	return station[i];
}

void cleartags(graph * g)
{
	int i;
	for(i=0; i<g->vexnum; ++i) {
		station[i]->isdiscovered = 0;
		station[i]->prev = 0;
	}
}

void printpath(graph * metro, vertex * desc)
{
	int i=0, leng=0;
	vertex * sta[300];
	vertex * v = desc;
	while(v) {
		sta[i++] = v;
		v = v->prev;
	}
	
	for(i--; i>=0; ++i){
		leng += sta[i]->dist;
		printf("%s %d", sta[i]->site, leng);
	}
}
