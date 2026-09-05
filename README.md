*This project has been created as part of the 42 curriculum by omito.*

# get next line

## Description

get_next_lineは、**引数として受け取ったファイルディスクリプタを読み、改行までの文字列を返す関数**を実装するプロジェクトです。

このプロジェクトを通して、read関数やstatic変数の概念を理解することができます。

---

## Instructions
//とりあえずBUFFER_SIZEでread
//取ってきたbufの中で改行があるか探す
//改行までを配列に格納。残りをstatic変数で保存
//またreadを繰り返して、残り＋改行

### コンパイル方法

ソースファイル内にmain関数を入れます
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

//ボーナス用(２つのファイルを交互に呼び出す)

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
```sh

# mandatoryの実行例
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
./a.out test.txt

# bonusの実行例
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
./a.out test.txt test2.txt
```

---
## 選択したアルゴリズムについて
### mandatory
1. `BUFFER_SIZE(データを一時的に保存するメモリ領域（バッファ）の大きさ）でread`を改行が見つかるまで繰り返します。<br>
読んだ文字列は配列(stash)に貯めます。
2. 改行までを配列(sub_buf)に格納して返り値として返し、残りをstatic変数の配列(stash)に保存します。
3. これをファイルの中身を読み切るまで繰り返し呼ぶことで、ファイル内の文字列を標準出力することができます。

### bonus
ボーナスの要件はstatic変数を１つだけ用いて、複数のファイルディスクリプタを同時に管理できるようにすることです。
主な構造はmandatoryと同様ですが、static変数の配列をポインタ配列にすることで、複数のファイルディスクリプタのstashを管理する構造にしました。

---

## Resources

### 参考資料

- [42 Norminette](https://github.com/42School/norminette)
- [42 GetNextLine subject](https://cdn.intra.42.fr/pdf/pdf/218327/en.subject.pdf)
- [Nani翻訳](https://nani.now/ja)
- [長い文字列作成ツール](https://tools.m-bsys.com/ex/long_text_maker.php)
- [C言語例文集ｰ>read()](https://cgengo.sakura.ne.jp/read.html)

### AIの使用について

使用ツール　：　Claude（Anthropic）

使用箇所　：　アルゴリズムの選定、read関数の仕様理解に使用しました。

使用していない箇所　：　ソースコードは自分で実装、理解しました。
