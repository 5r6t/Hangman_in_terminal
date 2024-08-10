#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hangman terminal game made by Jackie
void print_help(void){
    printf("Welcome to the classic hangman game! Made by Jackie in 2024\n");
}

void print_start_screen(){
    printf("--------------------------------------------------------\n");
    printf("------Start with a random word--------------------------\n");
    printf("------Start with a custom word--------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
}

int main (int argc, char **argv) {
    
    int c;

    if (strcmp(argv[1],"-h")== 0 || strcmp(argv[1],"-help")== 0 )  {
        print_help();
        return 0;
    }
    else print_start_screen();
    /*
    while((c=fgetc(stdin))!='x') {
        printf("\e[1;1H\e[2J");
        printf("press x to clear and end\n");
    }

    //system("clear"); //linux specific
    //system("cls"); // almost any platform
    printf("\e[1;1H\e[2J"); //regex - faster
    */
    printf("ended!\n");
    return 0;
}