#pragma once

#define _HELPERS_STRINGIFY_WRAPPED(x) #x
#define HELPERS_STRINGIFY(x) _HELPERS_STRINGIFY_WRAPPED(x)

#define UNUSED(x) (void)(x)
