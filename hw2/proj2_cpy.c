#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WHITE
#define GRAY
#define BLACK

typedef struct node{
    char* color;
    int data
    long dist;
    Node* next;
    Node* prev;
    int start;
    int finish;
}Node;

/*typedef struct edge{
    Node* start;
    long weight;
    Node* end;

}Edge;
*/
typedef struct graph{
    int numVertices;
    Node** adjLists;
}Graph;

/*
int maxDistance(int dist[], bool sptSet[]){
	//int max = INT_MAX, max_index;
	int max = -INT_MAX;//probably this cause finding max
	int max_index;
	for (int j = 0; j < N; j++){
	    if (sptSet[v] == false && dist[v] >= max)
		    max = dist[j], max_index = v;
	}
	return max_index;
}*/
/*
void relax(Node* u, Node* v, Edge* m){
	long val = u.dist + m.weight; //assuming m.start = u and m.end = v;
	long val = u.dist + weight(u,v);
	if(val > v.dist){
		v.dist = val;
		v.prev = u;
		decreasekey(H,v);
	}
}*/
void init(Graph* G, int dist[], int prev[]){
    for (int i = 0; i < G->numVertices; i++){
	dist[i] = -INT_MAX; //or -INFINITY
	prev[i] = NULL;
    }
}

void relax(int u, int v, int m){
	int val = dist[u] + m;
	if (val > dist[v]){
	    dist[v] = val;
	    prev[v] = u;
//	    decreasekey(H,v);
	}

}
//TODO: likely memory stuff wiht all the nodes im creating
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

int countLongest(int** dist, int N){
	int count;
	int max = i - 1;
	for (int i = 1; i < N; i++){
	    if (dist[i] > dist[i-1])
		max = dist[i];
	}
	for (int i = 0; i < N; i++){
	    if (dist[i] == max)
		    count++;
	}
	return count;
}

void longestPath(Graph* G,Node* topSort){
	Node* ordered = topSort;
	//bool visited[G->numVertices];
	//for (int i = 0; i < G->numVertices; i++){
	  //  visited[i] = false;
	//}
	init(G, dist, prev);
	dist[s] = 0;
	while (ordered!= NULL){ //currnode in graph. loop through nodes in order
	//or a for i loop
	    int i = ordered->data; //index for the array of nodes
	    
	    Node* u = G->adjLists[i]; //this is the vertex
	    Node* v = u->next;
	    if (dist[i] != -INFINITY){
		while (v != NULL){ //iterates through adjacent nodes
		    if (dist[v->data] < dist[u->data] + G->adjLists[i].weight)
		    	dist[v->data] = dist[u->data] + G->adjLists[i].weight;
		    v = v->next; //go to next neightbor node
		}
	    }
	    ordered = ordered->next;
	}

	//TODO:
	//find largest value in dist and print

}
//TODO: perform topological sort via DFS
//dfs sorts by time into ll
Node* topologicalSort(Graph* G){ //topological sort/
    Node* topSort = (Node*)malloc(sizeof(Node)); 
    DFS(G, topSort); //have finishing times for all. now sort
  
    //are in reverse order of their finishing time
    /*
    Node* head = (Node*)malloc(sizeof(Node)); 
    int times[G->numVertices];
    for (int i = 0; i < G->numVertices; i++){
    	Node* curr = G->adjLists[i];
	times[i] = curr->finish; 
    }

    bool visited;
    int *orderArr = (int*)malloc(sizeof(int)*N);
    for (int i = 0; i < N; i++){
		
    }*/
    return topSort;



}

//TODO: a thing
void update(){

}

Graph* initGraph(int N){

    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->numVertices = N;
    G->adjLists = (Node**)malloc(sizeof(Node*)*N);
	
    for (int i = 0; i < N; i++){
        G->adjLists[i] = NULL;
    }
    return G;
}

void addEdge(Graph* G, int s, int u){
    //for later with file i/o
    //adds edge from s to u
    Node* new = (Node*)malloc(sizeof(Node));
    new->data = u;
    new->next = G->adjLists[s]; //source node
    G->adjLists[s] = new;
}
//TODO:
int main(int argc, char* argv[]){

	int count = 0;
	//1. file i/o. first line is n m
	//second line and on is i j w
	//i is start, j is end, w is w[i,j]
	
	Graph* G = initGraph(N);
	
	//2. file i/o store in graph. 
	//STORE weight with the node so curr->weight is good and valid
	

	int dist[N]; //for i in 0-N will hold distance from src to i.
	int prev[N];
	
	//but not this at all
	
	int N = argv[2]; //number of nodes
	int M = argv[3]; //number of edges
		
	//3. init dist, prev and source dist 
	//init(dist, prev); //all set to 0
	//dist holds the distance information for each one. 0-N. I'll figure out how to order them later. and walk through stuff. 

	Node* sorted = topologicalSort(G, N); //topological sort

	
	longestPath(G, sorted);

	int count = countLongest(dist, N);

	//output information to file. 
	
	//free memory
	for (int i = 0; i < N; i++){
	    free(G[i]);
	}
	free(G);
}

