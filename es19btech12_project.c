//in this code i considered max edges that a particular vertex can be a part of
//time complexity is very high(try for 10000,500)

//Please refer to "es19btech12_project_doc.docx" for explanation of the graph and 10000,3000 debugging

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_VERTICES 10000   //10000
#define MAX_EDGES 500  //3000

struct graph_node   
{   
    //defining struct graph_node which is used for neighbours
    int neighbour_node_number;  
    struct graph_node* next;
};

struct list
{
    //defining list for vertices
    int vertex;
    struct graph_node* list_head;
    char status;
    int pred_inf_time;
    int recovery_time;
    int number_of_edges_left;
};

struct node
{
    //defining node for priority queue events
    int priority_time;
    struct list* node;
    char action;
    int node_number;
    struct node* next;
}*start=NULL,*q;    //declaring global struct node* start and  struct node* q

void insert(struct list* A[],int node_number,int time_to_be_executed,char action_to_be_done)
{
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->node = A[node_number];  //assigning values
    new->node_number = node_number;
    new->action=action_to_be_done;
    new->priority_time=time_to_be_executed;
    new->next=NULL; //setting next link to NULL
    if(start==NULL )
    {
        start=new;
    }
    else if(start!=NULL && time_to_be_executed<=start->priority_time)   //if inserted node has higher priority than start or same priority as start
    {   
        new->next=start;
        start=new;  //new becomes the new head
    }
    else
    {
        q=start;
        while(q->next != NULL && q->next->priority_time<=time_to_be_executed)
        {
            q=q->next;  //traversing to the node after which it should be inserted
        }
        new->next=q->next;  //inserting in the middle of q and q->next
        q->next=new;
    }
}
 
void delete()
{
    if(start==NULL) //in case queue is empty, delete is not possible
    {
        printf("\nQUEUE UNDERFLOW\n");
    }
    else
    {
        q=start;
        start=start->next;
        free(q);  //deleting the priority queue head
    }
}

int number_of_vertices; //global variables for number of vertices and edges
int number_of_edges;

int check_array_for_repetition(int initial_infectands[],int infected,int number_initially_infected)
{
    for(int i=0;i<number_initially_infected;i++)    //loops for all elements
    {
        if(initial_infectands[i]==infected)
        {
            return 2;   //return 2 if repetition present
        }
    }
    return 1;   //return 1 if no repetitions
}

/*void print_graph(struct list* A[])
{
    printf("The Graph is:\n");
    for(int i=0;i<number_of_vertices;i++)   //loop through vertices
    {
        struct graph_node* temp = A[i]->list_head;
        printf("%d: ",i);   //print node number
        while(temp!=NULL)  //if list is empty
        {
            printf("%d, ",temp->neighbour_node_number); //print the neighbour node
            temp=temp->next;    //traverse through the list
        }
        printf("\n");
    }

    printf("\n\n");
}*/

int times_counter,I_counter,S_counter,R_counter;  //global int variables to count number of elements in each list
int number_days=1;  //to traverse and print days

void print_arrays(int S[],int I[],int R[],int times[])
{
    if(times_counter < 1)    //in case we are still on day 0
    {
        return;
    }

    int day = times[times_counter-1];   //calculating which day we are on,ie,last element of array

    do
    {
        printf("Day %d: ",number_days); // represents the number of the day

        int j=0,k=0,l=0;
        printf("S: ");
        for(j=0;j<S_counter;j++)    //traversing through each list and printing each element
        {
            printf("%d, ", S[j]);
        }
        printf("\n");
        printf("I: ");
        for(k=0;k<I_counter;k++)
        {
            printf("%d, ", I[k]);
        }
        printf("\n");
        printf("R: ");
        for(l=0;l<R_counter;l++)
        {
            printf("%d, ", R[l]);
        }
        printf("\n");
        printf("\n");

        number_days++;
        
    }while(number_days < day);  //happens for each day before the actual day start->priority_time
    
}

void print_initial_array(int S[],int I[],int R[])
{
    printf("Day 0: ");

    int j=0,k=0,l=0;
    printf("S: ");
    for(j=0;j<S_counter;j++)    //traversing through each list and printing each element
    {
        printf("%d, ", S[j]);
    }
    printf("\n");
    printf("I: ");
    for(k=0;k<I_counter;k++)
    {
        printf("%d, ", I[k]);
    }
    printf("\n");
    printf("R: ");
    for(l=0;l<R_counter;l++)
    {
        printf("%d, ", R[l]);
    }
    printf("\n");
    printf("\n");
}

int find_in_array(int array[], int size, int keyToBeSearched) 
{ 
    int i; 
    //finding & returning the position of the element 
    for (i = 0; i < size; i++)
    {
        if (array[i] == keyToBeSearched) 
        {
            return i;
        }
    } 

    return -1; 
}

//key_to_insert = element to be inserted in the array
// size of the array
int add_to_array(int arr[], int number_of_elements, int key_to_insert, int size) 
{ 
    // check if the capacity of the array is already full 
    if (number_of_elements >= size)
    {
        return number_of_elements;
    } 
    //if not then the element is inserted at the last index and the new array size is returned
    arr[number_of_elements] = key_to_insert; 
    return (number_of_elements + 1); 
}


// size is the size of the array
// key_to_delete is the element to be deleted from the array
int delete_from_array(int array[], int size, int key_to_delete) 
{ 
    // calling find_in_array function to get the position of the element which needs to be deleted
    int pos = find_in_array(array, size, key_to_delete); 
    // if element is not found then it prints Element not found and returns the original size
    if (pos == -1) 
    {  
        return size; 
    } 
    // otherwise it deletes the element & moves rest of the element by one position
    int i; 
    for (i = pos; i < size - 1; i++) 
    {
        array[i] = array[i + 1];
    }
     
    return (size-1); 
} 

int calculate_gamma(int recovery_rate)  //recovery rate is 20%
{
    srand(time(NULL));
    int x = rand() % 100;
    int i=1;
    while(x >= recovery_rate)   //while x is not head = (80%)
    {   
        x = rand() % 100;
        i++;
    }
    return i;
}

int calculate_tou(int transmission_rate)  //transmission rate is 50%
{
    srand(time(NULL));
    int x = rand() % 100;
    int i=1;
    while(x >= transmission_rate)   //while x is not head(50%)
    {   
        x = rand() % 100;
        i++;
    }
    return i;
}

void find_trans(struct list* A[],struct node* start,int time,int transmission_rate,struct list* u,struct graph_node* v,int t_max)
{
    if(A[v->neighbour_node_number]->status=='S')    //if v vertex is S
    {
        int inf_time = time + calculate_tou(transmission_rate);   //find when it will be infected

        if(inf_time < u->recovery_time && inf_time < A[v->neighbour_node_number]->pred_inf_time  && inf_time < t_max) //inf_time must be minimum of these 3 //2nd condition makes sure that v is not initial infectand
        {
            insert(A,v->neighbour_node_number,inf_time,'T');    //insert node number v,time inf_time,action transmit
            A[v->neighbour_node_number]->pred_inf_time = inf_time;  //giving new value of pred_inf_time
        }
    }
}

int print_checker=0;  //global variable for print check

void trans_process(struct list* A[],int node_number,int t,int transmission_rate,int recovery_rate,int times[],int S[],int I[],int R[],struct node* start,int t_max)
{   
    struct list* u = A[node_number];    //taking u as A[node_number]

    if(print_checker!=t)    //this makes sure that when there are multiple events in a day, print doesnt occur more than once
    {
        print_checker=t;    //set value to current day
        if(t!=0)  //only add to times if t is not 0
        {
            times_counter=add_to_array(times,times_counter,t,t_max);  //add to times,R and delete from I
        }
        print_arrays(S,I,R,times);  //print all the before hand days before changing the arrays
    }
    
    S_counter = delete_from_array(S, S_counter, node_number); //remove element u from S 
    I_counter=add_to_array(I,I_counter,node_number,number_of_vertices); //add element to I

    u->status='I';  //marking as I
    u->recovery_time = t + calculate_gamma(recovery_rate);    //calculating recovery time of u
    if(u->recovery_time<t_max)  //recovery should happen before the max time
    {
        insert(A,node_number,u->recovery_time,'R');    //insert node number u,time u.recovery_time,action recover
    }

    struct graph_node* temp5 = u->list_head;    //temp5 is used to traverse the neighbours of u
    while(temp5!=NULL)
    {
        find_trans(A,start,t,transmission_rate,u,temp5,t_max);    //call to find_trans function for the particular neighbour
        temp5 = temp5->next;
    }

    delete();   //delete the queue node from queue
}

void recover_process(int node_number,struct list* A[],int t,int times[],int S[],int I[],int R[],int t_max)
{
    struct list* u = A[node_number];    //taking u as A[node_number]

    if(print_checker!=t)    //this makes sure that when there are multiple events in a day, print doesnt occur more than once
    {
        print_checker=t;    //set value to current day
        if(t!=0)  //only add to times if t is not 0
        {
            times_counter=add_to_array(times,times_counter,t,t_max);  //add to times,R and delete from I
        }
        print_arrays(S,I,R,times);  //print all the before hand days before changing the arrays
    }
    I_counter=delete_from_array(I,I_counter,node_number);   //delete from I
    R_counter=add_to_array(R,R_counter,node_number,number_of_vertices); //add to R

    u->status='R';  //mark as R

    delete();   //delete the queue node from queue
}

void SIR(struct list* A[],int transmission_rate,int recovery_rate,int initial_infectands[], int t_max, int number_initially_infected)   
{
    int times[t_max];
    int S[number_of_vertices],I[number_of_vertices],R[number_of_vertices];  //declaring all arrays

    for(int j=0;j<number_of_vertices;j++)    //loops for all vertices
    {
        S_counter = add_to_array(S, S_counter , j ,number_of_vertices); //add j to the array  //now S contains all the vertices initially and S_counter is updated
    }

    print_initial_array(S,I,R);

    //we have an empty priority q with head struct node *start

    for(int i=0;i<number_of_vertices;i++)
    {
        A[i]->status = 'S';     //marking everyone initially with status S
        A[i]->pred_inf_time = 3000;    //predicted inf time of A[i] is infinity(3000)  //value is above t_max
    }
    for(int j=0;j<number_initially_infected;j++)    //traversing through initially infected list
    {
        int i = initial_infectands[j];
        A[i]->pred_inf_time = 0;   //predicted infection time is 0
        insert(A,i,0,'T');   //insert node number,time 0,action transmit
    }

    while(start!=NULL)
    {
        if(start->action == 'T')    //if action is transmit
        {
            if(start->node->status =='S')      //if the transmitting node is S
            {
                trans_process(A,start->node_number,start->priority_time,transmission_rate,recovery_rate,times,S,I,R,start,t_max);    //call to trans_process
            }      
        }
        else
        {
            recover_process(start->node_number,A,start->priority_time,times,S,I,R,t_max);  //call to recover_process
        }
    }
    print_arrays(S,I,R,times);  //print any remaining days

}

int main()
{
    srand ( time(NULL) );

    //number of nodes in a graph
    number_of_vertices = (rand() % MAX_VERTICES) + 1;   //between 1 and MAX_VERTICES

    struct list* A[number_of_vertices];

    for(int i=0;i<number_of_vertices;i++)
    {
        A[i]= (struct list*)malloc(sizeof(struct list));  //allocating A[i] memory
        A[i]->list_head=NULL;   //initializing head
        A[i]->vertex=i; //allocating vertex
    }

    for(int i=0;i<number_of_vertices;i++)   //initialising number of neighbours present for each vertex
    {
        int number_of_neighbours;

        do  //calculating number of neighbours for each
        {
            number_of_neighbours = rand() % (MAX_EDGES + 1);  //number_of_neighbours a particular node can have = number of edges it is part of
        
        }while(number_of_neighbours > number_of_vertices-1);   //so that number of neighbours is not greater than number of total vertices

        if(number_of_neighbours!=0)
        {
            //creating neww as the first node/head node for list of neighbours of i
            struct graph_node* neww= (struct graph_node*)malloc(sizeof(struct graph_node)); //allocating space for neww
            neww->neighbour_node_number = -1;   //initializing value of neighbour node
            neww->next=NULL;
            A[i]->list_head = neww;
            A[i]->number_of_edges_left = number_of_neighbours;  //each head node of i will contain the value of number of edges left
        }

    }

    for(int i=0;i<number_of_vertices;i++)   //loops for each vertex
    {
        if(A[i]->list_head==NULL)
        {
            continue;  //if A[i] is NULL, there are no neighbours, therefore continue to the next i
        }

        while(A[i]->number_of_edges_left > 0)
        {   
            int neighbour_node;
            int count_check=0;
            do
            {   
                count_check++;
                if(count_check>=2)    //break from loop if it is performed 2 or more times
                {
                    break;   
                }
                neighbour_node = rand() % number_of_vertices;  //neighbour_node can be 0 to number_of_vertices-1 


            }while(neighbour_node == i || A[neighbour_node]->number_of_edges_left < 1 );    //so that no link to itself and an edge can actually be formed

            if(count_check>=2)    //decrease number of elements and break from loop and continue for next edge(so that it doesnt loop forever)
            {
                A[i]->number_of_edges_left = A[i]->number_of_edges_left - 1;    //updating number of edges left
                continue;
            }

            //traverse throught the list of i to make sure that node is inserted(without any repetitions)
            struct graph_node* tempi = A[i]->list_head;
            struct graph_node* temp1i = tempi;

            int check1=0;
            while(tempi!=NULL)  //tempi traverses to end of list
            {
                temp1i=tempi;   //keeping track of previous node
                if(tempi->neighbour_node_number==neighbour_node)
                {
                    check1++;    //increase check1 if node is already present
                }
                tempi=tempi->next;
            }
            if(check1==0 && A[i]->list_head->neighbour_node_number!=-1)    //no repetitions and we are considering the 
            {
                struct graph_node* neww= (struct graph_node*)malloc(sizeof(struct graph_node));
                neww->neighbour_node_number = neighbour_node;   //storing value of neighbour node
                neww->next=NULL;
                A[i]->number_of_edges_left = A[i]->number_of_edges_left - 1;    //updating number of edges left

                temp1i->next=neww;   //new element is added to the end of the i list
            }
            else if(check1==0 && A[i]->list_head->neighbour_node_number==-1)  //if there is only one node present in the list
            {
                A[i]->list_head->neighbour_node_number = neighbour_node;   //storing value of neighbour node
                A[i]->number_of_edges_left = A[i]->number_of_edges_left - 1;    //updating number of edges left
            }

            //traverse throught the list of neighbour_node to make sure that node is inserted(without any repetitions)
            struct graph_node* tempn = A[neighbour_node]->list_head;
            struct graph_node* temp1n = tempn;

            int check=0;
            while(tempn!=NULL)  //tempn traverses to last node
            {
                temp1n=tempn;   //keeping track of previous node
                if(tempn->neighbour_node_number==i)
                {
                    check++;    //increase check if node is already present
                }
                tempn=tempn->next;
            }
            if(check==0 && A[neighbour_node]->list_head->neighbour_node_number!=-1)    //no repetitions
            {
                struct graph_node* neww= (struct graph_node*)malloc(sizeof(struct graph_node));
                neww->neighbour_node_number = i;   //storing value of i
                neww->next=NULL;
                A[neighbour_node]->number_of_edges_left = A[neighbour_node]->number_of_edges_left - 1;    //updating number of edges left

                temp1n->next=neww;   //new element is added to the end of the neighbour_node list
            }
            else if(check==0 && A[neighbour_node]->list_head->neighbour_node_number==-1)  //if there is only one node present in the list
            {
                A[neighbour_node]->list_head->neighbour_node_number = i;   //storing value of neighbour node
                A[neighbour_node]->number_of_edges_left = A[neighbour_node]->number_of_edges_left - 1;    //updating number of edges left
            }

        } 
    }
    

    int number_initially_infected = (rand() % number_of_vertices) + 1; //ranges between 1 and number_of_vertices
    int initial_infectands[number_initially_infected];

    int infected_counter=0;
    for(int i=0;i<number_initially_infected;i++)
    {
        int infected;
        do
        {
            infected = rand()% number_of_vertices;       //ranges between 0 and number_of_vertices-1

        } while (check_array_for_repetition(initial_infectands,infected,infected_counter) == 2);   //looping so that repeated element is not present
        
        initial_infectands[i] = infected;   //storing the infected element within the array
        infected_counter++;
    }

    SIR(A,50,20,initial_infectands,300,number_initially_infected);    //perform SIR for 300 days with rates 50% and 20%
}

