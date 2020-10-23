#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
	int weight;
	struct edge * nextedge;
	struct vertex * adjtex;
} edge;

typedef struct vertex {
	char site[20];
	struct edge * firstedge;
	int isdiscovered;
} vertex;

typedef struct {
	vertex * vertices;
	int vexnum, edgnum;
}graph;

//global var
char  line[300][20];		//station name 
vertex * station[300]; 		//station pointer 


//function declare
graph * input(); 
int isexist(const char * sta, int k);
vertex * findvertexbyname(graph * g, const char * name);
int buildedge(vertex * from, vertex * to, int lineno);
void BFS(graph * g, vertex * root, vertex * des);

int main(int argc, char *argv[])
{
	
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
	
	graph * metro;
	
	vertex * src;
	vertex * des;
	
	metro = input();
//	char s1[20];
//	char s2[20];
//	scanf("%s", &s1);
//	scanf("%s", &s2);
	
	src = findvertexbyname(metro, s1);
	des = findvertexbyname(metro, s2);
	
	BFS(metro, src, des);
	

fclose(stdin);
fclose(stdout);	

	return 0;	
}

void BFS(graph * g, vertex * root, vertex * des)
{
	vertex * temsta[100];
	vertex * v;
	int head, tail, c;
	head = tail = c = 0;
	edge * arc;
	temsta[tail] = root;
	tail = (tail+1) % 100;
	c = root->isdiscovered = 1;
	while(tail != head) {
		v = temsta[head];
		head = (head + 1) % 100;
		printf("%s\n", v->site);
		if (v == des) return;
		arc = v->firstedge;
		while(arc) {
			if (arc->adjtex->isdiscovered == 0) {
				temsta[tail] = arc->adjtex;
				tail = (tail+1) % 100;
				arc->adjtex->isdiscovered = 1;
			}
			arc = arc->nextedge;
		}
		c++;
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
		if(atoi(staname)) 
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
			
			if (i > -1) 
			{
				v = station[i];
			}else {
				v = (vertex *)malloc(sizeof(vertex));
				v->firstedge = 0;
				v->isdiscovered = 0;
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
	arc->weight = lineno;
}

vertex * findvertexbyname(graph * g, const char * name)
{
	int i;
	for(i=0; i<g->vexnum; ++i) {
		if (strcmp(name, line[i]) ==0 ) return station[i];
	}
}
