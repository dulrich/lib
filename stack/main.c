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

#include "stack.h"


/* TESTS SECTION */
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
