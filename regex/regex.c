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

#define DEBUG 1

#ifdef DEBUG
	#define debug(level,format, ...) if (DEBUG <= level) printf("%s:%d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
	#define debug(level,format, ...) do { printf("") } while (0)
#endif

typedef enum {
	L_STEP = 0,
	L_DBUG = 1,
	L_PROD = 2
} DebugLevel;

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int ecode;
#define STATUS_SUCCESS 0
#define STATUS_MISSING_ARGS 1
#define STATUS_RAW_PATTERN_TOO_LONG 2
#define STATUS_INVALID_OPTIONAL 3
#define STATUS_INVALID_REPEAT 4

typedef enum {
	TEST_NONE = 0,
	TEST_LINE_START = 1,
	TEST_LINE_END   = 2,
	TEST_WORD_BREAK = 3
} Test;

struct Node {
	char pattern;
	Test test;
	uint8_t optional;
	int index_match;
	int index_fail;
};

struct Match {
	int pos_start;
	int pos_cur;
	int index;
};

ecode pattern_create(struct Node* pattern,int* length,const char* raw) {
	int i,l,n;
	
	l = strlen(raw);
	
	if (l > *length) {
		return STATUS_RAW_PATTERN_TOO_LONG;
	}
	
	for(i = 0,n = 0;i < l;i++) {
		debug(L_STEP,"processing node %d (%c)",i,raw[i]);
		
		switch(raw[i]) {
		case '?':
			if (n == 0) return STATUS_INVALID_OPTIONAL;
			
			debug(L_STEP,"set optional %d",n);
			pattern[n - 1].optional = 1;
			pattern[n - 1].index_fail = n;
			break;
		case '+':
			if (n == 0) return STATUS_INVALID_REPEAT;
			
			debug(L_STEP,"set repeat %d",n);
			pattern[n].pattern = pattern[n - 1].pattern;
			pattern[n].test = TEST_NONE;
			pattern[n].optional = 1;
			pattern[n].index_match = n;
			pattern[n].index_fail = n + 1;
			n++;
			break;
		default:
			debug(L_STEP,"set pattern %d (%c)",n,raw[i]);
			pattern[n].pattern = raw[i];
			pattern[n].test = TEST_NONE;
			pattern[n].optional = 0;
			pattern[n].index_match = n + 1;
			pattern[n].index_fail = -1;
			n++;
		}
	}
	
	for(i = 0;i < l;i++) {
		debug(L_DBUG,"%d: [%c]%s (%d,%d)",
			i,
			pattern[i].pattern,
			pattern[i].optional ? "?" : "",
			pattern[i].index_match,
			pattern[i].index_fail);
	}
	
	*length = n;
	
	return STATUS_SUCCESS;
}

struct Match* longest_match(const struct Match* matches,const int length) {
	int max_idx,max_len;
	int cur_len,i;
	struct Match* match;
	
	debug(L_DBUG,"===== matches =====");
	max_idx = -1;
	max_len = 0;
	for(i = 0;i < length;i++) {
		cur_len = matches[i].pos_cur - matches[i].pos_start + 1;
		
		if (cur_len > max_len) {
			max_idx = i;
			max_len = cur_len;
			
			debug(L_DBUG,"set max length %d at %d",max_len,max_idx);
		}
	}
	
	match = NULL;
	if (max_idx > -1) {
		match = malloc(sizeof(*match));
		memcpy(match,&matches[max_idx],sizeof(*match));
	}
	
	return match;
}

struct Match* pattern_match(struct Node* pattern,const int length,const char* input) {
	int i,l;
	struct Match *stack;
	struct Match *matches;
	struct Match *match;
	int stack_pos = -1;
	int matches_pos = 0;
	
	l = strlen(input);
	
	stack = malloc(100 * sizeof(*stack));
	matches = malloc(100 * sizeof(*matches));
	
	memset(stack,0,sizeof(*stack));
	memset(matches,0,sizeof(*matches));
	
	for(i = 0;i < l;i++) {
		stack_pos = i;
		stack[i].pos_start = -1;
		stack[i].pos_cur   =  i;
		stack[i].index     =  0;
	}
	
	while(stack_pos > -1) {
		match = &stack[stack_pos];
		
		if (match->index == -1) {
			stack_pos--;
			continue;
		}
		
		if (match->index == length && match->pos_start != -1) {
			debug(L_DBUG,"setting match %d (%d to %d) from stack %d",
				matches_pos,
				match->pos_start,
				match->pos_cur,
				stack_pos);
			
			matches[matches_pos].pos_start = match->pos_start;
			matches[matches_pos].pos_cur   = match->pos_cur;
			matches[matches_pos].index     = match->index;
			
			matches_pos++;
			
			stack_pos--;
			continue;
		}
		
		if (pattern[match->index].optional != 0) {
			stack_pos++;
			
			stack[stack_pos].pos_cur = match->pos_cur;
			stack[stack_pos].pos_start = match->pos_start;
			
			stack[stack_pos].index = pattern[match->index].index_fail;
			
			debug(L_STEP,"optional added to stack[%d] (%d to %d)",
				stack_pos,
				match->pos_start,
				match->pos_cur);
		}
		
		if (input[match->pos_cur] == pattern[match->index].pattern) {
			match->pos_cur++;
			match->index = pattern[match->index].index_match;
			
			if (match->pos_start == -1) match->pos_start = match->pos_cur;
			
			debug(L_STEP,"incremented pos_cur to %d",match->pos_cur);
		}
		else {
			match->index = -1;
		}
	}
	
	match = longest_match(matches,matches_pos);
	
	free(stack);
	free(matches);
	
	return match;
}

int main(int argc, char** argv) {
	struct Node* pattern;
	int pattern_length = 100;
	struct Match* match;
	
	if (argc != 3) {
		debug(L_PROD,"usage: regex <pattern> <input>");
		return STATUS_MISSING_ARGS;
	}
	
	pattern = malloc(sizeof(struct Node) * pattern_length);
	
	pattern_create(pattern,&pattern_length,argv[1]);
	
	match = pattern_match(pattern,pattern_length,argv[2]);
	
	if (match == NULL) {
		debug(L_PROD,"no match found");
	}
	else {
		debug(L_PROD,"best match is (%d,%d): %.*s",
			match->pos_start,
			match->pos_cur,
			(match->pos_cur - match->pos_start + 1),(argv[2] + match->pos_start - 1));
	}
	
	free(match);
	free(pattern);
	
	debug(L_DBUG,"done");
	
	return 0;
}
