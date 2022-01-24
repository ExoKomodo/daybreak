#pragma once

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <lex/token.h>

#define _TOKEN_BUFFER_SIZE 64

#define _LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character) \
	(token_buffer)[(token_length)++] = (character);

#define _LEX_RESET_BUFFER(buffer, length) \
	memset((buffer), '\0', sizeof(char) * (length));

void _build_token(const char* filename, char token_buffer[], size_t* buffer_length, size_t line, size_t column, struct Token** current_token);
struct Token* lex_file(const char* filename, FILE* file);
FILE* lex_open_file(const char* filename);

struct Token* lex_file(const char* filename, FILE* file) {
	if (!file) {
		return NULL;
	}
	struct Token* tokens = token_new(filename, NULL, NULL, 0, 0);
	struct Token* current = tokens;
	size_t line = 1;
	size_t column = 0;

	// Read from file character by character
	char character;
	char token_buffer[_TOKEN_BUFFER_SIZE] = {'\0'};
	size_t token_length = 0;
	bool is_comment = false;
	bool is_string = false;
	bool is_less_than = false;
	bool is_equals = false;
	while ((character = (char)fgetc(file)) != EOF) {
		column++;
		const size_t current_lex_column = column;
		const size_t current_lex_line = line;
		if (is_comment && character != '\n') {
			continue;
		}
		if (is_string && character != '"') {
			_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
			continue;
		}
		if (is_equals) {
			is_equals = false;
			if (character == '>') {
				_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
				_build_token(filename, token_buffer, &token_length, current_lex_line, current_lex_column, &current);
				continue;
			}
			_build_token(filename, token_buffer, &token_length, current_lex_line, current_lex_column, &current);
		}
		if (is_less_than && character != '-'){
			is_less_than = false;
			_build_token(
				filename,
				token_buffer,
				&token_length,
				current_lex_line,
				current_lex_column,
				&current
			);
		}
		switch (character) {
			case '\n': {
				column = 0;
				line++;
				if (is_comment) {
					is_comment = false;
					continue;
				}
				if (token_length > 0) {
					_build_token(
						filename,
						token_buffer,
						&token_length,
						current_lex_line,
						current_lex_column,
						&current
					);
				}
				continue;
			} break;
			case '"': {
				if (is_string) {
					is_string = false;
					_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
					_build_token(
						filename,
						token_buffer,
						&token_length,
						current_lex_line,
						current_lex_column,
						&current
					);
					continue;
				}
				is_string = true;
				_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
				continue;
			} break;
			case '<': {
				if (token_length > 0) {
					_build_token(
						filename,
						token_buffer,
						&token_length,
						current_lex_line,
						current_lex_column,
						&current
					);
				}
				is_less_than = true;
				_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
				continue;
			} break;
			case '-': {
				if (is_less_than) {
					is_less_than = false;
					_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
					_build_token(
						filename,
						token_buffer,
						&token_length,
						current_lex_line,
						current_lex_column,
						&current
					);
					continue;
				}
			} break;
			case '=': {
				is_equals = true;
				if (token_length > 0) {
					_build_token(
						filename,
						token_buffer,
						&token_length,
						current_lex_line,
						current_lex_column,
						&current
					);
				}
				_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
				continue;
			} break;
			case '>': {
				if (token_length > 0) {
					_build_token(
						filename,
						token_buffer,
						&token_length,
						current_lex_line,
						current_lex_column,
						&current
					);
				}
				_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
				_build_token(
					filename,
					token_buffer,
					&token_length,
					current_lex_line,
					current_lex_column,
					&current
				);
				continue;
			} break;
			case '.':
			case ':':
			case '{':
			case '}':
			case '(':
			case ')': {
				if (token_length > 0) {
					_build_token(
						filename,
						token_buffer,
						&token_length,
						current_lex_line,
						current_lex_column,
						&current
					);
				}
				_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
				_build_token(
					filename,
					token_buffer,
					&token_length,
					current_lex_line,
					current_lex_column,
					&current
				);
				continue;
			} break;
			case '?': {
				is_comment = true;
			} continue;
			case ';':
			case ',': {
				LOG_ERROR("Unexpected '%c'", character);
				exit(1);
			} break;
		}
		if (isspace(character)){
			if (token_length > 0) {
				_build_token(
					filename,
					token_buffer,
					&token_length,
					current_lex_line,
					current_lex_column,
					&current
				);
			}
			continue;
		}
		_LEX_APPEND_TOKEN_CHARACTER(token_buffer, token_length, character);
	}
	if (token_length > 0) {
		_build_token(
			filename,
			token_buffer,
			&token_length,
			line,
			column,
			&current
		);
	}

	// Skip empty head node
	token_chomp(&tokens);
	return tokens;
}

FILE* lex_open_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file != NULL) {
		return file;
	}
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		LOG_ERROR("Failed to get current working directory");
		return NULL;
	}
	char* full_path = malloc(strlen(cwd) + strlen(filename) + 2);
	sprintf(full_path, "%s/%s", cwd, filename);
	file = fopen(full_path, "r");
	if (file != NULL) {
		free(full_path);
		full_path = NULL;
		return file;
	}
	LOG_ERROR("Could not open file from either '%s' or '%s'", filename, full_path);
	free(full_path);
	full_path = NULL;
	return NULL;
}

void _build_token(
	const char* filename,
	char token_buffer[],
	size_t* buffer_length,
	size_t line,
	size_t column,
	struct Token** current_token
) {
	char* name = malloc(sizeof(char) * *buffer_length + 1);
	_LEX_RESET_BUFFER(name, *buffer_length + 1);
	strncpy(name, token_buffer, *buffer_length);
	(*current_token)->next = token_new(filename, name, NULL, line, column - *buffer_length);
	
	_LEX_RESET_BUFFER(token_buffer, *buffer_length);
	(*buffer_length) = 0;

	(*current_token) = (*current_token)->next;
}
