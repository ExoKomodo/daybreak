#include <stdio.h>
#include <lex/token.h>

// Open file from filename
FILE* _open_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open file %s\n", filename);
		exit(1);
	}
	return file;
}

struct Token* lex(const char* filename) {
	FILE* file = _open_file(filename);
	struct Token* tokens = new_token(NULL, NULL);

	// Read from file character by character
	char sentinel;
	while ((sentinel = fgetc(file)) != EOF) {
		// Create new token
		struct Token* token = new_token(sentinel, tokens);
		if (!tokens) {
			tokens = token;
		}
	}

	return tokens;
}