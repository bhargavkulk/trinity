#include "common.hh"
#include "compiler.hh"
#include "vm.hh"
#include "symbols.hh"
#include <cstdio>
#include <cstdlib>

extern int yyparse();
extern FILE *yyin;

#ifdef DEBUG_FLAG
FILE *compilation_log;
#endif /* DEBUG_FLAG */


int compile(FILE *source)
{
	init_symbols();

	yyin = source;
	int yyretval = yyparse();
	if(yyretval != 0)
	{
		return yyretval;
	}

	#ifdef DEBUG_FLAG
	const u8 *code;
	usize size;

	code = vm.get_raw_code(&size);

	// Make compile time log.
	for(usize i = 0; i < size; )
	{
		fprintf(compilation_log, "%lu: ", i);
		disassemble(&code[i], compilation_log);
		i += 1 + OP_DATA[code[i]].operand_size;
	}
	fflush(compilation_log);
	#endif /* DEBUG_FLAG */

	return 0;
}


#ifdef DEBUG_FLAG

void set_compilation_log(FILE *file)
{
	compilation_log = file;
}

#endif /* DEBUG_FLAG */