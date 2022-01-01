#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lex/token.h>

#define TOKEN_BUFFER_SIZE 64

#define RESET_STRING(str, length) \
	memset((str), '\0', sizeof(char) * (length));

// Open file from filename
FILE* _open_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open file %s\n", filename);
		return NULL;
	}
	return file;
}

struct Token* lex(const char* filename) {
	FILE* file = _open_file(filename);
	if (!file) {
		return NULL;
	}
	struct Token* tokens = new_token(NULL, NULL);
	struct Token* current = tokens;

	// Read from file character by character
	char sentinel;
	char token_buffer[TOKEN_BUFFER_SIZE] = {'\0'};
	int token_length = 0;
	while ((sentinel = fgetc(file)) != EOF) {
		if (isspace(sentinel) && token_length > 0) {
			char* name = malloc(sizeof(char) * token_length);
			memset(name, '\0', sizeof(char) * token_length);
			RESET_STRING(name, token_length);
			strncpy(name, token_buffer, token_length);
			current->next = new_token(name, NULL);
			
			RESET_STRING(token_buffer, token_length);
			token_length = 0;
			
			current = current->next;
			continue;
		}
		token_buffer[token_length++] = sentinel;
	}
	if (token_length > 0) {
		char* name = malloc(sizeof(char) * token_length);
		strncpy(name, token_buffer, token_length);
		current->next = new_token(name, NULL);
	}

	// Skip empty head node
	return tokens->next;
}