#pragma once

#include <lex/prelude.h>
#include <parser/prelude.h>

int compile(const char* filename) {
	// TODO: Handle NULL files
	FILE* file = lex_open_file(filename);
	struct Token* tokens = lex_file(filename, file);
	if (tokens->line_number == 0) {
		tokens = tokens->next;
	}
	struct ProgramNode* program = ast_parse_program(&tokens);
	if (program) {
		ast_free_program_node(program);
		program = NULL;
	}
	return 0;
}
