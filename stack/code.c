#include <stdio.h>
#include <stdlib.h>

struct Stack {
	int data;
	struct Stack *next;
};

void Stack_push(int data, struct Stack **head) {
	struct Stack *node = malloc(sizeof(struct Stack));
	
	if(node == NULL) {
		printf("ERROR: failed to create node");
		exit(1);
	} else {
		node->data = data;
		node->next = (head == NULL) ? NULL : *head;
		
		*head = node;
	}
}

int Stack_pop(struct Stack **head) {
	if(head == NULL) {
		printf("ERROR: stack underflow");
		exit(2);
	} else {
		struct Stack *top = *head;
		int value = top->data;
		*head = top->next;
		free(top);
		return value;
	}
}

int main(int argc, char *argv[]) {
	struct Stack *stack = malloc(sizeof(struct Stack));
	
	int (*po) (struct Stack **head) = Stack_pop;
	
	stack->data = 3;
	stack->next = NULL;
	
	Stack_push(4,&stack);
	Stack_push(5,&stack);
	
	do {
		printf("The value on the stack was %d\n", po(&stack));
	} while(stack != NULL);
	free(stack);
	
	return 0;
}
