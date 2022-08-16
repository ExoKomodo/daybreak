#pragma once

#include <stdbool.h>
#include <log/colors.h>

#ifndef DEBUG
  #define DEBUG true
#endif

#if DEBUG
  #define LOG_DEBUG(format_string, ...) \
    fprintf(stdout, ANSI_FOREGROUND_BRIGHT_MAGENTA "[DEBUG]:" format_string ANSI_RESET "\n", ##__VA_ARGS__)
#else
  #define LOG_DEBUG(format_string, ...) \
    do {} while (false)
#endif

#define LOG_ERROR(format_string, ...) \
  fprintf(stderr, ANSI_BACKGROUND_RED ANSI_FOREGROUND_BLACK "[ERROR]:" format_string ANSI_RESET "\n", ##__VA_ARGS__)

#define LOG_INFO(format_string, ...) \
  fprintf(stdout, ANSI_FOREGROUND_WHITE "[INFO]:" format_string ANSI_RESET "\n", ##__VA_ARGS__)

#define LOG_WARNING(format_string, ...) \
  fprintf(stdout, ANSI_FOREGROUND_BRIGHT_YELLOW "[WARN]:" format_string ANSI_RESET "\n", ##__VA_ARGS__)
