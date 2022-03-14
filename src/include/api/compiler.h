#pragma once

#include <stdio.h>

#include <generation/prelude.h>
#include <helpers/system.h>
#include <lex/prelude.h>
#include <parser/prelude.h>

int daybreak_compile(const char*, const char*);

int daybreak_compile(
	const char* source_file_path,
	const char* output_file_path
) {
	int error = setup_language_directories();
	if (error != 0) {
		return error;
	}

	FILE* source_file = lex_open_file(source_file_path, imported_file_paths[imported_file_count++]);
	if (!source_file) {
		return 1;
	}
	struct Token* tokens = lex_file(source_file_path, source_file);
	fclose(source_file);
	struct ProgramNode* program = ast_parse_program(&tokens);
	if (!program) {
		LOG_ERROR("Failed to parse program");
		return 1;
	}
	// TODO: Need to grab the end of the filename to give to the output file

	const char* standard_library_directory = get_standard_library_directory();
	size_t output_c_file_length = strlen(standard_library_directory) + strlen(OUTPUT_DIRECTORY) + strlen(DEFAULT_SOURCE_OUTPUT) + 1;
	char* output_c_file_path = malloc(sizeof(char) * output_c_file_length);
	memset(output_c_file_path, '\0', sizeof(char) * output_c_file_length);
	sprintf(output_c_file_path, "%s" OUTPUT_DIRECTORY DEFAULT_SOURCE_OUTPUT, standard_library_directory);
	
	error = generate_c_code(program, output_c_file_path);
	if (error != 0) {
		LOG_ERROR("Failed to generate C code. Received error: %d", error);
		if (program) {
			ast_free_program_node(program);
			program = NULL;
		}
		return error;
	}
	if (program) {
		ast_free_program_node(program);
		program = NULL;
	}
	error = compile_c_code(output_c_file_path, output_file_path);
	free(output_c_file_path);
	output_c_file_path = NULL;
	return error;
}
