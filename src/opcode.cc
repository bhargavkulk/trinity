#include "opcode.hh"
#include "common.hh"

const OPData OP_DATA[]
{
	{"ERR", 0},

	{"HLT", 0},

	{"ADD", 0},

	{"CONST", 1},

	{"VARSET", 1},
	{"VARGET", 1},

	{"LOGINT", 0},
	{"LOGSTR", 0},

	{"JMP_IF_FALSE", 2},
	{"JMP", 2},
	{"LOOP", 2},
};