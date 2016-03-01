// lib: basic data structures and algorithms
// Copyright (C) 2015 - 2016  David Ulrich
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DULIB_STACK_H
#define DULIB_STACK_H

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

#endif // DULIB_STACK_H
