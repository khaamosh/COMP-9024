#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


//Platform : Windows 10


// This template is only a guide 
// You need to include additional fields, data structures and functions  

// data type for heap nodes
typedef struct HeapNode { 
	// each node stores the priority (key), name, execution time,
	//  release time and deadline of one task
	int key; //key of this task
	int TaskName;  //task name 
	int Etime; //execution time of this task
	int Rtime; // release time of this task
	int Dline; // deadline of this task
	 // add additional fields here
	int degree;
	int core;
	
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
HeapNode *newHeapNode(int k, int n, int c, int r, int d,int s)
{ // k:key, n:task name, c: execution time, r:release time, d:deadline
  // ... you need to define other parameters yourself) 	 
	HeapNode *new;
	new = malloc(sizeof(HeapNode));
	assert(new != NULL);
	new->key = k;
	new->TaskName = n;
	new->Etime = c;
	new->Rtime = r; 
	new->Dline = d;
	new->core = s;
	
	 // initialise other fields 
	 new->child = new->parent = new->brother = NULL;
	 new->degree = 0;
	 
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



//code for the heap_union to combine the heap
//Complexity : O(Logn)

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
			if (curr->key <= next->key)
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

// put the time complexity analysis for Insert() here    
//Complexity :: O(logn)

void Insert(BinomialHeap *T, int k, int n, int c, int r, int d, int s)
{ // k: key, n: task name, c: execution time, r: release time, d:deadline 
  // You don't need to check if this task already exists in T 	 
  //put your code here
  
  //creating the heapnode with the given
  HeapNode *node = newHeapNode(k,n,c,r,d,s);
  
  //initalizing an empty heap
  BinomialHeap *temp = newHeap();	
  
  temp->head = node;
  
  //union heap called
  T->head = union_heap(T,temp);
  
  //temp heap was deleted.
  free(temp);
}


// helper funtion for min funtion.
//used for adjusting the heap.
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
//Time Complexity : O(logn) time
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
	 	if (next-> key < min->key)
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


//function to print the tree, used for checking the created tree.
// Complexity : n where n is the number of nodes in tree

void printTree(HeapNode *h) 
{ 
    while (h) 
    { 
        printf(" %d",h->key); 
        printTree(h->child); 
        h = h->brother; 
    } 
} 

// put your time complexity analysis for MyTaskScheduler here
//The complexity is  :: O(nlogn)

//The task shceduler relies on Binomial heap union and merge helper functions.
//Also the scheduler utilizes the size of the heap to fetch the available tasks.

int TaskScheduler(char *f1, char *f2, int m )
{
 // put your code here
 
 int tn, et, rt, dl ;
 
 int curr_time,temp_curr_time,input,i;
	
 int core_assign = 1 ;
	
 curr_time = temp_curr_time = 0;
 
 
 BinomialHeap *BH = newHeap();
 BinomialHeap *DH = newHeap();
 BinomialHeap *CH = newHeap();
 
 BinomialHeap *temp = newHeap();
 
 FILE *fp1, *fp2;
 
 fp1 = fopen(f1,"r");
 fp2 = fopen(f2,"w");
 
 if (fp1 == NULL)
 {
 	printf("File 1 does not exist\n");
 	exit(0);
	 //return 0;
 }
 //while( (input = fscanf(%d%d%d) )
 
 for( ; ( input = fscanf( fp1,"%d%d%d%d",&tn,&et,&rt,&dl)) !=EOF; )
 {
 	if (input!=0 && tn >=0 && et >=0 && rt >=0 && dl >=0)
 	{
 		Insert(BH,rt,tn,et,rt,dl,-1);
 		BH->size++;
	}
	else
	{
		printf("Input error while reading the attribute of task %d\n",tn);
		exit(0);
		//return 0;
	}
 	
 }
 
 //printTree(BH->head);
 	int current_counter_time = 1;
	int release_empty_flag = 0;
	
	int process_count;
	
	process_count = i = 0;
	//first = 0;
 
 while( process_count<=BH->size)
	{
		
		HeapNode*min ;
		
		//printf("\nCurrent_time is = %d\n",curr_time);
		//printf("Process_count = %d",process_count);
		
		if(process_count == BH->size)
		{
			break;
		}
		
		
		while(current_counter_time == 1 && release_empty_flag == 0)
		{
			min = RemoveMin(BH);
			//get the min release time from the BH
			
			if(min!=NULL)
			{
				if(min->key == curr_time)
				{
					//printf("\nMinTask is -: %d\n",min->TaskName);
				
					Insert(DH,min->Dline,min->TaskName,min->Etime,min->Rtime,min->Dline,min->core);
					//printf("\nInsert into DH___current___ :%d and task :%d",curr_time,min->TaskName);
					temp_curr_time = min->key;
			
					if( curr_time <temp_curr_time )
					{
						curr_time = temp_curr_time;
					}
					
					//counter updated here
					//i++;
				}
				else
				{
					current_counter_time = 0;
					Insert(BH,min->key,min->TaskName,min->Etime,min->Rtime,min->Dline,min->core);
					//curr_time++;
				}
			}
			else
			{
				release_empty_flag = 1;
			}
		}
		
		//getting the current time from the heap
	
		//current_counter_time = 1;
		
		HeapNode *min_dead = RemoveMin(DH);
		
		if (min_dead == NULL)
		{
			
			if(process_count<BH->size && release_empty_flag == 0)
			{
				current_counter_time = 1;
			}
			
			curr_time = curr_time+1;
			
		}
		
		if(min_dead!=NULL)
		{
			if (curr_time + min_dead->Etime <= min_dead->Dline)
				{
					//check for deadline break
								
					if ( CH->size == 0)
					{
						 	//insert data in the first core
						 	min_dead->core = core_assign;
						 	
							Insert(CH,curr_time + min_dead->Etime,min_dead->TaskName,min_dead->Etime,min_dead->Rtime,min_dead->Dline,min_dead->core);
							CH->size++;
							process_count++;
							//core_assign++;
							
							//printf("\nTaskName = %d and Time = %d and Core= %d",min_dead->TaskName, curr_time ,min_dead->core);
							fprintf(fp2,"%d Core%d %d ",min_dead->TaskName,min_dead->core,curr_time);
							
							//core_assign++;
					} 
						
					else
					{
						if (CH->size <m )
						{
							
							HeapNode *min_task = RemoveMin(CH);
							//printf("\nRemoved min task details as follows :\n");
							//printf("Task Name : %d and Core : %d\n", min_task->TaskName, min_task->core);
							
							if( curr_time < min_task->key)
							{
								Insert(CH,min_task->key,min->TaskName,min->Etime,min_task->Rtime,min_task->Dline,min_task->core);
								//Core_needs_to_be_changed
								//Insert(CH,first+min_dead->Etime+min->Rtime,min_dead->TaskName,min_dead->Etime,min_dead->Rtime,min_dead->Dline);
								
								//updating to the next available core
								core_assign++;
								
								min_dead->core = core_assign;
								
								//Here we will insert new cores from the list of cores
								Insert(CH,curr_time + min_dead->Etime,min_dead->TaskName,min_dead->Etime,min_dead->Rtime,min_dead->Dline,min_dead->core);
								CH->size++;
								process_count++;
								
								//printf("\nTaskName = %d and Time = %d and Core = %d",min_dead->TaskName, curr_time,core_assign);
								fprintf(fp2,"%d Core%d %d ",min_dead->TaskName,core_assign,curr_time);
								
								if (curr_time + min_dead->Etime > min_dead->Dline)
								{	
									//printf("\nDeadline1 detected");
									fprintf(fp2,"%d Core%d %d ",min_dead->TaskName,core_assign,curr_time);
									return 0;
									//break;
								}
							
							}	
						
							if (curr_time >=min_task->key)
							{	
								//core_assign++;
								//printf("\nMin task core is : %d",min_task->core);
								//printf("Name of task is :%d",min_task->TaskName);
								
								Insert(CH,curr_time + min_dead->Etime,min_dead->TaskName,min_dead->Etime,min_dead->Rtime,min_dead->Dline,min_task->core);
								//CH->size++;	
								process_count++;
								
								//printf("\nTaskName = %d and Time = %d and Core = %d",min_dead->TaskName, curr_time,min_task->core);
								fprintf(fp2,"%d Core%d %d ",min_dead->TaskName,min_task->core,curr_time);
								
								if (curr_time + min_dead->Etime > min_dead->Dline)
								{
									//printf("\nDeadline2 detected");
									fprintf(fp2,"%d Core%d %d ",min_dead->TaskName,min_task->core,curr_time);
									
									return 0;
									//break;
								}
							}
						}
						
						else
						{
							HeapNode *min_task = RemoveMin(CH);
							//printf("\n%d\n",min_dead->TaskName);
							
							//printf("\nThe current time is :%d",curr_time);
							
							//printf("The min task time is %d",min_task->key);
							
						
							if(curr_time >= min_task->key)
							{
								//curr_time = min_task->key;
								
								Insert(CH,curr_time + min_dead->Etime,min_dead->TaskName,min_dead->Etime,min_dead->Rtime,min_dead->Dline,min_task->core);
								process_count++;
							//CH->size++;
							
								//printf("\nTaskName = %d and Time = %d and Core = %d",min_dead->TaskName, curr_time,min_task->core);
								fprintf(fp2,"%d Core%d %d ",min_dead->TaskName,min_task->core,curr_time);
								
								if (curr_time + min_dead->Etime > min_dead->Dline)
								{
									//printf("\nDeadline3 detected");
									fprintf(fp2,"%d Core%d %d ",min_dead->TaskName,min_task->core,curr_time);
									return 0;
									//break;
								}	
							}
							else
							{
								Insert(CH,min_task->key,min_task->TaskName,min_task->Etime,min_task->Rtime,min_task->Dline,min_task->core);
								Insert(DH,min_dead->key,min_dead->TaskName,min_dead->Etime,min_dead->Rtime,min_dead->Dline,min_dead->core);
								curr_time= curr_time + 1;
							}
						
							//printf("The current time is :%d",curr_time);
						}
					}
							
				}
				else
				{
						//printf("Deadline breached--invalid");
						//printf("\nTaskName = %d and Time = %d and Core= %d",min_dead->TaskName, curr_time ,min_dead->core);
						fprintf(fp2,"DeadlineBreached");
						return 0;
						//break;
				}	
				
				
				//printTree(DH->head);
			}
		//printTree(DH->head);
		
		if(process_count<BH->size && release_empty_flag == 0)
		{
			current_counter_time = 1;
		}
	}

	
	//printf("\nNow the binomial heap is :\n");
	//printTree(DH->head);
	
	return 1;
}



int main() //sample main for testing 
{ int i;
  
  i=TaskScheduler("samplefile1.txt", "feasibleschedule1.txt", 4);
  if (i==0) printf("No feasible schedule!\n");

  /* There is a feasible schedule on 4 cores */
  i=TaskScheduler("samplefile1.txt", "feasibleschedule2.txt", 3);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 3 cores */
  i=TaskScheduler("samplefile2.txt", "feasibleschedule3.txt", 5);
  if (i==0) printf("No feasible schedule!\n");
  /* There is a feasible schedule on 5 cores */
  i=TaskScheduler("samplefile2.txt", "feasibleschedule4.txt", 4);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 4 cores */
  i=TaskScheduler("samplefile3.txt", "feasibleschedule5.txt", 2);
  if (i==0) printf("No feasible schedule!\n");
  /* There is no feasible schedule on 2 cores */
  
  i=TaskScheduler("samplefile4.txt", "feasibleschedule6.txt", 2);
  if (i==0) printf("No feasible schedule!\n");
  /* There is a feasible schedule on 2 cores */

   return 0; 
}
