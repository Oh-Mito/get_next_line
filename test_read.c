#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

# define BUF_SIZE 9

int main(void)
{
	int	fd;
	int	byte_num;
	char	buf[BUF_SIZE];

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1, "error", 5);
		return (1);
	}
	byte_num = read(fd, &buf, BUF_SIZE);
	if (byte_num == -1)
	{
		write (1, "read_error", 10);
		return (1);
	}
	printf("test.txtから%dバイト書き込みました！\n", byte_num);
	buf[byte_num] = '\0';
	printf("書き込んだ文字列%s\n", buf);

	close(fd);
	return(0);
}
