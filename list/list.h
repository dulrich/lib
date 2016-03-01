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

#ifndef DULIB_LIST_H
#define DULIB_LIST_H

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

#endif // DULIB_LIST_H
