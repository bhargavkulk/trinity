#include "opcode.hh"
#include "common.hh"
#include "debug.hh"
#include "vm.hh"
#include <cstdio>

#ifdef DEBUG_FLAG
FILE *execution_log;
#endif /* DEBUG_FLAG */

VM vm;
VM::VM() : pc(0), found_start(false), start_pc(0), vars_declared(0), max_vars_declared(0) {}

int VM::run()
{
	// TEMP
	if(!found_start)
	{
		printf("ERROR: start() not found\n");
		return 0;
	}

	bool has_halted = false;
	u64 halt_pc = 0;

	// Remove when stub added.
	callstack = std::vector<StackFrame>(1);

	pc = start_pc;

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

			case OP::CONST_0:
			{
				push(0);
				break;
			}

			case OP::GLOB_VARSET:
			{
				u64 val = pop();
				u8 id = read_byte();
				if(id >= globals.size())
					globals.insert(globals.end(), id - globals.size() + 1, 0);

				globals.at(id) = val;
				break;
			}

			case OP::GLOB_VARGET:
			{
				u8 id = read_byte();
				u64 val = globals.at(id);
				push(val);
				break;
			}

			case OP::VARSET:
			{
				u64 val = pop();
				u8 id = read_byte();
				auto &locals = callstack.back().locals;

				if(id >= locals.size())
					locals.insert(locals.end(), id - locals.size() + 1, 0);

				locals.at(id) = val;
				break;
			}

			case OP::VARGET:
			{
				u8 id = read_byte();
				u64 val = callstack.back().locals.at(id);
				push(val);
				break;
			}

			case OP::CALL:
			{
				u32 addr = read_dword();
				StackFrame frame;
				frame.retPC = pc;
				callstack.push_back(frame);
				pc = addr;
				break;
			}

			case OP::RET:
			{
				// Remove when stub added.
				if(callstack.size() == 1) return 0;

				pc = callstack.back().retPC;
				callstack.pop_back();
				break;
			}

			case OP::LOGINT:
			{
				printf("%ld\n", (i64) pop());
				break;
			}

			case OP::LOGSTR:
			{
				u64 str = pop();
				if(str == 0)
				{
					fprintf(stderr, "NIL Reference\n");
					return 1;
				}
				printf("%s\n", (const char *) str);
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

void VM::write_dword(u32 dword)
{
	bytecode.push_back(static_cast<u8>(dword));
	bytecode.push_back(static_cast<u8>(dword >> 8));
	bytecode.push_back(static_cast<u8>(dword >> 16));
	bytecode.push_back(static_cast<u8>(dword >> 24));
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

usize VM::write_decl_var(bool is_global)
{
	usize index = vars_declared;
	vars_declared += 1;
	if(max_vars_declared < vars_declared)
	{
		max_vars_declared = vars_declared;
	}

	bytecode.push_back(static_cast<u8>(is_global ? OP::GLOB_VARSET : OP::VARSET));
	bytecode.push_back(static_cast<u8>(index));
	return index;
}

void VM::undecl_vars(usize count)
{
	vars_declared -= count;
}

void VM::set_start(u64 pc)
{
	found_start = true;
	start_pc = pc;
}

u64 VM::bytecode_len()
{
	return bytecode.size();
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

u32 VM::read_dword()
{
	u32 dword = (bytecode.at(pc) | (static_cast<u32>(bytecode.at(pc + 1)) << 8) | 
		(static_cast<u32>(bytecode.at(pc + 2)) << 16) | (static_cast<u32>(bytecode.at(pc + 3)) << 24));
	pc += 4;
	return dword;
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