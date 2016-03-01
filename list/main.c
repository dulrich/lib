// lib: basic data structures and algorithms
// Copyright (C) 2015  David Ulrich
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

#include "list.h"

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
