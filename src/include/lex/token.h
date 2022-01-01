#pragma once

struct Token {
	char* name;
	struct Token* next;
};

struct Token* new_token(char* name, struct Token* next) {
	struct Token* token = malloc(sizeof(struct Token));
	token->name = name;
	token->next = next;
	return token;
}

void free_token(struct Token* token) {
	free(token->name);
	free(token);
}
