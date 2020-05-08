#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct tnode{
	char name[30];
	int age;
	struct tnode*left, *right;
}*root = NULL;


struct tnode *newNode(char name[], int age){
	struct tnode	*temp = (struct tnode*)malloc(sizeof(struct tnode));
	strcpy(temp->name, name);
	temp->age = age;
	temp->right = temp->left = NULL;
	return temp;
}

void insert(char name[], int age){
	struct tnode *node = newNode(name, age);

	if(!root) root = node;
	else{
		struct tnode *curr = root;
		while(curr){
			if(strcmp(name, curr->name) < 0){
				if(curr->left) curr = curr->left;
				else{
					curr->left = node;
					break;
				}
			}else if(strcmp(name, curr->name) > 0){
				if(curr->right) curr = curr->right;
				else{
					curr->right = node;
					break;
				}
			}
		}
	}
}

void delete_nama(struct tnode *node, struct tnode *parent){
	if(!node->left && !node->right){
		if(!parent){
			free(node);
			root = NULL;
		}else{
			if(parent->left == node) parent->left = NULL;
			else parent->right = NULL;

			free(node);
		}
	}else if(node->left && !node->right){
		if(!parent){
			root = root->left;
		}else{
			if(parent->left == node) parent->left = node->left;
			else parent->right = node->left;
		}
		free(node);
	}else if(!node->left && node->right){
		if(!parent){
			root = root->right;
		}else{
			if(parent->left == node) parent->left = node->right;
			else parent->right = node->right;
		}
		free(node);
	}else{
		struct tnode *temp = node;

		struct tnode *parent2 = node;
		node = node->left; 
		while(node->right){
			parent2 = node;
			node = node->right;
		}
    	char temp_xC[100];
    	strcpy(temp_xC, node->name);
		int temp_x = node->age;
		delete_nama(node, parent2);
		temp->age = temp_x;
		strcpy(temp->name, temp_xC);
	}
}

void cari_nama(char name[]){
	struct tnode *parent = NULL;
	if(root){
		tnode *curr = root;
		while(curr){
			if(strcmp(curr->name, name)==0)break;

			parent = curr;
			if(strcmp(name, curr->name) < 0)curr = curr->left;
			else curr = curr->right;
		}

		if(curr){
			delete_nama(curr, parent);
		}else{
			puts("Name not found!!");
		}
	}
}

void inOrder(struct tnode *node){
	if (node){
		inOrder(node->left);
		printf("Name: %s | Umur: %d\n", node->name, node->age);
		inOrder(node->right);
	}
}

int main() {
	int choose;
	do{
		system("cls");
		printf("1. Input\n");
		printf("2. View\n");
		printf("3. Delete\n");
		printf("4. Exit\n");
		scanf("%d", &choose);getchar();
		if(choose == 1){
			char nama[100];
			int age;
			printf("Input name: ");
			gets(nama);
			printf("Input age: ");
			scanf("%d", &age);
			insert(nama, age);
		}else if(choose == 2){
			inOrder(root);
			getchar();
		}else if(choose == 3){
			char nama[100];
			scanf("%s", nama);
			cari_nama(nama);
			getchar();
			getchar();
		}
	}while(choose != 4);
	return 0;
}
