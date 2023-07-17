#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(void)
{
	FILE *fp = fopen("/tmp/a.txt", "a");
	if (!fp)
	{
		perror("fopen");
		return 1;
	}
	while (1)
	{
		printf("Writing hello\n");
		fprintf(fp, "Hello World!\n");
		fflush(fp);
		sleep(1);
	}
	fclose(fp);
	return 0;
}
