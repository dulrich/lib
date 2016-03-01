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

#ifndef DULIB_QUEUE_H
#define DULIB_QUEUE_H

#include "../lib.h"

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct Queue {
	int length;
	Node *front;
	Node *back;
} Queue;


xcode Queue_init(Queue *Q) {
	if (Q == NULL) return X_NULL_PARAM;
	
	Q->length = 0;
	Q->front = NULL;
	Q->back = NULL;
	
	return X_SUCCESS;
}


xcode Queue_create(Queue **Q) {
	*Q = malloc(sizeof(Queue));
	
	if (*Q == NULL) return X_ALLOC_FAILURE;
	
	return Queue_init(*Q);
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
	Q = NULL;
	
	return X_SUCCESS;
}


xcode Queue_push(Queue *Q, int data) {
	Node *N;
	
	if (Q == NULL) return X_NULL_PARAM;
	
	N = malloc(sizeof(Node));
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


#endif // DULIB_QUEUE_H
