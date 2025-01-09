#include <stdlib.h>
#include "linked_list.h"

int list_find_student(list_t *list, int value) {
    // TODO Implement a better version of list search here
    if (list == NULL || list->head == NULL) {
       return -1; 
    }

    node_t *current = list->head;
    int index = 0;

    while (current != NULL) {
        if (current->value == value) {
           return index; 
       }
       current = current->next;
       index++;
    }
    return -1;
}
