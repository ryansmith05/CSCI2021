#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// This function creates a dictionary struct and returns a pointer to it
dictionary_t *create_dictionary() {
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    if (dict == NULL) {
        return NULL;
    }
    dict->root = NULL;
    dict->size = 0;
    return dict;
}

// Helper to prepare a new node. Notice the
// lack of a malloc() call in this function.
// Usage:
//   node_t *n = malloc(sizeof(node));
//   new_node(n, word);
// You don't need to use this function, but it is a nice helper.
// This code is correct and should not be modified.
void new_node(node_t* node, const char *key) {
    strcpy(node->word, key);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
}

// Helper: Larger of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}
// Helper to perform the "right" rotation.
// This code is correct and you should not modify it.
node_t *rotate_right(node_t *y)
{
    node_t *x = y->left;
    node_t *t = x->right;
    x->right = y;
    y->left = t;
    y->height = max((y->left != NULL) ? y->left->height : 0, 
                    (y->right != NULL) ? y->right->height : 0) + 1;
    x->height = max((x->left != NULL) ? x->left->height : 0, 
                    (x->right != NULL) ? x->right->height : 0) + 1;
    return x;
}

// Helper to perform the "left" rotation.
// This code is correct and you should not modify it.
node_t *rotate_left(node_t *x)
{
    node_t *y = x->right;
    node_t *t = y->left;
    y->left = x;
    x->right = t;
    x->height = max((x->left != NULL) ? x->left->height : 0, 
                    (x->right != NULL) ? x->right->height : 0) + 1;
    y->height = max((y->left != NULL) ? y->left->height : 0, 
                    (y->right != NULL) ? y->right->height : 0) + 1;
    return y;
}

// You may find writing your own helper functions
// to be useful.

// helper function to calculate the height of a node
int height(node_t *n) {
    return n == NULL ? 0 : n->height;
}

// helper function to calculate the balance factor of a node
int get_balance(node_t *n) {
    return n == NULL ? 0 : height(n->left) - height(n->right);
}

// helper function for dict_insert that inserts a word into the AVL tree and balances it
node_t* dict_insert_helper(node_t* node, const char *word) {
    if (node == NULL) {
        node_t* new_node_ptr = malloc(sizeof(node_t));
        if (new_node_ptr == NULL) {
            return NULL; 
        }
        new_node(new_node_ptr, word); 
        return new_node_ptr;
    }
    
    if (strcmp(word, node->word) < 0) {
        node->left = dict_insert_helper(node->left, word);
    } else if (strcmp(word, node->word) > 0) {
        node->right = dict_insert_helper(node->right, word);
    } else {
        return node; 
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && strcmp(word, node->left->word) < 0) {
        return rotate_right(node);
    }

    if (balance < -1 && strcmp(word, node->right->word) > 0) {
        return rotate_left(node);
    }

    if (balance > 1 && strcmp(word, node->left->word) > 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && strcmp(word, node->right->word) < 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

int dict_insert(dictionary_t *dict, const char *word) {
    // TODO Not yet implemented
    // Please see the project documentation for guidance
    // on implementing this function. It might be a lot!
    // Hint: Begin with just a basic binary search tree implementation,
    //          then come back later to work on the AVL balancing

    if (dict == NULL || word == NULL) {
        return -1; 
    }
    if (dict->root == NULL) {
        node_t* new_node_ptr = malloc(sizeof(node_t));
        if (new_node_ptr == NULL) {
            return -1;  
        }
        new_node(new_node_ptr, word); 
        dict->root = new_node_ptr;
        dict->size++;
        return 0;  
    }
    dict->root = dict_insert_helper(dict->root, word);
    dict->size++;
    return 0;
}

int dict_find(const dictionary_t *dict, const char *query) {
    // TODO Not yet implemented
    if (dict == NULL || query == NULL) {
        return 0;
    }
    node_t *current = dict->root;
    while (current != NULL) {
        int cmp = strcmp(query, current->word);
        if (cmp == 0) {
            return 1; 
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 0; 
}

// helper for dict_print
void dict_print_helper(node_t *node) {
    if (node == NULL) {
        return;
    }
    dict_print_helper(node->left);
    printf("%s\n", node->word);
    dict_print_helper(node->right);
}

void dict_print(const dictionary_t *dict) {
    // TODO Not yet implemented
    if (dict == NULL || dict->root == NULL) {
        return;
    }
    dict_print_helper(dict->root);
}

// helper for dict_free
void dict_free_helper(node_t *node) {
    if (node == NULL) {
        return;
    }
    dict_free_helper(node->left);
    dict_free_helper(node->right);
    free(node);
}

void dict_free(dictionary_t *dict) {
    // TODO Not yet implemented
    if (dict == NULL) {
        return;
    }
    dict_free_helper(dict->root);
    free(dict);
}

dictionary_t *read_dict_from_text_file(const char *file_name) {
    // TODO Not yet implemented
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return NULL;
    }
    dictionary_t *dict = create_dictionary();
    if (dict == NULL) {
        fclose(file);
        return NULL;
    }
    char word[MAX_WORD_LEN];
    while (fgets(word, MAX_WORD_LEN, file)) {
        word[strcspn(word, "\n")] = '\0';
        dict_insert(dict, word);
    }
    fclose(file);
    return dict;
}

// helper for write_dict_to_text_file
void write_helper(node_t *node, FILE *file) {
    if (node == NULL) {
        return;
    }
    write_helper(node->left, file);
    fprintf(file, "%s\n", node->word);
    write_helper(node->right, file);
}

int write_dict_to_text_file(const dictionary_t *dict, const char *file_name) {
    // TODO Not yet implemented
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        return -1;
    }
    if (dict != NULL && dict->root != NULL) {
        write_helper(dict->root, file);
    }
    fclose(file);
    return 0;
}
