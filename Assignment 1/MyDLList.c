// Author: Uttkarsh Sharma	
// Student ID: z5269665
// Platform: Windows 10, 64 bit OS with x64 processor
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item 
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here

//The time complexity for creation of DLList is as follows :: O(mn)

// here m is the number of the lines in the file and n are the number of elements.

DLList *CreateDLListFromFileDlist(const char *filename)
{
 // put your code here
 	
 	FILE *fp;
 	
	
 	int digit ;
 	int input ;
 	int flag =0;
 	int cmp ;
 	//fp = fopen("C:\\Users\\Uttkarsh Sharma\\Downloads\\testFile.txt","r");
 	
 	fp = fopen(filename,"r");
 	
	//creating an emmpty link_list here
 	DLList *link_list = newDLList();
	
	// first branch based on the file_name given
	cmp = strcmp(filename,"stdin");
	
	if( cmp == 0)
	{
		//the fp buffer
		char fp[10000] ;
		
		//copy buffer
		char copy[10000];
		
		//end_encountered copy buffer
		char end_copy[10000];
		
		int len,length ;
		int i=0,c=0,j ;
		int pos;
		
		int copy_len = 0 , temp_len=0,comp_val,flag=0;
		
		//digit array created
		char digit_array[10000];
		
		char *val;
		
		// meant for checking end occurence and comparison
		char end[4]= {'e', 'n' ,'d','\n'};
		char end1[3] = {'e', 'n' ,'d'};
		
		//flags for checks
		int end_check ;
		int zero_flag = -1 ;
		
		//delimiters for tokenization
		char delim[2] = { ' ', '\0'};
		
		//flags for the call checks
		int end_count = 0;
		int e_pos = -1;
		
		int middle_end = 0;
		
		//buffer read and checked against the provided keywords
		for( ; flag !=1 && fgets(fp,10000,stdin) && strcmp(fp,"end\n") ;)
		{
			
			len = strlen(fp);
			//printf("The string is:\n",len);
			//printf("%s",fp);
			
			// removing extra whitespaces here and sanitizing the string 
			for(i=0;i<len;i++)
			{
				if (!(fp[i] == ' ' && fp[i+1] == ' ')) 
				{
	        		copy[c] = fp[i];
	        		c++;
				}
			}
			
			//setting the string's last character to null
			copy[c] = '\0';
			
			//for logging purpouse and debugging
			
			//printf("The string is:\n");
			//printf("%s",copy);
			//printf("\n");
			
			
			//finding the postition of e
			char *pos = strchr(copy,'e');
			e_pos = (int)(pos - copy);
			
			//for logging and debugging
			//printf("%d",e_pos);
			
			//if e was encountered
			if(e_pos > 0)
			{
				if(copy[e_pos+1] == 'n' && copy[e_pos+2]=='d')
				{
					//printf("\nmiddle end\n");
					
					// creating a substring of the encountered copy
					for (j = 0; j<e_pos+3;j++)
					{
						end_copy[j] = copy[j];	
					}
					
					end_copy[j] = '\n';
					
					//set the flag for the string
					middle_end = 1;	
				}
				
				//printf("$$$$$$$$$$$$$");
				//printf("\n%s\n",end_copy);
				//printf("%%%%%%%%%%%%%");
				
				
				
			}
			
			//pos = strstr(end,copy);
			//printf("found at %d",&pos);
			
			//copy[0] = '\0';
			
			c=0; //setting the counter to zero for next iteration.
			
			
			//checking the flag 
			if (middle_end == 1)
			{
				length = strlen(end_copy);
			}
			else
			{
				length = strlen(copy);	
			}
			
			
			//char *rev_str;
			
			//rev_str = strrev(copy);
			//printf("The reversed string is :\n");
			//printf(rev_str);
			
			//strrev(copy);
			
			//finding the first occurence of e			
			
			// making sure that string is not empty
			if (length>0)
			{
				if(middle_end == 1)
				{
					//tokenization of the string
					val = strtok(end_copy,delim);
					//printf("------mi---->");	
				}
				else
				{
					val = strtok(copy,delim);	
				}
				
				
				//copy_len = 0;
				
				//validating the input
				/*
				sprintf(digit_array,"%d" , atoi(val));
						
				if (link_list->last == NULL)
				{
					if (strcmp(digit_array,val) != 0)
					{
						printf("Invalid input!");
						exit(0);
					}
					
					DLListNode *new_node = newDLListNode(atoi(val));
					
					link_list->first = link_list->last = new_node;
					link_list->size++;

					val = strktok(copy,delim);
				}
				*/
				/*
				else
				{
					link_list->last->next = new_node;
					new_node->prev = link_list->last;
					link_list->last = new_node;
					link_list->size++;				
				}
				
				*/
				
				// the above is another alternate way but was not efficient and had bugs
				
				//iterting over the tokens of the string
				
				while(val!=NULL)
				{
					temp_len = strlen(val);					
					//copy_len = copy_len + temp_len;
					
					//printf("Inside the tokens:\n");
					//printf("%s\n",val);
					
					//generation of the copy
					strcpy(end1,val);

					//comparison of the strings
					comp_val = strcmp(end1,"end") ;

					//printf("%c",end1[8]);
					//printf("%d",strlen(val)) ;
					//printf("%d",strlen(end1));

					//printf("%d",comp_val);

				/*	
					if( comp_val ==  0)
					{
						end_count +=1;
						printf("\n##### end--> encountered \n");
						printf("%d",copy_len);
						printf("%d",length);
						flag = 1;
						break;
						/*if (copy_len == length)
						{
							printf("-----------------------") ;
							printf("\nsetting the flag");
							flag = 1 ;
							break;
						}
						else
						{
							printf("\nin between end checking\n");
							printf("\n Yo! setting it my man!!") ;
						 	flag = 1;
							break;
						}
						
					}
					*/
					
					// as mentioned earlier, this method was also alternate apporach but not efficient
					
					//converting the token to integer
					int to_i = atoi(val);
					
					if (to_i !=0)
					{
						//array of digits created here
						
						sprintf(digit_array,"%d" , to_i);	
					/*	
						if (strcmp(digit_array,val) != 0)
						{
							printf("debugging here\n");
							printf("%d\n",end_check);
							printf("Invalid input!-----> 1\n");
							printf("length of val->%d", strlen(val));
				        //flag=1;
						//break;
							//exit(0);
						}
					*/	
						//creating of a new node
						
						DLListNode *new_node = newDLListNode(atoi(val));
						
						//printf("Here");
					//printf("%d",link_list->first->value);
						
						//if the list is empty, create the first node
						
						if (link_list->last == NULL)
						{
							if (strcmp(digit_array,val) != 0)
							{
								printf("Invalid input!");
								return NULL;
								//exit(0);
							}
					
					

						//DLListNode *new_node = newDLListNode(atoi(val));
					
							link_list->first = link_list->last = new_node;
							link_list->size++;

						//val = strktok(copy,delim);
						}
						else
						{
							link_list->last->next = new_node;
							new_node->prev = link_list->last;
							link_list->last = new_node;
							link_list->size++;
							
							//printf("Now");
						}
					}
					else if(val[0]!='\n')
					{
						//alternate code path
						
						int zero = strlen(val);
						
						if( val[0] == '0' && (zero == 1 || zero ==2) ) 
						{
							DLListNode *new_node = newDLListNode(0);
							
							if(link_list->last ==NULL)
							{
								link_list->first = link_list->last = new_node;
								link_list->size++;
							}
							else
							{
								link_list->last->next = new_node;
								new_node->prev = link_list->last ;
								link_list->last = new_node;
							
								link_list->size++;	
							}
							
							zero_flag = 1;
							
						}
						
						// encountering end and checking it
						
						if( strcmp(val,end) == 0 )
						{
							//printf("End encountered");
							
							//setting the flag
							flag=1;
							//printf("end_encountered") ;
							
							//exit(0);
						}
					
						else if (zero_flag!=1)
						{
							//printf("%d",strcmp(val,end));
							//printf("zero flag -> %d",zero_flag);
							printf("Invalid Input!!");
							return NULL;
							//exit(0);
						}
					}
					
					//end_check = strcmp(val,"end");

					//printf("values of end check is --> %d",end_check);
					
					//iterator for moving over the tokens generated
					
					val = strtok(NULL, delim);

					//printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^");
					//printf("%s\n",val);
					
					
					copy_len+=1;
					//to_check_for the postition of the end
					
				}
				
			}
		}
		
	}
	else
	{
		//for reading of the buffer of the file until EOF is encountered
		
		while( ( input = fscanf(fp, "%d", &digit)) !=EOF )
		{
			//if input was success
			if ( input == 1)
			{
				//printf("Success, an int was read %d\n", digit);
				
				//creating an empty node
				
				DLListNode *new_node = newDLListNode(digit);
				
				//checking if the link_list is empty
				if (link_list->last == NULL)
				{
					link_list->first = link_list->last = new_node;
					
				}
				else
				{
					link_list->last->next = new_node;
					new_node->prev = link_list->last;
					link_list->last = new_node;				
				}
				
				link_list->size++;
			
			}
			else
			{
				//fgetc(fp);
				
				printf("Invalid Input!!");
				
				//set the flag for invalid input
				flag = 1;
				break;
				
			} 
		}
		
		//close the file pointer
		
		fclose (fp);
			
	}
		
 	  
  
  if (flag == 1)
  {
  	return NULL;
  }
  else
  {
  	return link_list ;
  }
  
}

// clone a DLList
// put your time complexity analysis for cloneList() here :: 
//The time complexity of clone list is :: O(n)

DLList *cloneList(DLList *u)
{
 // put your code here
 
 //create an empty link list
 
 DLList *clone = newDLList();
 
 //creating a reference for the iterator of the node
 
 DLListNode *current ;
 
 //checking if the node is not null
 
 if(u!=NULL)
 {
 	//iterator used for copying of the node
 	
 	for (current= u->first; current!=NULL ; current = current->next)
 	{
 		//creating a node with the data
		DLListNode *new_node = newDLListNode(current->value);
 		
 		//checking if first node ?
 		if(clone->last == NULL)
 		{
 			clone->first = clone->last = new_node;	
		}
		
		else
		{
			//linking up new node at the end
			clone->last->next = new_node;
			new_node->prev = clone->last;
			clone->last = new_node;
		}
 		
 				
 	}
 	clone->size = u->size;
 } 
 
 return clone;
}


// helper function called for checking the value

int check(int val, DLList *u)
{
	DLListNode *current;
	
	for (current = u->first; current != NULL ; current= current->next)
	{
		//printf("\nPrinting current values\n");
		//printf("%d", current->value);
		//printf("\t");
		
		if (val == current->value)
		{
			return 0;
		}
		
	}
	
	return 1;
}


//combi
DLList *combine ( DLList *LL1 , DLList *LL2, int size)
{
	assert(LL1!= NULL);
	assert(LL2!=NULL);
	
	DLList *res = cloneList(LL1);
	
	DLListNode *current ;
	
	for(current = LL2->first; current!=NULL ; current = current->next )
	{
		DLListNode *node = newDLListNode(current->value);
		
		res->last->next = node;
		node->prev = res->last;
		
		res->last = node;
	}
	
	res->size = size + LL2->size ;
}

// compute the union of two DLLists u and v

// The time complexity is :: O(mn)
//where m are the elements of the first link list and n are the elements of the second linklist

DLList *setUnion(DLList *u, DLList *v)
{
 // put your code here
 
 //the union list
 DLList *union_result = newDLList();
 
 int temp_size = 0;
 int flag ;
 
 //iterator created
 DLListNode *current ;
 
 for (current = u->first; current!=NULL ; current = current->next)
 {
 	
 	//helper function called for checking
 	flag = check(current->value, v);
 	
 	if( flag == 1)
 	{
 		//creating a new node
 		
 		DLListNode *new_node = newDLListNode(current->value);
 		
 		if ( union_result->last == NULL)
 		{
 			union_result->first = union_result->last = new_node;
		}
		else
		{
			union_result->last->next = new_node;
			new_node->prev  = union_result->last;
			union_result->last = new_node;
			
		}
 		
 		temp_size++;
	}
	
	
  }

//combining the result here
DLList *result = combine(union_result, v, temp_size ); 	
}

//Function for flagging values for intersection

int check_intersect(int val, DLList *ll)
{
	DLListNode *current;
	
	for (current = ll->first; current!= NULL ; current = current->next)
	{
		if (val == current->value)
		{
			return 1 ;
		}
	}
	
	return 0;
}





// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here : 

//The time complexity of this function is : O(mn)
// where m is the number of elements in first link list and n are number of elements in second link list

DLList *setIntersection(DLList *u, DLList *v)
{
  // put your code here
  
  DLList *intersection_list = newDLList();
  int size = 0;
  int flag;
  
  //link_list iterator
  
  DLListNode *current;
  
  for ( current = u->first; current != NULL ; current = current->next )
  {
  	//helper function called
  	
  	flag = check_intersect(current->value , v);
  	
  	if(flag == 1)
  	{
  		//link list created here
  		DLListNode *new_node = newDLListNode(current->value);
		
		if(intersection_list->last == NULL)
		{
			intersection_list->first = intersection_list->last = new_node;
					
		}
		else
		{
			intersection_list->last->next = new_node;
			new_node->prev = intersection_list->last;
			intersection_list->last = new_node;
		}
		
		size++; 	
	}
  }
  
  intersection_list->size = size;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here :: O(n)
void freeDLList(DLList *L)
{
// put your code here	
	DLListNode *current = L->first;
	
	DLListNode *next;
	
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	
	free(L) ;
	//L->first = L->last = NULL;
}


// display items of a DLList
// put your time complexity analysis for printDDList() here :: O(n)
void printDLList(DLList *u)
{
 // put your code here

 //printf("@@@@@@@@@@@@@@@@@2\n");
 //printf("%d\n",u->last->value);
 //printf("^^^^^^^^^^^^^^^^^^^^^");
 	 
 DLListNode *current ;
 if(u!=NULL)
 {
 	for (current = u->first; current!=NULL ; current = current->next)
 	{
 		printf("%d\n",current->value);
 	}
 }
 
}

int main()
{
 DLList *list1, *list2, *list3, *list4;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);

 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");

 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");

 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 return 0; 
}
