#ifndef VM_HPP
#define VM_HPP

#include <vector>
#include "common.hh"
#include "opcode.hh"

class VM
{
	u64 pc;
	std::vector<u8> bytecode;
	std::vector<u64> stack;
	std::vector<u64> constants; // Both integers and string pointers.
	std::vector<u64> variables;
	usize vars_declared, max_vars_declared;

	OP read_op();
	u8 read_byte();
	u16 read_word();

	void push(u64 num);
	u64 pop();
	u64 peek(usize offset);

	public:
	VM();

	// Returns 1 on error, 0 on success.
	int compile();

	// Returns 1 on error, 0 on success.
	int run();

	void write_byte(u8 byte);
	void write_word(u16 word);
	void write_op(OP op);
	void write_constant_op(OP op, u64 constant);

	usize write_decl_var();

	#ifdef DEBUG_FLAG
	const u8 *get_raw_code(u64 *size);
	#endif /* DEBUG_FLAG */
};

extern VM vm;

#ifdef DEBUG_FLAG
#include <cstdio>

void set_execution_log(FILE *file);
#endif /* DEBUG_FLAG */

#endif /* VM_HPP */