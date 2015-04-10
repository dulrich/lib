#include "../lib.h"

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct Stack {
	int length;
	Node *front;
} Stack;


xcode Stack_init(Stack *S) {
	if (S == NULL) return X_NULL_PARAM;
	
	S->length = 0;
	S->front = NULL;
	
	return X_SUCCESS;
}


xcode Stack_create(Stack **S) {
	*S = malloc(sizeof(Stack));
	
	if (*S == NULL) return X_ALLOC_FAILURE;
	
	return Stack_init(*S);
}


xcode Stack_destroy(Stack *S) {
	Node *N;
	
	if (S == NULL) return X_NULL_PARAM;
	
	while (S->front != NULL) {
		N = S->front->next;
		free(S->front);
		S->front = N;
	}
	
	free(S);
	S = NULL;
	
	return X_SUCCESS;
}


xcode Stack_push(Stack *S, int data) {
	Node *N;
	
	if (S == NULL) return X_NULL_PARAM;
	
	N = malloc(sizeof(Node));
	if(N == NULL) {
		printf("ERROR: failed to create node");
		return X_ALLOC_FAILURE;
	}
	
	N->data = data;
	N->next = S->front;
	
	S->front = N;
	S->length++;
	
	return X_SUCCESS;
}


xcode Stack_pop(Stack *S, int *data) {
	Node *N;
	
	if (S == NULL) return X_NULL_PARAM;
	
	if (S->front == NULL) return X_STACK_UNDERFLOW;
	
	*data = S->front->data;
	
	N = S->front->next;
	free(S->front);
	S->front = N;
	
	S->length--;
	
	return X_SUCCESS;
}


xcode Stack_push_test(Stack *S) {
	int i;
	xcode x;
	
	printf("TEST: Start push test\n");
	
	for(i=3;i<6;i++) {
		x = Stack_push(S,i);
		if (x) printf("TEST: push error %d\n",x);
		else printf("TEST: Pushed %d\n", i);
	}
	
	printf("TEST: End push test\n");
	
	return X_SUCCESS;
}


xcode Stack_pop_test(Stack *S) {
	int v;
	xcode x;
	
	printf("TEST: Start pop test\n");
	
	do {
		x = Stack_pop(S,&v);
		
		if (x) printf("TEST: pop error %d\n",x);
		else printf("TEST: Popped %d\n", v);
	} while(S->length > 0);
	
	printf("TEST: End pop test\n");
	
	return X_SUCCESS;
}


xcode Stack_destroy_test(Stack *S) {
	xcode x;
	
	printf("TEST: Start destroy test\n");
	
	x = Stack_destroy(S);
	
	printf("TEST: End destroy test\n");
	
	return x;
}


int main(/*int argc, char *argv[]*/) {
	Stack *S;
	xcode x;
	
	x = Stack_create(&S);
	if (x) {
		printf("TEST: create error %d\n",x);
		return x;
	}
	
	x = Stack_push_test(S);
	x = Stack_pop_test(S);
	
	x = Stack_push_test(S);
	x = Stack_destroy_test(S);
	
	return 0;
}
