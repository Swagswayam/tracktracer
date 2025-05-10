#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include<time.h>
// Define ANSI color escape codes
#define green   "\x1b[32m"
#define red     "\x1b[31m"
#define reset   "\x1b[0m"  // Reset color to default
#define orange  "\033[38;2;255;165;0m"
#define blue    "\033[34m"
#define yellow  "\033[33m"
#define boldreset  "\033[0m"
#define bold   "\033[1m"



int main() {

    system("clear");

    // Define the initial message to be sent to the client
    char server_message[256] = "Welcome! You have connected to the server.\0";

    // Create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error: Socket creation failed");
        exit(1);
    }

    // Define server address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);//host to network short
    server_address.sin_addr.s_addr = INADDR_ANY;//Binds the socket to all available network interfaces on the machine

    // Bind the socket to the specified IP address and port
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error: Socket binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error: Socket listening failed");
        exit(1);
    }

 printf(yellow"\t\t\tWELCOME TO THE ADMIN SYSTEM\n");

    // Accept a client connection
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) {
        perror("Error: Accepting client connection failed");
        exit(1);
    }

    // Send initial welcome message to client
    send(client_socket, server_message, strlen(server_message), 0);
 
    // Prompt the client to enter the passkey
 // Generate a random OTP (4-digit)
    int otp = rand() % 10000;
    printf("Generated OTP: %d\n", otp);

    // Send the OTP to the client
send(client_socket, &otp, sizeof(otp), 0);

     if (recv(client_socket, &otp, sizeof(otp), 0) <= 0) {
        perror("Error: Passkey reception failed");
        close(client_socket);
        close(server_socket);
        exit(1);
    }
   
       
 printf("OTP sent to the client\n");

    char passkey_prompt[20] = "\nEnter passkey: ";
    send(client_socket, passkey_prompt, strlen(passkey_prompt), 0);

    // Receive passkey from client
    
    int passkey;
    if (recv(client_socket, &passkey, sizeof(passkey), 0) <= 0) {
        perror("Error: Passkey reception failed");
        close(client_socket);
        close(server_socket);
        exit(1);
    }
    printf(bold green"\n1)PASSKEY RECEIVED BY PASSENGER IS %d\n",passkey);

 
        
        
 
 if (passkey == otp) {

char nam_prompt[30] = "Enter passenger's name: ";
        send(client_socket, nam_prompt, strlen(nam_prompt), 0);
        


        // Receive age from client
         char nam[30];
        if (recv(client_socket, &nam, sizeof(nam), 0) <= 0) {
            perror("Error: Age reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
          printf(orange"PASSENGER IS %s\n",nam);


    
    char date_prompt[60] = "Enter your date of travel(DD/MM/YY): ";
        send(client_socket, date_prompt, strlen(date_prompt), 0);
        


        // Receive age from client
         char date[30];
        if (recv(client_socket, &date, sizeof(date), 0) <= 0) {
            perror("Error: Age reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
          printf(orange"DATE CHOSEN BY PASSENGER IS %s\n",date);
   // Prompt the client to enter their age
   
        char age_prompt[50] = "Enter age of passenger: ";
        send(client_socket, age_prompt, strlen(age_prompt), 0);
        // Receive age from client
        int age;
        if (recv(client_socket, &age, sizeof(age), 0) <= 0) {
            perror("Error: Age reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
        printf(blue"AGE OF PASSENGER IS %d\n",age);




    char gender_prompt[60] = "WHAT IS PASSENGER'S GENDER? ";
        send(client_socket, gender_prompt, strlen(gender_prompt), 0);

        // Receive train choice from client
      char gender;
        // recv(client_socket, &train_choice, sizeof(train_choice), 0);
        if (recv(client_socket, &gender, sizeof(gender), 0) <= 0) {
            perror("Error: Train choice reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
        printf("Gender of passenger is: %c\n", gender);

       // Prompt the client to choose a train
        char train_prompt[50] = "WHICH TRAIN WOULD PREFER FOR TRAVELLING (A/B/C)? ";
        send(client_socket, train_prompt, strlen(train_prompt), 0);

        // Receive train choice from client
        char train_choice;
        // recv(client_socket, &train_choice, sizeof(train_choice), 0);
        if (recv(client_socket, &train_choice, sizeof(train_choice), 0) <= 0) {
            perror("Error: Train choice reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
         printf(green"TRAIN CHOSE BY PASSENGER IS %c\n",train_choice);

         char seatprompt[100]= "CHOOSE YOUR SEAT(1 is occupied and 0 is vacant)\nFor choosing count from left to right:\n ";
         send(client_socket, seatprompt, strlen(seatprompt), 0);
        int seat[3][3];
            if (recv(client_socket, &seat, sizeof(seat), 0) <= 0) {
            perror("Error: Train choice reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
            int n;
            if (recv(client_socket, &n, sizeof(n), 0) <= 0) {
            perror("Error: Train choice reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }

        printf("SEAT CHOSEN BY PASSENGER IS %d\n",n);
        printf("Updated seat matrix:\n");
        for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
        printf("%d ",seat[i][j]);
  }
        printf("\n");
}
     
        FILE *fptr;
        fptr= fopen("ticket.txt", "a");
        
            fprintf(fptr, "Name: %s\n", nam);
            fprintf(fptr, "Seat no.: %d\n", n);
        fprintf(fptr,"Passkey: %d\n Date: %s\n Age: %d\n Train Choice: %c\n", passkey, date, age, train_choice);
        fclose(fptr);
        
         char food_prompt[60] = "DO YOU WANT TO ORDER FOOD(Y/N): ";
        send(client_socket, food_prompt, strlen(food_prompt), 0);
        
// Receive age from client
         char food[20];
        if (recv(client_socket, &food, sizeof(food), 0) <= 0) {
            perror("Error: Food reception failed");
            close(client_socket);
            close(server_socket);
            exit(1);
        }
        if(food=="Y"|| food== "y"){
          printf(orange"Passenger wants to order!!\n");
        
        } }


    
    else {
        // Send access denied message to client
        char access_denied_message[] = "Invalid passkey. Access denied.";
        send(client_socket, access_denied_message, strlen(access_denied_message), 0);
        printf("Invalid passkey. Access denied.\n");
    
    
    // Close the client socket
    close(client_socket);

    // Close the server socket
    close(server_socket);} 
 
    return 0;
    } 

    