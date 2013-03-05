#include <stdio.h>
#include "conn_io.h" // make sure we implement the same API

char *read_line(int fd, char *s, int max_size) {
	FILE *stream;

	stream = fdopen(fd, "r");
	if( stream == NULL )
	  return NULL;

	return fgets(s, max_size, stream);
}

