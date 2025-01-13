#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int visited[22];


// Structure of the tourist places
//Name, Entry fee and the rating of the place is taken

struct place
{
    char Pname[20];
    int Pprice;
    float Prating; //out of 5
};

//Structure of the Lodges and Restuarants
//Name, room charge per day and rating of the lodge is taken

struct lodge
{
    char Lname[20];
    int Lprice;
    float Lrating;  //out of 5
};

// Structure of hospitals
// The elements are number of doctors, rooms and ambulances availabel

struct hospital
{
    char name[30];
    int no_of_doctors;
    int no_of_rooms;
    int no_of_ambulance;
};


//Structure of restaurant in the city
//The elements of the structure is food that can include any starter main course or anything

struct restaurant
{
    char food[30];
};

//Structure of road connection between the points
//There are 3 elements src and dest are the points and dist is the distance between them

struct connection
{
    int src;
    int dest;
    float dist;
};

//Structure of the toursits
//Basically the details of the tourist like name mobile_number etc


struct tourist
{
    char name[30];
    int age;
    char password[30];
    int mobile_no;
};


//Structure of the family 
//It consists of name and age of a person

struct family
{
    int age;
    char name[30];
    struct family *left;
    struct family *right;
};


//Function name: inputs_of_place
//Description: Takes and stores the data from the place_input file
//Input Parameter: number of places and the struct place P array
//Return Type: NULL


void inputs_of_place(struct place P[10], int n)
{
    FILE *fp;
    int i;

    fp = fopen("place_input.txt","r");

    //Returns Null if file is not present in the same directory
    
    if(fp == NULL)
    {
        printf("File doesn't exist!\n");
    }

    for(i=0;i<n;i++)
    {
        fscanf(fp, "%s    %d    %f\n", &P[i].Pname, &P[i].Pprice, &P[i].Prating);
        //printf("%s\t%d\t%.1f\n", P[i]->Pname, P[i]->Pprice, P[i]->Prating);
    }

    fclose(fp);

}


//Function name: inputs_of_lodges
//Description: Takes and stores the data from the lodge_input file
//Input Parameter: number of lodges and the struct lodge L array
//Return Type: NULL


void inputs_of_lodge(struct lodge L[8], int n)
{
    FILE *fp;
    int i;

    fp = fopen("lodge_input.txt","r");

    //Returns Null if file is not present in the same directory
    
    if(fp == NULL)
    {
        printf("File doesn't exist!\n");
    }

    for(i=0;i<n;i++)
    {
        fscanf(fp, "%s   %d   %f\n", &L[i].Lname, &L[i].Lprice, &L[i].Lrating);
        //printf("%s   %d   %.1f\n", L[i].Lname, L[i].Lprice, L[i].Lrating);
    }

    fclose(fp);

}


//Function name: inputs_of_routes
//Description: Takes and stores the data from the distance file into an 2D array
//Input Parameter: An 2D array of float datatype and
//                 number of various postion of the city
//Return Type: NULL


void inputs_of_routes(float C[22][22], int n)
{
    FILE *fp;
    int i,j;

    fp = fopen("Distance.txt","r");

    //Returns Null if file is not present in the same directory
    
    if(fp==NULL)
    {
        printf("File doesn't exist!\n");
    }

    for(i=0;i<n;i++)
    {

        for(j=0;j<n;j++)
        {
            fscanf(fp,"%f   ",&C[i][j]);
        }

        fscanf(fp,"\n\n");

    }

}


//Function name: menu
//Description: Displays what functions you can do in city
//Input parameter: NULL
//Return type: NULL


void menu()
{
    printf("\n------------------------------------------------------\n");
    printf("\t\t\tMENU\n");
    printf("------------------------------------------------------\n\n");

    printf("0 - Know about our city\n");
    printf("1 - Distance between any two points in the city\n");
    printf("2 - Get all the lodges in the city\n");
    printf("3 - Get all the Tourist places in the city\n");
    printf("4 - Tourism packages\n");
    printf("5 - The minimum distance to travel every point in the city\n");
    printf("6 - Visit a popular places based on rating under the given budget including the staying at lodge\n");
    printf("7 - Get unique tourister id\n");
    printf("8 - Display your family tree\n");

    printf("---------------------------------------------------------\n");
}


//Function name: city_info
//Description: displays the beauty of the city that is stored in a file
//Input parameter: NULL
//Return typr: NULL;


void city_info()
{
    FILE *fp;
    char c;

    fp = fopen("welcome.txt","r");

    //Checking if the file exist or not
    
    if(fp == NULL)
    {
        printf("File is empty\n");
    }

    printf("\n");

    while((c = fgetc(fp)) != EOF)
    {
        //Printing the content from the file
        
        printf("%c",c);
    }

    printf("\n");

    fclose(fp);

}


//Function Name:   Shortest_path
//Description:     Displays the user the shortest distance between any two positions in the city
//Input parameter: Size of the various position
//                 and a 2D array of float datatype
//Return type:     NULL


void Shortest_path(float C [22][22], int n, int source, int dest)
{
    int i,j,k;

    inputs_of_routes(C,n);

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (C[i][k] + C[k][j] < C[i][j])
                {
                
                    C[i][j] = C[i][k] + C[k][j];
                
                }
            
            }
        
        }
    
    }

    printf("The distance between the place %d and the place %d is = %.2f kms\n",source,dest,C[source][dest]);

}


//Function Name : print_lodge
// Description : This function prints the sorted structure of lodge
//Input parameter : structure lodge and the number of lodges
//Return type : NULL


void print_lodge(struct lodge L[], int n)
{
    int i;

    printf("Slno\tName\tPrice\tRating\n");

    for(i=0;i<n;i++)
    {
        printf("%d\t%s\t%d\t%.2f\n",i+1,L[i].Lname,L[i].Lprice,L[i].Lrating);
    }

}


//Function Name : print_place
// Description : This function prints the sorted structure of places
//Input parameter : structure place and the number of tourist places
//Return type : NULL


void print_place(struct place P[10], int n)
{
    int i;

    printf("Slno.\tName\tPrice\tRating\n");

    for(i=0;i<n;i++)
    {
        printf("%d\t%s\t%d\t%.2f\n",i+1,P[i].Pname,P[i].Pprice,P[i].Prating);
    }

}


//Function name : swap
//Descritption : swaps two position
//Input parameter : pointers of two position of the structure
//Outpur parameter : NULL


void swap(struct lodge *A , struct lodge *B)
{
    struct lodge temp;

    temp = *A;
    *A = *B;
    *B = temp;

}


//Function name : partition
//Description : Its a sub function of quick sort where the actual swap of the structure happens
//Input parameter : structure of lodge and left and right position
//Return type : Null


int partition(struct lodge L[8],int l, int r){
    float p;
    int i,j;

    p = L[l].Lrating;
    i = l;
    j = r;

    while(j>=i)
    {
        do
        {
            i++;
        }while(p>=L[i].Lrating);

        do
        {
            j--;
        }while(p<L[j].Lrating);

        if(j>i)
            swap(&L[i],&L[j]);
    }

    swap(&L[l],&L[j]);

    return j;

}


//Function name : Lodge_sort
//Description : Sorting the lodges based on their rating
//Input parameter : structure of lodge, left and right position of structure array
//Return type : Null


void Lodge_sort(struct lodge L[8], int l, int r)
{
    int s;

    if(l<r)
    {
        s = partition(L,l,r);
        //printf("%d",s);
        Lodge_sort(L,l,s);
        Lodge_sort(L,s+1,r);
    
    }

}


//Function name : Place_sort
//Description : Sorting the places based on the rating
//Input parameter : structure array of place and number of places
//Return type : NULL


void Place_sort(struct place P[10], int n)
{
    struct place temp;
    int i,j;

    for(i=0;i<n-1;i++)
    {
        
        for(j=0;j<n-1-i;j++)
        {
            
            if(P[j].Prating<P[j+1].Prating)
            {
                temp = P[j];
                P[j] = P[j+1];
                P[j+1] = temp;

            }

        
        }

    }

}


//Function name : list
//Description : Showing the user the points of the city
//Input parameter : NULL
//Return type : NULL


void list()
{
    printf("\n0 --- Station\t\t\t11 --- P8\n");
    printf("1 --- L1\t\t\t12 --- P7\n");
    printf("2 --- L2\t\t\t13 --- P6\n");
    printf("3 --- L3\t\t\t14 --- P5\n");
    printf("4 --- L4\t\t\t15 --- Restaurant\n");
    printf("5 --- L5\t\t\t16 --- P2\n");
    printf("6 --- Hosp1\t\t\t17 --- P1\n");
    printf("7 --- P10\t\t\t18 --- P3\n");
    printf("8 --- P9\t\t\t19 --- L8\n");
    printf("9 --- L6\t\t\t20 --- P4\n");
    printf("10 --- L7\t\t\t21 --- Hosp2\n");
    /*printf("12---P8\n");
    printf("13---P7\n");
    printf("14---P6\n");
    printf("15---P5\n");
    printf("16---Restaurant\n");
    printf("17---P2\n");
    printf("18---P1\n");
    printf("19---P3\n");
    printf("20---L8\n");
    printf("21---P4\n");
    printf("22---Hosp2\n");*/
}


//Function name : bfs
//Description : Does the bfs traversal
//Input parameter : An 2d array b of size 22 and number of points and source
//Return type : NULL


void bfs(int B[22][22], int n, int source)
{
    float queue[30];
    int front = 0;
    int rear =  0;
    int u,i;
    int visited[22];

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    queue[rear] = source;
    visited[source] = 1;

    printf("The BFS company's travel will be... \n");

    while (front <= rear)
    {
        u = queue[front];
        printf("%d->", u);
        front = front + 1;

        for (i = 0; i < n; i++)
        {
            if (B[u][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                rear = rear + 1;
                queue[rear] = i;
            }
        
        }
    
    }

}


//Function name : path_traversal
//Description : Reads the input of 2d array and then calls bfs function to traverse
//Input parameter : An 2d array of size 22 and number of points and source
//Return type : NULL


void path_traversal(int B[22][22], int n, int source)
{
    FILE *fp;
    int i,j;

    fp = fopen("Distance2.txt","r");

    //Returns Null if file is not present in the same directory
    
    if(fp==NULL)
    {
        printf("File doesn't exist!\n");
    }

    for(i=0;i<n;i++)
    {

        for(j=0;j<n;j++)
        {

            fscanf(fp,"%d   ",&B[i][j]);
        
        }

        fscanf(fp,"\n\n");
    }

    bfs(B,22,source);

}


//Function name : dfs
//Description : Does the dfs traversal
//Input parameter : An 2d array b of size 22 and number of points and source
//Return type : NULL


void dfs(int B[22][22], int n, int source)
{
    int i;
    visited[source] = 1;

    for(i=0; i<22; i++)
    {
       
        if(B[source][i] == 1 && visited[i] == 0)
        {

            printf("%d->", i);
            dfs(B, n, i);

        }
    
    }

}


//Function name : dfs_traversal
//Description : Reads the input of 2d array and then calls dfs function to traverse
//Input parameter : An 2d array of size 22 and number of points and source
//Return type : NULL


void dfs_traversal(int B[22][22], int n, int source)
{
    FILE *fp;
    int i,j;

    fp = fopen("Distance2.txt","r");

    //Returns Null if file is not present in the same directory
    
    if(fp==NULL)
    {
        printf("File doesn't exist!\n");
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fscanf(fp,"%d   ",&B[i][j]);
        }

        fscanf(fp,"\n\n");
    }

    for (i= 0; i < 22; i++)
    {
        //Storing the visited array from 1 to 22
        visited[i] = 0;
    
    }

    printf("The DFS company's travels will be... \n");
    printf("%d->", source);

    dfs(B,n,source);

}


//Function name : sort
//Description : Sorts the connection structure using selection sort
//Input parameter : structure of connection and number of connection
//Return type : NULL


void sort(struct connection G[],int n)
{
    int i,j;
    int min;
    struct connection temp;

    for(i=0;i<n-1;i++)
    {
         min = i;
        for(j=i;j<n;j++)
        {
            
            if(G[j].dist<G[min].dist)
            {
                min = j;
            
            }
       
        }

        temp = G[i];
        G[i] = G[min];
        G[min] = temp;
    
    }

    /*for(i=0;i<26;i++){
        printf("%d\t%d\t%.2f\n",G[i].src,G[i].dest,G[i].dist);
    }*/

}



//Function name : find
//Description : Checks whether there exist a connection already
//Input parameter : An array and the two numbers
//Return type : Return 1 if the value of array at that numbers are equal
//              else return 0


int find(int a[], int x, int y)
{
    if(a[x] == a[y])
    {
        return 1;
    }

    else
    {
        return 0;
    }

}


//Function name : unionn
//Description : establishes a  connection between two points
//Input parameter : an array and two points position
//Return type : NULL


void unionn(int a[], int p, int q)
{
    int temp = a[p];
    int i;

    for(i=0; i<22; i++)
    {
        if(a[i] == temp)
        {
            a[i] = a[q];
        }
    }

}


//Function name : Spanning
//Description : Gives the shortest  total sum to travel all the points in the city
//Input parameter : An array, a structure of connection and number of connections
//Return type : NULL


void Spanning(int a[],struct connection G[], int n)
{
    sort(G,26);

    int count = 0;
    int sum = 0;
    int i,p,q,r;

    for(i=0;i<26;i++)
    {
        if(count < 22)
        {
            p = G[i].src;
            q = G[i].dest;
            r = find(a,p,q);

            if(r==0)
            {
                unionn(a,p,q);
                count++;
                sum = sum + G[i].dist;
                //printf("%d->",G[i].src);
            }
        }

    }

    list();

    printf("\nThe total distance to travel from 0 to all the places shown above is = %d kms\n",sum);

}


//Function name : budget_places
//Description : Calculates and gives the output of the places that can be visited
//Input parameter : Structure of place, budget amount and amount after the deduction of lodge stay
//Return type : NULL


void budget_places(struct place P[10], int bud, int amt)
{
    int i;
    int count = 0;
    struct place Q[10];
    int flag = 0;

    printf("The places you can visit on your remaining amount are:\n");
    printf("Place\tPrice\tRating\n");

    Place_sort(P,10);
    //printf("%d",amt);

    for(i=0;i<10;i++)
    {
        if(bud > P[i].Pprice)
        {
            flag = 1;

            printf("%s\t%d\t%.2f\n",P[i].Pname,P[i].Pprice,P[i].Prating);
            count = count + P[i].Pprice;
            //printf("%d\n",count);
        }

        else
        {
            continue;
        }

        if(flag == 1)
        {
            bud = bud - P[i].Pprice;
        }
    }

    amt = amt - count;

    printf("Total amount remaining after visiting all the places and the stay at lodge is %d\n",amt);

}


//Function name : budget
//Description : Asks to user where would he like to stay on his budget
//Input parameter : An structure of place and lodge, budget of the user and number of days of stay
//Return type : NULL


void budget(struct place P[10], struct lodge L[8], int bud, int day)
{
    int ch;
    int x;
    int amt = bud;

    Lodge_sort(L,0,8);
    print_lodge(L,8);

    printf("Select the lodge you want to stay on your perday budget\n");
    scanf("%d",&ch);

    switch(ch)
    {
        
        case 1: 
                x = day*550;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount after spending on lodge is %d\n",bud);

                budget_places(P,bud,amt);
                break;


        case 2: 
                x = day*599;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount is %d\n",bud);

                budget_places(P,bud,amt);
                break;


        case 3: 
                x = day*650;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount is %d\n",bud);

                budget_places(P,bud,amt);
                break;


        case 4: 
                x = day*699;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount is %d\n",bud);

                budget_places(P,bud,amt);
                break;

        case 5: 
                x = day*750;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount is %d\n",bud);

                budget_places(P,bud,amt);
                break;

        case 6: 
                x = day*799;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount is %d\n",bud);

                budget_places(P,bud,amt);
                break;

        case 7: 
                x = day*899;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount is %d\n",bud);

                budget_places(P,bud,amt);
                break;

        case 8: 
                x = day*999;

                bud = bud - x;
                amt = amt - x;

                printf("The amount spent on lodge is %d\n",x);
                printf("The remaining amount is %d\n",bud);

                budget_places(P,bud,amt);
                break;


        default: 
                printf("Invalid number\n");
                break;
    
    }

}


//Function Name: insert_tree
//Description: insert the details of the structure family in to the tree
//Input parameter: a pointer structure of family F and data
//Return type: struct family*


struct family* insert_tree(struct family *F,int data)
{
    struct family *newnode,*currnode,*parent;


	newnode=(struct family *)malloc(sizeof(struct family ));

    printf("Enter the name of the person\n");
    scanf("%s",newnode->name);

	if(newnode==NULL)
	{
        printf("Family allocation failed\n");
        return F;
	}

	newnode->age = data;
 	newnode->left = NULL;
	newnode->right = NULL;

	
    if(F == NULL)
	{
		F = newnode;
		printf("Root node inserted into tree\n");
		
        return F;
	}

	currnode = F;
	parent = NULL;
	
    while(currnode != NULL)
	{
		parent = currnode;
		
        if(newnode->age < currnode->age)
        {
			currnode = currnode->left;
        }

		else
        {
			currnode = currnode->right;
        }
	
    }

	if(newnode->age < parent->age)
    {
		parent->left = newnode;
    }

	else
    {
		parent->right = newnode;
    }

    printf("Person inserted successfully into the tree\n");
    return F;
}


/*
Function Name: inorder
Input Params:  Root of the tree
Return Type:   void
Description:   Recursively visits the tree in the order of
               Left, Root, Right
*/


void inorder(struct family *froot)
{
	if(froot != NULL)
    	{
        	inorder(froot->left);
        	
            printf("%s\t%d\n",froot->name,froot->age);
        	inorder(froot->right);
	
        }

}


/*
Function Name: preorder
Input Params:  Root of the tree
Return Type:   void
Description:   Recursively visits the tree in the order of
               Root, Left, Right
*/


void preorder(struct family *froot)
{
	if(froot != NULL)
	{
        printf("%s\t%d\n",froot->name,froot->age);
        	
        preorder(froot->left);
        preorder(froot->right);
	
    }

}


/*
Function Name: postorder
Input Params:  Root of the tree
Return Type:   void
Description:   Recursively visits the tree in the order of
               Left, Right, Root
*/


void postorder(struct family *froot)
{
	if(froot != NULL)
	{
        	postorder(froot->left);
        	postorder(froot->right);
        	
            printf("%s\t%d\n",froot->name,froot->age);
	
    }

}


/*
Function Name: delete_from_bst
Input Params:  Root of the tree, item data to be deleted
Return Type:   Updated root of the tree
Description:   Deletes the specified data and re-adjusts the
               tree structure according to bst tree constraints
*/


struct family * delete_from_bst(struct family * root, int data)
{
    struct family * currnode, *parent, *successor, *p;

    // Check if the tree is empty
   
    if(root == NULL)
    {
        printf("Tree is empty\n");
        return root;
    }

    // Traverse and reach the appropriate part of the tree
    
    parent = NULL;
    currnode = root;
    
    while (currnode != NULL && data != currnode->age)
    {
        parent = currnode;
        
        if(data < currnode->age)
        {
            currnode  = currnode->left;
        }
    
        else
        {
            currnode = currnode->right;
        }
    
    }

    // If the data is not present in the tree
    
    if(currnode == NULL)  
    {
        printf("Age not found\n");
        return root;
    }

    // Check and manipulate if either left subtree is absent,
    // or right subtree is absent
    // or both are present
    
    if(currnode->left == NULL)
    {
        p = currnode->right;
    }
    
    else if (currnode->right == NULL)
    {
        p = currnode->left;
    }
    
    else
    {
	 // Process of finding the inorder successor
        
        successor = currnode->right;

        while(successor->left != NULL)
        {
            successor = successor->left;
        }

        successor->left = currnode->left;
        p = currnode->right;
    }

    // The case of root deletion
    
    if (parent == NULL) 
    {
        free(currnode);
        return p;
    }

    if(currnode == parent ->left)
    {
        parent->left = p;
    }
    
    else
    {
        parent->right = p;
    }
    
    free(currnode);
    return root;
}


//Function Name: family tree
//Description: Takes input from the user to what actions he wants to perform
//Input parameter: NULL
//Return type: NULL


void familytree()
{
    int ch = 0;
    int i;
    int data = 0;
    struct family *F = NULL;
    int exitflag = 0;
    int n;

    while(!exitflag)
    {
        //printf("\n******** Menu *************\n");
       
        printf("1- Insert the details into the tree\n");
        printf("2- Display the family details from children to parent\n");
        printf("3- Perform a pre-order realtion\n");
        printf("4- Perform a post-order relation\n");
        printf("5- Delete from a family tree\n");
        printf("Any other option to print the family tree\n");
       
       // printf("*****************************\n");

        printf("Enter your choice\n");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: 
                    printf("Enter the number of persons in the family\n");
                    scanf("%d",&n);
                    
                    for(i=0;i<n;i++)
                    {
                        printf("Enter the age of the person to be inserted\n");
                        scanf("%d", &data);
                        F = insert_tree(F,data);
                    }
                    
                    exitflag = 0;
                    break;

            case 2: 
                    if(F == NULL)
                    {
                        printf("Tree is empty\n");
                    }

                    else
                    {
                        printf("Inorder relation is...\n");
                        inorder(F);
                    }
                    
                    exitflag = 0;
                    break;

            case 3: 
                    if(F == NULL)
                    {
                        printf("Tree is empty\n");
                    }
                    
                    else
                    {
                        printf("Preorder realtion is...\n");
                        preorder(F);
                    }
                    
                    exitflag = 0;
                    break;

            case 4: 
                    if(F == NULL)
                    {
                        printf("Tree is empty\n");
                    }
                    
                    else
                    {
                        printf("Postorder relation is...\n");
                        postorder(F);
                    }
                    
                    exitflag = 0;
                    break;

            case 5: 
                    printf("Enter the age of the person to be deleted\n");
                    scanf("%d", &data);
                    
                    F = delete_from_bst(F,data);
                    
                    exitflag = 0;
                    break;

            default: 
                    exitflag = 1;
                     
                     printf("Printing your family tree tree\n");
                     break;
        
        }
    
    }

}


//Function name: Hash
//Description: Using hashing we hash the password given by the user and
//             gives the unique id to the tourist 
//Input Parameter: structure of the tourist, maximum address i.e size of
//                 the hash table and number of members
//Return Type: NULL

void hash(struct tourist T[], int maxAddress,int mem)
{
    int sum;
    int i;
    int k;

    for(i=0;i<mem;i++)
    {
        sum = 0;
        k=0;

        while(T[i].password[k]!='\0')
        {
            sum = sum + T[i].password[k];
            k++;

        }

        printf("%s\t%d\n",T[i].name,(sum%maxAddress));
    
    }

}


//Function name: Hashed
//Description: Takes the input of family members and calls the hash function
//              to give unique id
//Input Parameter: structure of the tourist and number of members
//Return Type: NULL


void Hashed(struct tourist T[], int mem)
{
    int i;
    int x;
    int maxAddress = 100;

    printf("Enter the name, age, password and mobile number of each member\n");

    for(i=0;i<mem;i++)
    {
        
        scanf("%s%d%s%d",&T[i].name,&T[i].age,&T[i].password,&T[i].mobile_no);
    
    }

    printf("The unique id of your members are\n");
    printf("Name\tId\n");

    hash(T,maxAddress,mem);

}


//Main funtion
// Takes the input of the user what actions he wants to perform

int main()
{
    struct place P[10];
    struct lodge L[8];
    struct restaurant R[18];
    struct hospital H[2];
    float C[22][22];
    int source;
    int B[22][22];
    int x;
    int a[22];
    //struct family *F;
    //char search[30];
    struct tourist T[6];

    struct connection G[26]={{0,1,0.5},{1,2,0.25},{2,3,0.05},{3,4,0.05},{4,5,0.25},{5,6,2},{6,7,0.5},
                            {7,8,1},{8,11,2},{11,12,2},{12,13,1},{13,14,2},{14,20,3},{20,21,0.5},
                            {21,18,0.3},{18,17,2},{17,1,1},{16,17,1.5},{9,16,6},{16,15,1},{15,14,1},
                            {19,14,0.5},{18,20,4},{9,8,5},{10,9,0.1},{12,10,0.5}};

    printf("\n");

   // F = NULL;

    inputs_of_place(P,10);
    inputs_of_lodge(L,8);

    printf("\n");

    int ch;
    while(1)
    {
        menu();

        printf("Enter the choice\n");
        scanf("%d",&ch);

        switch(ch)
        {
            case 0: 
                    city_info();
                    break;


            case 1: 
                    list();

                    printf("Enter the source place\n");
                    scanf("%d",&source);

                    printf("Enter the destination\n");
                    scanf("%d",&x);

                    Shortest_path(C,22,source,x);
                    break;


            case 2: 
                    printf("\nHere are the list of lodges based on their ratings\n");

                    Lodge_sort(L,0,8);
                    print_lodge(L,8);
                    break;


            case 3: 
                    printf("\n  The list of the tourist places based on the customer review\n");

                    Place_sort(P,10);
                    print_place(P,10);
                    break;


            case 4: 
                    printf("\nSelect the tourism package company:\n");

                    printf("1 ---- BFS Travels\n");
                    printf("2 ---- DFS Travels\n");
                    scanf("%d",&x);

                    if(x==1)
                    {
                        list(C);
                        printf("\nEnter the number you are currently at based on above list\n");
                        scanf("%d",&source);

                        path_traversal(B,22,source);

                        printf("%d\n",source);
                        break;
                    }

                    else if(x==2)
                    {
                        list(C);

                        printf("\nEnter the number you want to start from based on above list\n");
                        scanf("%d",&source);

                        dfs_traversal(B,22,source);

                        printf("%d\n",source);
                        break;
                    }

                    else
                    {
                        printf("Invalid input\n");
                        break;
                    }


            case 5: 
                    for(x=0;x<22;x++)
                    {
                        a[x] = x;
                    }

                    Spanning(a,G,22);
                    break;


            case 6: 
                    printf("Enter your budget amount and number of days of stay\n");
                    scanf("%d%d",&x,&source);

                    budget(P,L,x,source);
                    break;


            case 7: 
                    printf("Enter the number of members\n");
                    scanf("%d",&x);

                    Hashed(T,x);
                    break;

            case 8: 
                    printf("Build and view your family tree\n");
                    familytree();
                    break;

            default: 
                        printf("Thank You! Visit Again!!\n");
                        exit(0);
                        break;
        
        }
    
    }
    
    return 0;

}
