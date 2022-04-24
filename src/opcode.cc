#include "opcode.hh"
#include "common.hh"

const OPData OP_DATA[]{
	{"ERR", 0},

	{"HLT", 0},

	{"ADD", 0},
	{"SUB", 0},
	{"MUL", 0},
	{"DIV", 0},
	{"MOD", 0},
	{"NEG", 0},

	{"LESS", 0},
	{"EQUAL", 0},
	{"LESS_EQUAL", 0},
	{"GREATER", 0},
	{"GREATER_EQUAL", 0},

	{"NOT", 0},
	{"AND", 0},
	{"OR", 0},

	{"CONST", 1},

	{"VARSET", 1},
	{"VARGET", 1},

	{"LOGINT", 0},
	{"LOGSTR", 0},

	{"JMP_IF_FALSE", 2},
	{"JMP", 2},
	{"LOOP", 2},
};