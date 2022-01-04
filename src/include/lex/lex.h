#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lex/token.h>

#define _TOKEN_BUFFER_SIZE 64

#define _LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character) \
	(token_buffer)[(token_length)++] = (character);

#define _LEX_RESET_BUFFER(buffer, length) \
	memset((buffer), '\0', sizeof(char) * (length));

void _build_token(const char* filename, char token_buffer[], size_t* buffer_length, unsigned long line, unsigned long column, struct Token** current_token);
struct Token* lex_line(const char* filename, FILE* file, unsigned long* line_number);
FILE* lex_open_file(const char* filename);


struct Token* lex_line(const char* filename, FILE* file, unsigned long* line_number) {
	if (!file) {
		return NULL;
	}
	struct Token* tokens = token_new(filename, NULL, NULL, 0, 0);
	struct Token* current = tokens;
	unsigned long column = 1;

	// Read from file character by character
	char character;
	char token_buffer[_TOKEN_BUFFER_SIZE] = {'\0'};
	size_t token_length = 0;
	bool is_comment = false;
	bool is_string = false;
	while ((character = fgetc(file)) != EOF) {
		int current_lex_column = column;
		switch (character) {
			case '\n':
				(*line_number)++;
				if (is_comment) {
					is_comment = false;
					continue;
				}
				if (token_length > 0) {
					_build_token(
						filename,
						token_buffer,
						&token_length,
						*line_number,
						current_lex_column,
						&current
					);
				}
				return tokens->next;
			case '"':
				if (!is_string) {
					is_string = true;
					_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
					continue;
				}
				break;
			case '?':
				is_comment = true;
				continue;
		}
		if (is_comment) {
			continue;
		}
		column++;
		if (is_string) {
			if (character == '"') {
				is_string = false;
				_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
				_build_token(
					filename,
					token_buffer,
					&token_length,
					*line_number,
					current_lex_column,
					&current
				);
				continue;
			}
			_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
			continue;
		}
		if (!is_string && isspace(character)){
			if (token_length > 0) {
				_build_token(
					filename,
					token_buffer,
					&token_length,
					*line_number,
					current_lex_column,
					&current
				);
			}
			continue;
		}
		_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
	}
	if (token_length > 0) {
		char* name = malloc(sizeof(char) * token_length);
		strncpy(name, token_buffer, token_length);
		current->next = token_new(
			filename,
			name,
			NULL,
			*line_number,
			column - token_length
		);
	}

	// Skip empty head node
	return tokens->next;
}

FILE* lex_open_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open file %s\n", filename);
		return NULL;
	}
	return file;
}

void _build_token(
	const char* filename,
	char token_buffer[],
	size_t* buffer_length,
	unsigned long line,
	unsigned long column,
	struct Token** current_token
) {
	char* name = malloc(sizeof(char) * *buffer_length);
	memset(name, '\0', sizeof(char) * *buffer_length);
	_LEX_RESET_BUFFER(name, *buffer_length);
	strncpy(name, token_buffer, *buffer_length);
	(*current_token)->next = token_new(filename, name, NULL, line, column - *buffer_length);
	
	_LEX_RESET_BUFFER(token_buffer, *buffer_length);
	(*buffer_length) = 0;

	(*current_token) = (*current_token)->next;
}