#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
// Define ANSI color escape codes
#define green   "\x1b[32m"
#define red     "\x1b[31m"
#define reset   "\x1b[0m"  // Reset color to default
#define orange  "\033[38;2;255;165;0m"
#define blue    "\033[34m"
#define yellow  "\033[33m"
#define boldreset  "\033[0m"
#define bold   "\033[1m"



struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *pt_2 = NULL,*newnode,*tailc = NULL;
struct node *pt_1 = NULL, *taila = NULL;
struct node *head_s;

void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add new items\n");
    printf("\t\t\t\t\t\t\t3. Delete items \n");
    printf("\t\t\t\t\t\t\t4. Display order menu\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

void customermenu()
{
    int d=8;
    printf("\n\t\t\t\t\t\t\t1. Place your order\n");
    printf("\t\t\t\t\t\t\t2. View the ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Display final bill\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

struct node* createadmin(struct node *head,int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        pt_1 = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return pt_1;
}

struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = pt_1;
    int s = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            s = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(s==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            pt_2 = tailc = newnode;
        else
        {
            int f=10;
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return pt_2;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    int b=6;
    if(temp1==NULL)
    {
        printf("\n\t\t\t\t\t\ttList is not full!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int s= 0;

    struct node *temp1 = pt_1;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                s= 1;
                break;
            }
            temp=temp->next;
        }

        if(s==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = pt_2;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* delete(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\n\t\t\t\t\t\t\tList is not full\n");
        int a=9;
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteadmin()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=pt_1;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            pt_1 = delete(num, pt_1, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

int deletecustomer()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int x;
    scanf("%d",&x);

    struct node* temp=pt_2;
    while(temp!=NULL)
    {
        if (temp->data == x)
        {
            pt_2 = delete(x, pt_2, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

void displaybill()
{
    displayList(pt_2);
    struct node *temp = pt_2;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",total_price);

}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void admin()
{
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        adminmenu();

        int o;
        scanf("%d",&o);

        if(o==5)
            break;

        switch (o)
        {
            case 1:
                displayList(head_s);
                break;
            case 2:

                printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
                int x,s = 0;
                char name[50];
                float price;
                scanf("%d",&x);

                struct node *temp = pt_1;

                while(temp!=NULL)
                {
                    if(temp->data==x)
                    {
                        printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
                        s= 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(s==1)
                    break;

                printf("\t\t\t\t\t\t\tEnter food item name: ");
                scanf("%s",name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f",&price);
                pt_1 = createadmin(pt_1, x, name, price);
                printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            case 3:
                if(deleteadmin())
                {
                    printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
                    displayList(pt_1);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");

                break;
            case 4:
                printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(pt_1);
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}

void customer()
{
    int s=0,j=1;
    char ch;
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        customermenu();

        int o;
        scanf("%d",&o);

        if(o==5)
            break;

        switch (o)
        {
            case 1:
                displayList(pt_1);
                printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                int n;
                scanf("%d",&n);
                printf("\t\t\t\t\t\tEnter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                pt_2 = createcustomer(pt_2, n, quantity);
                break;
            case 2:
                printf("\n\t\t\t\t\t\t List of ordered items ###\n");
                displayList(pt_2);
                break;
            case 3:
                if(deletecustomer())
                {
                    printf("\n\t\t\t\t\t\tUpdated list of your ordered food items\n");
                    displayList(pt_2);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculatetotsales();
                printf("\n\t\t\t\t\t\t\t  Final Bill \n");
                displaybill();
                pt_2 = deleteList(pt_2);
                printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
                fflush(stdin);
                ch=fgetc(stdin);
                s=1;
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
        if(s==1)
            break;
    }
}

void mainnenu()
{
    printf("\n                                 **************************************************************************\n");
    printf(green);
    printf("                                                     WELCOME TO TRACKY TREATS\n");
    printf("\033");
    printf("                                 **************************************************************************\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. Exit--> \n\n");
    printf("\t\t\t\t\t\t\tEnter Your Choice --->");
}

int main() {
    system("clear");
    int netsocket;
    netsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (netsocket == -1) {
        perror("Error: Socket creation failed");
        exit(1);
    }

    // Specify server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY; // Use the server's IP address here

    // Connect to the server
    int status = connect(netsocket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (status == -1) {
        perror("Error: Connection failed");
        close(netsocket);
        exit(1);
    }

    // Receive initial message from server
    char server_response[256];
    recv(netsocket, server_response, sizeof(server_response), 0);
    printf("Server says: %s\n", server_response);
memset(server_response, 0, sizeof(server_response));

 // Receive the OTP from the server
    int otp;
     recv(netsocket, &otp, sizeof(otp), 0);
    printf(orange"Server response: %d\n", otp); 
    memset(server_response, 0, sizeof(server_response));
    send(netsocket, &otp, sizeof(otp), 0);
    printf("Received OTP\n");



    recv(netsocket, server_response, sizeof(server_response), 0);
    printf(yellow"Server says: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
    // Prompt user for passkey
    int passkey;
    scanf("%d", &passkey);

   printf(bold blue"\nWELCOME!!\n");

    // Send passkey to server
     send(netsocket, &passkey, sizeof(passkey), 0);



    if (strcmp(server_response, "Invalid passkey. Access denied.") == 0) {
        // Access denied, close the socket and exit
        close(netsocket);
        return 0;
    }
    // Prompt user for date choice
   //loop
   
   char nam[30];
   recv(netsocket, server_response, sizeof(server_response), 0);
    printf(yellow"Server says: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
   
    scanf("%s", nam);
   

    // Send date choice to server
    send(netsocket, &nam, sizeof(nam), 0);

     char date[30];
    recv(netsocket, server_response, sizeof(server_response), 0);
    printf(green"Server says: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
   
    scanf("%s", date);

    // Send date choice to server
    send(netsocket, &date, sizeof(date), 0);
   

    // Receive final response from server (date confirmation)
    
    int age;
    recv(netsocket, server_response, sizeof(server_response), 0);
    printf(orange"Server response: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
    scanf("%d",&age);
    send(netsocket, &age, sizeof(age), 0);
        
    char gender;
    recv(netsocket, server_response, sizeof(server_response), 0);
    printf(yellow"Server response: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
   
    scanf(" %c", &gender);
    send(netsocket, &gender, sizeof(gender), 0);


    char train_choice;
    recv(netsocket, server_response, sizeof(server_response), 0);
    printf(orange"Server response: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
   
    scanf(" %c", &train_choice);
    send(netsocket, &train_choice, sizeof(train_choice), 0);
    int seat[3][3];
    
  while(1){  
if(train_choice=='A'){
    int seat[3][3]=  {{1 ,0 ,0},
                      {0 ,1, 0},
                      {0,0,1}};
                      break;
}
if(train_choice=='B'){
   int seat[3][3]= {{1 ,1 ,0},
                  {1 ,1, 0},
                   {0,0,1}};
                   break;
}
if(train_choice=='C'){
  int seat[3][3]= {{0 ,1 ,0},
                  {1 ,0, 0},
                  {0,0,1}};
break;
}  
else{
    printf("Invalid choice");
}       }     

for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        printf(green"%d ",seat[i][j]);
  }
    printf("\n");
}
  recv(netsocket, server_response, sizeof(server_response), 0);
    printf("Server response: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
   
  int n;
  while(1){

  scanf("%d", &n);
 if(n<=3){
    
    if(seat[0][n-1]== 1){
        printf(red"Seat already selected\n CHOOSE THE SEAT AGAIN\n");

    }
    else{
        seat[0][n-1]=1;
        printf(yellow"Seat number is %d\n", n);
        break;
    }}
    if(n>3 && n<=6){
    if(seat[1][n-4]== 1){
        printf(yellow"Seat already selected\n CHOOSE THE SEAT AGAIN\n");
    }
    else{
        seat[1][n-4]=1;
        printf(yellow"Seat number is %d\n", n);
        break;
    }}
        if(n>6 && n<=9){
    if(seat[2][n-7]== 1){
        printf(yellow"Seat already selected\n CHOOSE THE SEAT AGAIN\n");
    }
    else{
        seat[2][n-7]=1;
        printf(yellow"Seat number is %d\n", n);
        break;
    }
  }
  }
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        printf(blue"%d ",seat[i][j]);
  }
    printf("\n");
}

send(netsocket, &seat, sizeof(seat), 0);
send(netsocket, &n, sizeof(n), 0);

    printf("\nYOUR TICKET HAS BEEN BOOKED SUCCESSFULLY!\n");
    printf("TICKET\n\nName:%s\nSeat no.:%d\nDate of journey:%s\nAge:%d\nGender:%c\nTrain name:%c\n",nam,n,date,age,gender,train_choice);
    // Close the socket
    
     char food[20];
       
    recv(netsocket, server_response, sizeof(server_response), 0);
    printf(green"Server says: %s\n", server_response);
    memset(server_response, 0, sizeof(server_response));
   
  scanf("%s", food);
  
  send(netsocket, &food, sizeof(food), 0);

    if(strcmp(food, "Y")==0 || strcmp(food, "y")==0){
    pt_1 = createadmin(pt_1,1,"Pasta",100);
    pt_1 = createadmin(pt_1,2,"Pizza",200);
    pt_1 = createadmin(pt_1,3,"Manchurian Noodles",150);
    pt_1 = createadmin(pt_1,4,"Fried chicken Rice",180);
    pt_1 = createadmin(pt_1,5,"Chicken Noodles",80);

    while(1)
    {
        mainnenu();
        int select;
        scanf("%d",&select);

        if(select==3)
        {
            printf("\n\n\t\t\t\t\t\t\t########Thank you!!#######\n");
            break;
        }

        switch (select)
        {
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose right option\n");
                break;
        }
    }}
    else{
     printf("\n                                 **************************************************************************\n");
    printf("\033[0;31m");
    printf("                                                     WE WISH YOU SAFE AND HAPPY JOURNEY\n");
    printf("\033");
    printf("                                 **************************************************************************\n\n\n");
    }

    close(netsocket);
   
    return 0;
}