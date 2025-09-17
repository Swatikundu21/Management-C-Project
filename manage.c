#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
    char name[30];
    char password[30];
} User;

User users[10];
int count = 0;

void reg();
int login();
void fix(char*);
void mask(char*);

int main() {
    int n, index;

    do {
        printf("Welcome to User Management\n");
        printf("Enter your choice:");
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit\n");
        scanf("%d", &n);
        while (getchar() != '\n');  // Clear input buffer after scanf

        switch (n) {
            case 1:
                reg();
                break;

            case 2:
                index = login();
                if (index >= 0) {
                    printf("Login successful. Welcome %s\n", users[index].name);
                } else {
                    printf("\nLogin failed! Incorrect username or password.\n");
                }
                break;

            case 3:
                printf("Exiting Program\n");
                break;

            default:
                printf("Invalid Choice. Please Try Again\n\n");
                break;
        }
    } while (n != 3);

    return 0;
}

void reg() {
    if (count == 10) {
        printf("\nMaximum %d users are supported. No more registrations allowed!\n", count);
        return;
    }

    int new_index = count;

    printf("\nRegister a new user\n");
    printf("Enter username:\n");
    fgets(users[new_index].name, 30, stdin);
    fix(users[new_index].name);
    mask(users[new_index].password);
    printf("\nRegistration Successful!\n");
    count++;
}

int login() {
    char temp[30], password[30];

    printf("Enter username:\n");
    fgets(temp, 30, stdin);
    fix(temp);
    mask(password);

    for (int j = 0; j < count; j++) {
        if (strcmp(temp, users[j].name) == 0 && strcmp(password, users[j].password) == 0) {
            return j;
        }
    }

    return -1;
}

void fix(char* string) {
    int i = strcspn(string, "\n");
    string[i] = '\0';
}

void mask(char* password) {
    struct termios oldt, newt;
    int i = 0;
    char ch;

    printf("Enter password: ");

    // Turn echoing off
    tcgetattr(STDIN_FILENO, &oldt);       // get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ECHO);              // disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read password char-by-char and print '*'
    while ((ch = getchar()) != '\n' && ch != EOF && i < 29) {
        password[i++] = ch;
        printf("*");
        fflush(stdout);
    }
    password[i] = '\0';

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\n");
}
