#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdio.h>

typedef struct strbuf {
	char *ptr;
	size_t size;
} strbuf;

void defered_fclose(FILE **fp);
strbuf read_file_to_string(const char *file_name);

#endif /* UTIL_H */
