#include <lex/prelude.h>
#include <stdbool.h>
#include <stdlib.h>

void greeting() {
	puts("Welcome to the Daybreak compiler!");
}

bool check_args(int argc, char** argv) {
	if (argc < 2) {
		puts("Usage: daybreak <filename>");
		return false;
	}
	return true;
}

int main(int argc, char** argv) {
	greeting();
	if (!check_args(argc, argv)) {
		return 1;
	}
	
	const char* file = argv[1];
	printf("Lexing %s\n", file);
	struct Token* tokens = lex(file);
	// NOTE: Could write this as a set of tail recursive functions
	int count;
	for (count = 0; tokens; count++) {
		if (tokens->name) {
			printf("%c\n", tokens->name[0]);
		}
		free_token(tokens);
		tokens = tokens->next;
	}
	printf("Lexed %d tokens\n", count);

	return 0;
}