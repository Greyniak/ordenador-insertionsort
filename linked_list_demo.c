#include <stdio.h>
#include <stdlib.h>

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
};

typedef struct node node;
typedef struct linked_list linked_list;
typedef struct person person;


//return true if person a should be listed before person b
int compare_person(person *a, person *b) {
    printf("comparing %s and %s (%d)\n", a->name, b->name, a->age < b->age);
    return a->age < b->age;
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
}

void printList(linked_list *list) {
    node *curr = list->first;

    while (curr) {
        printf("%s\n", curr->data->name);
        printf("%d\n", curr->data->age);
        curr = curr->next;
        printf("\n");

    }
}

int main() {
    
    linked_list list = { .first = NULL };
    person p1 = { .name = "Douglas Adams", .age = 42 };
    person p2 = { .name = "Rutger Bregman", .age = 50 };
    person p3 = { .name = "Alice Roberts", .age = 38 };
    person p4 = { .name = "Paul Davies", .age = 18 };
    person p5 = { .name = "Yuval Harari", .age = 45 };

    add_to_list(&list, &p1);
    add_to_list(&list, &p2);
    add_to_list(&list, &p3);
    add_to_list(&list, &p4);
    add_to_list(&list, &p5);

    printList(&list);
    printf("\n");

    return 1;
}