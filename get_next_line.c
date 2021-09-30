#include "get_next_line.h"

size_t  ft_strlen(char *s)
{
    size_t len;

    len = 0;
    if (s)
        while (s[len])
            len++;
    return (len);
}

char    *append(char *s1, char *s2, int len)
{
    int     i;
    int     s1_len;
    char    *appended;

    i = 0;
    s1_len = ft_strlen(s1);
    appended = (char *)malloc(sizeof(char) * (s1_len + len + 1));
    if (!appended)
        return (NULL);
    while (i < s1_len)
    {
        appended[i] = s1[i];
        i++;
    }
    if (s1)
        free(s1);
    while (i - s1_len < len)
    {
        appended[i] = s2[i - s1_len];
        i++;
    }
    appended[i] = '\0';
    return (appended);
}

char    *get_next_line(int fd)
{
    static char	*tmp;
    char        *buf;
	int         rd;
	char		*tmp_free;
	int			i;

    
    if (tmp)
    {
        i = 0;
        while (tmp[i] != '\0' && tmp[i] != '\n')
            i++;
        if (tmp[i] == '\n')
        {
            tmp_free = append(NULL, tmp + i + 1, ft_strlen(tmp + i + 1));
            free(tmp);
            tmp = append(NULL, tmp_free, ft_strlen(tmp_free));
            free(tmp_free);
            return (tmp);
        }
        free(tmp);
    }
    if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
        return (NULL);
    while ((rd = read(fd, buf, BUFFER_SIZE)))
    {
        if (rd < 0)
            return (NULL);
        i = 0;
        buf[rd] = '\0';
        while (buf[i] != '\0' && buf[i] != '\n')
            i++;
        if (buf[i] == '\n')
        {
            tmp = append(NULL, buf + i + 1, ft_strlen(buf + i + 1));
            free(buf);
            return (tmp);
        }
    }
    free(buf);
    return (NULL);
}

#include <stdio.h>

int		main(int argc, char **argv)
{
	int		fd;
	// int		ret;
	char	*line;

	fd = 0;
	// ret = 1;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	while (fd)
    {
		printf("line = |%s|\n", (line = get_next_line(fd)));
        free(line);
    }
	return (0);
}