#include <stdio.h>
#include <stdlib.h>

struct cell{
    int data;
    struct cell *prev;
    struct cell *next;
};



void adaugare(struct cell **head, int data){

    struct cell *new = (struct cell*)malloc(sizeof(struct cell));

    struct cell *last = *head;

    new->data = data;
    new->next = NULL;

    if (*head == NULL){
        *head = new;
        return;
    }

    while (last->next != NULL){
        last = last->next;
    }

    last->next = new;
    return;

}


void pre(struct cell **head, int data){

    struct cell *new = (struct cell*)malloc(sizeof(struct cell));

    new->data = data;

    new->next = (*head);

    (*head) = new;
}


void reverse(struct cell **head){

    struct cell *current = *head;
    struct cell *prev = NULL;
    struct cell *next = NULL;

    while (current != NULL){
        next = current -> next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}


int size(struct cell *head){
    int count = 0;

    while (head != NULL){
        count++;
        head = head->next;
    }

    return count;
}


void insertAt(struct cell **head, int pos, int data){
    struct cell *new = (struct cell*)malloc(sizeof(struct cell));
    struct cell *current = *head;
    struct cell *prev = NULL;
    new->data = data;

    if ((pos < 1) || (pos > size(*head))){
        printf("Position doesn't exist\n");
        return;
    }

    if (pos == 1){
        pre(head, data);
        return;
    }

    if (pos > 1 && pos<=size(*head)){
        for(int i=1; i<pos;i++){
            prev = current;
            current = current->next;
        }
        new->data = data;
        prev->next = new;
        new->next = current;

    }

    if ((*head == NULL) || (pos >= size(*head))){
        adaugare(head, data);
        return;
    }
}


void remoreFrom(struct cell **head, int pos){
    struct cell *current = *head;
    struct cell *prev = NULL;
    struct cell *next = NULL;

    if (*head == NULL){
        printf("Nothing to delete.\n");
        return;
    }

    if ((pos < 1) || (pos > size(*head))){
        printf("Position doesn't exist\n");
        return;
    }

    if (pos == 1){
        next = current->next;
        free(*head);
        *head = next;
        return;
    }

    for(int i=1; i<pos; i++){
        prev = current;
        current = current->next;
        next = current->next;
    }

    prev->next = next;
    free(current);
}


void sort(struct cell **head){
    struct cell *current = *head;
    struct cell *next = NULL;
    struct cell *sorted = NULL;
    struct cell *cell = NULL;

    if (*head == NULL){
        printf("Nothing to sort.\n");
        return;
    }

    while (current != NULL){
        next = current->next;

        if (sorted == NULL || sorted->data >= current->data){
            current->next = sorted;
            sorted = current;
        }

        else {
            cell = sorted;
            while (cell->next != NULL && cell->next->data < current->data){
                cell = cell->next;
            }

            current->next = cell->next;
            cell->next = current;
        }

        current = next;
    }
    *head = sorted;
}


void search(struct cell *head, int data){

    if (head == NULL){
        printf("Nothing to search.\n");
        return;
    }

    int pos = 1;

    while (head->next != NULL && head->data != data){
        pos++;
        head = head->next;
    }
    if (head->data != data){
        printf("The value doesn't exist.\n");
        return;
    }

    if (head->data == data){
        printf("The value is at %d position.\n", pos);
        return;
    }
}


struct cell *join(struct cell *list1, struct cell *list2){
    struct cell *joined = NULL;


    if (list1 == NULL || list2 == NULL){
        printf("Nothing to join.\n");
        return 0;
    }

    while (list1 != NULL){
        adaugare(&joined, list1->data);
        list1 = list1->next;
    }

    while (list2 != NULL){
        adaugare(&joined, list2->data);
        list2 = list2->next;
    }

    return joined;
}


void print(struct cell *cell){
    while (cell != NULL){
        printf(" %d ->", cell->data);
        cell = cell->next;
    }
    printf(" NULL\n");
}


void serialize(struct cell *head, char name[]){
    FILE* file = fopen(name, "w");

    if(file == NULL){
        printf("Can't open the file\n");
        exit(1);
    }


    while(head != NULL){
        fprintf(file, " %d ->", head->data);
        head = head->next;
    }

    fprintf(file, " NULL");
    fclose(file);
}


void deserialize(struct cell *head, char name[]){
    FILE* file = fopen(name, "r");
    struct cell *cell = NULL;

    if(file == NULL){
        printf("Can't read the file\n");
        exit(2);
    }

    int val = 0;
    while((fscanf(file, " %d ->", &val)) > 0){
        adaugare(&cell, val);
    }

    fclose(file);

}


void appendDoubly(struct cell **head, int data){
    struct cell *new = (struct cell*)malloc(sizeof(struct cell));


    new->data = data;
    new->prev = NULL;
    new->next = (*head);

    if (*head != NULL){
        (*head)->prev = new;
    }

    (*head) = new;

}

void backwards(struct cell **head){
    struct cell *new = NULL;
    struct cell *current = (*head);

    while (current != NULL){
        appendDoubly(&new, current->data);
        current = current->next;
    }

    *head = new;
    return;
}

int main(){
    struct cell *arr[4] = {NULL};

    int head = 1;
    int option = 0, val = 0;
    int pos = 0;
    int list1 = 0, list2 = 0;

    char file_name[101] = {0};

    while(1){

        printf("Select:\n");
        printf("1 - Append\n");
        printf("2 - Prepend\n");
        printf("3 - Reverse\n");
        printf("4 - Append to the specific index\n");
        printf("5 - Remove\n");
        printf("6 - Sort\n");
        printf("7 - Search\n");
        printf("8 - Join two linked lists\n");
        printf("9 - Backwards traversal, using double-linked-list\n");
        printf("10 - New file\n");
        printf("11 - Read from a file\n");
        printf("12 - Choose the list\n");
        printf("0 - Exit\n");
        scanf("%d", &option);

    switch(option){

        case 1:{
            printf("Enter the value: ");
            scanf("%d", &val);
            adaugare(&arr[head], val);
            print(arr[head]);

            break;
        }

        case 2:{
            printf("Enter the value: ");
            scanf("%d", &val);
            pre(&arr[head], val);
            print(arr[head]);

            break;
        }

        case 3:{
            reverse(&arr[head]);
            print(arr[head]);

            break;
        }

        case 4:{
            printf("Position: ");
            scanf("%d", &pos);
            printf("Enter the value you want to insert: ");
            scanf("%d", &val);
            insertAt(&arr[head], pos, val);
            print(arr[head]);

            break;
        }

        case 5:{
            printf("Enter the position: ");
            scanf("%d", &pos);
            remoreFrom(&arr[head], pos);
            print(arr[head]);

            break;
        }

        case 6:{
            sort(&arr[head]);
            print(arr[head]);

            break;
        }

        case 7:{
            printf("Enter the value you want to find: ");
            scanf("%d", &val);
            search(arr[head], val);

            break;
        }

        case 8:{
            printf("What two lists should be joined?: ");
            scanf("%d %d", &list1, &list2);

            arr[head] = join(arr[list1], arr[list2]);
            print(arr[head]);

            break;
        }

        case 9:{
            backwards(&arr[head]);
            print(arr[head]);

            break;
        }

        case 10:{
            printf("Type the name of a file: \n");
            scanf("%s", file_name);
            serialize(arr[head], file_name);

            break;
        }

        case 11:{
            deserialize(arr[head], file_name);
            print(arr[head]);

            break;

        }

        case 12:{
            for(int i=1;i<4;i++){
                print(arr[i]);
            }

            printf("Choose the list: \n");
            scanf("%d", &head);
            break;
        }

        case 0:{
            return 0;
        }

        default:{
            printf("Try again\n");
            break;
        }
    }
}
    return 0;
}
