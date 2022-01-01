#include <lex/prelude.h>

void greeting() {
	puts("Welcome to the Daybreak compiler!");
}

int check_args(int argc, char** argv) {
	if (argc < 2) {
		puts("Usage: daybreak <filename>");
		return 1;
	}
	return 0;
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
		printf("%s\n", tokens->name);
		tokens = tokens->next;
	}

	return 0;
}