#include <stdio.h>
#include <stdlib.h>

struct node {
    char *key;
    struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

void printList() {
    struct node *ptr = head;

    while (ptr != NULL) {
        printf("%s ", ptr->key);
        ptr = ptr->next;
    }

    printf("\n ");
}

void insert(char *key) {
    // stworz liste
    struct node *link= (struct node*) malloc(sizeof(struct node));

    link->key = key;

    // wskaznik na stary pierwszy wezel
    link->next = head;

    // wskaz pierwszy na nowy pierwszy
    head = link;
}

void search(char *element) {
    int pos = 0;

    if (head == NULL) {
        printf("Lista jest pusta");
        return;
    }

    current = head;
    while (current->next != NULL) {
        if (current->key == element) {
            printf("%s znalezione na pozycji %d\n", element, pos);
            return;
        }
        
        current = current->next;
        pos++;
    }

    printf("%s nie istnieje na liscie\n", element);
}

int main() {
    insert("xx");
    insert("yy");
    insert("www");

    search("xx");
    search("xxx");

    printList();

    return 0;
}
