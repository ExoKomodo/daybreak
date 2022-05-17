#pragma once

#define _HELPERS_STRINGIFY_WRAPPED(x) #x
#define HELPERS_STRINGIFY(x) _HELPERS_STRINGIFY_WRAPPED(x)

#define DAYBREAK_NEXT_IMPORT_POINTER imported_file_paths[imported_file_count++]

#define UNUSED(x) (void)(x)
