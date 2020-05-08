#include <stdio.h>
#include <stdlib.h>

struct data{
	int nim;
	struct data *prev,*next;
}*head = NULL, *tail = NULL;

//create a node
struct data *newNode(int x){
	data *node = (data*)malloc(sizeof(data));
	node->nim = x;
	node->next = NULL;
	node->prev = NULL;
}

//to insert a node in the head
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

//to insert a node in the tail
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

//to insert a node in order
void pushMid(int x){
	//if there is only head
	if(head==tail)
		pushHead(x);
	//if the head value is bigger than x
	else if(head->nim > x)
		pushHead(x);
	//if the tail value is smaller than x
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


//delete node in the head
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

//delete node in the tail
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
		//if the key is in the head
		if(head->nim == x)
			popHead();
		//if the key is the tail
		else if(tail->nim == x)
			popTail();
		else{
			data *curr = head;
			//check until the end of the node
			while(curr->next != tail){
				if(curr->nim == x)
					break;
				curr = curr->next;
			}
			//if the key is found
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

//print the node
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
