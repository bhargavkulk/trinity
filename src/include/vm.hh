#ifndef VM_HPP
#define VM_HPP

#include <vector>
#include "common.hh"
#include "opcode.hh"

using std::vector;

typedef u64 (*NativeFun)(vector<u64> &);

class VM
{
	u64 pc;
	u64 start_pc, update_pc;
	bool found_start, found_update;
	bool has_halted;
	u64 halt_pc;

	vector<u8> bytecode;
	vector<u64> stack;
	vector<u64> constants; // Both integers and string pointers.
	vector<u64> globals;
	vector<NativeFun> natives;
	usize vars_declared, max_vars_declared;

	struct StackFrame
	{
		u64 retPC;
		vector<u64> locals;
	};

	vector<StackFrame> callstack;

	OP read_op();
	u8 read_byte();
	u16 read_word();
	u32 read_dword();

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
    void write_dword(u32 dword);
    void write_op(OP op);
    void write_constant_op(OP op, u64 constant);

    usize write_decl_var(bool is_global);
    void undecl_vars(usize count);
    
	void set_start(u64 pc);
	void set_update(u64 pc);

	void set_pc_to_update_pc();

	usize bytecode_len();
    void patch_jump(i64 offset);
	void patch_start_call(u64 call_pc);
	void patch_update_call(u64 call_pc);

	u32 add_native_fun(NativeFun fun);

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