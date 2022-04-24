#ifndef OPCODE_HPP
#define OPCODE_HPP

#include "common.hh"

// Opcodes.
enum class OP : u8 {
    ERR,  // Run-time fatal error. Crashes the program.

    HLT,  // Loops infinitely at the same instruction. Equivalent to "JMP 0".

    // Harsha adding the new byte code instruction types

    ADD,  // Adds 2 topmost numbers on stack
          // SUB, // sames
    // MUL, // sames
    // DIV,
    // MOD,
    // NEG,
    CONST,  // SETS

    // Nimish

    VARSET,
    VARGET,

    LOGINT,
    LOGSTR,

    // Bhargav
    JMP_TRUE,

};

struct OPData {
    const char *str;
    u64 operand_size;
};

extern const OPData OP_DATA[];

#endif /* OPCODE_HPP */