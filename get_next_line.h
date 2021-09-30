# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define ERR -1
#define DONE 1
#define END 0
#define OPEN_MAX 1000
#define BUFFER_SIZE 2048

char     *get_next_line(int fd);

#endif