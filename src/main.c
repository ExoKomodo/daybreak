#include <lex/prelude.h>
#include <stdbool.h>
#include <stdlib.h>

bool _check_args(int argc, char** argv);
int _compile(const char* filename);
void _greeting();
void _process_token(struct Token** tokens);

int main(int argc, char** argv) {
	_greeting();
	if (!_check_args(argc, argv)) {
		return 1;
	}
	return _compile(argv[1]);
}

bool _check_args(int argc, char** argv) {
	if (argc < 2) {
		puts("Usage: daybreak <filename>");
		return false;
	}
	return true;
}

int _compile(const char* filename) {
	FILE* file = lex_open_file(filename);
	struct Token* tokens;
	unsigned long line = 1;
	while ((tokens = lex_line(filename, file, &line)) != NULL) {
		if (tokens->line_number == 0) {
			continue;
		}
		while (tokens) {
			_process_token(&tokens);
		}
	}
}

void _greeting() {
	printf("#####################################\n");
	printf("# Welcome to the Daybreak compiler! #\n");
	printf("#####################################\n\n");
}

void _process_token(struct Token** tokens) {
	struct Token* token = *tokens;
	token_print(*token);
	struct Token* next = token->next;
	token_free(token);
	(*tokens) = next;
}
