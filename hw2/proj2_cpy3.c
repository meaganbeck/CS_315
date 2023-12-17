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
    for (int i = 0; i < N; i++){
	if (sptSet[i] == 0 && dist[i] >=max){
		max = dist[i];
		max_ind = i;
	}
    }
    return max_ind;
}

float dijkstra(Graph* G){
    
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
    float max = -INFINITY;
    for (int i = 0; i < G->numVertices; i++){
	if(dist[i] > max){
		max = dist[i];
	}
    }
    return max;
}

void DFS(Graph* G, int src, int v, int currDist, int *count, float max){
       int c;
       Node* tmp;
       if (G->adjLists[src] != NULL){

          tmp = G->adjLists[src]->next;
	   if (src == v){
		if (currDist == max){
		    (*count)++;
		}
	   }
 	   else{
	       while(tmp != NULL){
		  //currDist += tmp->weight;
		  printf("curr dist from %d to %d = %d\n",src, tmp->id-1, currDist);
		  
		  DFS(G, tmp->id-1, v, currDist += tmp->weight, count, max);
		  if (currDist == max && tmp->id-1 == v){
		      printf("we got one\n");
		      (*count)++;
		      //if (tmp != NULL)
		      	//currDist -=tmp->weight;
		  }
		  currDist -= tmp->weight;
		  //tmp = tmp->next;
		  //currDist -=tmp->weight;
		  tmp = tmp->next;
	    }
	}
       }
}



//find all paths. if weight == 20 increment
int findPaths(Graph* G, int src, int v, float max){
     int pathDist[G->numVertices]; //5
     for (int i = 0; i < G->numVertices; i++){
	pathDist[i] = 0;
     }
     int currDist = 0;
    
    int count = 0;
    int *cp = &count;
 	DFS(G, src, v, currDist, cp, max);
       return *cp; 
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
	    u->weight = 0;
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
        max = dijkstra(G);	
	int count = 0;
	

	//count = count + findPaths(G, s, 4, max);
	for (int v = 0; v < G->numVertices; v++){

		printf("new target is %d\n", v);
		if (v != s)
		count = count + findPaths(G, s, v, max);
	}
	printf("count = %d", count);
	output(argv[2], max, count);

	//free memory
	//TODO:fix this
	/*for (int i = 0; i < N; i++){
	    free(G[i]);
	}*/
//	free(G);
//	free(sorted);
	//more free stuff
}

