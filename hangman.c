#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <time.h> // for random numbers
#include <ctype.h>

#define MAX_WORD_SIZE 15
#define DICTIONARY_SIZE 100

//Declarations
void game_screen ();

void clear_input_buffer () {
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
}
void clear_screen () {
    printf("\e[1;1H\e[2J"); //regex - faster, clear the screen
}
void print_help(void){
    printf("Welcome to the classic hangman game! Made by Jackie in 2024\n");
}
enum menuOptions{
    randomWord = 1,
    customWord,
    help
};

struct game_data {
    int word_length;
    int mistakes;
    char input_letter;
    char game_word[MAX_WORD_SIZE+1];
    char line1[9];
    char line2[10];
    char line3[10];
    char line4[17 + MAX_WORD_SIZE];
    char line5[12];
    char line6[5];
    char line7[4];
};
struct game_data g1 = { .mistakes = 1, .line4 = {""} };

void game_update () {
    printf("DEBUG: word length = %d\n", g1.word_length);
    printf("DEBUG: game word: %s\n", g1.game_word);
    printf("DEBUG: mistakes: %d\n", g1.mistakes);
    //strcpy(g1.line4, "world!");
    //strcpy(&array[7], "world!");
    switch (g1.mistakes) {
        default: break;
        case 1:
            memcpy(g1.line2, "|/", strlen("|/"));
            memcpy(g1.line3, "|", strlen("|"));
            memcpy(g1.line4, "|", strlen("|"));
            memcpy(g1.line5, "|", strlen("|"));
            memcpy(g1.line6, "|\\", strlen("|\\"));
            memcpy(g1.line7, "| \\", strlen("| \\"));
            break;
        case 2:5
    }
    /*  printf("_______\n");                  //plank
    printf("|/     |\n");                //rope
    printf("|      o\n");              //head
    printf("|     /|\\\n");           //arms
    printf("|     / \\\n")           // legs
    printf("|\\\n");                // bottom1
    printf("| \\\n");              // bottom2*/
    game_screen();
}

void game_screen () {
    printf("--------------------------------------------------------\n");
    printf("%s\n",g1.line1);
    printf("%s\n",g1.line2);
    printf("%s\n",g1.line3);
    printf("%s\n",g1.line4);
    printf("%s\n",g1.line5);
    printf("%s\n",g1.line6);
    printf("%s\n",g1.line7);
    printf("--------------------------------------------------------\n");
    printf("please enter an alphabetic character of your choice: ");
    // entry from user - a single letter - checks if alpha
     while(1) {
         if (scanf("%1c", &g1.input_letter) == 1) {
            if (isalpha(g1.input_letter) != 0) {
                clear_input_buffer();
                break;
            }
            else {
                clear_input_buffer();  // Handle non-alphabetic input
                printf("Please enter a single alphabetic character:\n");
            }
         }
         else exit(1); //fail
    }
    clear_screen();
    game_update();
}

void random_game() {
    clear_screen();
    printf("--------------------------------------------------------\n");
    printf("-                   RANDOM WORD MODE                   -\n");
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("-       In this mode a random word is chosen for you.  -\n");
    printf("-                       Enjoy!                         -\n");
    printf("--------------------------------------------------------\n");
    printf("-                 Press ENTER to continue              -\n");
    printf("--------------------------------------------------------\n");

    clear_input_buffer();
    getchar();  
    FILE *file;
    if ((file = fopen("dictionary", "r")) == NULL) {
        fprintf(stderr, "There was a problem reading from the file \"dictionary\", please check\n");
        exit(1);
    }
    int word_number = rand() % DICTIONARY_SIZE;

    for (int i = 0; i < word_number; i++) {
        fgets(g1.game_word,MAX_WORD_SIZE, file);
    }
    g1.word_length = strlen(g1.game_word) - 1;
    game_screen();
    //printf("%d", word_number);

}

void custom_game() {
    printf("--------------------------------------------------------\n");
    printf("-                   CUSTOM WORD MODE                   -\n");
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("-     In this mode you get to choose your own word.    -\n");
    printf("-  LIMIT is 10 letters, longer words will be cut off.  -\n");
    printf("--------------------------------------------------------\n");
    printf("-            Type your desired word below:             -\n");
    printf("--------------------------------------------------------\n");
    
    char custom_word_buffer[MAX_WORD_SIZE];
    scanf("%10s", custom_word_buffer);
    clear_input_buffer();
    strcpy(g1.game_word, custom_word_buffer);
    g1.word_length = strlen(g1.game_word) - 1;
    clear_screen();
    game_screen();
}

void main_menu(){
    clear_screen();
    printf("--------------------------------------------------------\n");
    printf("                HANG MAN (by Jackie)                    \n");
    printf("--------------------------------------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("-           1.)Start with a random word                -\n");
    printf("-           2.)Start with a custom word                -\n");
    printf("-           3.)Help                                    -\n");
    printf("--------------------------------------------------------\n");
    printf("            (Choose by typing in a number):             \n");
    printf("--------------------------------------------------------\n");

    int sel_option;
    while(1) {
         if (scanf("%d", &sel_option) != 1) { //fail
            clear_input_buffer();
            printf("Enter a valid number (1 - 3): ");
         }
         else break;
    }
   
    switch (sel_option) {
        case randomWord:
            clear_screen();
            random_game();
            break;
        case customWord:
            clear_screen();
            custom_game();
            break;
        case help:
            clear_screen();
            print_help();
            break;
        default:
            main_menu();
    }
    return;
}


int main () {
    srand(time(0)); //seed for rand function
    main_menu();
    // end the game
    //clear_screen();
    printf("_______\n|/     |\n|      O\n|     /|\\ \t Thanks for playing! \n|     / \\\n|\\\n| \\\n");
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
    /*  printf("_______\n");                  //plank
    printf("|/     |\n");                //rope
    printf("|      o\n");              //head
    printf("|     /|\\\n");           //arms
    printf("|     / \\\n")           // legs
    printf("|\\\n");                // bottom1
    printf("| \\\n");              // bottom2
    printf(" \t ")                 //spacing */