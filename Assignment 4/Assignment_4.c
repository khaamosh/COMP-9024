#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include <string.h> /* memset */
#include <unistd.h>

//structure for the bus stops
typedef struct Stop
{
	int stop_code;
	char *stop_name;
	int distance;
	
	struct Stop *prev;
	struct Stop *next;
}Stop;
//###################################
//helper function for creation of new stop node
Stop *newStopNode(int sc,char *sn,int d)
{
	Stop *new;
	new = malloc(sizeof(Stop));
	assert(new != NULL);
	
	new->stop_code = sc;
	new->stop_name = sn;
	new->distance = d;
	
	new->prev = new->next = NULL;
	
	return new;
}

//#######################################

//data type for doubly linked lists
typedef struct StopList{
	int  size;      // count of items in list
	Stop *first; // first node in list
	Stop *last;  // last node in list
} StopList;

// create a new empty DLList
StopList *newStopList()
{
	StopList *L;

	L = malloc(sizeof (struct StopList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}
//#####################################

//structure of the bus names 

typedef struct Bus_Name
{
	int bus_code;
	struct Bus_Name *next;
	
}Bus_Name ;

//helper function for the new bus node

Bus_Name *newBus(int x)
{
	Bus_Name *new;
	new = malloc(sizeof(Bus_Name));
	
	assert(new != NULL);
	new->bus_code = x;
	new->next = NULL;
	
	return new;
	
}

//#####################################


//data type for doubly linked lists
typedef struct BusList{
	//int  size;      // count of items in list
	Bus_Name *first; 
} BusList;


// create a new empty bus list

BusList *newBusList()
{
	BusList *L;

	L = malloc(sizeof (struct BusList));
	assert (L != NULL);
	//L->size = 0;
	L->first = NULL;
	//L->last = NULL;
	return L;
}

//#####################################

// structure of the result for the adj list

typedef struct result
{
	StopList *adjList;
	int max;
	
}result;

//structure used for storing the names of the stops

typedef struct stopNames
{
	//stop names read from the file
	char stopNames[20];
}stopNames;

//**********************************

//global parameters used throughout the program

StopList *adj_List[10000];   //adjacent list 
StopList *rev_List[10000];  //reverse list
Bus_Name *bus_List[10000]; // bus list  

int vertex_max[10000];    // maximum of the vertex
int vL;                  // vertex list

stopNames stopList[10000];  // stop list of the matrix
int has_path[10000];        // the path exists for the matrix    

int path_len;               // the length of the path


//*************************************

//structure of the bus-routes

typedef struct Bus_Routes
{
	int stops[10000];
	int size;
}Bus_Routes;

//for the bus routes read from the file.
Bus_Routes bus_routes[10000];

//############################################

//structure for the queue used for question 3 bfs

typedef struct Queue
{
	int top,end, size;
	int capacity;
	int *elements;
};

// helper function for creation of the new empty queue
struct Queue *newQueue(int capacity)
{
	struct Queue *q = ( struct Queue*) malloc(sizeof(struct Queue));
	
	q->top = q->size = 0;
	q->end = capacity -1;
	
	q->capacity = capacity;
	
	q->elements = (int *) malloc(q->capacity *sizeof(int));
	
	return q;
}


// helper function which checks whether the queue is empty

//Complexity :: O(1)

int qEmpty(struct Queue* q)
{
	return (q->size == 0);
}

//function to remove values from the queue

//Complexity :: O(1)

int de_Queue(struct Queue* q)
{
	int val;
	
	if(qEmpty(q))
	{
		return INT_MIN;
	}
	
	val = q->elements[q->top];
	
	q->top = ( q->top +1)%q->capacity;
	
	q->size = q->size -1;
	
	return val;
	
}

// function to add values to the queue

//Complexity :: O(1)

void en_q(struct Queue *q,int val)
{
	q->end = (q->end+1) % q->capacity;
	q->elements[q->end] = val;
	
	q->size = q->size +1;
	
	//printf("Added the value to the Q%d\n",val);
}

//#############################################

//function that is responsible for the dfs of the matrix
//Complexity :: O(V+E)

void dfs(int max,char *vis,int curr,int flag)
{
	//printf("\n+++++++++++++INside dfs++++++\n");
	//printf("\n%d",curr);
	vis[curr] = '1' ;
	
	int itr,i;
	
	StopList *l;
	Stop *node;
	
	//printf("\n%d\t",curr);
	//printf()
	
	if(flag == 1)
	{
		l = adj_List[curr];
	}
	else
	{
		if (flag == 2)
		{
			l = rev_List[curr];
		}
		
	}
	
	
	if(l!=NULL)
	{
		node = l->first;
		
		if(node !=NULL)
		{
		//setting the current to visited
		
			while(node!=NULL)
			{
				curr = node->stop_code;
				if( vis[curr] == '0')
				{
					if (flag == 1)
					{
						dfs(max,vis,curr,1);
					}
					else
					{
						dfs(max,vis,curr,2);
					}
					
				}
		
				node = node->next;
			}
		}
	}
	
	
}

//######################################


// Strongly connected helper function

//Complexity :: O(V+E)

int StronglyConnected(int max)
{
	//dynamic memory allocation of visited matrix
	char *visited,ch;
	visited=(char *)malloc(max+1*sizeof(char));
	
	memset(visited,'0',max+1);
	int i;
	
	/*	
	printf("\nVisited matrix before\n");
	for (i=0;i<=max;i++)
	{
		printf("%c\t",visited[i]);
	}
	
	*/
	
	dfs(max,visited,0,1);
	
	//now checking if all the nodes were visited.
	
	//printf("\nVisited matrix after\n");
	
	for (i=0;i<=max;i++)
	{
		ch = visited[i];
		//printf("%c\t",ch);
		
		if( ch == '0')
		{	
		    //printf("Unreachable stop encountered");
			return 0;
			//break;
		}
			
	}
	
	//using memeset for setting the default values
	memset(visited,'0',max+1);
	
	//now checking for transpose of the matrix
	dfs(max,visited,0,2);
	
	
	//printf("\nVisited matrix after-2\n");
	
	for (i=0;i<=max;i++)
	{
		ch = visited[i];
		//printf("%c\t",ch);
		
		
		if( ch == '0')
		{	
		    //printf("Unreachable stop encountered");
			return 0;
			//break;
		}
		
			
	}

}

//###################################
//adj_construction

// helper function responsible for creation of adjacency list for the graph
// it also returns the count of the matrix vertixes  

//Complexity :: O(V+E) 

int  adj_construction()
{
	
	//int adjMatrix[100][100];
	
	//adjacency list
	
	
	//validation of the stop code
	int adj_valid[10000];
	
	struct result res;
	
	char dash,colon;
	
	int input,first_stop,next_stop,dist,max,i,j ;
	
	max = 0;
	
	FILE *fp;
	
	fp =fopen("r.txt","r");
	int curr_list = 0,l=0,temp_curr;
	
	
	//memset( adjMatrix, sizeof( adjMatrix ), -1 );
	
	//printf("\n#########################\n");
	
	while( (input = fscanf(fp,"%d%c%d%c%d",&first_stop,&dash,&next_stop,&colon,&dist) ) !=EOF )
	{
		Stop *new_node,*new_node_rev ;
		StopList *temp,*temp_rev;
		
		
		if(input!=0)
		{
			//adjMatrix[first_stop][next_stop] = dist;
			
			
			new_node = newStopNode(next_stop,NULL,dist);
			new_node_rev  = newStopNode(first_stop,NULL,dist);
			
			//printf("%d\t%d\n",first_stop,next_stop);
			
			temp = adj_List[first_stop] ;
			temp_rev = rev_List[next_stop];
			
			//check if this stop was encountered first, if new then
			if (temp == NULL)
			{
				StopList *sl = newStopList();
				sl->first = sl->last = new_node;
				
				adj_List[first_stop]= sl;
			}
			else
			{
				temp->last->next = new_node;
				new_node->prev = temp->last;
				temp->last = new_node;
			}
			
			//for the transpose of the matrix
			if (temp_rev == NULL)
			{
				StopList *sl_rev = newStopList();
				sl_rev->first = sl_rev->last = new_node_rev;
				
				rev_List[next_stop]= sl_rev;
			}
			else
			{
				temp_rev->last->next = new_node_rev;
				new_node_rev->prev = temp_rev->last;
				temp_rev->last = new_node_rev;
			}
			
			if ( first_stop > next_stop)
			{
				if(first_stop > max)
				{	
					max = first_stop;	
				}
			
			}
			else
			{
				if ( next_stop > first_stop)
				{
					if(next_stop > max)
					{
						max = next_stop;
					}
				}
			
			}
		}	
	}
		
	//printf("\n The max is : %d", max);
	
	//res.adjList = adj_List;
	//res.max = curr_list;
	
	return max;
}

//#######################################

//helper function used for checking path ways to the vertices

// Complexity :: O(V+E)

void fill_vertex(char *vis,int val)
{
	//printf("\nInside fill vertex\n");
	
	int curr;
	
	vis[val] = '1';
	
	StopList *l;
	Stop *node;
	
	l = adj_List[val];
	
	if(l!=NULL)
	{
		node = l->first;
		
		if(node !=NULL)
		{
		
			while(node!=NULL)
			{
				curr = node->stop_code;
				if( vis[curr] == '0')
				{
					fill_vertex(vis,curr);
				}
				node = node->next;
			}
	}
	
	//printf("\ninside vertex max : %d",val);
	vertex_max[vL] = val;
	vL++;

	}
}

//############################################

//This is the BFS function which performs the same,
//the name of the function was kept as dfs_max for the keeping the consistent flow during creation of program

//Complexity :: O(V+E)

void dfs_max(char *vis,int val)
{
	//printf("\nInside dfs_max\n");
	
	int curr;
	
	vis[val] = '1';
	
	printf("%s, ",stopList[val]);
	//printf("%d, ",val);
	
	StopList *l;
	Stop *node;
	
	l = rev_List[val];
	
	if(l!=NULL)
	{
		node = l->first;
		
		if(node !=NULL)
		{
		
			while(node!=NULL)
			{
				curr = node->stop_code;
				if( vis[curr] == '0')
				{
					dfs_max(vis,curr);
				}
				node = node->next;
			}
	}
	
	}
}

//######################################

//helper function that is being used for the max strongly connected vertex

//Complexity :: O(V+E)

void MaxStrongly(int max)
{
	char *visited,ch;
	visited=(char *)malloc(max+1*sizeof(char));
	
	memset(visited,'0',max+1);
	
	int i;
	Stop *node;
	
	vL= 0;
	
	int cnt =1;
	
	//vertex_length = 0;
	
	/*
	printf("\n##Visited Matrix before the fill vertex \n");
	
	for (i=0;i<=max;i++)
	{
		ch = visited[i];
		printf("%c\t",ch);
	
	}
	
	*/
	
	for (i=0;i<=max;i++)
	{
		if(visited[i] !='1')
		{
			node = adj_List[i]->first;
			fill_vertex(visited,node->stop_code);
		}
	}
	
	
	/*
	printf("\n##Visited matrix after-fill vertex\n");
	
	for (i=0;i<=max;i++)
	{
		ch = visited[i];
		printf("%c\t",ch);
		
		
		if( ch == '0')
		{	
		    printf("Unreachable stop encountered");
			//return 0;
			break;
		}
	
	}
	
	
	
	printf("\n##Vertex information sent here\n");
	
	for (i=0;i<=max;i++)
	{
		printf("%d\t",vertex_max[i]);
	}
	
	*/
	
	//setting the visited vertex as false
	memset(visited,'0',max+1);
	
	//printf("\n--------\n");
	
	for (i=vL;i>=0;i--)
	{
		if(visited[i] == '0')
		{
			printf("\nStrongly Connected Component : %d\n",cnt);
			cnt++;
			
			dfs_max(visited,vertex_max[i]);
			printf("\n");
		}
	}
}

//########################################

//helper function for reading and storing the names of the stops

//Complexity ;; O(N) where N are the number of stops

void stop_names(char *stops)
{
	FILE *fp ;
	fp = fopen(stops,"r");
	
	char colon;
	int code;
	int input;
	
	struct stopNames names;
	
	while( (input = fscanf(fp,"%d%c%[^\n]%*c",&code,&colon,&names.stopNames) ) !=EOF )
	{
		//names.stopNames = sn;
		//printf("\n%d\t%s",code,names.stopNames);
		stopList[code] = names;
	}
	
	
}

//########################################

//helper function that takes into account for the vertex that are reachable from the source


void reachable(int max,char *s)
{
	//printf("\nInside-Reachable\n");
	int first =0 ;
	
	char *visited,ch;
	
	visited=(char *)malloc(max+1*sizeof(char));
	
	//int *queue,i,curr,sc,cmp;
	
	int i,curr,sc,cmp;
	
	struct Queue *queue;
	
	//queue = (int*)malloc(max+1*(sizeof(int)));
	
	queue = newQueue(10000);
	
	int qu_cnt=0,vis_cnt=0,li_cnt;
	
	/*
	for (i=0;i<=max;i++)
	{
		queue[i] = -1;
	}
	
	*/
	
	// the utility function for setting the visited matrix default value
	
	memset(visited,'0',max+1);
	
	//setting the visited matrix value to True here
	
	for(i=0;i<=max;i++)
	{
		cmp = strcmp(stopList[i].stopNames, s);
		
		if(cmp == 0 )
		{
			li_cnt = i;
			break;
		}
	}
	
	
	//put this counter inside the queue;
	//queue[qu_cnt] = adj_List[li_cnt]->first->stop_code;
	
	//printf("$-%d , ",adj_List[li_cnt]->first->stop_code);
	li_cnt = li_cnt-1;
	
	en_q(queue,adj_List[li_cnt]->first->stop_code);
	
	visited[adj_List[li_cnt]->first->stop_code] = '1';
	
	//printf("%d",queue[0]);
	
	//qu_cnt++;
	//li_cnt++;
	//vis_cnt++;
	
	//printf("QS->%d",queue->size);
	
	while(queue->size>=0)
	{
		
		//sc = queue[qu_cnt];
		
		sc = de_Queue(queue);
		//qu_cnt++;
		
		if(sc <0)
		{
			break;
		}
		
		//printing the variable here
		//printf("Queue va - %d,\n",sc);	
		
		if (first == 0)
		{
			printf("\nThe stops reachable from %s :",stopList[sc].stopNames);
			printf("\n");
			first =1;	
		}
		else
		{
			printf("%s , ", stopList[sc].stopNames);	
		}
		
		
		//printf("%s, ",stopList[sc].stopNames);
		//stopList[code] = names;
		
		StopList *l;
		Stop *node;
	
		l = adj_List[sc];
	
	
		if(l!=NULL)
		{
			node = l->first;
		
			if(node !=NULL)
			{
				while(node!=NULL)
				{
					curr = node->stop_code;
					
					if( visited[curr] == '0')
					{
						
						visited[curr] = '1';
						//queue[qu_cnt] = curr;
						//adding elements to the queue
						//printf("Adding %d ,\n",curr);
						
						en_q(queue,curr);
					}
					
					node = node->next;
				}
			}
		}
		
		li_cnt++;
		//qu_cnt++;
	}
	
	//printf("Queue count %d",queue[qu_cnt]);
}


//code for the heap implementation via the Priority Queue

//#############################################

typedef struct HeapNode { 
	// each node stores the priority (key), name, execution time,
	//  release time and deadline of one task
	int weight; //key of this task
	int code;
	
	int degree;
	
	struct HeapNode *child;
	struct HeapNode *parent;
	struct HeapNode *brother;
		
} HeapNode;


//data type for a priority queue (heap) 
typedef struct BinomialHeap{ //this is heap header
	HeapNode *head;
	int  size;      // count of items in the heap
	//... // add additional fields here
} BinomialHeap;


// create a new heap node to store an item (task) 
HeapNode *newHeapNode(int w, int c)
{ // k:key, n:task name, c: execution time, r:release time, d:deadline
  // ... you need to define other parameters yourself) 	 
	HeapNode *new;
	new = malloc(sizeof(HeapNode));
	assert(new != NULL);
	new->weight = w;
	new->code = c;
	
	new->degree = 0;

	 // initialise other fields 
	 new->child = new->parent = new->brother = NULL;
	 	 
	return new;
}


// create a new empty heap-based priority queue
BinomialHeap *newHeap()
{ // this function creates an empty binomial heap-based priority queue
	BinomialHeap *T;
	T = malloc(sizeof(BinomialHeap));
	assert (T != NULL);
	//... // initialise all the fields here
	T->head = NULL;
	T->size =0;
	
	return T;
}



//code for merging two heaps of the given 

HeapNode *merge_heap(BinomialHeap *h1, BinomialHeap *h2)
{
	//checking if the given heap was empty or not
	
	if (h1->head == NULL)
	{
		return h2->head;
	}
	
	//checking if the heap was empty or not
	
	if(h2->head == NULL)
	{
		return h1->head;
	}
	
	//heap node for the head created.
	
	HeapNode *head;
	
	// heap iterator for the given heaps.
	
	HeapNode *h1_it = h1->head;
	HeapNode *h2_it = h2->head;
	
	//this is for the second iterator which will be taken forward to create the heap
	HeapNode *tail;
	
	//first case when we are comparing the degree
	
	if(h1->head->degree <= h2->head->degree)
	{
		head = h1->head;
		h1_it = h1_it->brother;
	}
	
	else
	{
		head = h2->head;
		h2_it = h2_it->brother;
	}
	
	tail = head;
	
	//this is if there are any left over elements in the first heap or second heap
	// also note that is one single iteration.
	while( h1_it !=NULL && h2_it !=NULL)
	{
		if (h1_it->degree <= h2_it->degree)
		{
			tail->brother = h1_it;
			h1_it = h1_it->brother;		
		}
		else
		{
			tail->brother = h2_it;
			h2_it = h2_it->brother;
		}
		
		tail =tail->brother;
	}
	
	//checking and assigning the last element of the heap.
	tail->brother = (h1_it !=NULL) ? h1_it : h2_it ;
	
	//returning the head of the heap, it is for this reason that second iterator was used.
	//Note to self : check if the same can be done with only one iterator (assumption is if then it would become circular)
	return head;
}




//union
//code for the heap_union to combine the heap

HeapNode *union_heap(BinomialHeap *ori, BinomialHeap *temp)
{
	//calling the heap merge for the given heaps
	HeapNode *new_head = merge_heap(ori,temp);
	
	//first we set both the heads to Null.
	
	ori->head = NULL;
	temp->head = NULL;
	
	//checking if the new head is null or not
	
	if ( new_head == NULL)
	{
		return NULL;
	}
	
	//these are our iterators for the loop
	HeapNode *prev = NULL;
	HeapNode *curr = new_head;
	HeapNode *next = new_head->brother;
	
	//single iteration till end of the heap
	while(next !=NULL)
	{
		//Case 1. of the heap algo and for Case2.
		if (curr->degree != next->degree || (next->brother !=NULL && next->brother->degree == curr->degree ))
		{
			prev = curr;
			curr = next;
		}
		else
		{
			//Case 3. comparing the keys of the iterators.
			if (curr->weight <= next->weight)
			{
				curr->brother = next->brother;
				next->parent = curr;
				next->brother = curr->child;
				curr->child = next;
				curr->degree++;
			}
			else
			{
				if (prev == NULL)
				{
					new_head = next;
				}
				else
				{
					prev->brother = next;
				}
				
				//.Case 4. of the heap algo
				curr->parent = next;
				curr->brother = next->child;
				next->child = curr;
				next->degree++;
				
				curr = next;
			}
		}
		
		next = curr->brother;
	}
	
	return new_head;
}


// helper funtion for min funtion.

void heap_remove( BinomialHeap *heap, HeapNode *head, HeapNode *before)
{
	
	//primary check required for the given heaps.
	if (head == heap->head)
	{
		heap->head = head->brother;
	}
	else
	{
		before->brother = head->brother;
	}
	
	//setting the child nodes and new head instance
	HeapNode *new_head = NULL;
	HeapNode *child = head->child;
	
	//single iteration of the child node
	
	while(child !=NULL)
	{
		HeapNode *next = child->brother;
		child->brother = new_head;
		child->parent = NULL;
		new_head = child;
		child = next;
	}
	
	BinomialHeap *temp = newHeap();
	
	temp->head = new_head;
	
	//heap_union called for the temp instance and the heap passed
	heap->head = union_heap(heap,temp);
	free(temp);
} 


// put your time complexity for RemoveMin() here
HeapNode *RemoveMin(BinomialHeap *T)
{
 // put your code here for the remove min heap.
 	
 	//check if heap is null or not
 	if (T->head == NULL)
 	{
 		return NULL;
 	}
 
 	//new min heap node
	 HeapNode *min = T->head;
	 HeapNode *min_prev = NULL;
	 
	 //next iterator 
	 HeapNode *next = min->brother;
	 HeapNode *next_prev = min;
	 
	 //setting the iteration till end of the heap
	 while( next !=NULL)
	 {
	 	if (next-> weight < min->weight)
	 	{
	 		min = next ;
			min_prev = next_prev;	
		}
		
		next_prev = next;
		next = next->brother;
	 }
	 
	 //calling heap_remove for adjusting the heap
	 heap_remove(T, min, min_prev);
 
 return min;
}

// put the time complexity analysis for Insert() here    
void Insert(BinomialHeap *T, int w,int c)
{ // k: key, n: task name, c: execution time, r: release time, d:deadline 
  // You don't need to check if this task already exists in T 	 
  //put your code here
  
  //creating the heapnode with the given
  HeapNode *node = newHeapNode(w,c);
  
  //initalizing an empty heap
  BinomialHeap *temp = newHeap();	
  
  temp->head = node;
  
  //union heap called
  T->head = union_heap(T,temp);
  
  //temp heap was deleted.
  free(temp);
}

//###############################################


void printTree(HeapNode *h) 
{ 
	printf("\n Inside print tree");
	
    while (h) 
    { 
        printf("(%d,%d)",h->weight,h->code); 
        printTree(h->child); 
        h = h->brother; 
    } 
} 


//Complexity :: O(n)

void printPath(int parent[], int j,int p) 
{ 
    
    p++;
    path_len = p;
    // Base Case : If j is source 
    if (parent[j] == - 1) 
        return; 
  	
  	
    printPath(parent, parent[j],p); 
  
    //printf("%d ", j);
	
	has_path[p] = j;
	//p++;
	 
} 
  
//Complexity :: O(n)
 
int printSolution(int dist[], int n,  
                      int parent[],int stop) 
{ 
    int src=8,i = 0; 
    //printf("\nVertex\t Distance\tPath"); 
    for (i = 0; i <= n; i++) 
    { 
        if(i==stop)
        {
        	//printf("\n%d -> %d \t\t %d\t\t%d ",src,i, dist[i]); 
        	printPath(parent, i,0); 
		}

    } 
} 


// helper function for checking the min distance
// Complexity :: O((m+n)logn)

void min_distance(int max,int start,int stop)
{
	//printf("\nInside min disancen");
	int i,distance[max],parent[max];
	
	HeapNode *min;
	
	BinomialHeap *PQ = newHeap();
	
	StopList *ad_li;
	Stop *node;
	
	char *visited,ch;
	visited=(char *)malloc(max+1*sizeof(char));
	
	//heap initialized with the start point
	//Insert(PQ,0,start);
	//visited[start] = '1';
	
	//for the intial node.
	Insert(PQ,0,start);
	distance[start] = 0;
	parent[start] = 0;
	memset(visited,'0',max+1);
	
	for(i=0;i<=max;i++)
	{
		if(i!=start)
		{
			parent[i] = -1;
			//Insert(PQ,65535,i);
			distance[i] = INT_MAX;	
		}
		
	}
	
	
	//get the first minimum value form the heap
	min = RemoveMin(PQ);
	//printf("%d\t%d",min->code,min->weight);
	while(min!=NULL)
	{
		if(visited[min->code]=='0')
		{
			//setting the vertex visited flag
			visited[min->code] = '1';
			
			ad_li = adj_List[min->code];
			
			if(ad_li!=NULL)
			{
				node = ad_li->first;
				//traversing through the adjacent list
				while(node!=NULL)
				{
					if( distance[min->code] != INT_MAX &&  node->distance + distance[min->code] < distance[node->stop_code])
					{
						distance[node->stop_code] = distance[min->code] + node->distance;
						Insert(PQ,node->distance,node->stop_code);
						
						parent[node->stop_code] = min->code;						
					}
					
					node = node->next; 
				}	
			}
				
		}
		
		min = min = RemoveMin(PQ);
	}
	
	//printTree(PQ->head);
	
	/*
	printf("Distance matrix is as follows\n");
	
	for(i=0;i<=max;i++)
	{
		printf("%d,",distance[i]);
	}
	
	*/
	printSolution(distance,max, parent,stop);	
}


//global variable for the bus_list 
BusList *busn[10000];

//helper function for reading the bus notes
//Complexity :: O(n)

void reading_bus_routes(char *busRoutes)
{
	//BusList *busn[10000];
	
	BusList *temp;
	Bus_Name *bn_temp,*prev;
	
	int bs,dup;
	
	FILE *fp;
	
	int bus_code,bus_stop,input,flag=0,res;
	
	int stop_arr[1000],ar_c =0;
	
	char colon,d;
	
	fp = fopen(busRoutes,"r");
	
	//printf("Bus Routes are as follows :\n");
	int flag_stop = 1;
	
	//fscanf(fp,"%d%c",&bs,&colon);
	
	//printf("Bus Routes for :%d",bs);
	
	Bus_Name *bn;
	
	while( (input = fscanf(fp,"%d%c",&bus_stop,&colon) ) !=EOF )
	{
		//bn = newBus(bus_stop);
		if( flag_stop == 1 )
		{
			//printf("Bus is : %d\t,",bus_stop);
			//bs = bus_stop;
			bn = newBus(bus_stop);
			//printf("^^%d^^\n",bn->bus_code);
			flag_stop = 2;
		}
		else
		{
			//printf("%d, ",bus_stop);
			temp = busn[bus_stop];
			
			if (temp == NULL)
			{
				BusList *L = newBusList();
				L->first = bn;
				
				busn[bus_stop] = L;
			}
			else
			{
				bn_temp = temp->first;
				
				dup = 0;
				
				
				
				while(bn_temp!=NULL)
				{
					if(bn_temp->bus_code == bn->bus_code)
					{
						dup = 1;
						break;
					}
					//printf("*%d,",bn_temp->bus_code);
					prev = bn_temp;
					bn_temp = bn_temp->next;
				}
				
				if( dup == 0)
				{
					prev->next = bn;	
				}
				
			}
			
		}	
		
		//stop_arr[ar_c] = bus_stop;
		//ar_c++;
			
		//printf("%c",colon);
	
		if(colon == '#')
		{
			
			//printf("\n");
			flag_stop = 1;
		}
	}
	
	
	//printing the bus_list as follows:
	int i;
	
	//printf("Data here : ");
	//printf("%d",busn[0]->first->bus_code);
	
	
	//Bus_N
	
	/*
	for(i=0;i<=15;i++)
	{
		//BusList *temp;
	//Bus_Name *bn_temp;
	
		temp = busn[i];
		
		bn_temp = temp->first;
		
		printf("For stop :-> %d buses are : ",i);
		while(bn_temp!=NULL)
		{
			printf("%d,",bn_temp->bus_code);
			bn_temp = bn_temp->next;
		}
		
		printf("\n");
	}
	
	*/
}

//global return value for the vairables;
int re ;
int max;



//Function called for checking the strongly connected components
//Complexity :: O(V+E) 

int StronglyConnectivity( char *busStops, char *BusNames, char *BusRoutes, char *Distance)
{
	//int re;
	
	//for reading the stops from the file
	stop_names(busStops);
	
	//for reading the bus routes form the file
	reading_bus_routes(BusRoutes);
	
	//Matrix construction being done here,which returns adjacency matrix and result
	re = adj_construction();
	max = re;
		
	//The adjacency matrix is constructed and now we will check for strong connectivity
	return StronglyConnected(re);
}

//Function for the maximal strongly connected components
//Complexity :: O(V+E)

void maximalStronlyComponents(char *busStops,char *BusNames,char *BusRoutes,char *Distance)
{
	//helper function call
	int res = StronglyConnectivity("BusStops.txt","BusNames.txt","BusRoutes.txt","Distance.txt");
	
	MaxStrongly(re);
}


//Function for checking the stops are reachale from the source stop
//Complexity :: O(V+E)

void reachableStops(char *sourceStop, char *busStops, char *BusNames, char *BusRoutes, char *Distance)
{
	//helper function call
	int res = StronglyConnectivity("BusStops.txt","BusNames.txt","BusRoutes.txt","Distance.txt");
	
	reachable(re,sourceStop);
}


//Function that finds the minimum distance from one vertex to another.
// Complexity :: O((V+E)log(E)

void TravelRoute(const char *sourceStop, const char *destinationStop, const char *busStops, const char *BusNames, const char *BusRoutes, const char *Distance)
{
	int z,i,cmp;
	int sc,dest;
	
	//helper function call
	int res = StronglyConnectivity("BusStops.txt","BusNames.txt","BusRoutes.txt","Distance.txt");
	
	for(z=0;z<10000;z++)
	{
		has_path[z] = -1;
	}
	
	//first getting the source and the destination stop, values
	
	for(i=0;i<=max;i++)
	{
		cmp = strcmp(stopList[i].stopNames, sourceStop);
		
		if(cmp == 0 )
		{
			sc = i;
			break;
		}
	}	
	
	for(i=0;i<=max;i++)
	{
		cmp = strcmp(stopList[i].stopNames, destinationStop);
		
		if(cmp == 0 )
		{
			dest = i;
			break;
		}
	}
	
	min_distance(max,sc,dest);
	
	//printf("\nPath array is as follows\n");
	printf("\n\nTravel Route from  %s to %s \n",stopList[sc].stopNames,stopList[dest].stopNames);
	//printf("Path length is : %d",path_len);
	
	BusList *st,*end;
	Bus_Name *st_temp,*end_temp;
	
	int no_flag = 1,found =1;
	
	//printf
	for(z=path_len-1;z>1;z--)
	{
		if(has_path[z]>=0)
		{
			//found = 1;
			
			//printf("\n%d",has_path[z]);
			
			
			st = busn[z];
			end  = busn[z-1];
			
			st_temp = st->first;
			end_temp = st->first;
			
			while(st_temp!=NULL)
			{
				found = 1;
				
				if(found ==1)
				{
					while(end_temp!=NULL)
					{	
						if(st_temp->bus_code == end_temp->bus_code)
						{	
							//stopList[sc].stopNames
							
							//printf(" Bus Name %d (%d,%d) ",st_temp->bus_code,has_path[z],has_path[z-1]);
							
							printf(" Bus Name %d (%s,%s) ",st_temp->bus_code,stopList[has_path[z]].stopNames,stopList[has_path[z-1]].stopNames);
							
							no_flag = 0;
							found = 0;
							break;
						}
						end_temp = end_temp->next;
					}	
				}
				
				if (found == 0)
				{
					break;
				}
				
				st_temp =st_temp->next;
				
			}
			
			if( no_flag == 1 )
			{
				printf("No bus routes exist for this pathway");	
			}		
				
		}	
	}
	
}

int main(void)
{
	//int *adjMat;
	
	//	variables for connectivity for the matrix
	
	int connected;
	
	//calling StronglyConnectivity for question 1
	connected = StronglyConnectivity("BusStops.txt","BusNames.txt","BusRoutes.txt","Distance.txt");
	
	if(connected == 0)
	{
		printf("\nThe stops are not connected\n\n");
	}
	
	
	//calling maximalStronglyComponents for question 2 
	maximalStronlyComponents("BusStops.txt","BusNames.txt","BusRoutes.txt","Distance.txt");
	
	//Reachable stops for question 3 --> Provide the value of the source Stop here/take from the console

	reachableStops("Bridge Street","BusStops.txt","BusNames.txt","BusRoutes.txt","Distance.txt"); 
	
	//reachableStops(re,"Bridge Street");
	
	
	//for the question 4 Minimum distance from source stop to destination stops
	TravelRoute("Bridge Street","Bathurst Street","BusStops.txt","BusNames.txt","BusRoutes.txt","Distance.txt");
	
	
}
