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

#include "piglatin.h"


int main(int argc, char** argv) {
	struct Word* sentence;
	int sentence_length = 100;
	int i;
	
	if(argc < 2) {
		debug(L_PROD, "usage: piglatin <word> ...");
		return X_MISSING_ARGS;
	}
	
	// debug(L_DBUG, "CharType is %lu", sizeof(CharType));
	// debug(L_DBUG, "char is %lu", sizeof(char));
	// debug(L_DBUG, "struct Char is %lu", sizeof(struct Char));
	// debug(L_DBUG, "struct Char* is %lu", sizeof(struct Char*));
	//
	// debug(L_DBUG, "is Y an initial vowel? %d", vowel_initial('Y'));
	// debug(L_DBUG, "is Y a middle vowel? %d", vowel_middle('Y'));
	//
	// debug(L_DBUG, "is X an initial vowel? %d", vowel_initial('X'));
	// debug(L_DBUG, "is X a middle vowel? %d", vowel_middle('X'));
	
	sentence = calloc(sentence_length, sizeof(struct Word));
	
	for(i = 1; i < argc; i++) {
		sentence[i].english = argv[i];
		sentence[i].length = strlen(argv[i]);
		
		english_to_piglatin(&sentence[i]);
		
		debug(L_DBUG, "%s ", sentence[i].piglatin);
	}
	
	debug(L_PROD, "=====");
	
	for(i = 1; i < argc; i++) {
		if(sentence[i].piglatin != NULL) {
			free(sentence[i].piglatin);
		}
	}
	
	free(sentence);
	
	debug(L_DBUG, "done");
	
	return 0;
}
