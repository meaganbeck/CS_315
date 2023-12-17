#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define s 0


typedef struct node{
    int id; //id
    struct node* next;
    struct node* prev;
    float weight;
}Node;

typedef struct graph{
    int numVertices;
    Node** adjLists;
    int numEdges;
}Graph;
/*
typedef struct queue{
    Node* front;
    Node* back;
}Queue;

void enqueue(Queue* Q, int id){
    Node* tmp = malloc(sizeof(Node));
    tmp->id = id;
    tmp->next = NULL;

    if (Q->back == NULL){
	Q->front = tmp;
	Q->back = tmp;
	return;
    }
    Q->back->next = tmp;
    Q->back = tmp;
}

int dequeue(Queue* Q){

    int ret = Q->front->id;
    if (Q->front == NULL){
	return 0;
    }
    Node* tmp = Q->front;
    Q->front = Q->front->next;

    if (Q->front == NULL)
	    Q->back = NULL;
    free(tmp);
    return ret;
}

int q_contains(Queue* Q, int v){
    Node* curr = Q->front;
    while(curr != NULL){
	if(curr->id == v){
	    return 1;
	}
	curr = curr->next;
    }
    return 0;

}
*/
int maxDist(int prev, Graph* G, int N, float* dist, int *sptSet){
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
    
    //while(
    int prev = s;

    int u;
    for (int i = 0; i < n; i++){ //
	u = maxDist(prev, G, n, dist, sptSet);
	prev = u;
	sptSet[u] = 1;
	printf("\nmax index %d\n", u);

	Node* tmp;
	if (G->adjLists[u] != NULL){
	     tmp = G->adjLists[u]->next; //first node of maxnode
	     while(tmp != NULL){
	        if (dist[u] + tmp->weight > dist[tmp->id]){
		     dist[tmp->id-1] = dist[u] + tmp->weight;
	        }
		tmp = tmp->next;
	     }
    }

    int count = 0;
    float max = -INFINITY;
    for (int i = 0; i < G->numVertices; i++){
	if(dist[i] > max)
		max = dist[i];
	printf("dist[%d]: %f\n",i+1, dist[i]);
    }
    for (int i = 0; i < n; i++){ 
	u = i;
	//u = maxDist(prev, G, n, dist, sptSet);
	prev = u;
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
    
    printf("COUNT = %d", count);
    return dist;
}

int countPaths(Graph* G, float max){
    
    int n = G->numVertices;
    int m = (int)max;
    float* dist = malloc(sizeof(float)*n);
    int* sptSet = malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++){
	dist[i] = -INFINITY;
	sptSet[i] = 0;
    }
    //init 
    dist[s] = 0;
    int count = 0;
    int prev = s;
    printf("%d\n", m);
    printf("%f\n", max);

    int u;
    for (int i = 0; i < n; i++){ //
	u = maxDist(prev, G, n, dist, sptSet);
	prev = u;
	sptSet[u] = 1;

	Node* tmp;
	if (G->adjLists[u] != NULL){
	     tmp = G->adjLists[u]->next; //first node of maxnode
	     while(tmp != NULL){
	        if (dist[u] + tmp->weight > dist[tmp->id-1]){
	//        if (!sptSet[tmp->id] && tmp->weight && dist[u] != -INFINITY && dist[u] + tmp->weight > dist[tmp->id]){
		     dist[tmp->id-1] = dist[u] + tmp->weight;
	        }
	        if (dist[u] + tmp->weight == m){
			printf("u is %d and v is %d sum: %f\n",u, tmp->id, dist[u] + tmp->weight);
			count++;
		}
		tmp = tmp->next;
	     }
	}
    }
    return count;
}
/*
int countPaths(Graph* G, int u, int v, int k){
    int count = 0
    
    if (k == 0 && u == v)
	    return 1;
    Node* tmp = G->adjLists[u];
    while(tmp->id != v && tmp != NULL){
	    tmp = tmp->next;
    if (k == 1 && tmp->id)
	    return 1;
    if (k <= 0)
	    return 0;
    while (tmp != NULL){
	if (tmp->id 
    }
}*/

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
	//const char* filename = "inSample1.txt";
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
	printf("n %d, m %d\n", N, M);

	Graph* G = initGraph(N, M);

	//Node* tmp_u = malloc(sizeof(Node));

	int i = 0;

	while (fscanf(f, "%d", &buffer[i]) != EOF){
	    Node* v = malloc(sizeof(Node));
	    Node* u = malloc(sizeof(Node));
	    fscanf(f, "%d", &buffer[i+2]);
	    fscanf(f, "%d", &buffer[i+4]);
	    u->id = buffer[i];
	    //tmp_u->id = buffer[i];
	    //tmp_u->next = NULL;
	    u->next = NULL;
	    v->id = buffer[i+2];
	    v->weight = (float)buffer[i+4];
	    v->next = NULL;

	    i+=5;
            printf("%d %d %f\n", u->id, v->id, v->weight);
	    if (G->adjLists[u->id-1] != NULL){
		v->next = G->adjLists[u->id-1]->next;
		G->adjLists[u->id-1]->next = v;
		printf("probably print this 3 times??\n");
	    }
	    else{ //new vertex
	//	Node* u = malloc(sizeof(Node));
	//	u = tmp_u;
		v->next = NULL;
		u->next = v;
	    	G->adjLists[u->id-1] = u;
		//G->adjLists[u->id-1]->next = v;
		printf("print this 4 times\n");
	    }
	 }
	
	
	fclose(f);

	//free(tmp_u);
	//free(tmp_v);
	free(buffer);
	
	return G;
}


void output(const char* filename, int max, int count){

	FILE *f = fopen(filename, "w");
	if (f == NULL)
		exit(EXIT_FAILURE);
	fprintf(f, "max: %d, count: %d\n", max, count);
	fclose(f);
}
//TODO:
int main(int argc, char* argv[]){

	float max = -INFINITY;
	Graph *G = getGraph(argv[1]);	
        float* dist = dijkstra(G);	
	
	//float max = -INFINITY;
	
/*	for (int i = 0; i < G->numVertices; i++){
	    if(dist[i] > max)
		    max = dist[i];
	    printf("dist[%d]: %f\n",i+1, dist[i]);
	}
	printf("Max: %f\n", max);
*/
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

