#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void pinput();
void pcess();
int findfman();
int findpreorder(int index, int o);
void oput();
void descourse();


int N;
int * mancp;
int * womencp;
int ** man;
int ** women;

int main(int argc, char *argv[]) 
{

freopen("input.txt","r",stdin);
freopen("output.txt","w", stdout);


	scanf("%d", &N);
	
	pinput();
	
	pcess();
	
	oput();
	
	descourse();
	
fclose(stdin);
fclose(stdout);

	return 0;
}

void pinput()
{
	int i, j, k;
	
	
	man = (int **)malloc(sizeof(int *) * N);
	women = (int **)malloc(sizeof(int *) * N);
	
	mancp = (int *)malloc(sizeof(int) * N);
	womencp = (int *)malloc(sizeof(int) * N);
	
	for(i=0; i<N; ++i) {
		man[i] = (int *)malloc(sizeof(int) * N);
		women[i] = (int *)malloc(sizeof(int) * N);
		
		mancp[i] = 0;
		womencp[i] = 0;
	}
	
	for(i=0; i<N; ++i){
		for(j=0; j<N; ++j){
			scanf("%d", &k);
			man[i][k-1] = j+1;  //按照喜好优先级 顺序输入。第(i+1)喜欢的是第K个女生。k是女生编号，对应的下标应减一。 
		}
	}
	
	for(i=0; i<N; ++i){
		for(j=0; j<N; ++j)
		{
			scanf("%d", &k);
			women[i][k-1] = j+1; 
		}
			
	}
}

void pcess()
{
	int i, j, k;
	int count = N;
	int o;
	
	while(count) {
		o = 1;
		i = findfman(N);
		j = findpreorder(i, o);
		while( womencp[j] != 0 && women[j][i] > women[j][womencp[j]-1])
		{
			j = findpreorder(i, ++o);
		}
		
		if (womencp[j] == 0) {
			mancp[i] = j + 1;
			womencp[j] = i+1;
			count--;
		} else if(women[j][i] < women[j][womencp[j]]){
			mancp[womencp[j] -1] = 0;
			mancp[i] = j + 1;
			womencp[j] = i+1;
		}
	}
}

int findfman()
{
	int i;
	for(i=0; i<N; ++i)
	{
		if (mancp[i] == 0)
			return i;
	}
}

//返回的是喜好优先级较高的女生的下标 
int findpreorder(int index, int o)
{
	int i;
	for(i=0; i<N; ++i) {
		if (man[index][i] == o)
			return i;
	}
}

void oput()
{
	int i;
	for(i=0; i<N; ++i) {
		printf("m:%d w:%d\n",i+1, mancp[i]);
	}
}

void descourse()
{
	int i;
	for (i=0; i<0; ++i)
	{
		free(man[i]);
		free(women[i]);
	}
	free(man);
	free(women);
	free(mancp);
	free(womencp);
}

