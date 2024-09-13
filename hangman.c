#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hangman terminal game made by Jackie
void print_help(void){
    printf("\e[1;1H\e[2J"); //regex - faster, clear the screen

    printf("Welcome to the classic hangman game! Made by Jackie in 2024\n");
}
enum menuOptions{
    randomWord = 1,
    customWord,
    help
};
void main_menu(){
    printf("\e[1;1H\e[2J"); //regex - faster, clear the screen

    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("---------HANG MAN (by Jackie)---------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("---  1.)Start with a random word  ----------------------\n");
    printf("---  2.)Start with a custom word  ----------------------\n");
    printf("---  3.)Help                      ----------------------\n");
    printf("--------------------------------------------------------\n");
    printf("---   (Choose by selecting a number)   -----------------\n");
    
    int sel_option = help; // in case something breaks, it will be initialized
    (void)sel_option;
    scanf("%d", &sel_option);
    switch (sel_option) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            print_help();
            break;
        default:
            main_menu();
    }
    // if selected then call xyz, else do nothing
    
}

int main (int argc, char **argv) {
    if ((argc != 1)&&(strcmp(argv[1],"-h")== 0 || strcmp(argv[1],"-help")== 0 ))  {
        print_help();
        return 0;
    }
    else main_menu();

    printf("\nended!\n");
    return 0;
}

    /*
    while((c=fgetc(stdin))!='x') {
        printf("\e[1;1H\e[2J");
        printf("press x to clear and end\n");
    }

    //system("clear"); //linux specific
    //system("cls"); // almost any platform
    printf("\e[1;1H\e[2J"); //regex - faster
     printf("_______\n|/     |\n|      O\n|     /|\\\n|     / \\\n|\\\n| \\");
    */