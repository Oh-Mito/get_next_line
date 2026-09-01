#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

# define BUF_SIZE 40

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
	setbuf(stdout, NULL);
	int fd;
	char buf[BUF_SIZE + 1];
	int	byte_num;

	
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1, "error", 5);
		return (1);
	}
	while(1)
	{
		byte_num = read(fd, &buf, BUF_SIZE);
		if (byte_num == 0)
			break ;
		if (byte_num == -1)
		{
			write (1, "read_error", 10);
			close (fd);
			return (1);
		}
		write(1, buf, byte_num);
		printf("test.txtから%dバイト読み込みました！\n", byte_num);
//		write(1, "読んだ文字数は", 7);
//		write(1, &byte_num, byte_num);
		buf[byte_num] = '\0';

		//		write(1, "\n", 1);
//		write(1, "読み込んだ文字列は", 9);
//		write(1, buf, BUF_SIZE);
		printf("読み込んだ文字列%s\n", buf);
	}
	close(fd);
	return (0);
}

//read(fd, buf, n) は、常に buf の先頭から最大 n バイト書き込む。
//
//「どこまで読んだか」を覚えているのはカーネル側の fd であって、あなたのバッファではありません。バッファは毎回まっさらな着地点として使い回されます。
//
//1回目: read → buf[0] に 'H'    (ファイル内の位置: 0 → 1)
//2回目: read → buf[0] に 'e'    (ファイル内の位置: 1 → 2)
//3回目: read → buf[0] に 'l'    (ファイル内の位置: 2 → 3)
//        ↑ 常に buf[0]。buf[1], buf[2] には何も入らない
//
