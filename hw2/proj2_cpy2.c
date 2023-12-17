#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define s 0 //is 1 but formatting nonsense
//enum Colors{WHITE, GRAY, BLACK};

typedef struct node{
    int color;
    int id; //id
    //long dist; //value while sorting
    struct node* next;
    struct node* prev;
    float weight;
    int start;
    int finish;
}Node;

typedef struct graph{
    int numVertices;
    Node** adjLists;
    int numEdges;
}Graph;

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

int maxDist(int N, int* dist, int *sptSet){
    int max = -INFINITY;
    int max_ind;

    for (int i = 0; i < N; i++){
	if (sptSet[i] == false && dist[i] >=max)
		max = dist[v];
		max_index = v;
    }
    return max_index;
}

int dijkstra(Graph* G, Queue* Q){
    
    float maxDist;
    int n = G->numVertices;
    
    float dist[n];
    int sptSet[n];

    int prev[n], visited[n];
    int count = 1;
    int nextnode = 0;
    
    for (int i = 0; i < n; i++){
	dist[i] = -INFINITY;
	sptSet[i] = false;
    }
    
    //init 
    for (int i = 0; i < n; i++){
    //while (curr != NULL){
	//dist[i] = G->adjLists[i]->weight;
	prev[i] = s;
	visited[i] = 0;
	printf("dist: %f\n", dist[i]);
    }

    dist[s] = 0;
    //set<int> S;
    //list<int> Q;
    //
    int S[n];
    Node* SLL = malloc(sizeof(Node));
    visited[s] = 1;
    count = 1;

    Node* tmp = G->adjLists[s];
    enqueue(Q, s);
    //enqueue neighbors of source.
    while(tmp->id != NULL){
    //TODO: look at article. iterate through neighbors of each node. (whole array list)
    //if not in queue, enqueue. then when dequeued and used. add to set. 
	if (!q_contains(Q, tmp->id)){
	    enqueue(Q, tmp->id);
	}
	tmp = tmp->next;
    }
    //if (!q_contains(Q, node)){
//	enqueue(Q, v->id);
  //  }
    //queue ll
    //insert at end
  //  for (int u = 0; u < n; u++){
//	enqueue(Q, u);
  //  }
    for (int count = 0; i < n-1; i++){
    //while(Q->front != NULL){
    //while (count < n -1){
        //maxDist = -INFINITY;
	int u = maxDist(distance, sptSet);
	sptSet[u] = true;

//    	int i = dequeue(Q);
//	visited[i] = 1;
	//will enque neighbors of just dequeud one
	Node* tmp = G->adjLists[i];
    	while(tmp->id != NULL){
	    if (!q_contains(Q, tmp->id) && visited[tmp->id] == 0){
	        enqueue(Q, tmp->id);
	    }
	    tmp = tmp->next;
    	}	
    /*for (int i = 1; i < n; i++)
	    if (dist[i] > dist[i] && !visited[i]){ //if dist 0 > -inf
		printf("dist[i: %f at %d\n", dist[i], i);
	    	maxDist = dist[i];
	    	nextnode = i;
	    }*/

	//make a queue.... goddamnit
	
	Node* tmp = G->adjLists[i]->next; //
	for (int v = 0; v < n; v++){
	//while(tmp != NULL){
	    if (dist[u] + tmp->weight > dist[v]; 
	    if (dist[i] + tmp->weight > dist[tmp->id]){
//		dist[tmp->id] = dist[i] + tmp->weight;
//	    	prev[tmp->id] = i;
	    }


	}

  /*  
    	visited[nextnode] = 1;
	//printf("nextnode: %d\n", nextnode);
    	
	Node* v = G->adjLists[nextnode]->next; //first neighbor
        while(v != NULL){
	    if (!visited[i]){
	    	if (maxDist + v->weight > dist[i]) {
	            dist[i] = maxDist + v->weight;
		    prev[i] = nextnode;
	    	}
	    }
	    v = v->next;
         }*/
//	 count++;
    }

    int m = max(dist);
    return m;
}

/*Node* createNode(int v){
    Node* new = malloc(sizeof(Node));
    new->id = v;
    new->next = NULL;
    return new;
}*/

/*void addEdge(Graph* G, int u,int v){
    Node* v = createNode;
    G->adjLists[u-1]->next = v;
  
  //  Node* new = createNode(v-1);
    //new->next = G->adjLists[u-1];
    G->adjLists[u-1] = new;

}*/
Graph* initGraph(int N, int M){

    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->numVertices = N;
    G->numEdges = M

    G->adjLists = (Node**)malloc(sizeof(Node*)*N);
	
    for (int i = 0; i < N; i++){
	if (i == s){
    	    Node* source = malloc(sizeof(Node));
    	    source->id = s;
    	    source->next = NULL;
	    source->weight = 0;
	    G->adjLists[s] = source;
	}
	else
            G->adjLists[i] = NULL;
    }
    return G;
}


//TODO: change filename
Graph* getGraph(const char* filename, Queue *Q){
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

	Node* tmp_u = malloc(sizeof(Node));

	int i = 0;

	while (fscanf(f, "%d", &buffer[i]) != EOF){
	    Node* v = malloc(sizeof(Node));
	    
	    fscanf(f, "%d", &buffer[i+2]);
	    fscanf(f, "%d", &buffer[i+4]);
	    tmp_u->id = buffer[i];
	    v->id = buffer[i+2];
	    v->weight = (float)buffer[i+4];

	    //printf("u %d, v %d, w %f\n", u->id, v->id, v->weight);
	    i+=5;

	    if (G->adjLists[tmp_u->id-1] != NULL){
	//	Node* v = malloc(sizeof(Node));
	//	v = tmp_v;
		v->next = G->adjLists[tmp_u->id-1]->next;
		G->adjLists[tmp_u->id-1]->next = v;
		printf("probably print this 3 times??\n");
	    }
	    else{
	//	Node* v = malloc(sizeof(Node));
		Node* u = malloc(sizeof(Node));
		u = tmp_u;
	    	G->adjLists[u->id-1] = u;
		G->adjLists[u->id-1]->next = v;
		v->next = NULL;
		printf("print this 4 times\n");
	    }
	    //doesn't contain value. enqueue
	   /* if (!q_contains(Q, v->id)){
		enqueue(Q, v->id);
	    }*/
	 }
	
	
	fclose(f);

	free(tmp_u);
	//free(tmp_v);
	free(buffer);
	
	return G;
}

void output(const char* filename, int max, int count){

	FILE *f = fopen(filename, "w");
	if (f == NULL)
		exit(EXIT_FAILURE);

	//TODO: change to fputs
	fputc(/*"The max is %d",*/ max, f);
	fputc(/*"The count is: %d",*/ count, f);
	fclose(f);
}
//TODO:
int main(int argc, char* argv[]){

	//const char* filename = argv[1];
	//1. file i/o. first line is n m
	int M;
	Queue* Q = malloc(sizeof(Queue));
	Graph *G = getGraph(argv[1], Q);	
//	float* dist = malloc(sizeof(int)*G->numVertices);
	printf("First %d\n", Q->front->id);	
	//3. init dist, prev and source dist 
        int count = dijkstra(G, Q);	
//	int max = longestPath(G, sorted, dist);
//	int count = countLongest(dist, G->numVertices, max);

	//output information to file. 
	
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

