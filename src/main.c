#include <api/prelude.h>
#include <stdbool.h>
#include <stdlib.h>

bool _check_args(int argc);
void _greeting();

int main(int argc, char** argv) {
	_greeting();
	if (!_check_args(argc)) {
		return 1;
	}
	return compile(argv[1]);
}

bool _check_args(int argc) {
	if (argc < 2) {
		puts("Usage: daybreak <filename>");
		return false;
	}
	return true;
}

void _greeting() {
	puts(ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET);
	puts(ANSI_FOREGROUND_YELLOW "# Welcome to the Daybreak compiler! #" ANSI_RESET);
	puts(ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET "\n");
}

