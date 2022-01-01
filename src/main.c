#include <lex/prelude.h>
#include <stdbool.h>
#include <stdlib.h>

void _greeting() {
	printf("#####################################\n");
	printf("# Welcome to the Daybreak compiler! #\n");
	printf("#####################################\n\n");
}

bool _check_args(int argc, char** argv) {
	if (argc < 2) {
		puts("Usage: daybreak <filename>");
		return false;
	}
	return true;
}

int main(int argc, char** argv) {
	_greeting();
	if (!_check_args(argc, argv)) {
		return 1;
	}
	
	const char* file = argv[1];
	struct Token* tokens = lex(file);
	// NOTE: Could write this as a set of tail recursive functions
	while (tokens) {
		if (tokens->name) {
			printf("%s, %lu:%lu\n", tokens->name, tokens->row, tokens->column);
		}
		struct Token* next = tokens->next;
		token_free(tokens);
		tokens = next;
	}

	return 0;
}