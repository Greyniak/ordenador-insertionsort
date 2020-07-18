#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct person {
    char *name;
    int age;
};

struct linked_list{
    struct node *first;
};

struct node {
    struct person *data;
    struct node *next;
    struct node *previous;
};

typedef struct node node;
typedef struct linked_list linked_list;
typedef struct person person;


//return true if person a should be listed before person b
int compare_person(person *a, person *b) {
    printf("comparing %s and %s (%d)\n", a->name, b->name, strcmp(a->name, b->name));
    return strcmp(a->name, b->name) < 0;
}

/*void add_to_list(linked_list *list, person *data) {

    node *to_be_added = malloc(sizeof *to_be_added);
    to_be_added->data = data;
    to_be_added->next = NULL;

    node *curr_node = list->first;

    //if list is empty this should be the first element
    if (!curr_node) {
        to_be_added->next = NULL;
        list->first = to_be_added;
    }
    //otherwise let`s check if should be placed at the first position...
    else if (compare_person(to_be_added->data, curr_node->data)) {
        to_be_added->next = curr_node;
        list->first = to_be_added;
    } else {
        //...else, try to find a node for which the next one is "higher" than the one to be added
        while (curr_node->next) {
            if (compare_person(to_be_added->data, curr_node->next->data)) {
                to_be_added->next = curr_node->next;
                curr_node->next = to_be_added;
                return;
            }
            curr_node = curr_node->next;
        }

        //...else place it in the last position
        curr_node->next = to_be_added;
    }
}*/

void printList(linked_list *list) {
    node *curr = list->first;

    while (curr) {
        printf("%s", curr->data->name);
        if (curr->previous)
            printf("  previous:%s", curr->previous->data->name);
        if (curr->next)
            printf("  next:%s", curr->next->data->name);
        printf("\n");
        curr = curr->next;
        printf("\n");
    }
}

void add_to_list(linked_list *list, person *data) {
    node *to_be_added = malloc(sizeof *to_be_added);
    to_be_added->data = data;
    to_be_added->next = NULL;

    node *curr_node = list->first;

    //if list is empty this should be the first element
    if (!curr_node) {
        to_be_added->next = NULL;
        list->first = to_be_added;
    } 
    // else add to the end of the list
    else {
        while (curr_node->next) {
            curr_node = curr_node->next;
        }
        //...else place it in the last position
        to_be_added->previous = curr_node;
        curr_node->next = to_be_added;
    }
}

//will break if the list only has one item
void insertion_sort(linked_list *list) {
    node *pivot = list->first->next;
    node *swap;

    printf("00 %s\n", pivot->data->name);

    int counter = 0;

    while (counter < 40 && pivot) {

        counter = counter + 1;
        printf("01 %s\n", pivot->data->name);
         swap = pivot;
        while ( counter < 40 && swap->previous && compare_person(pivot->data, swap->previous->data)) {

            counter = counter + 1; 
            printf("02\n");
            swap = swap->previous;
        }

        node* next_pivot = pivot->next;

        if (swap != pivot) {
            printf("03 swap %s and %s\n", pivot->data->name, swap->data->name);
            node *temp_prev;
            
            if (pivot->previous) {
                printf("03.01\n");
                pivot->previous->next = pivot->next;
            } if (pivot->next) {
                printf("03.02\n");
                pivot->next->previous = pivot->previous;
            }

            if (swap->previous) {
                printf("03.03\n");
                node *temp = swap->previous->next;

                printf("03.03.01\n");
                swap->previous->next = pivot;
                pivot->previous = swap->previous;
                printf("03.03.02\n");
            } else {
                printf("03.04\n");
                list->first = pivot;
                pivot->previous = NULL;
            }

            swap->previous = pivot;
            pivot->next = swap;
        }

        printf("04\n\n\n\n");
        printList(list);
        printf("05\n\n\n\n");
        pivot = next_pivot;
    }
}

int main() {
    
    linked_list list = { .first = NULL };

    person p1 = { .name = "Alice Roberts", .age = 38 };
    person p2 = { .name = "Rutger Bregman", .age = 50 };
    person p3 = { .name = "Douglas Adams", .age = 42 };
    person p4 = { .name = "Paul Davies", .age = 18 };
    person p5 = { .name = "Yuval Harari", .age = 45 };

    add_to_list(&list, &p3);
    add_to_list(&list, &p5);
    add_to_list(&list, &p4);
    add_to_list(&list, &p2);
    add_to_list(&list, &p1);

    insertion_sort(&list);

    printList(&list);

    printf("\n");

    return 1;
}