#include "preprocessor.hh"
#include "common.hh"
#include <cstdio>

int preprocess(char *source_buf, usize size)
{
	bool in_comment = false;
	usize lineno = 1;
	for(usize i = 0; i < size - 1; i++)
	{
		if(source_buf[i] == '\n')
		{
			lineno += 1;
		}

		if(source_buf[i] == '*' && source_buf[i + 1] == ')')
		{
			if(!in_comment)
			{
				fprintf(stderr, "ERROR: [Line %lu] Stray comment-ending symbol\n", lineno);
				return 1;
			}
			in_comment = false;
			source_buf[i] = ' ';
			source_buf[i + 1] = ' ';
		}
		else if(in_comment)
		{
			source_buf[i] = ' ';
		}
		else if(source_buf[i] == '(' && source_buf[i + 1] == '*')
		{
			in_comment = true;
			source_buf[i] = ' ';
			source_buf[i + 1] = ' ';
		}
	}

	if(in_comment)
	{
		fprintf(stderr, "ERROR: [Line %lu] Unclosed comment\n", lineno);
		return 1;
	}

	return 0;
}