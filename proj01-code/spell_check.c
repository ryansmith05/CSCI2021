#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

#define MAX_CMD_LEN 128

// A helper function to spell check a specific file
// 'file_name': Name of the file to spell check
// 'dict': A dictionary containing correct words
int spell_check_file(const char *file_name, const dictionary_t *dict) {
    // TODO Not yet implemented
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Spell check failed\n");
        return -1;
    }

    char word[MAX_WORD_LEN];
    char x;
    int i = 0;

    while ((x = fgetc(file)) != EOF) {
        if (isalpha(x)) {
            word[i++] = x;
        } else {
            if (i > 0) {
                word[i] = '\0';  
                i = 0;
                
                if (!dict_find(dict, word)) {
                    printf("%s[X]%c", word, x); 
                } else {
                    printf("%s%c", word, x);  
                }
            } else {
                printf("%c", x); 
            }
        }
    }
    fclose(file);
    return 0;
}

/*
 * This is in general *very* similar to the list_main file seen in lab
 */
int main(int argc, char **argv) {
    dictionary_t *dict = create_dictionary(); //changed this from NULL to create_dictionary()
    char cmd[MAX_CMD_LEN];
    if (argc > 1) { //added this "if" block to pass tests 28-32 since I changed line 50 from NULL
        dictionary_t *temp_dict = read_dict_from_text_file(argv[1]);
        if (temp_dict == NULL) {
            printf("Failed to read dictionary from text file\n");
            dict_free(dict);  
            return 1;  
        }else {
            printf("Dictionary successfully read from text file\n");
        }
        dict_free(dict);  
        dict = temp_dict;  
        if (argc > 2) {
            spell_check_file(argv[2], dict);
            dict_free(dict); 
            return 0;  
        }
    }

    printf("CSCI 2021 Spell Check System\n");
    printf("Commands:\n");
    printf("  add <word>:              adds a new word to dictionary\n");
    printf("  lookup <word>:           searches for a word\n");
    printf("  print:                   shows all words currently in the dictionary\n");
    printf("  load <file_name>:        reads in dictionary from a file\n");
    printf("  save <file_name>:        writes dictionary to a file\n");
    printf("  check <file_name>: spell checks the specified file\n");
    printf("  exit:                    exits the program\n");

    while (1) {
        printf("spell_check> ");
        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        if (strcmp("exit", cmd) == 0) {
            break;
        }

        // TODO Add cases for the other commands
        // Read in the command and any additional arguments (where needed)

        else if (strcmp("add", cmd) == 0) {
            scanf("%s", cmd);  
            int success = dict_insert(dict, cmd);
            if (success !=0){
                printf("Failed to add word '%s'\n", cmd);
            }
        }

        else if (strcmp("lookup", cmd) == 0) {
            scanf("%s", cmd);  
            if (dict_find(dict, cmd)) {
                printf("'%s' present in dictionary\n", cmd);
            } else {
                printf("'%s' not found\n", cmd);
            }
        }

        else if (strcmp("print", cmd) == 0) {
            dict_print(dict);
        }

        else if (strcmp("load", cmd) == 0) {
            char file_name[MAX_CMD_LEN];
            scanf("%s", file_name);

            dictionary_t *new_dict = read_dict_from_text_file(file_name);
            if (new_dict != NULL) {
                dict_free(dict);
                dict = new_dict;
                printf("Dictionary successfully read from text file\n");
            } else {
                printf("Failed to read dictionary from text file\n");
            }
        }

        else if (strcmp("save", cmd) == 0) {
            char file_name[MAX_CMD_LEN];
            scanf("%s", file_name);

            if (write_dict_to_text_file(dict, file_name) == 0) {
                printf("Dictionary successfully written to text file\n");
            } else {
                printf("Failed to write dictionary to text file\n");
            }
        }

        else if (strcmp("check", cmd) == 0) {
            char file_name[MAX_CMD_LEN];
            scanf("%s", file_name);
            spell_check_file(file_name, dict);
        }

        else {
            printf("Unknown command %s\n", cmd);
        }
    }

    dict_free(dict);
    return 0;
}
