#pragma once

#include <log/prelude.h>
#include <string.h>

struct Token {
	const char* filename;
	char* name;
	size_t length;
	struct Token* next;
	size_t line_number;
	size_t column;
};

struct Token* token_new(
	const char* filename,
	char* name,
	struct Token* next,
	size_t line_number,
	size_t column
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

static inline void token_print(struct Token token) {
	if (token.name && token.filename) {
		LOG_DEBUG(
			"%s:%zu:%zu -> '%s'",
			token.filename,
			token.line_number,
			token.column,
			token.name
		);
	}
}

static inline void token_advance(struct Token** tokens) {
  if (*tokens) {
		(*tokens) = (*tokens)->next;
	}
}

#define TOKEN_FUN fun
#define TOKEN_IS is
#define TOKEN_END end
#define TOKEN_SYMBOLIC_FAT_ARROW fat_arrow
#define TOKEN_FAT_ARROW_SYMBOL =>

#define _TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(token_type) \
	static inline bool token_is_##token_type(struct Token token) { \
	  return strcmp(token.name, "" #token_type "") == 0; \
	}

#define _TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(token_type, override) \
	static inline bool token_is_##token_type(struct Token token) { \
	  return strcmp(token.name, "" override "") == 0; \
	}

// NOTE: Lexing keywords
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	end
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	fun
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	fat_arrow,
	"=>"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	open_paren,
	"("
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	close_paren,
	")"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION
(
	is
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	int
)

static inline bool token_is_string_literal(struct Token token) {
	return (
		token.length >= 2 &&
		token.name[0] == '"'
		&& token.name[token.length - 1] == '"'
	);
}

static inline bool token_is_numeric(struct Token token) {
	for (size_t i = 0; i < token.length; i++) {
		if (!isdigit(token.name[i])) {
			return false;
		}
	}
	return true;
}