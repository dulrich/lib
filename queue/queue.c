#include <stdio.h>
#include <stdlib.h>

typedef int xcode;

enum {
	 X_SUCCESS
	,X_NULL_PARAM
	,X_ALLOC_FAILURE
	,X_QUEUE_UNDERFLOW
};

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct Queue {
	int length;
	Node *front;
	Node *back;
} Queue;


xcode Queue_create(Queue **Q) {
	*Q = malloc(sizeof(Queue));
	
	if (*Q == NULL) return X_ALLOC_FAILURE;
	
	return Queue_init(*Q);
}


xcode Queue_init(Queue *Q) {
	if (Q == NULL) return X_NULL_PARAM;
	
	Q->length = 0;
	Q->front = NULL;
	Q->back = NULL;
	
	return X_SUCCESS;
}


xcode Queue_destroy(Queue *Q) {
	Node *N;
	
	if (Q == NULL) return X_NULL_PARAM;
	
	while (Q->front != NULL) {
		N = Q->front->next;
		free(Q->front);
		Q->front = N;
	}
	
	free(Q);
	
	return X_SUCCESS;
}


xcode Queue_push(Queue *Q, int data) {
	Node *N = malloc(sizeof(Node));
	
	if(N == NULL) {
		printf("ERROR: failed to create node");
		return X_ALLOC_FAILURE;
	}
	
	N->data = data;
	N->next = NULL;
	
	if (Q->length == 0) {
		Q->front = N;
		Q->back = N;
	} else {
		Q->back->next = N;
		Q->back = N;
	}
	
	Q->length++;
	
	return X_SUCCESS;
}


xcode Queue_pop(Queue *Q, int *data) {
	Node *N;
	
	if (Q == NULL) return X_NULL_PARAM;
	
	if (Q->front == NULL) return X_QUEUE_UNDERFLOW;
	
	*data = Q->front->data;
	
	N = Q->front->next;
	free(Q->front);
	Q->front = N;
	
	if (Q->length == 1) Q->back = NULL;
	
	Q->length--;
	
	return X_SUCCESS;
}


xcode Queue_push_test(Queue *Q) {
	int i;
	xcode x;
	
	printf("TEST: Start push test\n");
	
	for(i=3;i<6;i++) {
		x = Queue_push(Q,i);
		if (x) printf("TEST: push error %d\n",x);
		else printf("TEST: Pushed %d\n", i);
	}
	
	printf("TEST: End push test\n");
	
	return X_SUCCESS;
}


xcode Queue_pop_test(Queue *Q) {
	int v;
	xcode x;
	
	printf("TEST: Start pop test\n");
	
	do {
		x = Queue_pop(Q,&v);
		
		if (x) printf("TEST: pop error %d\n",x);
		else printf("TEST: Popped %d\n", v);
	} while(Q->length > 0);
	
	printf("TEST: End pop test\n");
	
	return X_SUCCESS;
}


xcode Queue_destroy_test(Queue *Q) {
	xcode x;
	
	printf("TEST: Start destroy test\n");
	
	x = Queue_destroy(Q);
	
	printf("TEST: End destroy test\n");
	
	return x;
}


int main(int argc, char *argv[]) {
	Queue *Q;
	xcode x;
	
	x = Queue_create(&Q);
	if (x) printf("TEST: create error %d\n",x);
	
	x = Queue_push_test(Q);
	x = Queue_pop_test(Q);
	
	x = Queue_push_test(Q);
	x = Queue_destroy_test(Q);
	
	return 0;
}
