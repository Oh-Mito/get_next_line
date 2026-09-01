#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

# define BUF_SIZE 1

//int main(void)
//{
//	int	fd;
//	int	byte_num;
//	char	buf[BUF_SIZE + 1];
//
//	fd = open("test.txt", O_RDONLY);
//	if (fd == -1)
//	{
//		write(1, "error", 5);
//		return (1);
//	}
//	byte_num = read(fd, &buf, BUF_SIZE);
//	if (byte_num == -1)
//	{
//		write (1, "read_error", 10);
//		return (1);
//	}
//	printf("test.txtから%dバイト読み込みました！\n", byte_num);
//	buf[byte_num] = '\0';
//	printf("読み込んだ文字列%s\n", buf);
//
//	close(fd);
//	return(0);
//}
//
int main(void)
{
	int fd;
	int byte_num;
	char buf[BUF_SIZE + 1];

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1, "error", 5);
		return (1);
	}
	while
	{
		byte_num += read(fd, &buf, 1);
		if (byte_num == 0)
			break ;
		write(1, &buf[byte_num], 1);
	}



}
