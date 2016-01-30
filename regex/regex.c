#define DEBUG 1

#ifdef DEBUG
#define debug(format, ...) printf("%s:%d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
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
			break;
		default:
			debug("set pattern %d (%c)",n,raw[i]);
			pattern[n].pattern = raw[i];
			pattern[n].test = TEST_NONE;
			pattern[n].optional = 0;
			n++;
		}
	}
	
	*length = n;
	
	return STATUS_SUCCESS;
}

int pattern_match(struct Node* pattern,const int length,const char* input) {
	int i,l;
	int n = 0;
	
	l = strlen(input);
	
	for(i = 0;i < l;i++) {
		debug("state %d %c %d",n,pattern[n].pattern,pattern[n].optional);
		
		if (input[i] == pattern[n].pattern || pattern[n].optional != 0) {
			n++;
			debug("incremented n to %d",n);
		}
		else if (input[i] == pattern[0].pattern) {
			debug("set n = 1");
			n = 1;
		}
		else {
			debug("set n = 0");
			n = 0;
		}
		
		if (n == length) {
			debug("returning %d - %d = %d",i,n,i-n+1);
			return i - n + 1;
		}
	}
	
	return -1;
}

int main(int argc, char** argv) {
	struct Node* pattern;
	int pattern_length = 100;
	
	if (argc != 3) {
		debug("usage: regex <pattern> <input>");
		return STATUS_MISSING_ARGS;
	}
	
	pattern = (struct Node*)malloc(sizeof(struct Node) * pattern_length);
	
	pattern_create(pattern,&pattern_length,argv[1]);
	
	debug("pattern starts at: %d",pattern_match(pattern,pattern_length,argv[2]));
	
	free(pattern);
	
	debug("done");
	
	return 0;
}
