#include <stdio.h>
#include <stdlib.h>

#include "util.h"

void defered_fclose(FILE **fpp)
{
	fclose(*fpp);
}

strbuf read_file_to_string(const char *file_name)
{
	FILE *fp = fopen(file_name, "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "failed to open file '%s'.\n", file_name);
		exit(2);
	}

	size_t buf_size = 2048;
	strbuf ret_buf = {0};
	ret_buf.ptr = malloc(buf_size);
	if (ret_buf.ptr == NULL)
	{
		fclose(fp);
		fprintf(stderr, "failed to allocate the initial buffer size\n");
		exit(3);
	}

	size_t cur_chunk_read;
	
	while ((cur_chunk_read = fread(ret_buf.ptr + ret_buf.size, 1, buf_size - ret_buf.size- 1, fp)) > 0)
	{
		ret_buf.size += cur_chunk_read;
		if (ret_buf.size >= buf_size - 1)
		{
			buf_size *= 2;
			char *temp_buf = realloc(ret_buf.ptr, buf_size);
			if (temp_buf == NULL)
			{
				free(ret_buf.ptr);
				fclose(fp);
				fprintf(stderr, "failed to reallocate buffer with size %zu\n", buf_size);
				exit(4);
			}
			ret_buf.ptr = temp_buf;
		}
	}

	ret_buf.ptr[ret_buf.size++] = '\0';
	fclose(fp);

	return ret_buf;
}

