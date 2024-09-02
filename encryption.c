#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function Prototypes
void encryptMenu();
void decryptMenu();

void chomp(char * word);
void encrypt(char * message, char * key, int k, int f);
void decrypt(char * message, char * key, int f);
void fixChar(char c);

int main() {

    // Setting Up Randomness
    srand(time(NULL));

    // Vars
    int running = 1;
    int choice = 0;


    printf("Welcome to Monkey Encryption Software!\n\n");

    while (running) {

        printf("What would you like to do?\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            encryptMenu();
        } else if (choice == 2) {
            decryptMenu();
        } else if (choice == 3) {
            running == 0;
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }

    }

    printf("Goodbye!\n");
    return 0;
}

void encryptMenu() {

    int r = 1;
    char * message = malloc(sizeof(char) * 501);
    char * key = malloc(sizeof(char) * 4);
    FILE * file;
    char * fileName = malloc(sizeof(char) * 21);

    while (r) {

        int f;

        printf("Welcome to the encrypting menu!\n");
        printf("What would you like to encrypt?\n");
        printf("1. Short Message\n");
        printf("2. File\n");
        printf("3. Cancel\n");
        scanf("%d", &f);

        if (f == 1 || f == 2) {
            f -= 1;
        } else if (f == 3) {
            printf("Returning to menu...\n\n");
            r = 0;
            break;
        } else {
            printf("Invalid Option. Returning to menu.\n\n");
            r = 0;
            break;
        }

        int c = 0;

        printf("Do you want to encrypt with a random key or a specific one?\n");
        printf("1. Encrypt with random key\n");
        printf("2. Encrypt with a specific key\n");
        printf("3. Cancel\n");
        scanf("%d", &c);

        if (!f) {
            if (c == 1) {
                printf("What message would you like to encrypt?\n");
                printf("(Note: Max message length is 500 characters)\n");
                getchar();
                fgets(message, 100, stdin);
                chomp(message);
                printf("\n\n");
                printf("Message recieved... Encrypting...\n\n");
                encrypt(message, key, 0, f);
                r = 0;
                break;
            } else if (c == 2) {
                printf("What message would you like to encrypt?\n");
                printf("(Note: Max message length is 500 characters)\n");
                getchar();
                fgets(message, 100, stdin);
                chomp(message);
                printf("What is the key you would like to use?\n");
                printf("(Note: Max length is 3 characters)\n");
                fgets(key, 100, stdin);
                chomp(key);
                printf("\n\n");
                printf("Message recieved... Encrypting...\n\n");
                encrypt(message, key, 1, f);
                r = 0;
                break;
            } else if (c == 3) {
                printf("\n");
                r = 0;
                break;
            } else {
                printf("Invalid option. Returning to menu.\n");
                r = 0;
                break;
            }
        } else if (f) {
            if (c == 1) {

                printf("Enter the name of your file, including the file extension.\n");
                printf("(Note: Max length is 20 characters, use no spaces)\n");
                getchar();
                fgets(fileName, 20, stdin);
                chomp(fileName);
                printf("\nOpening %s...\n", fileName);
                
                file = fopen(fileName, "r");

                if (file == NULL) {
                    printf("Invalid File. Returning to menu.\n");
                    break;
                }

                fgets(message, 500, file);
                printf("Message recieved... Encrypting...\n\n");
                encrypt(message, key, 0, f);

                fclose(file);
                r = 0;
                break;
            } else if (c == 2) {

                printf("Enter the name of your file, including the file extension.\n");
                printf("(Note: Max length is 20 characters, use no spaces)\n");
                getchar();
                fgets(fileName, 20, stdin);
                chomp(fileName);
                printf("What is the key you would like to use?\n");
                printf("(Note: Max length is 3 characters)\n");
                fgets(key, 100, stdin);
                chomp(key);
                printf("\nOpening %s...\n", fileName);
                
                file = fopen(fileName, "r");

                if (file == NULL) {
                    printf("Invalid File. Returning to menu.\n");
                    break;
                }

                fgets(message, 500, file);
                printf("Message recieved... Encrypting...\n\n");
                encrypt(message, key, 1, f);

                fclose(file);
                r = 0;
                break;
            }
        }
    }
    free(message);
    free(key);
}

void decryptMenu() {

    char * message = malloc(sizeof(char) * 101);
    char * key = malloc(sizeof(char) * 4);
    char * fileName = malloc(sizeof(char) * 21);
    int f = 0;
    int r = 1;
    FILE * file;

    while (r) {
        
        printf("Welcome to the decrypting menu!\n");
        printf("What would you like to decrypt?\n");
        printf("1. Short Message\n");
        printf("2. File\n");
        printf("3. Cancel\n");
        scanf("%d", &f);
        
        if (f == 1 || f == 2) {
            f -= 1;
        } else if (f == 3) {
            printf("Returning to menu...\n\n");
            r = 0;
            break;
        } else {
            printf("Invalid Option. Returning to menu.\n\n");
            r = 0;
            break;
        }

        if (!f) {

            printf("(Note: Max message length is 100 characters)\n");
            getchar();
            fgets(message, 100, stdin);
            chomp(message);
            printf("What is the key you would like to use?\n");
            printf("(Note: Max length is 3 characters)\n");
            fgets(key, 5, stdin);
            chomp(key);
            printf("\n\n");
            printf("Message recieved... Decrypting...\n\n");
            decrypt(message, key, f);

        } else if (f) {

            printf("Enter the name of your file, including the file extension.\n");
            printf("(Note: Max length is 20 characters, use no spaces)\n");
            getchar();
            fgets(fileName, 20, stdin);
            chomp(fileName);
            printf("What is the key you would like to use?\n");
            printf("(Note: Max length is 3 characters)\n");
            fgets(key, 5, stdin);
            chomp(key);
            printf("\nOpening %s...\n", fileName);
                
            file = fopen(fileName, "r");

            if (file == NULL) {
                printf("Invalid File. Returning to menu.\n");
                break;
            }

            fgets(message, 500, file);
            printf("Message recieved... Decrypting...\n\n");
            decrypt(message, key, f);

            fclose(file);
            r = 0;
            break;
        }
    }
}

void encrypt(char * message, char * key, int k, int f) {

    FILE * res;

    if (k == 0) {
        char r1 = (char)'h' + (rand() % 4); // hijk
        char r2 = (char)'A' + (rand() % 4); // ABCD
        char r3 = (char)'q' + (rand() % 4); // qrst

        key[0] = r1;
        key[1] = r2;
        key[2] = r3;
        key[3] = '\0';
    }

    for (int i = 0; i < strlen(message); i++)
    {

        // KEY 0
        if (key[0] == 'h') {
            message[i] += 1;
        } else if (key[0] == 'i') {
            message[i] += 2;
        } else if (key[0] == 'j') {
            message[i] += 3;
        } else if (key[0] == 'k') {
            message[i] += 4;
        }

        fixChar(message[i]);

        // KEY 1

        if (key[1] == 'A' && i % 2 == 0) {
            message[i] += 1;
        } else if (key[1] == 'B' && i % 2 == 0) {
            message[i] -= 1;
        } else if (key[1] == 'C' && i % 2 == 0) {
            message[i] -= 2;
        } else if (key[1] == 'D' && i % 2 == 0) {
            message[i] += 2;
        }

        fixChar(message[i]);

        // KEY 2

        if (key[1] == 'q') {
            if (i % 4 == 0) {
                message[i] += 4;
            } else if (i % 6 == 0) {
                message[i] -= 2;
            } else {
                message[i] += 1;
            }
        } else if (key[1] == 'r') {
            if (i % 4 == 0) {
                message[i] += 3;
            } else if (i % 6 == 0) {
                message[i] -= 3;
            } else {
                message[i] += 2;
            }
        } else if (key[1] == 's') {
            if (i % 4 == 0) {
                message[i] += 2;
            } else if (i % 6 == 0) {
                message[i] -= 5;
            } else {
                message[i] += 3;
            }
        } else if (key[1] == 't') {
            if (i % 4 == 0) {
                message[i] += 1;
            } else if (i % 6 == 0) {
                message[i] -= 6;
            } else {
                message[i] += 4;
            }
        }

        fixChar(message[i]);
    }

    if (!f) {
        printf("Your encrypted message: %s\n", message);
        printf("*IMPORTANT* Your key: %s\n\n", key);
    } else {
        res = fopen("result.txt", "w");
        fputs(message, res);
        printf("Your file has been encrypted.\n");
        printf("The result is stored in [result.txt].\n");
        printf("*IMPORTANT* Your key: %s\n\n", key);

        fclose(res);
    }

}

void decrypt(char * message, char * key, int f) {

    FILE * res;
    
    for (int i = 0; i < strlen(message); i++)
    {

        // KEY 0
        if (key[0] == 'h') {
            message[i] -= 1;
        } else if (key[0] == 'i') {
            message[i] -= 2;
        } else if (key[0] == 'j') {
            message[i] -= 3;
        } else if (key[0] == 'k') {
            message[i] -= 4;
        }

        fixChar(message[i]);

        // KEY 1

        if (key[1] == 'A' && i % 2 == 0) {
            message[i] -= 1;
        } else if (key[1] == 'B' && i % 2 == 0) {
            message[i] += 1;
        } else if (key[1] == 'C' && i % 2 == 0) {
            message[i] += 2;
        } else if (key[1] == 'D' && i % 2 == 0) {
            message[i] -= 2;
        }

        fixChar(message[i]);

        // KEY 2

        if (key[1] == 'q') {
            if (i % 4 == 0) {
                message[i] -= 4;
            } else if (i % 6 == 0) {
                message[i] += 2;
            } else {
                message[i] -= 1;
            }
        } else if (key[1] == 'r') {
            if (i % 4 == 0) {
                message[i] -= 3;
            } else if (i % 6 == 0) {
                message[i] += 3;
            } else {
                message[i] -= 2;
            }
        } else if (key[1] == 's') {
            if (i % 4 == 0) {
                message[i] -= 2;
            } else if (i % 6 == 0) {
                message[i] += 5;
            } else {
                message[i] -= 3;
            }
        } else if (key[1] == 't') {
            if (i % 4 == 0) {
                message[i] -= 1;
            } else if (i % 6 == 0) {
                message[i] += 6;
            } else {
                message[i] -= 4;
            }
        }

        fixChar(message[i]);
    }


    if (!f) {
        printf("Your decrypted message: %s\n", message);
        printf("*IMPORTANT* Your key: %s\n\n", key);
    } else {
        res = fopen("result.txt", "w");
        fputs(message, res);
        printf("Your file has been decrypted.\n");
        printf("The result is stored in [result.txt].\n");
        printf("*IMPORTANT* Your key: %s\n\n", key);

        fclose(res);
    }
}

void chomp(char * word) {
    word[strlen(word)-1] = '\0';
}

void fixChar(char c) {
    // Stop character overflow and underflow
        if (c > 122) {
            c -= 90;
        }
        if (c < 32 && c > 0) {
            c += 90;
        }
}