#include "opcode.hh"
#include "common.hh"

const OPData OP_DATA[]
{
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

	{"POP", 0},
	{"CONST_0", 0},

	{"GLOB_VARSET", 1},
	{"GLOB_VARGET", 1},

	{"VARSET", 1},
	{"VARGET", 1},

	{"CALL", 4},
	{"RET", 0},

	{"ARR", 1},
	{"ARRSET", 0},
	{"ARRGET", 0},

	{"LOGINT", 0},
	{"LOGSTR", 0},

	{"JMP_IF_FALSE", 2},
	{"JMP", 2},
	{"LOOP", 2},
};