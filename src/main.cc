#include <cstdio>
#include <cstdlib>
#include "debug.hh"
#include "preprocessor.hh"
#include "compiler.hh"
#include "vm.hh"


FILE *runtime_log = NULL;

void cleanup()
{
	#ifdef DEBUG_FLAG
	if(runtime_log)
	{
		fclose(runtime_log);
	}
	#endif /* DEBUG_FLAG */
}


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "FATAL ERROR: Expecting exactly 1 argument, the name of the Trinity source file\n");
		return EXIT_FAILURE;
	}

	atexit(cleanup);

	/************************************************
	 * 				READING SOURCE FILE     		*
	 ************************************************/

	FILE *source = fopen(argv[1], "r"); // check error.
	if(!source)
	{
		perror("Could not open source file");
		return EXIT_FAILURE;
	}

	fseek(source, 0, SEEK_END);
	long len = ftell(source);
	fseek(source, 0, SEEK_SET);
	char *source_buf = (char*) malloc(sizeof(char) * (len + 1));
	if(!source_buf)
	{
		perror("Source file buffer allocation failed\n");
		return EXIT_FAILURE;
	}
	if(fread(source_buf, sizeof(char), len, source) < sizeof(char) * len)
	{
		perror("Source file read failed\n");
		return EXIT_FAILURE;
	}
	fclose(source);

	source_buf[len] = 0;


	/************************************************
	 * 				  PREPROCESSING     			*
	 ************************************************/

	if(preprocess(source_buf, len) != 0)
	{
		free(source_buf);
		return EXIT_FAILURE;
	}

	FILE *preprocessed_source = fmemopen(source_buf, len, "r");
	if(!preprocessed_source)
	{
		perror("");
		free(source_buf);
		return EXIT_FAILURE;
	}


	vm = VM();

	/************************************************
	 * 				  	COMPILING     				*
	 ************************************************/

	#ifdef DEBUG_FLAG
	const char *compilation_log = "log/compile.log";
	FILE *compile_log = fopen(compilation_log, "w");
	if(!compile_log)
	{
		perror("Could not create compilation log");
	}
	set_compilation_log(compile_log);
	#endif /* DEBUG_FLAG */

	int retval = compile(preprocessed_source);
	fclose(preprocessed_source);

	#ifdef DEBUG_FLAG
	if(compile_log)
	{
		fclose(compile_log);
	}
	#endif /* DEBUG_FLAG */

	if(retval != 0)
	{
		return EXIT_FAILURE;
	}

	/************************************************
	 * 				  	EXECUTING     				*
	 ************************************************/

	#ifdef DEBUG_FLAG
	const char *execution_log = "log/runtime.log";
	runtime_log = fopen(execution_log, "w");
	if(!compile_log)
	{
		perror("Could not create execution log");
	}
	set_execution_log(runtime_log);
	#endif /* DEBUG_FLAG */

	vm.run();
	
	return 0;
}