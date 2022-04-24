#include "opcode.hh"
#include "common.hh"

const OPData OP_DATA[]
{
	{"ERR", 0},

	{"HLT", 0},

	{"ADD", 0},

	{"CONST", 1},

	{"CONST_0", 0},

	{"GLOB_VARSET", 1},
	{"GLOB_VARGET", 1},

	{"VARSET", 1},
	{"VARGET", 1},

	{"CALL", 4},
	{"RET", 0},

	{"LOGINT", 0},
	{"LOGSTR", 0},
};