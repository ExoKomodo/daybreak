#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <generation/prelude.h>
#include <helpers/system.h>
#include <lex/prelude.h>
#include <parser/prelude.h>

#define DAYBREAK_USAGE_TEXT "Usage: daybreak <filename> [-o <output>]"


typedef struct {
	const char *source_file_path;
	const char *output_file_path;
} DaybreakArgs;

typedef struct {
	bool is_success;
	const DaybreakArgs args;
} DaybreakArgParseResult;

int daybreak_compile(const DaybreakArgs);
void daybreak_greeting();
DaybreakArgParseResult daybreak_parse_args(int, const char **);

int daybreak_compile(const DaybreakArgs args) {
	int error = setup_language_directories();
	if (error != 0) {
		return error;
	}

	FILE *source_file = lex_open_file(args.source_file_path, imported_file_paths[imported_file_count++]);
	if (!source_file) {
		return 1;
	}
	struct Token *tokens = lex_file(args.source_file_path, source_file);
	fclose(source_file);
	struct ProgramNode *program = ast_parse_program(&tokens);
	if (!program) {
		LOG_ERROR("Failed to parse program");
		return 1;
	}
	// TODO: Need to grab the end of the filename to give to the output file

	const char *standard_library_directory = get_standard_library_directory();
	size_t output_c_file_length = strlen(standard_library_directory) + strlen(OUTPUT_DIRECTORY) + strlen(DEFAULT_SOURCE_OUTPUT) + 1;
	char *output_c_file_path = malloc(sizeof(char) * output_c_file_length);
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
	if (!args.output_file_path) {
		const char *output_file_path = get_default_output_file();
		LOG_INFO("Output file: %s", output_file_path);
		error = compile_c_code(output_c_file_path, output_file_path);
		free(output_file_path);
		output_file_path = NULL;
	} else {
		LOG_INFO("Output file: %s", args.output_file_path);
		error = compile_c_code(output_c_file_path, args.output_file_path);
	}
	free(output_c_file_path);
	output_c_file_path = NULL;
	return error;
}

void daybreak_greeting()
{
	puts(ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET);
	puts(ANSI_FOREGROUND_YELLOW "# Welcome to the Daybreak compiler! #" ANSI_RESET);
	puts(ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET "\n");
}

DaybreakArgParseResult daybreak_parse_args(
	int argc,
	const char **argv)
{
	if (argc < 2) {
		puts(DAYBREAK_USAGE_TEXT);
		return (DaybreakArgParseResult) {
			.is_success = false,
		};
	}
	bool is_output = false;
	char *temp_output_file_path = NULL;
	char *temp_source_file_path = NULL;
	for (int i = 1; i < argc; i++) {
		if (is_output) {
			temp_output_file_path = argv[i];
			is_output = false;
		} else {
			is_output = strcmp(argv[i], "-o") == 0;
			if (is_output) {
				continue;
			}
			temp_source_file_path = argv[i];
		}
	}
	if (
			!temp_source_file_path ||
			is_output) {
		puts(DAYBREAK_USAGE_TEXT);
		return (DaybreakArgParseResult){
			.is_success = false,
		};
	}
	return (DaybreakArgParseResult) {
			.is_success = true,
			.args = (DaybreakArgs) {
				.source_file_path = temp_source_file_path,
				.output_file_path = temp_output_file_path,
			}
	};
}
