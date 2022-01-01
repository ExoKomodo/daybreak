#include <lex/prelude.h>
#include <stdbool.h>

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
	while (tokens) {
		if (tokens->name) {
			printf("%c\n", tokens->name[0]);
		}
		tokens = tokens->next;
	}

	return 0;
}