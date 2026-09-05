*This project has been created as part of the 42 curriculum by omito.*

# get next line

## Description


//とりあえずBUFFER_SIZEでread
//取ってきたbufの中で改行があるか探す
//改行までを配列に格納。残りをstatic変数で保存
//またreadを繰り返して、残り＋改行

```c

//テキストファイルの中身を全て出力したい場合

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

```c 

//get_next_lineを一回呼んで、指定した区切り文字まで出力したい場合。(mandatoryの場合１つ目の改行まで出力)
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
	sub_buf = get_next_line(fd);
		printf("%s", sub_buf);
		free(sub_buf);
	close(fd);
}
```


``` c 
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;

	char	*sub_buf;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY); 
	if (fd1 == -1 || fd2 == -1)
	{
		printf("open_error\n");
		return (1);
	}
		sub_buf = get_next_line(fd1);
		printf("%s", sub_buf);
		free(sub_buf);
		sub_buf = get_next_line(fd2);
		printf("%s", sub_buf);
		free(sub_buf);
		sub_buf = get_next_line(fd1);
		printf("%s", sub_buf);
		free(sub_buf);
		sub_buf = get_next_line(fd2);
		printf("%s", sub_buf);
		free(sub_buf);
	close(fd1);
	close(fd2);
}
```
