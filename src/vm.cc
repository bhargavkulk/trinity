#include "opcode.hh"
#include "common.hh"
#include "debug.hh"
#include "vm.hh"
#include "structures.hh"
#include <cstdio>
#include <cstdlib>

#ifdef DEBUG_FLAG
FILE *execution_log;
#endif /* DEBUG_FLAG */

VM vm;
VM::VM() : pc(0), start_pc(0), found_start(false), vars_declared(0), max_vars_declared(0) {}

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
	callstack = vector<StackFrame>(1);

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
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				// printf("OP1 is %ld ,OP2 is %ld, and the sum is - %ld ", op1, op2, op1 + op2);
				push((u64)(op1 + op2));
				break;
			}

			case OP::SUB:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)(op1 - op2));
				break;
			}
			case OP::MUL:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)(op1 * op2));
				break;
			}

			case OP::DIV:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				// error checking for division by zero error
				if (op2 == 0)
				{
					fprintf(stderr, "Division by zero, PLEASE CHANGE THIS NOW");
					break;
				}
				push((u64)(op1 / op2));
				break;
			}

			case OP::MOD:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)(op1 % op2));
				break;
			}

			case OP::EQUAL:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)((op1 == op2) ? (1) : (0)));
				break;
			}
			case OP::LESS:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)((op1 < op2) ? (1) : (0)));
				break;
			}
			case OP::LESS_EQUAL:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)((op1 <= op2) ? (1) : (0)));
				break;
			}
			case OP::GREATER:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)((op1 > op2) ? (1) : (0)));
				break;
			}
			case OP::GREATER_EQUAL:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)((op1 >= op2) ? (1) : (0)));
				break;
			}

			case OP::NEG:
			{
				i64 op2 = (i64)pop();
				push((u64)(-1 * op2));
				break;
			}

			case OP::AND:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)((op1 * op2 != 0) ? (1) : (0)));
				break;
			}
			case OP::OR:
			{
				i64 op2 = (i64)pop();
				i64 op1 = (i64)pop();
				push((u64)((op1 + op2 != 0) ? (1) : (0)));
				break;
			}

			case OP::NOT:
			{
				i64 op1 = (i64)pop();
				push((u64)((op1 == 0) ? (1) : (0)));
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

			// PLEASE ADD ARR DELETE FUNCTION
			case OP::ARR:
			{
				u8 dim_count = read_byte();
				Array *array = new Array;
				i64 flat_size = 1;
				array->dims.insert(array->dims.end(), dim_count, 0);

				for(auto rit = array->dims.rbegin(), rend = array->dims.rend(); rit != rend; rit++)
				{
					*rit = static_cast<i64>(pop());
					if(*rit <= 0)
					{
						fprintf(stderr, "Error: Dimension of array (here %ld) must be a positive integer\n", *rit);
						return 1;
					}
					flat_size *= *rit;
				}

				array->arr.insert(array->arr.end(), flat_size, 0);

				push(reinterpret_cast<u64>(array));
				break;
			}

			// Order of stack from top: array ptr, value, indices.
			case OP::ARRSET:
			{
				Array *array = reinterpret_cast<Array *>(pop());
				u64 value = pop();
				vector<i64> indices(array->dims.size());
				i64 flat_index = 0, multiplicand = 1;
				for(int i = indices.size() - 1; i >= 0; i--)
				{
					indices[i] = pop();
					if(indices[i] < 0)
					{
						fprintf(stderr, "Error: Index of array (%ld) must be a non-negative integer\n", indices[i]);
						return 1;
					}
					else if(indices[i] >= array->dims[i])
					{
						fprintf(stderr, "Error: Index of array (here %ld) must be less than the corresponding dimension (%ld)\n", indices[i], array->dims[i]);
						return 1;
					}

					flat_index += indices[i] * multiplicand;
					multiplicand *= array->dims[i];
				}
				array->arr[flat_index] = value;
				break;
			}

			case OP::ARRGET:
			{
				Array *array = reinterpret_cast<Array *>(pop());
				vector<i64> indices(array->dims.size());
				i64 flat_index = 0, multiplicand = 1;
				for(int i = indices.size() - 1; i >= 0; i--)
				{
					indices[i] = pop();
					if(indices[i] < 0)
					{
						fprintf(stderr, "Error: Index of array (%ld) must be a non-negative integer\n", indices[i]);
						return 1;
					}
					else if(indices[i] >= array->dims[i])
					{
						fprintf(stderr, "Error: Index of array (here %ld) must be less than the corresponding dimension (%ld)\n", indices[i], array->dims[i]);
						return 1;
					}

					flat_index += indices[i] * multiplicand;
					multiplicand *= array->dims[i];
				}
				push(array->arr[flat_index]);
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
				u16 offset = read_word() + 3;
				pc -= offset;
				break;
			}

			case OP::POP:
			{
				pop();
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

void VM::patch_start_jump(u64 jmp_pc)
{
	if(!found_start) return;
	u16 value = static_cast<u16>(start_pc - jmp_pc);
	bytecode.at(jmp_pc + 1) = static_cast<u8>(value);
	bytecode.at(jmp_pc + 2) = static_cast<u8>(value >> 8);
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