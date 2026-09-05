*This project has been created as part of the 42 curriculum by omito.*


//とりあえずBUFFER_SIZEでread
//取ってきたbufの中で改行があるか探す
//改行までを配列に格納。残りをstatic変数で保存
//またreadを繰り返して、残り＋改行

```c
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*sub_buf;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("open_error\n");
		return (1);
	}
	while ((sub_buf = get_next_line(fd)) != NULL)
	{
		printf("%s", sub_buf);
		free(sub_buf);
	}
	close(fd);
}

```
