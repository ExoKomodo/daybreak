#pragma once

#include <string.h>

struct Token {
	const char* filename;
	char* name;
	unsigned short length;
	struct Token* next;
	unsigned long line_number;
	unsigned long column;
};

struct Token* token_new(
	const char* filename,
	char* name,
	struct Token* next,
	unsigned long line_number,
	unsigned long column
) {
	struct Token* token = malloc(sizeof(struct Token));
	token->filename = filename;
	token->name = name;
	if (name) {
		token->length = strlen(name);
	}
	token->next = next;
	token->line_number = line_number;
	token->column = column;
	return token;
}

void token_free(struct Token* token) {
	if (!token) {
		return;
	}
	if (token->name) {
		free(token->name);
	}
	free(token);
}

void token_print(struct Token token) {
	if (token.name && token.filename) {
		printf(
			"%s:%lu:%lu -> '%s'\n",
			token.filename,
			token.line_number,
			token.column,
			token.name
		);
	}
}

#define _TOKEN_FUN fun
#define _TOKEN_IS is
#define _TOKEN_END end
#define _TOKEN_SYMBOLIC_FAT_ARROW fat_arrow
#define _TOKEN_FAT_ARROW_SYMBOL =>
#define _TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(token_type) \
	bool token_is_##token_type(struct Token token) { \
	  return strcmp(token.name, "" #token_type "") == 0; \
	} \

#define _TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(token_type, override) \
	bool token_is_##token_type(struct Token token) { \
	  return strcmp(token.name, "" #override "") == 0; \
	} \

// NOTE: Lexing keywords
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(_TOKEN_END)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	_TOKEN_SYMBOLIC_FAT_ARROW,
	_TOKEN_FAT_ARROW_SYMBOL
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(_TOKEN_FUN)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(_TOKEN_IS)