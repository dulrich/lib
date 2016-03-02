// lib: basic data structures and algorithms
// Copyright (C) 2016  David Ulrich
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

#ifndef DULIB_PIGLATIN_H
#define DULIB_PIGLATIN_H

#define DEBUG 1

#include "../lib.h"


typedef enum __attribute__ ((__packed__)) {
	CHAR_CONSONANT = 0,
	CHAR_VOWEL = 1
} CharType;

struct Char {
	CharType t;
	char c;
	struct Char* next;
};

struct Word {
	char* english;
	char* piglatin;
	int length;
	struct Char* suffix;
};

CharType vowel_initial(char c) {
	c = tolower(c);
	
	return (c=='a') || (c=='e') || (c=='i') || (c=='o') || (c=='u');
}

CharType vowel_middle(char c) {
	c = tolower(c);
	
	return (c=='a') || (c=='e') || (c=='i') || (c=='o') || (c=='u') || (c=='y');
}

xcode english_to_piglatin(struct Word* w) {
	int first_vowel = -1;
	int i, len;
	
	if(w == NULL) return X_NULL_PARAM;
	
	if(w->english == NULL) return X_NULL_PARAM;
	
	if(w->piglatin != NULL) return X_SUCCESS;
	
	len = w->length;
	w->piglatin = calloc(len + 4, sizeof(char));
	
	if(w->piglatin == NULL) return X_ALLOC_FAILURE;
	
	if(vowel_initial(w->english[0]) == CHAR_VOWEL) {
		strncpy(w->piglatin, w->english, len);
		
		w->piglatin[len + 0] = 'w';
		w->piglatin[len + 1] = 'a';
		w->piglatin[len + 2] = 'y';
		
		return X_SUCCESS;
	}
	
	for(i = 1; i < len; i++) {
		if(vowel_middle(w->english[i]) == CHAR_VOWEL) {
			first_vowel = i;
			
			break;
		}
	}
	
	if(first_vowel == -1) return X_SUCCESS;
	
	for(i = 0; i < len; i++) {
		debug(L_STEP, "set %d to %c", (len - first_vowel + i) % len, w->english[i]);
		
		w->piglatin[(len - first_vowel + i) % len] = w->english[i];
	}
	
	w->piglatin[len + 0] = 'a';
	w->piglatin[len + 1] = 'y';
	
	return X_SUCCESS;
}

#endif // DULIB_PIGLATIN_H
