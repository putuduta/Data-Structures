#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Food Storage Program with Hash Chaining

struct data {
    char food[100];
    int price;
    struct data *next, *prev;
};

//to print all the hash
void print(struct data *head[100]) {

    for (int i = 0; i < 100; i++) {
        if (head[i]) {
            struct data *temp = head[i];
            printf("%d. ", i);
            while (temp) {
                if (temp->next == NULL) {
                    printf("%s(Rp. %d)\n", temp->food, temp->price);
                }
                else {
                    printf("%s(Rp. %d)->", temp->food, temp->price);
                }
                temp = temp->next;
            }
        }else {
            printf("%d. \n", i);
        }
    }
}

//to create a node
struct data *insertNode(char nama[], int price) {
    struct data *newNode = (struct data *)malloc(sizeof(struct data));
    newNode->price = price;
    strcpy(newNode->food, nama);
    newNode->next = NULL;
    newNode->prev = NULL;
}

//insert node to hash chaining
void insert(struct data **slot, struct data **tail, char nama[], int price) {

    struct data *newNode = insertNode(nama, price);

    if (!(*slot)) {
        *slot = *tail = newNode;

    }
    else {
        struct data *temp = *slot;

        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
        *tail = newNode;
    }
}

//find key
void insert_el(struct data *head[], struct data *tail[], char nama[], int price) {
    int l = strlen(nama);
    int val = 0;
    for(int j = 0; j < l; j++){
        if(nama[j] >= 'a' && nama[j] <= 'z')
            val += nama[j] - 'a';
        else if (nama[j] >= 'A' && nama[j] <= 'Z'){
            val += nama[j] - 'A';
        }
    }
    int key = val % 100;

    insert(&head[key], &tail[key], nama, price);
}


int main() {   
    struct data *head[100];
    struct data *tail[100];
    for (int i = 0; i < 100; i++) {
        head[i] = NULL;
        tail[i] = NULL;
    }

    int choose;
    do{
        system("cls");
        printf("Food Storage\n");
        printf("============\n");
        printf("1. Insert\n");
        printf("2. View All\n");
        printf("3. Exit\n");
        scanf("%d", &choose);getchar();

        if(choose == 1){
            char name[100];
            int price;
            printf("Input Food's Name' >> ");
            gets(name);
            printf("Input price >> ");
            scanf("%d", &price);
                insert_el(head, tail, name, price);
        }else if(choose == 2){
            print(head);
            getchar();
        }
    }while(choose != 3);
    return 0;
}

//created by putud
