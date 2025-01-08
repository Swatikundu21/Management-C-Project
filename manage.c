#include <stdio.h>
#include<string.h>

typedef struct {
    char name[30];
    char password[30];
}User;

User users[10];
int count=0;

void reg();
int login();
void fix(char*);
void mask(char*);


int main() {
    int n,index;
    
    do{
    printf("Welcome to User Management \n");
    printf("Enter your choice:");
    printf("\n1. Register");
    printf("\n2. Login");
    printf("\n3. Exit \n");
    scanf("%d",&n);
    
    switch(n)
    {
        case 1:
        reg();
        break;
        
        case 2:
        index = login();
        if (index>=0){
            printf("Login successful. Welcome %s", users[index].name);
        }
        else{
            printf("\nLogin failed! Incorrect username or Password.\n");
        }
        break;
        
        case 3:
        printf("Exiting Program");
        break;
        
        default:
        printf("Invalid Choice. Please Try Again\n\n");
        break;
    }


}while(n!=3);
    return 0;
}

void reg (){
    
    if(count==10){
        printf("\nMaximum %d users are supported. No more registrations allowed!\n",count);
        return;
    }
    
    int new_index = count;
    
    printf("\nRegister a new user \n");
    printf("Enter username:\n");
    fgets(users[new_index].name, 30, stdin);
    fix(users[new_index].name);
    mask(users[new_index].password);
    printf("\nRegistration Successful!");
    count++;
}

int login(){
    char temp[30],password[30];
    
     printf("Enter username:\n");
    fgets(temp, 30, stdin);
    fix(temp);
    mask(password);
    
    for(int j=0;j<count;j++){
        if (strcmp(temp,users[j].name)==0 && strcmp (password,users[j].password)){
        return j;
        
    }
    }

        
    
    return -1;
}

void mask(char* password){
    printf("\nEnter password:");
    fgets(password, 30,stdin);
    fix(password);
}

void fix(char* string){
   int i= strcspn(string,"\n");
   string[i]='\0';
}

