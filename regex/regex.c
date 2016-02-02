#define DEBUG 1

#ifdef DEBUG
	#define debug(format, ...) printf("%s:%d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
	#define debug(format, ...) do { printf("") } while (0)
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int ecode;
#define STATUS_SUCCESS 0
#define STATUS_MISSING_ARGS 1
#define STATUS_RAW_PATTERN_TOO_LONG 2

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
		debug("processing node %d (%c)",i,raw[i]);
		
		switch(raw[i]) {
		case '?':
			debug("set optional %d",n);
			pattern[n - 1].optional = 1;
			pattern[n - 1].index_fail = n;
			break;
		default:
			debug("set pattern %d (%c)",n,raw[i]);
			pattern[n].pattern = raw[i];
			pattern[n].test = TEST_NONE;
			pattern[n].optional = 0;
			pattern[n].index_match = n + 1;
			pattern[n].index_fail = -1;
			n++;
		}
	}
	
	*length = n;
	
	return STATUS_SUCCESS;
}

struct Match* longest_match(struct Match* matches,const int length) {
	int max_idx,max_len;
	int cur_len,i;
	struct Match* match;
	
	debug("===== matches =====");
	max_idx = -1;
	max_len = 0;
	for(i = 0;i < length;i++) {
		debug("one");
		cur_len = matches[i].pos_cur - matches[i].pos_start + 1;
		debug("two");
		if (cur_len > max_len) {
			max_idx = i;
			max_len = cur_len;
			
			debug("set max length %d at %d",max_len,max_idx);
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
	int stack_pos;
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
	
	while(stack_pos > 0) {
		match = &stack[stack_pos];
		
		if (match->index == -1) {
			stack_pos--;
			continue;
		}
		
		if (match->index == length && match->pos_start != -1) {
			debug("setting match %d (%d to %d) from stack %d",
				matches_pos,
				match->pos_start,
				match->pos_cur,
				stack_pos);
			
			if (match->pos_start > 1) {
				match->pos_start--;
			}
			
			if (match->pos_cur > 0) {
				match->pos_cur--;
			}
			
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
			
			debug("optional added to stack[%d] (%d to %d)",stack_pos,match->pos_start,match->pos_cur);
		}
		
		if (input[match->pos_cur] == pattern[match->index].pattern) {
			match->pos_cur++;
			match->index = pattern[match->index].index_match;
			
			if (match->pos_start == -1) match->pos_start = match->pos_cur;
			
			debug("incremented pos_cur to %d",match->pos_cur);
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
		debug("usage: regex <pattern> <input>");
		return STATUS_MISSING_ARGS;
	}
	
	pattern = malloc(sizeof(struct Node) * pattern_length);
	
	pattern_create(pattern,&pattern_length,argv[1]);
	
	match = pattern_match(pattern,pattern_length,argv[2]);
	
	if (match == NULL) {
		debug("no match found");
	}
	else {
		debug("best match is (%d,%d): %.*s",
			match->pos_start,
			match->pos_cur,
			(match->pos_cur - match->pos_start + 1),(argv[2] + match->pos_start));
	}
	
	free(pattern);
	
	debug("done");
	
	return 0;
}
