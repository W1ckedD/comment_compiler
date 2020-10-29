#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

bool isEmptySpace(char c);
bool isForwardSlash(char c);
bool isAsterisk(char c);
bool isEnter(char c);
bool hasFinished(char c);

int findComment(char text[]);

int main() {
    // Reading tokens from a file named "text.txt"
    FILE *fp;
    int i = 0;
    int ascii;
    char text[255] = "";
    fp = fopen("text.txt", "r");
    while((ascii = getc(fp)) != EOF) {
        char c = ascii;
        text[i] = c;
        i++;
    }
    text[i] = '\0';
    fclose(fp);

    // Identifying comments
    int code = findComment(text);

    // Logging the result
    printf("\nprogram exited with code %d \n", code);
    printf("press any key to continue... \n");
    getch();
    return 0;
}

bool isEmptySpace(char c) {
    return c == ' ';
}

bool isForwardSlash(char c) {
    return c == '/';
}

bool isAsterisk(char c) {
    return c == '*';
}

bool isEnter(char c) {
    return (int)c == 10 || (int)c == 13;
}

bool hasFinished(char c) {
    return c == '\0';
}

int findComment(char text[]) {
    int state = 0;
    int index = 0;
    char token[255] = "";
    
    do {
        char current = text[index];
        switch(state) {
            case 0:
                if (isEmptySpace(current)) {
                    state = 5;
                    token[index] = current; 
                    ++index;
                    break;
                } else if (isForwardSlash(current)) {
                    state = 1;
                    token[index] = current;
                    ++index;
                    break;
                } else {
                    printf("error\n");
                    printf("token: \n%s", token);
                    return -1;
                }
            case 1:
                if (isForwardSlash(current)) {
                    state = 6;
                    token[index] = current;
                    ++index;
                    break;
                } else if(isAsterisk(current)) {
                    state = 2;
                    token[index] = current;
                    ++index;
                    break;
                } else {
                    printf("error\n");
                    printf("token: \n%s", token);
                    return -1;
                }
            case 2:
                if(hasFinished(current)) {
                    printf("error\n");
                    printf("token: \n%s", token);
                    return -1;
                } else if (isAsterisk(current)) {
                    state = 3;
                    token[index] = current;
                    ++index;
                    break;
                } else {
                    token[index] = current;
                    ++index;
                    break;
                }
            case 3:
                if(hasFinished(current)) {
                    printf("error\n");
                    printf("token: \n%s", token);
                    return -1;
                } else if(isAsterisk(current)) {
                    token[index] = current;
                    ++index;
                    break;
                } else if(isForwardSlash(current)) {
                    state = 4;
                    token[index] = current;
                    ++index;
                    break;
                } else {
                    state = 2;
                    token[index] = current;
                    ++index;
                    break;
                }
            case 4:
                printf("comment identified!\n");
                printf("token: \n%s", token);
                return -2;
            case 5:
                if (isEmptySpace(current)) {
                    token[index] = current;
                    ++index;
                    break;
                } else {
                    printf("comment identified!\n");
                    printf("token: \n%s", token);
                    return -2;
                }
            case 6:
                if (isEnter(current)) {
                    state = 7;
                    ++index;
                    break;
                } else {
                    token[index] = current;
                    ++index;
                    break;
                }
            case 7:
                printf("comment identified!\n");
                printf("token: \n%s", token);
                return -2;
            default:
                printf("error\n");
                printf("token: \n%s", token);
                return -1;
        }
    } while(true);
}