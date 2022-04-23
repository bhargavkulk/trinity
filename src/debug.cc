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
		fprintf(file, "%s\n", OP_str(op));
		break;

		case OP::ADD:
		// case OP::SUB;
		// case OP::
		break;

		case OP::CONST:
		fprintf(file, "%s %d\n", OP_str(op), *(u16 *) &instruction[1]);
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