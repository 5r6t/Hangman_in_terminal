#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <time.h> // seed for rand function
#include <ctype.h>

#define MAX_WORD_SIZE 15 // please don't increase the size
#define DICTIONARY_SIZE 100 // for proper seed

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
    printf("--------------------------------------------------------\n");
    printf("|       Welcome to the Terminal Hangman Game!          |\n");
    printf("|               Made by Jackie in 2024                 |\n");
    printf("--------------------------------------------------------\n\n");

    printf("This game currently has 2 game modes:\n");
    printf("\t1. Custom: You type in your desired word.\n");
    printf("\t2. Random: A word is randomly chosen for you.\n\n");

    printf("You can add words to the dictionary, but please:\n");
    printf("\t* Do not exceed 15 letters per word.\n");
    printf("\t* Ensure the dictionary always contains exactly\n");
    printf("\t  100 words.\n\n");

    printf("--------------------------------------------------------\n");
    printf("          Thanks for trying out my game! :3\n");
    printf("--------------------------------------------------------\n");

}

enum menuOptions{ randomWord = 1, customWord = 2, help = 3};
enum gameEnd{ win = 0, loss = 1, start = 2 };
enum Boolean{ bool_true = 0, bool_false = 1 };

struct game_data {
    int flag_game_end;
    int word_length;
    int mistakes;
    char input_letter;
    char game_word[MAX_WORD_SIZE+1];
    char game_hidden_word[MAX_WORD_SIZE+1];
    char* lines[7];
};
struct game_data g1 = { .mistakes = 0, .flag_game_end = start};

void array_initializer () {
    for (int i = 0; i < 7; i++) {
        g1.lines[i] = malloc(50);
        memset(g1.lines[i], ' ', 49);
        g1.lines[i][49] = '\0';
    }
}
void init_word () {
    memset(g1.game_hidden_word, '_', g1.word_length);  // Set 'word_length' spaces
    g1.game_hidden_word[g1.word_length+1] = '\0';    
}
void array_free () {
     for (int i = 0; i < 7; i++) {
        free(g1.lines[i]);
    }
}
void game_update () {
    //printf("DEBUG: word length = %d\n", g1.word_length);
    //printf("DEBUG: game word: %s\n", g1.game_word);
    switch (g1.mistakes) { // for clarity and debugging purposes, each number of mistakes can build its own gallow
        default: break; // no mistakes
        case 1: // gallows vertical
            memcpy(g1.lines[1], "|/",          strlen("|/"));
            memcpy(g1.lines[2], "|",           strlen("|"));
            memcpy(g1.lines[3], "|",           strlen("|"));
            memcpy(g1.lines[4], "|",           strlen("|"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 2: // gallows horizontal
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/",          strlen("|/"));
            memcpy(g1.lines[2], "|",           strlen("|"));
            memcpy(g1.lines[3], "|",           strlen("|"));
            memcpy(g1.lines[4], "|",           strlen("|"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 3: // gallows rope
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/     |",    strlen("|/     |"));
            memcpy(g1.lines[2], "|",           strlen("|"));
            memcpy(g1.lines[3], "|",           strlen("|"));
            memcpy(g1.lines[4], "|",           strlen("|"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 4: // hangman head
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/     |",    strlen("|/     |"));
            memcpy(g1.lines[2], "|      O",    strlen("|      O"));
            memcpy(g1.lines[3], "|",           strlen("|"));
            memcpy(g1.lines[4], "|",           strlen("|"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 5: // hangman torso
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/     |",    strlen("|/     |"));
            memcpy(g1.lines[2], "|      O",    strlen("|      O"));
            memcpy(g1.lines[3], "|      |",    strlen("|      |"));
            memcpy(g1.lines[4], "|",           strlen("|"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 6: // hangman left arm
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/     |",    strlen("|/     |"));
            memcpy(g1.lines[2], "|      O",    strlen("|      O"));
            memcpy(g1.lines[3], "|     /|",    strlen("|     /|"));
            memcpy(g1.lines[4], "|",           strlen("|"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 7: // hangman right arm
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/     |",    strlen("|/     |"));
            memcpy(g1.lines[2], "|      O",    strlen("|      O"));
            memcpy(g1.lines[3], "|     /|\\",  strlen("|     /|\\"));
            memcpy(g1.lines[4], "|",           strlen("|"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 8: // hangman left leg
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/     |",    strlen("|/     |"));
            memcpy(g1.lines[2], "|      O",    strlen("|      O"));
            memcpy(g1.lines[3], "|     /|\\",  strlen("|     /|\\"));
            memcpy(g1.lines[4], "|     /",     strlen("|     /"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            break;
        case 9: // hangman right leg  -> fail - signal/display game end    
            memcpy(g1.lines[0], "_______",     strlen("_______"));
            memcpy(g1.lines[1], "|/     |",    strlen("|/     |"));
            memcpy(g1.lines[2], "|      O",    strlen("|      O"));
            memcpy(g1.lines[3], "|     /|\\",  strlen("|     /|\\"));
            memcpy(g1.lines[4], "|     / \\",  strlen("|     / \\"));
            memcpy(g1.lines[5], "|\\",         strlen("|\\"));
            memcpy(g1.lines[6], "| \\",        strlen("| \\"));
            g1.flag_game_end = loss;
            break;
    } // end switch
    game_screen();
}
void find_letter() {
    // g1.input_letter + g1.game_word + g1.word_length
    int found = 0;

    for (int i = 0; i <= g1.word_length; i++) {
        if (g1.input_letter == g1.game_word[i]) { // match found 
            found = 1;
            break;
        }
    }
    if (!found) {
        g1.mistakes++;
    }
    else {
        for (int i = 0; i <= g1.word_length; i++) {
            if (g1.input_letter == g1.game_word[i]) {
                g1.game_hidden_word[i] = g1.game_word[i];
            }
        }
    }
    game_update();
}

void game_screen () {
    memcpy(g1.lines[3]+17, g1.game_hidden_word, strlen(g1.game_hidden_word));
    printf("--------------------------------------------------------\n");
    printf("> Mistakes: %d/9\n", g1.mistakes);
    printf("--------------------------------------------------------\n");
    printf("\t%s\n",g1.lines[0]);
    printf("\t%s\n",g1.lines[1]);
    printf("\t%s\n",g1.lines[2]);
    printf("\t%s\n",g1.lines[3]);
    printf("\t%s\n",g1.lines[4]);
    printf("\t%s\n",g1.lines[5]);
    printf("\t%s\n",g1.lines[6]);
    printf("--------------------------------------------------------\n");
    printf("Please type an alphabetic character of your choice:     \n> ");

    int match = bool_true;
    for (int i = 0; i < g1.word_length; i++) { 
        if (g1.game_word[i] != g1.game_hidden_word[i]) {
            match = bool_false;
            break;
        }
    }
    if (match == bool_true) g1.flag_game_end = win;

    if (g1.flag_game_end == win) {
        clear_screen();
        printf("--------------------------------------------------------\n");
        printf("> Mistakes: %d/9\n", g1.mistakes);
        printf("--------------------------------------------------------\n");
        printf("\n\"You saved me!\"\n\t     \\ O\n\t       |\\ \t Thanks for playing! \n\t      / \\\n\n"); //saved man with text
        printf("--------------------------------------------------------\n");
        printf("> The word was: %s\n", g1.game_word);
        printf("--------------------------------------------------------\n");
        printf("> Press Enter Key to Exit The Game\n");
        getchar(); 
        array_free ();
        return;
    }
    else if (g1.flag_game_end == loss) {
        clear_screen();
        printf("--------------------------------------------------------\n");
        printf("> Mistakes: %d/9\n", g1.mistakes);
        printf("--------------------------------------------------------\n");
        printf("\t_______\n\t|/     |\n\t|      O\n\t|     /|\\ \t Thanks for playing! \n\t|     / \\\n\t|\\\n\t| \\\n"); //hanged man with text
        printf("--------------------------------------------------------\n");
        printf("> The word was: %s\n", g1.game_word);
        printf("--------------------------------------------------------\n");
        printf("> Press Enter Key to Exit The Game\n");
        getchar(); 
        array_free ();
        return;
    }

    while(1) {
         if (scanf("%1c", &g1.input_letter) == 1) {
            if (isalpha(g1.input_letter) != 0) {
                clear_input_buffer();
                break;
            }
            else {
                clear_input_buffer();
                printf("Please enter a single alphabetic character:\n");
            }
         }
         else exit(1); //fail
    } // end loop
    clear_screen();
    find_letter();
}

void random_game() {
    clear_screen();
    printf("--------------------------------------------------------\n");
    printf("|                   RANDOM WORD MODE                   |\n");
    printf("--------------------------------------------------------\n\n");

    printf("--------------------------------------------------------\n");
    printf("|     In this mode, a random word is chosen for you.   |\n");
    printf("|                        Enjoy!                        |\n");
    printf("--------------------------------------------------------\n\n");

    printf("--------------------------------------------------------\n");
    printf("|               Press ENTER to continue                |\n");
    printf("--------------------------------------------------------\n");


    clear_input_buffer();
    getchar(); // wait for any character

    FILE *file;
    if ((file = fopen("dictionary", "r")) == NULL) {
        fprintf(stderr, "There was a problem reading from the file \"dictionary\", please check\n");
        exit(1);
    }

    int word_number = rand() % DICTIONARY_SIZE;
    // retrieve game word
    for (int i = 0; i < word_number; i++) {
        fgets(g1.game_word,MAX_WORD_SIZE, file);
    }
    fclose(file);
    g1.word_length = strlen(g1.game_word) - 1; // '\0'
    init_word();
    clear_screen();
    game_screen();
}

void custom_game() {
    printf("--------------------------------------------------------\n");
    printf("|                   CUSTOM WORD MODE                   |\n");
    printf("--------------------------------------------------------\n\n");

    printf("--------------------------------------------------------\n");
    printf("|      In this mode, you get to choose your own word.  |\n");
    printf("|   LIMIT is 10 letters; longer words WILL be cut off. |\n");
    printf("--------------------------------------------------------\n\n");

    printf("--------------------------------------------------------\n");
    printf("|             Type your desired word below:            |\n");
    printf("--------------------------------------------------------\n");

    
    char str[11];
        while (1) {
        printf("> ");
        scanf("%10s", str);  // Read up to 10 characters
        int valid = 1;  // Assume the input is valid initially

        for (size_t i = 0; i < strlen(str); i++) {
            if (!isalpha(str[i])) {
                valid = 0;  // Set valid to false if a non-alphabetic character is found
                break;
            }
        }

        if (valid) {
            break;
        } else {
            printf("Only alphabetic characters are allowed. Please try again.\n");
            clear_input_buffer();  
        }
    }
    clear_input_buffer();
    strcpy(g1.game_word, str);
    g1.word_length = strlen(g1.game_word);
    clear_screen();
    init_word();
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
    array_initializer ();
    main_menu();

    return 0;
}