# <center>稳定匹配问题</center>
#### 1.问题描述
给定N个男性m~1~,,⋯,m~n~和N个女性w~1~,⋯,w~n~
* 每个男性对女性由最喜欢到最不喜欢进行排序
* 每个女性对男性由最喜欢到最不喜欢进行排序

目标：找到一个稳定的匹配使得不满意度最低。
#### 2.输入
第一行输入N，表示需要处理的匹配的对数。男性按照1，2，3...N的编号表示，女性同样如此。
接下来N行，每行N个数字，表示该行男性对所有女性的好感度排名。
再接下来N行，每行N个数字，表示该行女性对所有男性的好感度排名。
例如：
3
1 2 3
2 1 3
1 2 3
2 1 3
1 2 3
1 2 3

#### 3.输出
输入N行，每行输出一个匹配的结果，格式为：m:编号，w:编号.
例如:
m:1 w:1
m:2 w:2
m:3 w:3

#### 4.核心思想
![20201010211020](https://cdn.jsdelivr.net/gh/cyasts/cyasts.github.io@master/images/20201010211020.png)

#### 4.算法实现
```C
#include <stdio.h>
#include <stdlib.h>

void input();
void process();
int findfman();
int findpreorder(int index, int o);
void output();
void desource();


int N;
int * mancp;
int * womencp;
int ** man;
int ** women;

int main(int argc, char *argv[]) 
{

//freopen("input.txt","r",stdin);
//freopen("output.txt","w", stdout);


	scanf("%d", &N);
	
	input();
	
	process();
	
	output();
	
	desource();
	
//fclose(stdin);
//fclose(stdout);

	return 0;
}

void input()
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

void process()
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
		} else if(women[j][i] < women[j][womencp[j]-1]){
			mancp[womencp[j] -1] = 0;
			mancp[i] = j + 1;
			womencp[j] = i+1;
		}
	}
}

//找到未分配的男性成员下标 
int findfman()
{
	int i;
	for(i=0; i<N; ++i)
	{
		if (mancp[i] == 0)
			return i;
	}
}

//根据男性index下标找到第o个中意的女性 
int findpreorder(int index, int o)
{
	int i;
	for(i=0; i<N; ++i) {
		if (man[index][i] == o)
			return i;
	}
}

void output()
{
	int i;
	for(i=0; i<N; ++i) {
		printf("m:%d w:%d\n",i+1, mancp[i]);
	}
}

void desource()
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

```
#### 5.测试数据
---
第一组：
输入：

    3
    1 2 3
    2 1 3
    1 2 3
    2 1 3
    1 2 3
    1 2 3

输出：

    m:1 w:1
    m:2 w:2
    m:3 w:3 

---
第二组：
输入：

    10
    2 5 4 7 3 6 9 8 10 1
    3 2 1 4 5 9 6 10 8 7
    5 4 9 10 1 3 2 8 7 6
    3 8 7 2 5 4 9 1 10 6
    6 4 9 5 3 1 8 7 2 10
    6 1 2 8 3 9 10 5 7 4
    7 3 10 9 1 8 6 2 5 4
    10 8 2 9 1 3 6 7 4 5
    9 1 6 10 7 8 2 3 5 4
    8 10 2 7 3 1 6 9 5 4
    4 6 1 7 10 5 9 8 3 2
    1 2 4 3 8 9 6 10 5 7
    2 1 8 10 4 3 6 9 7 5
    3 1 7 4 5 2 6 8 10 9
    6 7 9 4 3 1 10 5 2 8
    4 1 2 8 10 9 3 5 7 6
    7 3 8 9 1 10 5 2 6 4
    10 4 2 3 1 8 6 7 9 5
    5 2 6 10 7 8 1 3 9 4
    7 1 2 8 3 10 6 9 5 4
输出：

    m:1 w:2
    m:2 w:3
    m:3 w:4
    m:4 w:5
    m:5 w:6
    m:6 w:1
    m:7 w:7
    m:8 w:10
    m:9 w:9
    m:10 w:8

---
