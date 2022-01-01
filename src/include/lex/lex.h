#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lex/token.h>

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

	// Read from file character by character
	char sentinel[2] = {'\0', '\0'};
	while ((sentinel[0] = fgetc(file)) != EOF) {
		// Create new token
		char* name = malloc(sizeof(char) * 2);
		strcpy(name, sentinel);
		struct Token* token = new_token(name, tokens);
		if (!tokens) {
			tokens = token;
		}
	}

	return tokens;
}