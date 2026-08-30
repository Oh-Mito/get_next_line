#include <unisted>

int main(void)
{
	int	fd;

	fd = open("text.txt", 0_RDONLY);
	if (fd == -1)
		write(1, "error", 5);



}
