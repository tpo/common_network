#ifndef __READLINE_H_
#define __READLINE_H_
/* 
 * identisch mit fgets, ausser, dass es auf Sockets funktioniert.
 * Siehe man 2 fgets
 */
char *read_line(int fd, char *s, int max_size);

#endif
