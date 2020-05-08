#include <stdio.h>
#include <stdlib.h>

struct data{
	int nim;
	struct data *prev,*next;
}*head = NULL, *tail = NULL;

struct data *newNode(int x){
	data *node = (data*)malloc(sizeof(data));
	node->nim = x;
	node->next = NULL;
	node->prev = NULL;
}

void pushHead(int x){
	data *node = newNode(x);
	if(!head){
		head = tail = node;
	}else{
		head->prev = node;
		node->next = head;
		head = node;
	}
}

void pushTail(int x){
	data *node = newNode(x);
	if (!tail){
		head = tail = node;
	}
	else{
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

void pushMid(int x){
	if(head==tail)
		pushHead(x);
	else if(head->nim > x)
		pushHead(x);
	else if(tail->nim < x)
		pushTail(x);
	else{
		data *curr = head;
		data *temp = newNode(x);
		while (curr->nim < x){
			curr = curr->next;
		}
		temp->prev = curr->prev;
		curr->prev->next = temp;
		temp->next = curr;
		curr->prev = temp;
	}
}



void popHead(){
	if(head){
		if(head == tail){
			free(head);
			head = tail = NULL;
		}else{
			data *temp = head;
			head = head->next;
			head->prev = NULL;
			free(temp);
		}
	}else
		printf("Data kosong\n");
}

void popTail(){
	if(head){
		if(head == tail){
			free(tail);
			head = tail = NULL;
		}else{
			data *temp = tail;
			tail = tail->prev;
			tail->next = NULL;
			free(temp);
		}
	}else
		printf("Data kosong\n");
}

void popKey(int x){
	if(head){
		if(head->nim == x)
			popHead();
		else if(tail->nim == x)
			popTail();
		else{
			data *curr = head;
			while(curr->next != tail){
				if(curr->nim == x)
					break;
				curr = curr->next;
			}
			if(curr->nim == x){
				data *temp = curr->next;
				temp->prev = curr->prev;
				temp->prev->next = curr->next;
				free(curr);
			}else
				printf("Data tidak ditemukan\n");
		}
	}else
		printf("Data Kosong\n");
}

void print(){
	data *curr = head;
	while (curr){
		if (!curr->next)
			printf("%d\n", curr->nim);
		else
			printf("%d->", curr->nim);
		curr = curr->next;
	}
}

int main(){
	// pushMid(3);
	// pushMid(1);
	// pushMid(8);
	// pushMid(2);
	pushTail(8);
	pushTail(2);
	pushTail(3);
	pushTail(4);
	popHead();
	// popKey(2);
	print();
	
	
	
	return 0;
}
