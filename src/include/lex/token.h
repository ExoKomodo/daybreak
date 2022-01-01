#pragma once

struct Token {
	char* name;
	unsigned short length;
	struct Token* next;
	unsigned long row;
	unsigned long column;
};

struct Token* token_new(
	char* name,
	struct Token* next,
	unsigned long row,
	unsigned long column
) {
	struct Token* token = malloc(sizeof(struct Token));
	token->name = name;
	if (name) {
		token->length = strlen(name);
	}
	token->next = next;
	token->row = row;
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
