#pragma once

struct Token {
	const char* name;
	struct Token* next;
};

struct Token* new_token(const char* name, struct Token* next) {
	struct Token* token = malloc(sizeof(struct Token));
	token->name = name;
	token->next = next;
	return token;
}