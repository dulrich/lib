#include <stdio.h>
#include <stdlib.h>

struct Stack {
	int data;
	struct Stack *next;
};

void Stack_destroy(struct Stack **head) {
	struct Stack *next;
	
	if (*head == NULL) {
		printf("WARNING: stack already NULL");
		return;
	}
	
	do {
		next = (*head)->next;
		free(*head);
		*head = next;
	} while (*head != NULL);
}


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


struct Stack *Stack_push_test() {
	struct Stack *stack = malloc(sizeof(struct Stack));
	
	printf("TEST: Start push test\n");
	
	stack->data = 3;
	stack->next = NULL;
	
	Stack_push(4,&stack);
	Stack_push(5,&stack);
	
	printf("TEST: End push test\n");
	
	return stack;
}


void Stack_pop_test(struct Stack **head) {
	printf("TEST: Start pop test\n");
	
	if (*head == NULL) {
		printf("ERROR: Cannot pop test NULL Stack");
		return;
	}
	
	do {
		printf("TEST: Popped %d\n", Stack_pop(head));
	} while(*head != NULL);
	
	free(*head);
	
	printf("TEST: End pop test\n");
}


void Stack_destroy_test(struct Stack **head) {
	printf("TEST: Start destroy test\n");
	
	if (*head == NULL) {
		printf("ERROR: Cannot destroy test NULL Stack");
		return;
	}
	
	Stack_destroy(head);
	
	printf("TEST: End destroy test\n");
}


int main(int argc, char *argv[]) {
	struct Stack *stack = Stack_push_test();
	Stack_pop_test(&stack);
	
	stack = Stack_push_test();
	Stack_destroy_test(&stack);
	
	return 0;
}
