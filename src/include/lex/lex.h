#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lex/token.h>

#define _TOKEN_BUFFER_SIZE 64

#define _LEX_RESET_STRING(str, length) \
	memset((str), '\0', sizeof(char) * (length));

struct Token* lex(const char* filename);
FILE* _lex_open_file(const char* filename);

int _lex_row = 1;
int _lex_column = 1;

struct Token* lex(const char* filename) {
	FILE* file = _lex_open_file(filename);
	if (!file) {
		return NULL;
	}
	struct Token* tokens = token_new(NULL, NULL, 0, 0);
	struct Token* current = tokens;

	// Read from file character by character
	char character;
	char token_buffer[_TOKEN_BUFFER_SIZE] = {'\0'};
	int token_length = 0;
	while ((character = fgetc(file)) != EOF) {
		int current_lex_column = _lex_column;
		int current_lex_row = _lex_row;
		if (character == '\n') {
			_lex_row++;
			_lex_column = 0;
		}
		_lex_column++;
		if (isspace(character) && token_length > 0) {
			char* name = malloc(sizeof(char) * token_length);
			memset(name, '\0', sizeof(char) * token_length);
			_LEX_RESET_STRING(name, token_length);
			strncpy(name, token_buffer, token_length);
			current->next = token_new(name, NULL, current_lex_row, current_lex_column - token_length);
			
			_LEX_RESET_STRING(token_buffer, token_length);
			token_length = 0;
			
			current = current->next;
			
			continue;
		}
		token_buffer[token_length++] = character;
	}
	if (token_length > 0) {
		char* name = malloc(sizeof(char) * token_length);
		strncpy(name, token_buffer, token_length);
		current->next = token_new(name, NULL, _lex_row, _lex_column - token_length);
	}

	// Skip empty head node
	return tokens->next;
}

// Open file from filename
FILE* _lex_open_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open file %s\n", filename);
		return NULL;
	}
	return file;
}