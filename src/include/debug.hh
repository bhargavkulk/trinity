#ifndef DEBUG_HPP
#define DEBUG_HPP

//#define DEBUG_FLAG

#ifdef DEBUG_FLAG
#include <cstdio>
#include <vector>
#include "opcode.hh"
#include "common.hh"

// Writes disassembled instruction to file.
void disassemble(const u8 *instruction, FILE *file);

// Dumps the stack to file.
void stack_dump(const std::vector<u64> &stack, FILE *file);

#endif /* DEBUG_FLAG */

#endif /* DEBUG_HPP */