#include "../lib.h"

typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct List {
	int length;
	Node *front;
	Node *back;
} List;


xcode List_init(List *L) {
	if (L == NULL) return X_NULL_PARAM;
	
	L->length = 0;
	L->front = NULL;
	L->back = NULL;
	
	return X_SUCCESS;
}


xcode List_create(List **L) {
	*L = malloc(sizeof(List));
	
	if (*L == NULL) return X_ALLOC_FAILURE;
	
	return List_init(*L);
}


xcode List_destroy(List *L) {
	Node *N;
	
	if (L == NULL) return X_NULL_PARAM;
	
	while (L->front != NULL) {
		N = L->front->next;
		free(L->front);
		L->front = N;
	}
	
	free(L);
	L = NULL;
	
	return X_SUCCESS;
}


xcode List_push_front(List *L, int data) {
	Node *N;
	
	if (L == NULL) return X_NULL_PARAM;
	
	N = malloc(sizeof(Node));
	if(N == NULL) {
		printf("ERROR: failed to create node");
		return X_ALLOC_FAILURE;
	}
	
	N->data = data;
	N->prev = NULL;
	N->next = L->front;
	
	if (L->length == 0) {
		L->back = N;
	} else {
		L->front->prev = N;
	}
	
	L->front = N;
	L->length++;
	
	return X_SUCCESS;
}

xcode List_push_back(List *L, int data) {
	Node *N;
	
	if (L == NULL) return X_NULL_PARAM;
	
	N = malloc(sizeof(Node));
	if (N == NULL) {
		printf("ERROR: failed to create node");
		return X_ALLOC_FAILURE;
	}
	
	N->data = data;
	N->prev = L->back;
	N->next = NULL;
	
	if (L->length == 0) {
		L->front = N;
	} else {
		L->back->next = N;
	}
	
	L->back = N;
	L->length++;
	
	return X_SUCCESS;
}


xcode List_insert(List *L, int data, int pos) {
	int i;
	Node *it, *N;
	
	if (L == NULL) return X_NULL_PARAM;
	
	// handle insertions at front and back
	if (pos == 0) {
		return List_push_front(L,data);
	}
	else if (pos >= L->length) {
		return List_push_back(L,data);
	}
	
	N = malloc(sizeof(Node));
	if(N == NULL) {
		printf("ERROR: failed to create node");
		return X_ALLOC_FAILURE;
	}
	
	N->data = data;
	N->prev = NULL;
	N->next = NULL;
	
	it = L->front;
	for(i=1;i<L->length;i++) {
		if (pos == i) {
			if (it->next != NULL) {
				it->next->prev = N;
				N->next = it->next;
			}

			it->next = N;
			N->prev = it;
			
			L->length++;
			
			break;
		}
		else {
			it = it->next;
		}
	}
	
	return X_SUCCESS;
}


xcode List_pop_front(List *L, int *data) {
	Node *N;
	
	if (L == NULL) return X_NULL_PARAM;
	
	if (L->front == NULL) return X_LIST_UNDERFLOW;
	
	*data = L->front->data;
	
	N = L->front->next;
	free(L->front);
	L->front = N;
	
	if (L->length == 1) L->back = NULL;
	
	L->length--;
	
	return X_SUCCESS;
}


xcode List_pop_back(List *L, int *data) {
	Node *N;
	
	if (L == NULL) return X_NULL_PARAM;
	
	if (L->back == NULL) return X_LIST_UNDERFLOW;
	
	*data = L->back->data;
	
	N = L->back->prev;
	free(L->back);
	L->back = N;
	
	if (L->length == 1) L->front = NULL;
	
	L->length--;
	
	return X_SUCCESS;
}


/* TESTS SECTION */
xcode List_push_front_test(List *L) {
	int i;
	xcode x;
	
	printf("TEST: Start push front test\n");
	
	for(i=3;i<6;i++) {
		x = List_push_front(L,i);
		if (x) printf("TEST: push error %d\n",x);
		else printf("TEST: Pushed %d\n", i);
	}
	
	printf("TEST: End push front test\n");
	
	return X_SUCCESS;
}


xcode List_push_back_test(List *L) {
	int i;
	xcode x;
	
	printf("TEST: Start push back test\n");
	
	for(i=3;i<6;i++) {
		x = List_push_back(L,i);
		if (x) printf("TEST: push error %d\n",x);
		else printf("TEST: Pushed %d\n", i);
	}
	
	printf("TEST: End push back test\n");
	
	return X_SUCCESS;
}


xcode List_push_mixed_test(List *L) {
	int i;
	xcode x;
	
	printf("TEST: Start push mixed test\n");
	
	for(i=2;i<6;i++) {
		if (i % 2 == 0) x = List_push_front(L,i);
		else x = List_push_back(L,i);
		
		if (x) printf("TEST: push error %d\n",x);
		else printf("TEST: Pushed %d\n", i);
	}
	
	printf("TEST: End push mixed test\n");
	
	return X_SUCCESS;
}


xcode List_pop_front_test(List *L) {
	int v;
	xcode x;
	
	printf("TEST: Start pop front test\n");
	
	do {
		x = List_pop_front(L,&v);
		
		if (x) printf("TEST: pop error %d\n",x);
		else printf("TEST: Popped %d\n", v);
	} while (L->length >0);

	printf("TEST: End pop front test\n");
	
	return X_SUCCESS;
}


xcode List_pop_back_test(List *L) {
	int v;
	xcode x;
	
	printf("TEST: Start pop back test\n");
	
	do {
		x = List_pop_back(L,&v);
		
		if (x) printf("TEST: pop error %d\n",x);
		else printf("TEST: Popped %d\n", v);
	} while (L->length >0);

	printf("TEST: End pop back test\n");
	
	return X_SUCCESS;
}


xcode List_pop_mixed_test(List *L) {
	int v;
	xcode x;
	
	printf("TEST: Start pop mixed test\n");
	
	do {
		if (L->length % 2 == 0) x = List_pop_front(L,&v);
		else x = List_pop_back(L,&v);
		
		if (x) printf("TEST: pop error %d\n",x);
		else printf("TEST: Popped %d\n", v);
	} while (L->length > 0);

	printf("TEST: End pop mixed test\n");
	
	return X_SUCCESS;
}


xcode List_insert_test(List *L) {
	int i;
	xcode x;
	
	printf("TEST: Start insert test\n");
	
	for(i=2;i<6;i++) {
		x = List_insert(L,i,i%3);
		
		if (x) printf("TEST: push error %d\n",x);
		else printf("TEST: Pushed %d at %d\n", i, i%3);
	}
	
	printf("TEST: End insert test\n");
	
	return x;
}


xcode List_destroy_test(List *L) {
	xcode x;
	
	printf("TEST: Start destroy test\n");
	
	x = List_destroy(L);
	
	printf("TEST: End destroy test\n");
	
	return x;
}


int main(/*int argc, char *argv[]*/) {
	List *L;
	xcode x;
	
	x = List_create(&L);
	if (x) {
		printf("TEST: create error %d\n",x);
		return x;
	}
	
	x = List_push_front_test(L);
	x = List_pop_front_test(L);
	
	x = List_push_back_test(L);
	x = List_pop_back_test(L);

	x = List_push_mixed_test(L);
	x = List_pop_mixed_test(L);
	
	x = List_insert_test(L);
	x = List_pop_front_test(L);
	
	x = List_insert_test(L);
	x = List_destroy_test(L);
	
	return 0;
}
