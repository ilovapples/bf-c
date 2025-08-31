#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "util.h"

#define DATA_SIZE 32768

int32_t main(int32_t argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <file_name>\n", argv[0]);
		return 1;
	}

	strbuf file_contents = read_file_to_string(argv[1]);
	char *instr_ptr = file_contents.ptr;
	
	uint8_t data[DATA_SIZE] = {0};
	uint8_t *data_ptr = data;

	//char (*bracket_pos)[16] = {NULL};

	size_t N_nested = 0;
	size_t save_nested = N_nested;

	while (instr_ptr < file_contents.ptr + file_contents.size - 1)
	{
		if (isspace(*instr_ptr))
		{
			instr_ptr++;
			continue;
		}
		switch (*instr_ptr) {
		case '#':
			while (*instr_ptr != '\n' && *instr_ptr != '\0')
				instr_ptr++;
			break;
		case '>':
			data_ptr++;
			break;
		case '<':
			data_ptr--;
			break;
		case '+':
			(*data_ptr)++;
			break;
		case '-':
			(*data_ptr)--;
			break;
		case '.':
			fputc(*data_ptr, stdout);
			break;
		case ',':
			*data_ptr = fgetc(stdin);
			break;
		case '[':
			if (!*data_ptr)
			{
				save_nested = N_nested++;
				while (save_nested != N_nested)
				{
					instr_ptr++;
					if (*instr_ptr == '[')
						N_nested++;
					else if (*instr_ptr == ']')
						N_nested--;
				}
			}
			break;
		case ']':
			if (*data_ptr)
			{
				save_nested = N_nested++;
				while (save_nested != N_nested)
				{
					instr_ptr--;
					if (*instr_ptr == ']')
						N_nested++;
					else if (*instr_ptr == '[')
						N_nested--;
				}
			}
		}

		instr_ptr++;
	}

	free(file_contents.ptr);

	return 0;
}
