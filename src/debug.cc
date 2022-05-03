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
		case OP::CONST_0:
		case OP::LOGINT:
		case OP::LOGSTR:
		case OP::RET:
		case OP::ADD:
		case OP::SUB:
		case OP::DIV:
		case OP::MUL:
		case OP::MOD:
		case OP::EQUAL:
		case OP::LESS:
		case OP::LESS_EQUAL:
		case OP::GREATER:
		case OP::GREATER_EQUAL:
		case OP::NEG:
		case OP::NOT:
		case OP::OR:
		case OP::AND:
		case OP::ARRSET:
		case OP::ARRGET:
		case OP::POP:
		case OP::DEL:
		fprintf(file, "%s\n", OP_str(op));
		break;

		case OP::CONST:
		case OP::GLOB_VARSET:
		case OP::GLOB_VARGET:
		case OP::VARSET:
		case OP::VARGET:
		case OP::ARR:
		fprintf(file, "%s %d\n", OP_str(op), instruction[1]);
		break;

		case OP::JMP_IF_FALSE:
		case OP::JMP:
		case OP::LOOP:
		fprintf(file, "%s %d\n", OP_str(op), instruction[1] | static_cast<i16>(instruction[2]) << 8);
		break;
		
		case OP::CALL:
		fprintf(file, "%s %u\n", OP_str(op), *(u32 *) &instruction[1]);
		break;

		case OP::CALL_NAT:
		fprintf(file, "%s %u %u\n", OP_str(op), *(u32 *) &instruction[1], *(u8 *) &instruction[5]);
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