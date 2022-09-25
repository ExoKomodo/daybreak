#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <log/prelude.h>

typedef struct Token {
	const char* filename;
	char* name;
	size_t length;
	struct Token* next;
	size_t line_number;
	size_t column;
} Token;

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
		token->name = NULL;
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

static inline void token_chomp(struct Token** tokens) {
  if (*tokens) {
		struct Token* next = (*tokens)->next;
		token_free(*tokens);
		*tokens = next;
	}
}

#define TOKEN_BINDING_ARROW_SYMBOL <-
#define TOKEN_DO do
#define TOKEN_END end
#define TOKEN_FAT_ARROW_SYMBOL =>
#define TOKEN_FUN fun
#define TOKEN_IMPORT import
#define TOKEN_IMPORTC importc
#define TOKEN_IS is
#define TOKEN_LEFT_ANGLE <
#define TOKEN_LET let
#define TOKEN_MATCH match
#define TOKEN_PERIOD .
#define TOKEN_RIGHT_ANGLE >
#define TOKEN_STRUCT struct
#define TOKEN_SYMBOLIC_FAT_ARROW fat_arrow
#define TOKEN_TYPE type

#define _TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(token_type) \
	static inline bool token_is_##token_type(struct Token token) { \
	  return strcmp(token.name, "" #token_type "") == 0; \
	}

#define _TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(token_type, override) \
	static inline bool token_is_##token_type(struct Token token) { \
	  return strcmp(token.name, "" override "") == 0; \
	}

_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION
(
	do
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	end
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	enum
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	fun
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	import
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	importc
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION
(
	is
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	let
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	match
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	mut
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	new
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	return
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	struct
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	type
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION(
	union
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	binding_arrow,
	"<-"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	fat_arrow,
	"=>"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	hash,
	"#"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	open_paren,
	"("
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	close_paren,
	")"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	open_brace,
	"{"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	close_brace,
	"}"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	open_bracket,
	"["
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	close_bracket,
	"]"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	period,
	"."
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	colon,
	":"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	left_angle,
	"<"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	right_angle,
	">"
)
_TOKEN_GENERATE_TOKEN_MATCH_FUNCTION_SYMBOL_OVERRIDE(
	shebang,
	"#!"
)

static inline bool token_is_string_literal(struct Token token) {
	return (
		token.length >= 2 &&
		token.name[0] == '"'
		&& token.name[token.length - 1] == '"'
	);
}

static inline bool token_is_numeric(struct Token token) {
	bool is_double = false;
	for (size_t i = 0; i < token.length; i++) {
		const char character = token.name[i];
		if (character == '.') {
			if (is_double) {
				return false;
			}
			is_double = true;
			continue;
		}
		if (!isdigit(token.name[i])) {
			return false;
		}
	}
	return true;
}

static inline bool token_is_double(struct Token token) {
	bool is_double = false;
	for (size_t i = 0; i < token.length; i++) {
		const char character = token.name[i];
		if (character == '.') {
			if (is_double) {
				return false;
			}
			is_double = true;
			continue;
		}
		if (!isdigit(token.name[i])) {
			return false;
		}
	}
	return is_double;
}

static inline bool token_is_integer(struct Token token) {
	for (size_t i = 0; i < token.length; i++) {
		if (!isdigit(token.name[i])) {
			return false;
		}
	}
	return true;
}

static inline bool token_is_keyword(struct Token token) {
	return (
		token_is_do(token) ||
		token_is_end(token) ||
		token_is_fun(token) ||
		token_is_import(token) ||
		token_is_importc(token) ||
		token_is_is(token) ||
		token_is_let(token) ||
		token_is_match(token) ||
		token_is_mut(token) ||
		token_is_new(token) ||
		token_is_return(token) ||
		/* Not included as keywords due to the use of an IdentifierNode
		  to determine the kind of TypeDeclarationNode
		token_is_struct(token) ||
		token_is_union(token) ||
		token_is_enum(token)
		*/
		token_is_type(token)
	);
}

static inline bool token_is_identifier(struct Token token) {
	if (token_is_keyword(token)) {
		return false;
	}
	for (size_t i = 0; i < token.length; i++) {
		const char c = token.name[i];
		if (
			!(
				i == 0 &&
				(
					isalpha(c) || c == '_'
				)
			) && !(
				i != 0 &&
				(
					isalnum(c) || c == '_' || c == '/' || c == '\\'
				)
			)
		) {
			return false;
		}
	}
	return true;
}
