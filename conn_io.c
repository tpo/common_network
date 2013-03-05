#include <stdio.h>
#include "conn_io.h" // make sure we implement the same API

char *read_line(int socket_fd, char *s, int max_size) {
	FILE *stream;

	stream = fdopen(socket_fd, "r");
	if( stream == NULL )
	  return NULL;

	return fgets(s, max_size, stream);
}

