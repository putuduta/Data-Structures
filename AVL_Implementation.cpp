#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node {
    int key;
    int height;
    char name[100];
    struct node *left;
    struct node *right;
};

int max(int a, int b) {
    if (a < b)
        return b;
    else
        return a;
}

int getHeight(struct node *root) {
    if (root == NULL)
        return 0;
    return root->height;
}

int getBF(struct node *root) {
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

struct node *rightRotate(struct node *y) {
    struct node *x = y->left;
    struct node *B = x->right;

    // rotate
    x->right = y;
    y->left = B;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct node *leftRotate(struct node *x) {
    struct node *y = x->right;
    struct node *B = y->left;

    // rotate
    y->left = x;
    x->right = B;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct node *successor(struct node *root) {
    // di subtree kanan, ambil nilai terkecil
    struct node *cur = root->right;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

struct node *predecessor(struct node *root) {
    // di subtree kiri, ambil nilai terbesar
    struct node *cur = root->left;
    while (cur->right != NULL) {
        cur = cur->right;
    }
    return cur;
}

struct node *newNode(int x, char name[]) {
    struct node *curNewNode =
        (struct node *)malloc(sizeof(struct node));

    curNewNode->key = x;
    strcpy(curNewNode->name, name);
    curNewNode->height = 1;
    curNewNode->left = NULL;
    curNewNode->right = NULL;

    return curNewNode;
}

struct node *insert(struct node *root, int value, char name[]) {
    if (root == NULL)
        return newNode(value, name);
    else if (value < root->key) {
        root->left = insert(root->left, value, name);
    }
    else {
        root->right = insert(root->right, value, name);
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int bfactor = getBF(root);

    if (bfactor > 1 && value < root->left->key) {
        return rightRotate(root);
    }
    if (bfactor < -1 && value > root->right->key) {
        return leftRotate(root);
    }
    if (bfactor > 1 && value > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bfactor < -1 && value < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int cek(char nama[]) {
    int count = 0;
    int l = strlen(nama);
    for (int i = 0; i < l; i++) {
        if (nama[i] >= '0' && nama[i] <= '9') {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

struct node *deleteValue(struct node *root, int value) {
    if (root == NULL)
        return NULL; // jika tidak ada...
    if (value < root->key) {
        root->left = deleteValue(root->left, value);
    }
    else if (value > root->key) {
        root->right = deleteValue(root->right, value);
    }
    else {


        // jika tidak punya anak
        // jika hanya punya anak kiri
        // jika hanya punya anak kanan
        if ((root->left == NULL) || (root->right == NULL)) {

            struct node *temp = NULL;
            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {

            //jika ada 2 anak, maka kita ambil suksesor / predesesor 
            struct node *temp = predecessor(root);
            root->key = temp->key;

            // delete
            root->left = deleteValue(root->left, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Kita perlu fix height dlsbnya
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int bfactor = getBF(root);

    if (bfactor > 1 && getBF(root->left) >= 0) {
        return rightRotate(root);
    }
    if (bfactor > 1 && getBF(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bfactor < -1 && getBF(root->right) <= 0) {
        return leftRotate(root);
    }
    if (bfactor < -1 && getBF(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void printAll(struct node *root) {
    if (root == NULL)
        return;
    printAll(root->left);
    printf("Name: %s\nValue: %d\nHeight: %d\n\n", root->name, root->key, root->height);
    printAll(root->right);
}

struct node *freeAll(struct node *root) {
	if (root == NULL) return NULL;
	root->left = freeAll(root->left);
	root->right = freeAll(root->right);
	free(root);
	return NULL;
}

void update(struct node *root, char nama[], char nama2[]) {
    if (root == NULL)
        return;
    update(root->left, nama, nama2);
    if(strcmp(root->name, nama) == 0) {
        strcpy(root->name, nama2);
    }
    update(root->right, nama, nama2);
}


int main() {
    int opt;
    struct node *root = NULL;
    do {
        system("cls");
        printf("Stuff Store\n");
        printf("1. Insert\n");
        printf("2. Delete by Value\n");
        printf("3. Update Name\n");
        printf("4. View\n");
        printf("5. Exit\n");
        printf(">> ");
        scanf("%d", &opt);
        getchar();
        if (opt == 1) {
            char nama[100];
            do {
                printf("Input Name [Must contains alphabet and numeric] : ");
                gets(nama);
            } while (cek(nama) == 0);
            int key;
            do {
                printf("Input Value [Must between 0 and 50000]: ");
                scanf("%d", &key);getchar();
            } while (key < 0 || key > 50000);

            root = insert(root, key, nama);
            printAll(root);
            getchar();
        }else if(opt == 2){
            int val;
            printAll(root);
            printf("Input Value: ");
            scanf("%d", &val);
            root = deleteValue(root, val);
        }else if(opt == 3){
            printAll(root);
            char nama[100];
            char nama2[100];
            printf("Input Name : ");
            gets(nama);
            do {
                printf("Update Name [Must contains alphabet and numeric] : ");
                gets(nama2);
            } while (cek(nama2) == 0);
            update(root, nama, nama2);
        }else if(opt == 4){
            printAll(root);
            getchar();
        }else if(opt == 5){
            root = freeAll(root);
            printf("Thank you!!");
            getchar();
        }
    } while (opt != 5);
    return 0;
}