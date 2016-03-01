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

#include "queue.h"


/* TESTS SECTION */
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


int main(/*int argc, char *argv[]*/) {
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
