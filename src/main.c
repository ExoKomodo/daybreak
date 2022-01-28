#include <api/prelude.h>
#include <stdbool.h>
#include <stdlib.h>

#define USAGE_TEXT "Usage: daybreak <filename> [-o <output>]"

bool _parse_args(int, const char**, const char**, const char**);
void _greeting();

int main(int argc, const char** argv) {
	_greeting();
	const char* source_file_path = NULL;
	const char* output_file_path = NULL;
	if (
		!_parse_args(
			argc,
			argv,
			&source_file_path,
			&output_file_path
		)
	) {
		return 1;
	}
	bool must_free_output_file_path = false;
	if (!output_file_path) {
		must_free_output_file_path = true;
		output_file_path = get_default_output_file();
	}
	LOG_INFO("Compiling source file: %s", source_file_path);
	const int error = daybreak_compile(
		source_file_path,
		output_file_path
	);
	if (error != 0) {
		return error;
	}
	LOG_INFO("Output file: %s", output_file_path);
	if (must_free_output_file_path) {
		free((void*)output_file_path);
		output_file_path = NULL;
	}
	return 0;
}

bool _parse_args(
	int argc,
	const char** argv,
	const char** source_file_path,
	const char** output_file_path
) {
	if (argc < 2) {
		puts(USAGE_TEXT);
		return false;
	}
	bool is_output = false;
	const char* temp_output_file_path = NULL;
	const char* temp_source_file_path = NULL;
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
		is_output
	) {
		puts(USAGE_TEXT);
		return false;
	}
	(*source_file_path) = temp_source_file_path;
	(*output_file_path) = temp_output_file_path;
	return true;
}

void _greeting() {
	puts(ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET);
	puts(ANSI_FOREGROUND_YELLOW "# Welcome to the Daybreak compiler! #" ANSI_RESET);
	puts(ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET "\n");
}
