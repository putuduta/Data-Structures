#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data{
    char word[100];
    struct data *next, *prev;
} *head = NULL, *tail = NULL;

int i = 1;

struct data *newNode(char word[]){
    data *node = (data *)malloc(sizeof(data));
    strcpy(node->word, word);
    node->next = NULL;
    node->prev = NULL;
}


void insertAtEnd(char word[]) {
    data *node = newNode(word);
    if (!tail){
        head = tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void insertAfter(char word1[], char word2[]) {
    struct data *curr2 = newNode(word2);
    if (head == tail)
        insertAtEnd(word1);
    else if (strcmp(tail->word, word2) == 0)
        insertAtEnd(word1);
    else {
        data *curr = head;
        data *currTemp = head->next;
        data *temp = newNode(word1);
        while (strcmp(curr->word, word2) != 0) {
            curr = curr->next;
            currTemp = currTemp->next;
        }
        if(strcmp(curr->word, word2) == 0){
            temp->next = curr->next;
            curr->prev = currTemp->prev;
            curr->next = temp;
            temp->next = currTemp;
        }else{
            printf("Word not found!");
        }
    }
}

void undo() {
    if (head) {
        if (head == tail) {
            free(tail);
            head = tail = NULL;
        }
        else {
            data *temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
    }
    else
        printf("Empty\n");
}

void search_word(char word[]){
    struct data *curr = head;
    i = 1;
    while(curr){
        if (strcmp(curr->word, word) != 0)
            break;
        curr = curr->next;
        i++;
    }

    if(strcmp(curr->word, word) == 0)
        printf("The word is found at location %d", i);
    else
        printf("Word not found");
}

void edit_word(char word5[], char word4[]){
    struct data *curr = head;
    while (curr) {
        if (strcmp(curr->word, word5) != 0) break;
            curr = curr->next;
    }
    if(strcmp(curr->word, word5) == 0){
        strcpy(curr->word, word4);
    }else{
        printf("Word not found");
    }
    puts("");
}


void display() {
    data *curr = head;
    while (curr) {
        printf("%s ", curr->word);
        curr = curr->next;
    }
}

void freeAll(){
    while(head){
        free(head);
        head = head->next;
    }
    head = tail = NULL;
}

int main(){
    printf("Simple Word Processor\n\n");
    char pilih;
    do{
        system("cls");
        printf("a. Type a word at the end of the sentence\n");
        printf("b. Insert a word in the middle of the sentence\n");
        printf("c. Undo typing\n");
        printf("d. Search for a word\n");
        printf("e. Edit a specific word\n");
        printf("f. Exit Program\n");
        printf("g. Display\n");
        scanf("%c", &pilih);getchar();

        switch (pilih) {
            case 'a':
                char word[100];
                printf("Enter a word: ");
                gets(word);
                insertAtEnd(word);
                getchar();
            break;
            case 'b':
                char word1[100], word2[100];
                printf("Enter the word that you want to add? ");
                gets(word1);
                printf("Adding after what word? ");
                gets(word2);
                insertAfter(word1, word2);
                printf("\nPress enter to continue....");
                getchar();
            break;
            case 'c':
                undo();
                getchar();
            break;
            case 'd':
                char word3[100];
                printf("Enter the word which you want to search? ");
                gets(word3);
                search_word(word3);
                puts("");
                printf("Press enter to continue....");
                getchar();    
            break;
            case 'e':
                char word6[100], word7[100];
                printf("Enter the word that you want to edit? ");
                gets(word6);
                printf("Enter the new word: ");
                gets(word7);
                edit_word(word6, word7);
                printf("Press enter to continue....");
                getchar();
            break;
            case 'f':
                freeAll();
                printf("Thank you for using application!!");
                puts("");
                getchar();
            break;
            case 'g' : 
                display();
                puts("");
                getchar();
            break;
        }

    }while(pilih !=  'f');
}