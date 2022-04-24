#include "debug.hh"

#ifdef DEBUG_FLAG

#include "common.hh"

static inline const char *OP_str(OP op)
{
	return OP_DATA[static_cast<usize>(op)].str;
}

void disassemble(const u8 *instruction, FILE *file)
{
	OP op = static_cast<OP>(*instruction);
	switch (op)
	{
		case OP::ERR:
		case OP::HLT:
		case OP::LOGINT:
		case OP::LOGSTR:
		fprintf(file, "%s\n", OP_str(op));
		break;

		case OP::ADD:
		break;

		case OP::CONST:
		case OP::VARSET:
		case OP::VARGET:
		fprintf(file, "%s %d\n", OP_str(op), instruction[1]);
		break;

		case OP::JMP_IF_FALSE:
		case OP::JMP:
		case OP::LOOP:
		fprintf(file, "%s %d\n", OP_str(op), instruction[1] | static_cast<i16>(instruction[2]) << 8);
		break;

		default:
		fprintf(stderr, "INVALID OPCODE\n");
		break;
	}
}

void stack_dump(const std::vector<u64> &stack, FILE *file)
{
	fprintf(file, "[ ");
	for (u64 element : stack)
	{
		fprintf(file, "%ld ", element);
	}
	fprintf(file, "]\n");
}

#endif /* DEBUG_FLAG */