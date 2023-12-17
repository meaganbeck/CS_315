#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define s 0
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct node{
    int id; //id
    struct node* next;
    struct node* prev;
    float weight;
    int color;
}Node;

typedef struct graph{
    int numVertices;
    Node** adjLists;
    int numEdges;
}Graph;

int maxDist(Graph* G, int N, float* dist, int *sptSet){
    float max = -INFINITY;
    int max_ind;
    //int max = -INFINITY, max_ind
   
    /*Node* tmp;
    tmp = G->adjLists[prev]->next;
    int i = 0;
    while (tmp != NULL){
  //  for (int i = 0; i < N; i++){
	if (sptSet[tmp->id] == 0 && dist[tmp->id] >=max){
		max = dist[tmp->id];
		max_ind = tmp->id;
	}
//	i++;
//	tmp = tmp->next;
    */
    for (int i = 0; i < N; i++){
	if (sptSet[i] == 0 && dist[i] >=max){
		max = dist[i];
		max_ind = i;
	}
    }
//	i++;
    return max_ind;
}

float* dijkstra(Graph* G){
    
    int n = G->numVertices;
    
    float*dist = malloc(sizeof(float)*n);
    int* sptSet = malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++){
	dist[i] = -INFINITY;
	sptSet[i] = 0;
    }
    //init 
    dist[s] = 0; 

    int u;
    for (int i = 0; i < n; i++){ //
	u = maxDist( G, n, dist, sptSet);
	sptSet[u] = 1;
	Node* tmp;
	if (G->adjLists[u] != NULL){
	     tmp = G->adjLists[u]->next; //first node of maxnode
	     while(tmp != NULL){
	        if (dist[u] + tmp->weight > dist[tmp->id-1]){
		     dist[tmp->id-1] = dist[u] + tmp->weight;
	        }
		tmp = tmp->next;
	     }
        }
    }
/*
    for (int i = 0; i < n; i++){
//	dist[i] = -INFINITY;
	sptSet[i] = 0;
    }

    int count = 0;
    float max = -INFINITY;
    for (int i = 0; i < G->numVertices; i++){
	if(dist[i] > max){
		max = dist[i];
	}
		printf("dist[%d]: %f\n", i, dist[i]);
    }
    printf("Max: %f", max);
*/
    /*for (int i = 0; i < n; i++){ 
//	u = i;
	u = maxDist(G, n, dist, sptSet);
	sptSet[u] = 1;
	printf("\nmax index %d\n", u);

	Node* tmp;
	if (G->adjLists[u] != NULL){
	     tmp = G->adjLists[u]->next; //first node of maxnode
	     while(tmp != NULL){
	        if (dist[u] + tmp->weight == max){
			printf("u is %d and v is %d sum: %f\n",u, tmp->id, dist[u] + tmp->weight);
			count++;
		}
		tmp = tmp->next;
	     }
	}

    }
    printf("COUNT = %d\n", count);*/
    return dist;
}
/*
int countingFunction(Graph *G){

	//MAYBE TRAVERSE EVERY POSSIBLE PATH OF DAG
    for (int i = 0; i < n; i++){
	dist[i] = -INFINITY;
	sptSet[i] = 0;
    }

    int count = 0;
    float max = -INFINITY;
    for (int i = 0; i < G->numVertices; i++){
	if(dist[i] > max){
		max = dist[i];
	}
		printf("dist[%d]: %f\n", i, dist[i]);
    }
    printf("Max: %f", max);

    for (int i = 0; i < n; i++){ 
//	u = i;
	u = maxDist(G, n, dist, sptSet);
	sptSet[u] = 1;
	printf("\nmax index %d\n", u);

	Node* tmp;
	if (G->adjLists[u] != NULL){
	     tmp = G->adjLists[u]->next; //first node of maxnode
	     while(tmp != NULL){
	        if (dist[u] + tmp->weight <= max){
			dist[
			printf("u is %d and v is %d sum: %f\n",u, tmp->id, dist[u] + tmp->weight);
			count++;
		}
		tmp = tmp->next;
	     }
	}

    }

    printf("COUNT = %d\n", count);

}*/

void DFSVisit(Graph* G, Node* curr, int time, Node* topSort){ //or u is an int
    time = time + 1;
    curr->start = time;
    curr->color = GRAY;
    Node* topSort; 

    Node* adj = curr;
    while (adj != NULL){ //for all edges of curr
	adj = adj->next;
	if (adj->color == WHITE){
	    adj->prev = curr;
	    DFSVisit(G, adj, time, topSort);
	}
	curr->color = BLACK;
	time = time + 1;
	curr->finish = time;
	//adding to topological sort
        topSort->next = topSort;
	topSort = curr;

    }
}

//TODO: fix array/node discourse. is source an int or a node?
//add const globals for colors
//maybe have return value
void DFS(Graph* G, int s, Node* topSort){ 
    Node* curr = (Node)malloc(sizeof(Node));
    topSort = G->adjLists[s]; //source node first
    for (int i = 0; i < G->numVertices; i++){ //initializing and creating LL of vertices
	curr= G->adjLists[i]; //node id
	curr->color = WHITE;
   	curr->prev = NULL;
    }
    int time = 0;
    
    for (int i = 0; i < G->numVertices; i++){
	curr= G->adjLists[i]; //node id
	if(curr->color == WHITE)
		DFSVisit(G, curr, time, topSort); //idk if i want i or curr
	curr = curr->next;
    }
    
    //return head;

}

//GOOOD one
void DFS(Graph* G, int s, int v, int* pathDist, int* count, float* max){

	Node* tmp;
       tmp = G->adjLists[s]->next;
	if (s == v)
		pathDist[s] = 0;
	else{
	    while(tmp != NULL){
		pathDist[v] = pathDist[v] + tmp->weight; 
		DFS(G, tmp, v, pathDist, &count, &max);
		tmp = tmp->next;
	    }
	    if (pathDist[v] == max)
		    count++;
	}
}


//counts all paths from s to v (call for all vertices)
//TODO: if G->adjLists->weight == max
//add up the weight and distances of the paths and then see. 
void CountingFunc(Graph* G, int v){ 
    int n = G->numVertices;
    int* visited = malloc(sizeof(int)* n);
    int* path = malloc(sizeof(int)* n);
    int path_index = 0;

    //init
    for (int i =0 ; i < n; i++)
    {
	visited[i] = 0;
    }
    CountingFuncUtil(s, v, visited, path, path_index);
}


void CountingFuncUtil(int curr, int d, int* visited, int* path, int& path_index){
    visted[curr] = 1;
    G->adjLists[]
    path[path_index] = curr;
    path_index++;

    //loop through adjacency list. add weight to distance. if distance == 20. new path
    if (curr == d){
	for(int i = 0; i < path_index; i++)

    }
	    	

}

//find all paths. if weight == 20 increment
void findPaths(Graph* G, int s, int v, int*count, float* max){
    //int* paths; //malloc
    int* pathDist = malloc(sizeof(int)*N); //ig

    pathDist[s] = 0;
    pathDist[s] = G->adjLists[s]->weight;

    DFS(G, s, v, pathDist, &count, &max);

}

Graph* initGraph(int N, int M){

    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->numVertices = N;
    G->numEdges = M;

    G->adjLists = (Node**)malloc(sizeof(Node*)*N);
	
    for (int i = 0; i < N; i++){
	if (i == s){
    	    Node* source = malloc(sizeof(Node));
    	    source->id = s;
    	    source->next = NULL;
	    source->weight = 0;
	    G->adjLists[s] = source;
	}
	else{
            G->adjLists[i] = NULL;
	}
    }
    return G;
}


//TODO: change filename
Graph* getGraph(const char* filename){
	int N, M;
	FILE *f = fopen(filename, "r"); //change to filename final 
	
	if (f == NULL)
		exit(EXIT_FAILURE);
	
	fseek(f, 0, SEEK_END);
	int numBytes = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	int* buffer = malloc(numBytes*4);
	fscanf(f, "%d ", &buffer[0]);
	fscanf(f, "%d", &buffer[2]);
	N = buffer[0];
	M = buffer[2];

	Graph* G = initGraph(N, M);
	int i = 0;

	while (fscanf(f, "%d", &buffer[i]) != EOF){
	    Node* v = malloc(sizeof(Node));
	    Node* u = malloc(sizeof(Node));
	    fscanf(f, "%d", &buffer[i+2]);
	    fscanf(f, "%d", &buffer[i+4]);
	    u->id = buffer[i];
	    u->next = NULL;
	    v->id = buffer[i+2];
	    v->weight = (float)buffer[i+4];
	    v->next = NULL;

	    i+=5;
	    if (G->adjLists[u->id-1] != NULL){
		v->next = G->adjLists[u->id-1]->next;
		G->adjLists[u->id-1]->next = v;
	    }
	    else{ //new vertex
		v->next = NULL;
		u->next = v;
	    	G->adjLists[u->id-1] = u;
	    }
	 }
	
	fclose(f);

	//free(tmp_u);
	//free(tmp_v);
	free(buffer);
	
	return G;
}


void output(const char* filename, float max, int count){

	FILE *f = fopen(filename, "w");
	if (f == NULL)
		exit(EXIT_FAILURE);
	fprintf(f, "max: %f, count: %d\n", max, count);
	fclose(f);
}
//TODO:
int main(int argc, char* argv[]){

	float max = -INFINITY;
	Graph *G = getGraph(argv[1]);	
        float* dist = dijkstra(G);	
	int count = 0;
	//float max = -INFINITY;
	
	for (int i = 0; i < G->numVertices; i++){
//	    if(dist[i] > max)
//		    max = dist[i];
	    printf("dist[%d]: %f\n",i+1, dist[i]);
	}
	for (int v = 0; v < G->numVertices; v++){
		findPaths(G, s, v, &count, &max);
			}
	//I THINK I NEED A SEPARATE THING FOR part 2.
//	printf("Max: %f\n", max);

//	int count = countPaths(G, max);
//	printf("count = %d", count);
//	output(argv[2], max, count);

	//free memory
	//TODO:fix this
	/*for (int i = 0; i < N; i++){
	    free(G[i]);
	}*/
//	free(G);
//	free(sorted);
	//more free stuff
}

