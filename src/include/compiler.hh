#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "debug.hh"
#include <cstdio>

int compile(FILE *source);


#ifdef DEBUG_FLAG
void set_compilation_log(FILE *file);
#endif /* DEBUG_FLAG */

#endif /* COMPILER_HPP */