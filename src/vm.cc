#include "opcode.hh"
#include "common.hh"
#include "debug.hh"
#include "vm.hh"
#include <cstdio>
#include <cstdlib>

#ifdef DEBUG_FLAG
FILE *execution_log;
#endif /* DEBUG_FLAG */

VM vm;
VM::VM() : pc(0), vars_declared(0), max_vars_declared(0) {}

int VM::run()
{
	bool has_halted = false;
	u64 halt_pc = 0;

	variables = std::vector<u64>(max_vars_declared);

	// TEMPORARY: REPLACE WITH WINDOW FLAG.
	while (pc < bytecode.size())
	{
		if (has_halted)
		{
			if (pc != halt_pc)
			{
				has_halted = false;
			}
			else
			{
				// TEMP BREAK
				break;

				continue;
			}
		}
		else
		{
#ifdef DEBUG_FLAG
			fprintf(execution_log, "%lu: ", pc);
			disassemble(&bytecode[pc], execution_log);
			fflush(execution_log);
#endif /* DEBUG_FLAG */
		}

		switch (read_op())
		{
			case OP::ERR:
			{
				return 1;
			}

			case OP::HLT:
			{
				printf("hlt\n");
				has_halted = true;
				pc -= 1;
				halt_pc = pc;
				break;
			}

			case OP::ADD:
			{
				i64 a1 = (i64) pop();
				break;
			}

			case OP::CONST:
			{
				u8 index = read_byte();
				push(constants.at(index));
				break;
			}

			case OP::VARSET:
			{
				u64 val = pop();
				u8 id = read_byte();
				variables.at(id) = val;
				break;
			}

			case OP::VARGET:
			{
				u8 id = read_byte();
				u64 val = variables.at(id);
				push(val);
				break;
			}

			case OP::LOGINT:
			{
				printf("%ld\n", (i64) pop());
				break;
			}

			case OP::LOGSTR:
			{
				printf("%s\n", (const char *) pop());
				break;
			}

			case OP::JMP_IF_FALSE:
			{
				u16 offset = read_word() - 3;
				i64 cond = (i64) pop();
				pc += cond ? 0 : offset;
				break;
			}

			case OP::JMP:
			{
				u16 offset = read_word() - 3;
				pc += offset;
				break;
			}

			case OP::LOOP:
			{
				u16 offset = read_word() - 3;
				pc -= offset;
				break;
			}
		}
#ifdef DEBUG_FLAG
		stack_dump(stack, execution_log);
		fprintf(execution_log, "\n");
		fflush(execution_log);
#endif /* DEBUG_FLAG */
	}

	return 0;
}

void VM::write_byte(u8 byte)
{
	bytecode.push_back(byte);
}

void VM::write_word(u16 word)
{
	bytecode.push_back(static_cast<u8>(word));
	bytecode.push_back(static_cast<u8>(word >> 8));
}

void VM::write_op(OP op)
{
	bytecode.push_back(static_cast<u8>(op));
}

void VM::write_constant_op(OP op, u64 constant)
{
	usize index = constants.size();
	constants.push_back(constant);

	bytecode.push_back(static_cast<u8>(op));
	bytecode.push_back(static_cast<u8>(index));

	// TODO: long constant opcode.
}

usize VM::write_decl_var()
{
	usize index = vars_declared;
	vars_declared += 1;
	if(max_vars_declared < vars_declared)
	{
		max_vars_declared = vars_declared;
	}

	bytecode.push_back(static_cast<u8>(OP::VARSET));
	bytecode.push_back(static_cast<u8>(index));
	return index;
}

void VM::undecl_vars(usize count)
{
	vars_declared -= count;
}

/*********************************************************************/

OP VM::read_op()
{
	return static_cast<OP>(bytecode.at(pc++));
}

u8 VM::read_byte()
{
	return bytecode.at(pc++);
}

u16 VM::read_word()
{
	u16 word = (bytecode.at(pc) | (static_cast<u16>(bytecode.at(pc + 1)) << 8));
	pc += 2;
	return word;
}

/*********************************************************************/

void VM::push(u64 num)
{
	stack.push_back(num);
}

u64 VM::pop()
{
	u64 popped = stack.at(stack.size() - 1);
	stack.pop_back();
	return popped;
}

u64 VM::peek(usize offset)
{
	return stack.at(stack.size() - 1 - offset);
}

/*********************************************************************/
usize VM::bytecode_len() {
	return bytecode.size();
}

void VM::patch_jump(i64 offset) {
	i64 jump = bytecode.size() - offset;
	if(jump > UINT16_MAX) {
		exit(1);
	}
	bytecode[offset + 1] = static_cast<u8>(jump & 0xff);
    bytecode[offset + 2] = static_cast<u8>((jump >> 8) & 0xff);
}

/*********************************************************************/

#ifdef DEBUG_FLAG

const u8 *VM::get_raw_code(u64 *size)
{
	*size = bytecode.size();
	return &bytecode[0];
}

void set_execution_log(FILE *file)
{
	execution_log = file;
}

#endif /* DEBUG_FLAG */