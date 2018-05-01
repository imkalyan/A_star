#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
	int matrix[4][4];
	struct node *parent;
	int cost;
	int level;
	int x,y;
	struct node *next;
}NODE;
typedef struct queue{
	NODE data;
	struct queue *next;
}Queue;
void swap(int a,int b)
{
	int temp=a;
	a=b;
	b=temp;
}
NODE *createnode(int mat[4][4],int x,int y,int a,int b,NODE *parent,int level)
{
	NODE *node = (NODE*)malloc(sizeof(NODE));
	node->parent=parent;
	

	memcpy(node->matrix, mat, sizeof node->matrix);
	swap(node->matrix[x][y],node->matrix[a][b]);
	node->x=a;
	node->y=b;
	node->cost=INT_MAX;
	node->level=level;
	node->next=NULL;
	return node;
	
} 
int misplacedtiles(int mat[][4],int goal[][4])
{
	int cost=0;
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
		{
			if(mat[i][j]!=goal[i][j] && mat[i][j]!=0)
				cost+=1;
		}
	}
	return cost;
}
int misplacedtiles1(int mat[][4],int goal[][4])
{
	int cost=0;
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
		{
			if(mat[i][j]!=goal[i][j] && mat[i][j]!=0)
				cost+=1;
		}
	}
	return cost;
}
NODE *insertdata(NODE* head,NODE *data)
{
	NODE *temp=head;
	//Queue *newnode=(Queue*)malloc(sizeof(Queue));
	//newnode->data=data;
	//printf("%d",(newnode->data)->level);
	//newnode->next=NULL;
	if (head==NULL){
		temp->cost=data->cost;
		temp->x=data->x;
		temp->y=data->y;
		temp->level=data->level;
		memcpy(temp->matrix,data->matrix,sizeof temp->matrix );
		temp->parent=data->parent;

		return temp;
	}
	else{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}	
		temp->cost=data->cost;
		temp->x=data->x;
		temp->y=data->y;
		temp->level=data->level;
		memcpy(temp->matrix,data->matrix,sizeof temp->matrix );
		temp->parent=data->parent;

	}	

	return head;
}

int empty(Queue *head)
{
	if(head->next!=NULL)
	{
		return 1;
	}
	return 0;
}
NODE *extractmin(NODE *head)
{
	//printf("asq");
	NODE *temp=head;
	NODE *temp1=head;
	int min=INT_MAX;
	//printf("%d",temp.cost);
	
	while(temp!=NULL)
	{
		//NODE *data=temp;
		
		if(min > temp->cost){//printf("as1");																					//check
			min=temp->cost;
		}
		temp=temp->next;
	}
	while(temp1!=NULL)
	{
		
		if(temp1->cost==min){
			NODE *newnode=(NODE*)malloc(sizeof(NODE));
			newnode->x=temp1->x;
			newnode->y=temp1->y;
			newnode->cost=temp1->cost;
			newnode->level=temp1->level;
			newnode->parent=temp1->parent;
			memcpy(newnode->matrix,temp1->matrix,sizeof newnode->matrix);
			return newnode; 
		}
		temp1=temp1->next;
	}
}
int isSafe(int x, int y)
{
    return (x >= 0 && x < 4&& y >= 0 && y < 4);
}
int check(NODE temp,int mat[][4])
{
	int i,j;
	for( i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(temp.matrix[i][j]!=mat[i][j])
				return 0;
		}
	}
	return 1;
}
 /*void pop(Queue *head,int data[][4])

 {
 	printf("as \n");
 	Queue *temp=head;
 	printf("as1 \n");
 	Queue *temp2=NULL;
 	printf("ads");
 	while(temp!=NULL)
 	{
 		
 		if(check(temp,data))
 		{
 			temp=temp2;
 			
 			temp->next=(temp->next)->next;
 			
 		}
 		
 		else{
 			temp2=temp;
 			temp=temp->next;
 		}
 		
 	}
 
 }*/
 int findlength(Queue *temp)
 {
 	Queue *head=temp;
 	int c=0;
 	while(head!=NULL)
 	{
 		c++;
 		head=head->next;
 	}
 	return c;
 }
 NODE *closed;
 void mark_visited(NODE* root,NODE* parent){
	
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	int i,j;
		//printf("%d %d %d %d\n",x,y,newx,newy);
		temp->parent = parent;
		for( i=0;i<4;i++){
			for( j=0;j<4;j++){	
				temp->matrix[i][j]=root->matrix[i][j];
			}
		}
		temp->cost = root->cost;	
		temp->x = root->x;
		temp->y = root->y; 
		temp->level=root->level;
		temp->next = closed;
		closed = temp;
		
	
}
 
 
 
int check_visited_closed(NODE* root){ 
 
 	//printf("adasddsa\n");
 	//PrintNode(root);
 	NODE* temp=closed;
 	//printf("i am hererr \n");
 	while(temp!=NULL){
 		int count=0,i,j;
 		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if (temp->matrix[i][j]!=root->matrix[i][j]){
					count++;
					break;
				}
			}
			if(count)
			{
				count=0;
				break;
			}
		}
		//printf("%d\n",count);
		if(i==4 && j==4){
			
			
			return 1;
		}
		temp=temp->next;
 	}
 	return 0;
 		
}

void solvepuzzle(int mat[][4],int x,int y,int goal[][4])
{
	NODE *node=createnode(mat,x,y,x,y,NULL,0);
	NODE *head=(NODE*)malloc(sizeof(NODE));
	int cost=misplacedtiles(mat,goal);
	node->cost=cost;

	int row[] = { 1, 0, -1, 0 };
	int col[] = { 0, -1, 0, 1 };
	//printf("%d",node->y);
	head=insertdata(head,node);

	
	//printf("%d",(head->data).cost);
	NODE *temp=head;
	NODE *temp1=head;

	NODE *min;
	/*while(temp!=NULL)
	{
	
		min =extractmin(head);
		/*
		//printf("a \n");
		//pop(temp1,min->matrix);
		//printf("%d %d ",min->x,min->y);
		if(min->cost==0)
			{
				printf("asd");
				break;
			}
		else{
			if(check_visited_closed(min)==0){
			int i;
			for ( i = 0; i < 4; i++)
        	{
         	   if (isSafe(min->x + row[i], min->y + col[i]))
            	{
            		
                	// create a child node and calculate
                // i	ts cost
               		 NODE* child = createnode(min->matrix, min->x,
                              min->y, min->x + row[i],
                              min->y + col[i], min,
                              min->level + 1);
                		child->cost = misplacedtiles(child->matrix, goal);
 					temp=insertdata(temp,child);
                // Add child to list of live nodes
               }
        	}
        //	printf("%d\n\n",z);					
			}	
		}
	
		/*
		else
		{
			int d=findlength(temp);
			printf("%d ",d);
			break;
		}
		
		mark_visited(min,min->parent);
	}*/
	//printf("%d",(head->data)->x);	*/
}
int main()
{
	//int matrix[4][4],parent,level,x,y,cost;
	int matrix[4][4] =
    {
        {1, 2, 3,4},
        {5, 6, 7,8},
        {9, 10, 11,12},
        {0,14,15,13}
    };
 
    // Solvable Final configuration
    // Value 0 is used for empty space
    int final[4][4] =
    {
        {1, 2, 3,4},
        {5, 6, 7,8},
        {9, 10, 11,12},
        {13,14,15,0}
    };
 
    // Blank tile coordinates in initial
    // configuration
    int x = 1, y = 2;
 	solvepuzzle(matrix,x,y,final);
	
	return 0;
}