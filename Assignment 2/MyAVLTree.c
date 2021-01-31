#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 


//duplicate flag

static int DUPLICATE_flag = 1;
static int delete_flag = 1;

// data type for avl tree nodes
typedef struct AVLTreeNode {
	int key; //key of this item
	int  value;  //value (int) of this item 
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *parent; //pointer to parent
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);
	new->key = k;
	new->value = v;
	new->height = 0; // height of this new node is set to 0
	new->left = NULL; // this node has no child
	new->right = NULL;
	new->parent = NULL; // no parent
	return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}

//The following are the helper functions that were writen to facilitate the programs execution
//complexity =O(1) one comparison

int max( int x, int y)
{
	if(x> y)
	{
		return x;
	}
	else
	{
		return y;
	}
}


// to return the height of the node
//complexity = O(1)

int height( AVLTreeNode *node)
{
	if(node == NULL)
	{
		return -1;
	}
	
	return node->height;
}


// this function is responsible for checking the balancing factor of the height of the trees
// complexity = O(1) straight subtraction

int balance(AVLTreeNode * node)
{
	if(node == NULL)
	{
		return 0;
	}
	else
	{
		return  height(node->left) - height(node->right) ;
	}
}

// this function is responsible for right rotating the nodes
//Complexity = O(1)

AVLTreeNode *right_rotation(AVLTreeNode *node)
{
	AVLTreeNode *root = node->left;
	AVLTreeNode *right = root -> right;
	
	root->right = node;
	node->left = right;
	
	node->height = 1 + max(height(node->left), height(node->right));
	root->height = 1 + max(height(root->left), height(root->right));
	
	return root;
}

//This function is responsible for left rotating the tree
//Complexity = O(1)


AVLTreeNode *left_rotation(AVLTreeNode * node)
{
	AVLTreeNode *root  = node->right;
	AVLTreeNode *left  = root->left;
	
	root->left = node;
	node->right = left;
	
	node->height = 1 + max( height(node->left), height(node->right));
	root->height = 1 + max( height(root->left), height(root->right)) ;
	
	return root; 
	
}


//helper function for the creation of the AVL Tree 
//complexity of the function is O(mlogn)

AVLTreeNode *insert(AVLTreeNode *node , int k , int v)
{
	int balance_factor ;
	
	if(node == NULL)
	{
		return newAVLTreeNode(k,v);
	}
	
	if ( k <= node->key )
	{
		if(k == node->key)
		{
			if(v == node->value)
			{
				//printf("This is duplicate value");
				DUPLICATE_flag = 0;
				return node;
				//return NULL;
			}
			else if (v < node->value)
			{
				node->left = insert(node->left, k, v);
				//printf("Entered %d and %d\n", k,v);
			}
			else if (v > node->value)
			{
				node->right = insert(node->right, k , v);
				//printf("Entered %d and %d\n", k ,v);
			}
		}
		else
		{
			node->left = insert(node->left,k,v);
		}
	}
	
	else if(k > node->key)
	{
		node->right = insert(node->right, k , v);
		//printf("Entered %d and %d\n", k, v);
	}
	
	
	if(node!=NULL)
	{
		node->height = 1 + max( height( node->left) , height(node->right));
	
		balance_factor = balance(node);
	
		//Left Left Rotation
		if ( balance_factor > 1 && k < node->left->key)
		{
			return right_rotation(node);
		}

	
		// Left Right rotation
		if( balance_factor > 1 && k >= node->left->key)
		{
			node->left = left_rotation(node->left);
			return right_rotation(node);
		}
	
		//Right right rotation
		if (balance_factor < -1 &&  k > node->right->key)
		{
			return left_rotation(node);
		} 
	
		// Right Left Rotation
		if (balance_factor < -1 && k<=node->right->key)
		{
			node->right = right_rotation(node->right);
			return left_rotation(node);
		}

		
	}
		
	return node;
		 
}


//helper function for the printing of the trees
//Complexity = O(n)
 
void In_Order(AVLTreeNode *root) 
{ 
    if(root != NULL) 
    { 
         
        In_Order(root->left); 
        printf("(%d,%d),%d\n", root->key,root->value,root->height);
		In_Order(root->right); 
    } 
} 

//------------------end of the helper functions-----------------------------

// put your time complexity analysis of CreateAVLTree() here
//Complexity of the function is -> O(nlogm)

AVLTree *CreateAVLTree(const char *filename)
{
 // put your code here
 	
	 // empty AVLTree
 	AVLTree *tree = newAVLTree();
 	
 	FILE *fp;
   	
   	fp = fopen(filename, "r");
   	
   	char before[100];
   	
   	char first[100];
   	char first_rev[100];
   	char first_copy[100];
   	
	char middle[100];
	char middle_copy[100];
	
   	char after[10] ;
   	int input;
   	
	char error[100];
   	int test,test_rev;
   	int test_1,test_1_rev;
   	
   	int cmp = 0;
   	int cnt;
   	
	// scanset expression :: "%[(^,]%[^,]%*c%[^)]
	
	cmp = strcmp(filename,"stdin");
	
	if(cmp==0)
	{
		//for reading the data from buffer
		
		for( ; (input = fscanf(stdin,"%[(]%[^,]%*c%[^)]",before,first,middle,after) ) !=EOF ; )
			{
				if(input!=0)
				{
					test = atoi(first);
   					test_rev = atoi(strrev(first));
   			
   					test_1 = atoi(middle);
   					test_1_rev = atoi(middle);
   			
			//printf("header___%sfrom__%sto__%s and%s\n", before, first,middle,after);
		
					if (test !=0 && test_rev!=0 && test_1_rev!=0 && test_1!=0)
					{
						//printf("%d\t",test);	
						//printf("%d\n",test_1);
						
						tree->root = insert(tree->root, test,test_1); 
  						tree->size++;
					}
					else
					{
						
						//printf("code check for zero else error\n");
						//remove spaces and check for zero else break;
						
   						long first_num;
   						long middle_num;
   						
    					char *first_end;
    					char *middle_end;
    					
    					strrev(first);
    					strrev(middle);
    					
    					first_num = strtol(first, &first_end, 10);        //10 specifies base-10
    					
						if (first_end == first)     //if no characters were converted these pointers are equal
        				{
        					printf("Invalid Input!!\n");
        					exit(0);
						}
						
						middle_num = strtol(middle,&middle_end,10);
						
						if (middle_end == middle)     //if no characters were converted these pointers are equal
        				{
        					printf("Invalid Input!!\n");
        					exit(0);
						}
						
						
						tree->root = insert(tree->root, first_num,middle_num); 
  						tree->size++;
						
						//if( val[0] == '0' && (zero == 1 || zero ==2) ) 
						//{
		/*
						if (test[0] ==0 && test_rev[0]==0 && test_1_rev!=0 && test_1!=0)
						{
						//printf("%d\t",test);	
						//printf("%d\n",test_1);
						
							tree->root = insert(tree->root, test,test_1); 
  							tree->size++;
						}
						else
						{
							printf("Invalid Input->Error");
							exit(0);
						}
						*/
					}	
				}
			//len = strlen(fp);
			//printf("The string is:\n",len);
			//printf("%s",fp);
				
				else
				{
					error[cnt] = fgetc(stdin);
					cnt++;
					
					if(error[0] == 'e')
					{
						error[cnt] = fgetc(stdin);
						cnt++;
						
						if(error[1] == 'n')
						{
							error[cnt] = fgetc(stdin);
							cnt++;
							
							if (error[2] == 'd')
							{
								break;
							}
							else
							{
								cnt =0;
							
								if(error[2] !='(' && error[2]!=',' && error[2]!=')' && error[2]!=' ' && error[2]!='\n')
								{
									printf("This is an error-");
									exit(0);
									//printf("%c\n",error[2]);
								}
							}
						}
						else
						{
							cnt =0;
							
							if(error[1] !='(' && error[1]!=',' && error[1]!=')' && error[1]!=' ' && error[1]!='\n')
							{
								printf("This is an error-");
								exit(0);
								//printf("%c\n",error[1]);
							}
						}
					}
					else 
					{
						cnt = 0;
						
						if(error[0] !='(' && error[0]!=',' && error[0]!=')' && error[0]!=' ' && error[0]!='\n')
						{
							printf("This is an error-");
							exit(0);
							//printf("%c\n",error[0]);
						}
						
					}
					
				}
			}
		
	}
	else
	{  
		while( (input = fscanf(fp,"%[(]%[^,]%*c%[^)]",before,first,middle,after) ) !=EOF )
   		{
   			if(input!=0)
   			{
   				
   				test = atoi(first);
   				strrev(first);
   				test_rev = atoi(first);
   				
   				test_1 = atoi(middle);
   				strrev(middle);
   				test_1_rev = atoi(middle); 
   				
   			
   			//test_1 = atoi(middle);
			//printf("header___%sfrom__%sto__%s and%s\n", before, first,middle,after);
		
				if (test !=0 && test_rev!=0 && test_1!=0 && test_1_rev!=0)
				{
					//printf("%d\t",test);
					//printf("%d\n",test_1);
					
					tree->root = insert(tree->root, test,test_1); 
  					tree->size++;	
  					
  					//printf("The details of the inserted node\n")
  					
				//printf("%d\n",test_rev);
				}
				else
				{
					printf("code check for zero else error\n");
					
					long first_num;
   						long middle_num;
   						
    					char *first_end;
    					char *middle_end;
    					
    					strrev(first);
    					strrev(middle);
    					
    					first_num = strtol(first, &first_end, 10);        //10 specifies base-10
    					
						if (first_end == first)     //if no characters were converted these pointers are equal
        				{
        					printf("Invalid Input!!\n");
        					exit(0);
						}
						
						middle_num = strtol(middle,&middle_end,10);
						
						if (middle_end == middle)     //if no characters were converted these pointers are equal
        				{
        					printf("Invalid Input!!\n");
        					exit(0);
						}
						
						
						tree->root = insert(tree->root, first_num,middle_num); 
  						tree->size++;
				//remove spaces and check for zero else break;
				
				}
			
			}
			else
			{
				fgetc(fp);
			}
		   
		}
	}  
   	
 return tree;
}

//helper function of the Clone Tree
// Complexity -> O(n)

AVLTreeNode *Clone(AVLTreeNode *root)
{
	if (root == NULL)
	{
		return NULL;
	}
	
	AVLTreeNode *node = newAVLTreeNode(root->key,root->value);
	node->height = root->height;
	
	node->left = Clone(root->left);
	node->right = Clone(root->right);
	
	return node;
}


// put your time complexity analysis for CloneAVLTree() here
//the complexity of the function is -> O(n) 
//uses the helper function clone

AVLTree *CloneAVLTree(AVLTree *T)
{
 // put your code here
 
 AVLTree *Tree = newAVLTree();
 
 Tree->root = Clone(T->root);
 
 return Tree;
  
}

//structure defined for keys and values
typedef struct Data
{
	int key;
	int val;
}data;

//merged data structure defined

typedef struct DataMerged
{
	struct Data *d;
	int count;
	
}datamerged;

// helper function used in merging of the in-order traversal of 
//complexity = O(n+m)

struct DataMerged merge(struct Data T1[], struct Data T2[], int m, int n )
{
	
	int i,j,k,count;
	i=0,j=0,k=0;
	
	count = 0;
	
	int combined_size = m + n ;
	
	struct DataMerged DM;
	
	struct Data *merged = (struct Data *) malloc( combined_size * sizeof(struct Data *));
	
	while(i< m && j < n)
	{
		if( T1[i].key <= T2[j].key)
		{
			if( T1[i].key == T2[j].key)
			{
				if ( T1[i].val <= T2[j].val)
				{
					if( T1[i].val == T2[j].val)
					{
						i++;
						//printf("Copy val\n");
						//printf("%d and %d\n", T1[i], T2[j]);
					}
					
					else
					{
						merged[k] = T1[i];
						k++;
						i++;
						count++;	
					}
								
				}
				else 
				{
					merged[k] = T2[j];
					k++;
					j++;
					count++;
				}
			}
			
			else
			{
				merged[k] = T1[i];
				k++;
				i++;
				count++;
			}
			
			
		}
		else
		{
			merged[k] = T2[j];
			k++;
			j++;
			count++;
		}
	}
	
	while(i<m)
	{
		merged[k] = T1[i];
		k++;
		i++;
		count++;
	}
	
	while(j<n)
	{
		merged[k] = T2[j];
		k++;
		j++;
		count++;
	}
	
	DM.d = merged;
	DM.count = count;
	//return merged;
	
	return DM;
}


//helper function for union and intersection
//Complexity O(n)

void in_array(AVLTreeNode *node, struct Data arr[],int *c,int size)
{
	
	if (node == NULL)
	{
		return ;
	}
	
	in_array(node->left,arr,c,size);
	
	if(*c < size)
	{
		struct Data d ;
		d.key = node->key;
		d.val = node->value;
	
	
		//printf("\n%d -> %d", d.key, d.val);	
		arr[*c] = d;
		*c = *c + 1;
	}	
	
		
		//printf("%d\t",*counter);
		//*counter = *counter + 1;
		//printf("%d",*counter);
	in_array(node->right, arr,c,size);
		
		//merge_keys[*counter] = node->key;
		//merge_vals[*counter] = node->value;
		//*counter = *counter + 1;
		
}

// helper function for creation of the tree (union/intersection)
//complexity O(n+m)

AVLTreeNode *tree_construction(struct Data combi[],int start, int end)
{
	int sum = 0;
	
	if (start > end)
	{
		//root->height = 0;
		return NULL;
	}
	
	sum = start + end+1 ;
	
	int mid = ceil((sum)/2);
	//printf("D->%d\n",mid);
	
	int key = combi[mid].key;
	int val = combi[mid].val;
	
	AVLTreeNode *root = newAVLTreeNode(key,val);
	//height information not considered have to add later.
	
	
	//root->height = 1 + max( height( root->left) , height(root->right)) ;
	root->left = tree_construction(combi,start,mid-1);
	
	//root->height = 1 + max( height( root->left) , height(root->right));
	
	root->right = tree_construction(combi, mid+1,end);
	root->height = 1 + max( height( root->left) , height(root->right));
	
	//root->height = mid-1;
	
	//return root;
}


// put your time complexity for ALVTreesUNion() here
//Complexity of the function is = O(m+n)

AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{
	//put your code here
	
	int total_size,*counter_pointer,counter;
	
	struct DataMerged merged_items;
	
	counter = 0;
	
	counter_pointer = &counter;
	
	total_size = T1->size + T2->size ;
	 
	struct Data *Tr1 = (struct Data *) malloc(T1->size * sizeof(struct Data));
	struct Data *Tr2 = (struct Data *) malloc(T2->size * sizeof(struct Data)) ;
	
	in_array(T1->root,Tr1,&counter,T1->size);
	
	counter = 0;
	
	in_array(T2->root,Tr2,&counter,T2->size);
	
	
	AVLTree *Tree3 = newAVLTree();
	//printf("\nEntereed AVL Tree is as follows :\n");
	//In_Order(Tree1->root);


	//printf("Now second tree is as follows :\n");
	//In_Order(Tree2->root);
	

	//printf("Now the  of the funtion are as follows:\n");
	//printf("%d and %d",T1->key,T1->val);
	
	merged_items = merge(Tr1,Tr2,T1->size,T2->size);
	
	//printf("%d -> %d", merged_items[0].key, merged_items[0].val);
	
	//now constructing the AVL Tree from this array of structures
	
	Tree3 = newAVLTree();
	Tree3->root = tree_construction(merged_items.d,0 , merged_items.count-1);
	
	//printf("\n------Final Union of the trees is:----\n");
	//In_Order(Tree3->root);
	
	//int i ;
	
	//int combined_size = Tree1->size + Tree2->size;
	
	
	
	return Tree3;
	
}


//Data_merged for intersection helper function
//complexity O(m + n)

struct DataMerged merge_intersection(struct Data T1[], struct Data T2[], int m, int n )
{
	int i,j,k,count;
	i=0,j=0,k=0;
	
	count = 0;
	
	int combined_size = m + n ;
	
	struct DataMerged DM;
	
	struct Data *merged = (struct Data *) malloc( combined_size * sizeof(struct Data *));
	
	while(i< m && j < n)
	{
		if( T1[i].key <= T2[j].key)
		{
			if( T1[i].key == T2[j].key)
			{
				if ( T1[i].val <= T2[j].val)
				{
					if( T1[i].val == T2[j].val)
					{
						merged[k] = T1[i];
						i++;
						k++;
						j++;
						count++;
						//printf("Copy val\n");
					}
					
					else
					{
						//merged[k] = T1[i];
						//k++;
						i++;
						//count++;	
					}
								
				}
				else 
				{
					//merged[k] = T2[j];
					//k++;
					j++;
					//count++;
				}
			}
			
			else
			{
				//merged[k] = T1[i];
				//k++;
				i++;
				//count++;
			}
			
			
		}
		else
		{
			//merged[k] = T2[j];
			//k++;
			j++;
			//count++;
		}
	}
	
/*	
	while(i<m)
	{
		//merged[k] = T1[i];
		//k++;
		//i++;
		//count++;
	}
	
	while(j<n)
	{
		//merged[k] = T2[j];
		//k++;
		//j++;
		//count++;
	}
*/
	
	DM.d = merged;
	DM.count = count;
	//return merged;
	
	return DM;
}




// put your time complexity for ALVTreesIntersection() here
//Complexity of the function is O(m+n)

AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2)
{
	 //put your code here
	
	AVLTree *Tree3; 
	int total_size,*counter_pointer,counter;
	
	struct DataMerged merged_items;
	
	//struct Data *merged_items ;
	
	counter = 0;
	
	counter_pointer = &counter;
	 
	total_size = T1->size + T2->size ;
	 
	struct Data *Tr1 = (struct Data *) malloc(T1->size * sizeof(struct Data));
	struct Data *Tr2 = (struct Data *) malloc(T2->size * sizeof(struct Data)) ;
	
	in_array(T1->root,Tr1,&counter,T1->size);
	
	counter = 0;
	
	in_array(T2->root,Tr2,&counter,T2->size);
	
	
	//Tree3 = newAVLTree();
	//printf("\nEntereed AVL Tree is as follows :\n");
	//In_Order(Tree1->root);


	//printf("Now second tree is as follows :\n");
	//In_Order(Tree2->root);
	

	//printf("Now the  of the funtion are as follows:\n");
	//printf("%d and %d",T1->key,T1->val);
	
	merged_items = merge_intersection(Tr1,Tr2,T1->size,T2->size);
	
	//printf("%d -> %d", merged_items[0].key, merged_items[0].val);
	
	//now constructing the AVL Tree from this array of structures
	
	Tree3 = newAVLTree();
	Tree3->root = tree_construction(merged_items.d,0 , merged_items.count-1);
	
	//printf("\n------Final Union of the trees is:----\n");
	//In_Order(Tree3->root);
	
	//int i ;
	
	//int combined_size = Tree1->size + Tree2->size;
/*	
	printf("Array one is as follows :\n");
	
	for(i=0;i<Tree1->size;i++)
	{
		printf("%d and %d\n", T1[i].key, T1[i].val );
	}
*/
	
/*
printf("Now the other output is as follows:\n");
	
	for(i=0 ; i< combined_size;i++)
	{
		printf("%d and %d\n", merged_items[i].key, merged_items[i].val) ;	
	}
*/	
	 
	return Tree3;	 
	 
}




// put the time complexity analysis for InsertNode() here
//Complexity of the function is -> O(mlogn)

int InsertNode(AVLTree *T, int k, int v)
{
	//put your code here
	DUPLICATE_flag=1;
	
	T->root = insert(T->root,k,v);
	
	if(DUPLICATE_flag == 1)
	{
		T->size+=1;		
		return 1;
	}
	
	return 0;
	
	
	
}


//delete node helper function
//C
AVLTreeNode *find_min_right(AVLTreeNode *root)
{
	
	while(root->left!= NULL)
	{
		root = root->left;
	}
	
	return root;
	
}


AVLTreeNode *del(AVLTreeNode* root, int k, int v)
{
	int balance_fact = 0;
	
	if( root == NULL)
	{
		return root;
	}
	
	if (k < root->key)
	{
		root->left = del(root->left, k, v);
	}
	else if (k > root->key)
	{
		root->right = del(root->right,k,v);
	}
	
	else if(k == root->key)
	{
		if(v== root->value)
		{
			//this is our temp node that we have created.
			
			//AVLTreeNode * temp;
			//this handled the case when root node has only one child or does not have a child
			
			if(root->left == NULL || root->right==NULL)
			{
				AVLTreeNode * temp;
				
				temp = root->left ? root->left : root->right;
			
				if (temp == NULL)
				{ // this handles the case of not having any child nodes.
				
					temp = root;
					root = NULL;
				}
				else
				{
					//*temp = *root;
					*root = *temp;	
				}
				
				// deleted the temp node for this case
				free(temp);
				delete_flag = 2;	
			}
			
			
			//now we will handle case when node has two children.
			else
			{
				//the logic here is that while we are removing a node which has 
				//two children, the node that will replace this will be the minimum of the right sub-tree
				//which is left most node of the right sub tree.
				
				AVLTreeNode *temp;
				
				temp = find_min_right(root->right);
				
				root->key = temp->key;
				root->value = temp->value;
				
				root->right = del(root->right,temp->key,temp->value);
			}
			
		}
		
		else if(v < root->value)
		{
			root->left = del(root->left,k,v);
		}
		else if(v > root->value)
		{
			root->right = del(root->right,k,v);
		}
		
	}
	
	if (root == NULL)
	{
		return root;
	}
	
	//update the height of the node
	root->height = 1 + max( height(root->left), height(root->right) );
	
	//now we will check if the tree is balanced or not
	
	balance_fact = balance(root);
	
	//left left case
	if (balance_fact > 1 && balance(root->left) >0)
	{
		return right_rotation(root);
	}
	
	//Left Right Case
	if (balance_fact >1 && balance(root->left) <0)
	{
		root->left = left_rotation(root->left);
		return right_rotation(root);
	} 
	
	//Right Right Case
	
	if( balance_fact < -1 && balance(root->right)<0)
	{
		return left_rotation(root);
	}
	
	if(balance_fact <-1 && balance(root->right)>0)
	{
		root->right = right_rotation(root->right);
		return left_rotation(root);
	}
	
	return root;
}




// put your time complexity for DeleteNode() here
//Complexity of the functoin is O(logn)
int DeleteNode(AVLTree *T, int k, int v)
{
 // put your code here
 	delete_flag = 1;
 	
 	AVLTree *Tree1,*Tree2,*Tree3;
	int total_size,*counter_pointer,counter;
	
	
	AVLTreeNode *del_root ;
	
	del_root = del(T->root,k,v);
	
	if (delete_flag == 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

// put your time complexity analysis for Search() here
//Complexity of the function is : O(n)

AVLTreeNode *Search(AVLTree *T, int k, int v)
{
  // put your code here
  
  AVLTreeNode *node = T->root;
  
  while(node!=NULL)
  {
  	if (k <= node->key)
  	{
  		if (k == node->key)
  		{
  			if(v == node->value)
  			{
  				return node;	
			}
			else if (v < node->value)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
  			
		}
		else
		{
			node = node->left;
		}

	}
	else
	{
		node = node->right;
	}
  }
  
  return NULL;
}

void freeavl(AVLTreeNode *root) 
{ 
    if(root != NULL) 
    { 
         
        freeavl(root->left); 
		freeavl(root->right);
		
		free(root);
		 
    } 
} 

// put your time complexity analysis for freeAVLTree() here
//Complexity of the function : O(n)

void FreeAVLTree(AVLTree *T)
{
// put your code here
	
	freeavl(T->root);
	
	free(T);	

}

// put your time complexity analysis for PrintAVLTree() here
//complexity of the function O(n)

void PrintAVLTree(AVLTree *T)
{
 // put your code here
 
 In_Order(T->root); 
 
}

int main() //sample main for testing 
{ 
 
 int i,j;
 AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
 AVLTreeNode *node1;
 
 tree1=CreateAVLTree("stdin");
 printf("---Tree1 is as follows--- :\n");
 PrintAVLTree(tree1);
 FreeAVLTree(tree1);
 
 //you need to create the text file file1.txt
 // to store a set of items without duplicate items
 tree2=CreateAVLTree("file1.txt"); 
 printf("---Tree2 is as follows--- :\n");
 PrintAVLTree(tree2);
 tree3=CloneAVLTree(tree2);
 printf("---Tree3 is as follows--- :\n");
 PrintAVLTree(tree3);
 FreeAVLTree(tree2);
 FreeAVLTree(tree3);
 //Create tree4 
 tree4=newAVLTree();
 j=InsertNode(tree4, 10, 10);
 for (i=0; i<15; i++)
  {
   j=InsertNode(tree4, i, i);
   if (j==0) printf("(%d, %d) already exists\n", i, i);
  }
  printf("---Tree4 is as follows--- :\n");
  PrintAVLTree(tree4);
  node1=Search(tree4,20,20);
  if (node1!=NULL)
    printf("key= %d value= %d\n",node1->key,node1->value);
  else 
    printf("Key 20 does not exist\n");
  
  for (i=17; i>0; i--)
  {
    j=DeleteNode(tree4, i, i);
	if (j==0) 
	  printf("Key %d does not exist\n",i);  
    PrintAVLTree(tree4);
  }
 FreeAVLTree(tree4);
 //Create tree5
 tree5=newAVLTree();
 j=InsertNode(tree5, 6, 25);
 j=InsertNode(tree5, 6, 10);
 j=InsertNode(tree5, 6, 12);
 j=InsertNode(tree5, 6, 20);
 j=InsertNode(tree5, 9, 25);
 j=InsertNode(tree5, 10, 25);
 
 printf("---Tree5 is as follows--- :\n");
 PrintAVLTree(tree5);
 //Create tree6
 tree6=newAVLTree();
 j=InsertNode(tree6, 6, 25);
 j=InsertNode(tree6, 5, 10);
 j=InsertNode(tree6, 6, 12);
 j=InsertNode(tree6, 6, 20);
 j=InsertNode(tree6, 8, 35);
 j=InsertNode(tree6, 10, 25);
 
 printf("---Tree6 is as follows--- :\n");
 PrintAVLTree(tree6);
 tree7=AVLTreesIntersection(tree5, tree6);
 tree8=AVLTreesUnion(tree5,tree6);
 
 printf("---Tree7 is as follows--- :\n");
 PrintAVLTree(tree7);
 printf("---Tree8 is as follows--- :\n");
 PrintAVLTree(tree8);
 
 return 0; 
}
